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
	//�α�� ���Ͽ� ���� ����������
	static FILE* logfile;
	static int tcp, udp, icmp, others, igmp, dns, total, i, j;//������ �������ݿ� ���� ī���� �ʱ�ȭ
	static struct sockaddr_in source, dest;//���ô��
	static char hex[2];

	//Its free!
	static IPV4_HDR* iphdr;
	static TCP_HDR* tcpheader;
	static UDP_HDR* udpheader;
	static ICMP_HDR* icmpheader;
	static CoreUnit* instance;
	static SOCKET sniffer;//RAW SOCKET�� ����
	
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
		char* Buffer = (char*)malloc(sizeof(char)* 65536); //��Ŷ�� ������ ����
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
			//sniffer�������κ��� ��Ŷ�� �о�´�.
			//�� ��Ʈ��ũ �������̽��� ���� ������ ��� IPv4, IPv6��Ŷ�� ���⼭ �д´�.
			recvState = recvfrom(sniffer, Buffer, 65536, 0, 0, 0);

			if (recvState > 0)
			{//�о��ٸ�
				end = clock();
				*duration = (double)(end - start) / CLOCKS_PER_SEC;
				ProcessPacket(Buffer, recvState, duration);//�α� �� ī���� ó��
			}
			else
			{//�߸� ������� �����޼��� ���
				
				break;
			}
		} while (recvState > 0);//�����߻��� ��� �ش� do-while ������ ������Ű�� ���ؼ� break;
	}

	//���ۿ� ����� ��Ŷ�� � ���������� �������� ���� ������ ó���Լ��� �б��Ѵ�.
	//����, ��Ŷ�� �´� �������� ī���͸� ������Ų��
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










