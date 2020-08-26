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
			CoreUnit::dns = 0,
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
clock_t CoreUnit::start;
clock_t CoreUnit::end;

std::vector<char*> CoreUnit::packetVector;
std::vector<double*> CoreUnit::timeVector;

void CoreUnit::setThreadHandle(HANDLE handle) {
	CoreUnit::captureThread = handle;
}

int CoreUnit::initializer()
{
	
	WSADATA wsa;
	//���� �ʱ�ȭ
	//Initialise Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return 1;
	}

	return 0;
}

int CoreUnit::startCapture(struct hostent* local, int decision)
{
	tcp = 0;
	udp = 0;
	icmp = 0;
	others = 0;
	igmp = 0;
	dns = 0;
	total = 0;
	i = 0;
	j = 0;
	struct in_addr addr;
	int in = decision;

	char hostname[100];

	//Create a RAW Socket
	sniffer = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
	//2��° �з����ͷ� SOCK_RAW�� �ۼ��ؼ� RAW SOCKET����
	//�̶�, ���α׷��� ������ ����(Administrater)���� �����ؾ� RAW SOCKET�� ������ �� �ִ�
	if (sniffer == INVALID_SOCKET)
	{//�ȱ׷��� ������
		return 1;
	}



	//������ ip�ּ� �ʱ�ȭ�ϰ�, �Է��� ������ �ٲ�
	memset(&dest, 0, sizeof(dest));
	memcpy(&dest.sin_addr.s_addr, local->h_addr_list[in], sizeof(dest.sin_addr.s_addr));
	dest.sin_family = AF_INET;
	dest.sin_port = 0;
	//���ε� ����
	if (bind(sniffer, (struct sockaddr*) & dest, sizeof(dest)) == SOCKET_ERROR)
	{
		memcpy(&addr, local->h_addr_list[in], sizeof(struct in_addr));
		return 1;
	}

	//Enable this socket with the power to sniff : SIO_RCVALL is the key Receive ALL ;)

	j = 1;
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
		return 1;
	}

	//Begin
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

CSubFormViewDlg* CoreUnit::mainFrame;

void CoreUnit::setMainFrame(CSubFormViewDlg* mainFrame) {
	CoreUnit::mainFrame = mainFrame;
}