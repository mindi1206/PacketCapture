#pragma once


#include <stdio.h>
#include <winsock2.h>
#include <vector>
#include <stdlib.h>
#include <malloc.h>
#include "resource.h"
#include "SubFormViewDlg.h"


#pragma comment(lib,"ws2_32.lib") //For winsock
#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1) //this removes the need of mstcpip.h

#include "HeaderType.h"


class CoreUnit
{
	static clock_t start;
	static clock_t end;
	//로깅용 파일에 대한 파일포인터
	static FILE* logfile;
	static int tcp, udp, icmp, others, igmp, dns, total, i, j;//각각의 프로토콜에 대한 카운터 초기화
	static struct sockaddr_in source, dest;//감시대상
	static char hex[2];

	//Its free!
	static IPV4_HDR* iphdr;
	static TCP_HDR* tcpheader;
	static UDP_HDR* udpheader;
	static ICMP_HDR* icmpheader;
	static CoreUnit* instance;
	static SOCKET sniffer;//RAW SOCKET용 변수
	
public:
	static CSubFormViewDlg* mainFrame;
	static void setMainFrame(CSubFormViewDlg* mainFrame);
	static void clearPackerVector();
	static void setThreadHandle(HANDLE handle);
	static HANDLE captureThread;
	static std::vector<char*> packetVector;
	static std::vector<double*> timeVector;

	static HANDLE newItemEventHandle;

	static CoreUnit* getInstance();
	static int initializer();
	int startCapture(struct hostent* local, int decision);
	static void CoreUnit::stopCapture();
	static void terminateProgram();


	void StartSniffing(SOCKET sniffer)
	{
		char* Buffer = (char*)malloc(sizeof(char)* 65536); //패킷을 저장할 버퍼
		double* duration;
		int flag = 0;
		
		int recvState;

		if (Buffer == NULL)
		{
			
			return;
		}

		do
		{

			Buffer = (char*)malloc(sizeof(char) * 65536);
			duration = (double*)malloc(sizeof(double) * 65536);
			if (flag == 0) {
				start = clock();
				flag++;
			}
			//sniffer소켓으로부터 패킷을 읽어온다.
			//즉 네트워크 인터페이스로 부터 들어오는 모든 IPv4, IPv6패킷을 여기서 읽는다.
			recvState = recvfrom(sniffer, Buffer, 65536, 0, 0, 0);

			if (recvState > 0)
			{//읽었다면
				end = clock();
				*duration = (double)(end - start) / CLOCKS_PER_SEC;
				ProcessPacket(Buffer, recvState, duration);//로깅 및 카운팅 처리
			}
			else
			{//잘못 읽은경우 에러메세지 출력
				
				break;
			}
		} while (recvState > 0);//에러발생한 경우 해당 do-while 조건을 만족시키지 못해서 break;
	}

	//버퍼에 저장된 패킷이 어떤 프로토콜을 쓰는지에 따라 각각의 처리함수로 분기한다.
	//직후, 패킷에 맞는 프로토콜 카운터를 증가시킨다
	void ProcessPacket(char* Buffer, int Size, double* duration)
	{
		unsigned short iphdrlen;
		iphdr = (IPV4_HDR*)Buffer;
		

		++total;

		switch (iphdr->ip_protocol) //Check the Protocol and do accordingly...
		{
		case 1: //ICMP Protocol
			++icmp;
			CoreUnit::packetVector.push_back(Buffer);
			CoreUnit::timeVector.push_back(duration);
			break;

		case 2: //IGMP Protocol
			++igmp;
			break;

		case 6: //TCP Protocol
			++tcp;
			CoreUnit::packetVector.push_back(Buffer);
			CoreUnit::timeVector.push_back(duration);
			//== DNS Checker
			iphdrlen = iphdr->ip_header_len * 4;
			tcpheader = (TCP_HDR*)(Buffer + iphdrlen);
			if ( ntohs( tcpheader->source_port ) == 53 || ntohs(tcpheader->dest_port) == 53 ) {
				++dns;
			}
			//==
			break;

		case 17: //UDP Protocol
			++udp;
			CoreUnit::packetVector.push_back(Buffer);
			CoreUnit::timeVector.push_back(duration);
			//== DNS Checker
			iphdrlen = iphdr->ip_header_len * 4;
			udpheader = (UDP_HDR*)(Buffer + iphdrlen);
			if (ntohs(udpheader->source_port) == 53 || ntohs(udpheader->dest_port) == 53) {
				++dns;
			}
			//==
			break;

		default: //Some Other Protocol like ARP etc.
			++others;
			break;
		}
		
		CString str;
		str.Format(_T("%d"), tcp);
		mainFrame->TcpCounter.SetWindowTextW(str);

		str.Format(_T("%d"), udp);
		mainFrame->UdpCounter.SetWindowTextW(str);

		str.Format(_T("%d"), dns);
		mainFrame->DnsCounter.SetWindowTextW(str);

		str.Format(_T("%d"), icmp);
		mainFrame->IcmpCounter.SetWindowTextW(str);
	}


};










