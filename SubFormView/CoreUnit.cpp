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
			CoreUnit::total = 0, CoreUnit::i, CoreUnit::j;//각각의 프로토콜에 대한 카운터 초기화
struct sockaddr_in CoreUnit::source, CoreUnit::dest;//감시대상
char CoreUnit::hex[2];

//Its free!
IPV4_HDR* CoreUnit::iphdr;
TCP_HDR* CoreUnit::tcpheader;
UDP_HDR* CoreUnit::udpheader;
ICMP_HDR* CoreUnit::icmpheader;
SOCKET CoreUnit::sniffer;//RAW SOCKET용 변수
HANDLE CoreUnit::captureThread;

HANDLE CoreUnit::newItemEventHandle;

std::vector<char*> CoreUnit::packetVector;

void CoreUnit::setThreadHandle(HANDLE handle) {
	CoreUnit::captureThread = handle;
}

int CoreUnit::initializer()
{
	
	WSADATA wsa;
	//윈속 초기화
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
	//2번째 패러미터로 SOCK_RAW를 작성해서 RAW SOCKET생성
	//이때, 프로그램을 관리자 권한(Administrater)으로 실행해야 RAW SOCKET을 생성할 수 있다
	if (sniffer == INVALID_SOCKET)
	{//안그러면 에러남
		printf("Failed to create raw socket.\n");
		return 1;
	}
	printf("Created.");

	std::cout << "decision : " << decision << std::endl;


	//감시할 ip주소 초기화하고, 입력한 정보로 바꿈
	memset(&dest, 0, sizeof(dest));
	memcpy(&dest.sin_addr.s_addr, local->h_addr_list[in], sizeof(dest.sin_addr.s_addr));
	dest.sin_family = AF_INET;
	dest.sin_port = 0;
	std::cout << "Bind Start" << std::endl;
	//바인드 수행
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
	//해당 코드를 통해, 네트워크 인터페이스를 통과하는 모든 IPv4 또는 IPv6패킷을 수신할 수 있게 해준다.
	//즉, sniffer 소켓에 대해서 SIO_RCVALL속성을 이용해서 위의 기능을 수행하도록 설정한다.
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
	/*계속해서 네트워크 인터페이스를 통과하는
	모든 IPv4, IPv6패킷을 수신하고 로깅하고, 터미널에 카운팅하는 함수 시작*/
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