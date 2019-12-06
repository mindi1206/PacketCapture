#include "stdafx.h"
#include "CoreUnit.h"
#include <iostream>

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

HANDLE CoreUnit::newItemEventHandle;

std::vector<char*> CoreUnit::packetVector;

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

int CoreUnit::startCapture(struct hostent* local, int decision)
{
	tcp = 0;
	udp = 0;
	icmp = 0;
	others = 0;
	igmp = 0;
	total = 0;
	i = 0;
	j = 0;
	struct in_addr addr;
	int in = decision;

	char hostname[100];

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

	std::cout << "decision : " << decision << std::endl;


	//������ ip�ּ� �ʱ�ȭ�ϰ�, �Է��� ������ �ٲ�
	memset(&dest, 0, sizeof(dest));
	memcpy(&dest.sin_addr.s_addr, local->h_addr_list[in], sizeof(dest.sin_addr.s_addr));
	dest.sin_family = AF_INET;
	dest.sin_port = 0;
	std::cout << "Bind Start" << std::endl;
	//���ε� ����
	printf("\nBinding socket to local system and port 0 ...");
	if (bind(sniffer, (struct sockaddr*) & dest, sizeof(dest)) == SOCKET_ERROR)
	{
		memcpy(&addr, local->h_addr_list[in], sizeof(struct in_addr));
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
void CoreUnit::clearPackerVector() {
	std::vector<char*>::iterator iter;
	std::vector<char*> v = CoreUnit::packetVector;
	int i = 1;

	for (iter = v.begin(); iter != v.end(); ++iter, i++) {
		char* packet = *iter;
		free(packet);
	}//for loop end here

	CoreUnit::packetVector.clear();
}