#include "stdafx.h"
#include "CoreUnit.h"

CoreUnit* CoreUnit::instance;
CoreUnit* CoreUnit::getInstance()
{
	if (CoreUnit::instance == NULL)
	{
		CoreUnit::instance = new CoreUnit();
	}
	return CoreUnit::instance;
}

FILE* CoreUnit::logfile;
int CoreUnit::tcp = 0,
			CoreUnit::udp = 0, CoreUnit::icmp = 0, CoreUnit::others = 0, CoreUnit::igmp = 0,
			CoreUnit::total = 0, CoreUnit::i, CoreUnit::j;//������ �������ݿ� ���� ī���� �ʱ�ȭ
struct sockaddr_in CoreUnit::source, CoreUnit::dest;//���ô��
char CoreUnit::hex[2];

//Its free!
IPV4_HDR* CoreUnit::iphdr;
TCP_HDR* CoreUnit::tcpheader;
UDP_HDR* CoreUnit::udpheader;
ICMP_HDR* CoreUnit::icmpheader;
SOCKET CoreUnit::sniffer;//RAW SOCKET�� ����
HANDLE CoreUnit::captureThread;

void CoreUnit::setThreadHandle(HANDLE handle) {
	CoreUnit::captureThread = handle;
}

int CoreUnit::initializer()
{
	
	WSADATA wsa;
	//���� �ʱ�ȭ
	//Initialise Winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("WSAStartup() failed.\n");
		return 1;
	}
	printf("Winsock Initialised");

	return 0;
}

int CoreUnit::startCapture()
{
	struct in_addr addr;
	int in;

	char hostname[100];
	struct hostent* local;

	//�α�� ���� ����
	fopen_s(&logfile, "log.txt", "w");
	if (logfile == NULL)
	{
		printf("Unable to create file.");
	}

	//Create a RAW Socket
	printf("\nCreating RAW Socket...");
	sniffer = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
	//2��° �з����ͷ� SOCK_RAW�� �ۼ��ؼ� RAW SOCKET����
	//�̶�, ���α׷��� ������ ����(Administrater)���� �����ؾ� RAW SOCKET�� ������ �� �ִ�
	if (sniffer == INVALID_SOCKET)
	{//�ȱ׷��� ������
		printf("Failed to create raw socket.\n");
		return 1;
	}
	printf("Created.");

	//Retrive the local hostname
	if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR)
	{
		printf("Error : %d", WSAGetLastError());
		return 1;
	}
	printf("\nHost name : %s \n", hostname);//���� ��ǻ���� �̸�

	//Retrive the available IPs of the local host
	local = gethostbyname(hostname);
	printf("\nAvailable Network Interfaces : \n");
	if (local == NULL)
	{
		printf("Error : %d.\n", WSAGetLastError());
		return 1;
	}

	for (i = 0; local->h_addr_list[i] != 0; ++i)
	{//���� ������ �������̽� ����� ���
		memcpy(&addr, local->h_addr_list[i], sizeof(struct in_addr));
		printf("Interface Number : %d Address : %s\n", i, inet_ntoa(addr));
	}

	printf("Enter the interface number you would like to sniff : ");
	scanf_s("%d", &in);//������ �������̽��� ����ڷκ��� �Է¹���

	//������ ip�ּ� �ʱ�ȭ�ϰ�, �Է��� ������ �ٲ�
	memset(&dest, 0, sizeof(dest));
	memcpy(&dest.sin_addr.s_addr, local->h_addr_list[in], sizeof(dest.sin_addr.s_addr));
	dest.sin_family = AF_INET;
	dest.sin_port = 0;

	//���ε� ����
	printf("\nBinding socket to local system and port 0 ...");
	if (bind(sniffer, (struct sockaddr*) & dest, sizeof(dest)) == SOCKET_ERROR)
	{
		printf("bind(%s) failed.\n", inet_ntoa(addr));
		return 1;
	}
	printf("Binding successful");

	//Enable this socket with the power to sniff : SIO_RCVALL is the key Receive ALL ;)

	j = 1;
	printf("\nSetting socket to sniff...");
	//�ش� �ڵ带 ����, ��Ʈ��ũ �������̽��� ����ϴ� ��� IPv4 �Ǵ� IPv6��Ŷ�� ������ �� �ְ� ���ش�.
	//��, sniffer ���Ͽ� ���ؼ� SIO_RCVALL�Ӽ��� �̿��ؼ� ���� ����� �����ϵ��� �����Ѵ�.
	if (WSAIoctl(sniffer,
		SIO_RCVALL,
		&j,
		sizeof(j),
		0,
		0,
		(LPDWORD)&in,
		0,
		0) == SOCKET_ERROR)
	{
		printf("WSAIoctl() failed.\n");
		return 1;
	}
	printf("Socket set.");

	//Begin
	printf("\nStarted Sniffing\n");
	printf("Packet Capture Statistics...\n");
	/*����ؼ� ��Ʈ��ũ �������̽��� ����ϴ�
	��� IPv4, IPv6��Ŷ�� �����ϰ� �α��ϰ�, �͹̳ο� ī�����ϴ� �Լ� ����*/
	StartSniffing(sniffer);
	return 0;
}
void CoreUnit::stopCapture()
{
	closesocket(sniffer);
}
void CoreUnit::terminateProgram()
{
	WSACleanup();
}