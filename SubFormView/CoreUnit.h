#pragma once


#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") //For winsock
#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1) //this removes the need of mstcpip.h

#include "HeaderType.h"


class CoreUnit
{

	//로깅용 파일에 대한 파일포인터
	static FILE* logfile;
	static int tcp, udp, icmp, others, igmp, total, i, j;//각각의 프로토콜에 대한 카운터 초기화
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
	static CoreUnit* getInstance();
		
	static int initializer();
	void startCapture();
	static void CoreUnit::stopCapture();
	static void terminateProgram();

	void StartSniffing(SOCKET sniffer)
	{
		char* Buffer = (char*)malloc(65536); //패킷을 저장할 버퍼
		int recvState;

		if (Buffer == NULL)
		{
			printf("malloc() failed.\n");
			return;
		}

		do
		{
			//sniffer소켓으로부터 패킷을 읽어온다.
			//즉 네트워크 인터페이스로 부터 들어오는 모든 IPv4, IPv6패킷을 여기서 읽는다.
			recvState = recvfrom(sniffer, Buffer, 65536, 0, 0, 0);

			if (recvState > 0)
			{//읽었다면
				ProcessPacket(Buffer, recvState);//로깅 및 카운팅 처리
			}
			else
			{//잘못 읽은경우 에러메세지 출력
				printf("recvfrom() failed.\n");
			}
		} while (recvState > 0);//에러발생한 경우 해당 do-while 조건을 만족시키지 못해서 break;

		free(Buffer);//패킷 저장할 버퍼의 동적할당을 free시킨다.
	}

	//버퍼에 저장된 패킷이 어떤 프로토콜을 쓰는지에 따라 각각의 처리함수로 분기한다.
	//직후, 패킷에 맞는 프로토콜 카운터를 증가시킨다
	void ProcessPacket(char* Buffer, int Size)
	{
		iphdr = (IPV4_HDR*)Buffer;
		++total;

		switch (iphdr->ip_protocol) //Check the Protocol and do accordingly...
		{
		case 1: //ICMP Protocol
			++icmp;
			PrintIcmpPacket(Buffer, Size);
			break;

		case 2: //IGMP Protocol
			++igmp;
			break;

		case 6: //TCP Protocol
			++tcp;
			PrintTcpPacket(Buffer, Size);
			break;

		case 17: //UDP Protocol
			++udp;
			PrintUdpPacket(Buffer, Size);
			break;

		default: //Some Other Protocol like ARP etc.
			++others;
			break;
		}
		printf("TCP : %d UDP : %d ICMP : %d IGMP : %d Others : %d Total : %d\r", tcp, udp, icmp, igmp, others, total);
	}

	//IP헤더 출력
	void PrintIpHeader(char* Buffer)
	{
		unsigned short iphdrlen;

		iphdr = (IPV4_HDR*)Buffer;
		iphdrlen = iphdr->ip_header_len * 4;

		memset(&source, 0, sizeof(source));
		source.sin_addr.s_addr = iphdr->ip_srcaddr;

		memset(&dest, 0, sizeof(dest));
		dest.sin_addr.s_addr = iphdr->ip_destaddr;

		fprintf(logfile, "\n");
		fprintf(logfile, "IP Header\n");
		fprintf(logfile, " |-IP Version : %d\n", (unsigned int)iphdr->ip_version);
		fprintf(logfile, " |-IP Header Length : %d DWORDS or %d Bytes\n", (unsigned int)iphdr->ip_header_len, ((unsigned int)(iphdr->ip_header_len)) * 4);
		fprintf(logfile, " |-Type Of Service : %d\n", (unsigned int)iphdr->ip_tos);
		fprintf(logfile, " |-IP Total Length : %d Bytes(Size of Packet)\n", ntohs(iphdr->ip_total_length));
		fprintf(logfile, " |-Identification : %d\n", ntohs(iphdr->ip_id));
		fprintf(logfile, " |-Reserved ZERO Field : %d\n", (unsigned int)iphdr->ip_reserved_zero);
		fprintf(logfile, " |-Dont Fragment Field : %d\n", (unsigned int)iphdr->ip_dont_fragment);
		fprintf(logfile, " |-More Fragment Field : %d\n", (unsigned int)iphdr->ip_more_fragment);
		fprintf(logfile, " |-TTL : %d\n", (unsigned int)iphdr->ip_ttl);
		fprintf(logfile, " |-Protocol : %d\n", (unsigned int)iphdr->ip_protocol);
		fprintf(logfile, " |-Checksum : %d\n", ntohs(iphdr->ip_checksum));
		fprintf(logfile, " |-Source IP : %s\n", inet_ntoa(source.sin_addr));
		fprintf(logfile, " |-Destination IP : %s\n", inet_ntoa(dest.sin_addr));
	}

	void PrintTcpPacket(char* Buffer, int Size)
	{
		unsigned short iphdrlen;

		iphdr = (IPV4_HDR*)Buffer;
		iphdrlen = iphdr->ip_header_len * 4;

		tcpheader = (TCP_HDR*)(Buffer + iphdrlen);

		fprintf(logfile, "\n\n***********************TCP Packet*************************\n");

		PrintIpHeader(Buffer);

		fprintf(logfile, "\n");
		fprintf(logfile, "TCP Header\n");
		fprintf(logfile, " |-Source Port : %u\n", ntohs(tcpheader->source_port));
		fprintf(logfile, " |-Destination Port : %u\n", ntohs(tcpheader->dest_port));
		fprintf(logfile, " |-Sequence Number : %u\n", ntohl(tcpheader->sequence));
		fprintf(logfile, " |-Acknowledge Number : %u\n", ntohl(tcpheader->acknowledge));
		fprintf(logfile, " |-Header Length : %d DWORDS or %d BYTES\n"
			, (unsigned int)tcpheader->data_offset, (unsigned int)tcpheader->data_offset * 4);
		fprintf(logfile, " |-CWR Flag : %d\n", (unsigned int)tcpheader->cwr);
		fprintf(logfile, " |-ECN Flag : %d\n", (unsigned int)tcpheader->ecn);
		fprintf(logfile, " |-Urgent Flag : %d\n", (unsigned int)tcpheader->urg);
		fprintf(logfile, " |-Acknowledgement Flag : %d\n", (unsigned int)tcpheader->ack);
		fprintf(logfile, " |-Push Flag : %d\n", (unsigned int)tcpheader->psh);
		fprintf(logfile, " |-Reset Flag : %d\n", (unsigned int)tcpheader->rst);
		fprintf(logfile, " |-Synchronise Flag : %d\n", (unsigned int)tcpheader->syn);
		fprintf(logfile, " |-Finish Flag : %d\n", (unsigned int)tcpheader->fin);
		fprintf(logfile, " |-Window : %d\n", ntohs(tcpheader->window));
		fprintf(logfile, " |-Checksum : %d\n", ntohs(tcpheader->checksum));
		fprintf(logfile, " |-Urgent Pointer : %d\n", tcpheader->urgent_pointer);
		fprintf(logfile, "\n");
		fprintf(logfile, " DATA Dump ");
		fprintf(logfile, "\n");

		fprintf(logfile, "IP Header\n");
		PrintData(Buffer, iphdrlen);

		fprintf(logfile, "TCP Header\n");
		PrintData(Buffer + iphdrlen, tcpheader->data_offset * 4);

		fprintf(logfile, "Data Payload\n");
		PrintData(Buffer + iphdrlen + tcpheader->data_offset * 4
			, (Size - tcpheader->data_offset * 4 - iphdr->ip_header_len * 4));

		fprintf(logfile, "\n###########################################################");
	}

	void PrintUdpPacket(char* Buffer, int Size)
	{
		unsigned short iphdrlen;

		iphdr = (IPV4_HDR*)Buffer;
		iphdrlen = iphdr->ip_header_len * 4;

		udpheader = (UDP_HDR*)(Buffer + iphdrlen);

		fprintf(logfile, "\n\n***********************UDP Packet*************************\n");

		PrintIpHeader(Buffer);

		fprintf(logfile, "\nUDP Header\n");
		fprintf(logfile, " |-Source Port : %d\n", ntohs(udpheader->source_port));
		fprintf(logfile, " |-Destination Port : %d\n", ntohs(udpheader->dest_port));
		fprintf(logfile, " |-UDP Length : %d\n", ntohs(udpheader->udp_length));
		fprintf(logfile, " |-UDP Checksum : %d\n", ntohs(udpheader->udp_checksum));

		fprintf(logfile, "\n");
		fprintf(logfile, "IP Header\n");

		PrintData(Buffer, iphdrlen);

		fprintf(logfile, "UDP Header\n");

		PrintData(Buffer + iphdrlen, sizeof(UDP_HDR));

		fprintf(logfile, "Data Payload\n");

		PrintData(Buffer + iphdrlen + sizeof(UDP_HDR), (Size - sizeof(UDP_HDR) - iphdr->ip_header_len * 4));

		fprintf(logfile, "\n###########################################################");
	}

	void PrintIcmpPacket(char* Buffer, int Size)
	{
		unsigned short iphdrlen;

		iphdr = (IPV4_HDR*)Buffer;
		iphdrlen = iphdr->ip_header_len * 4;

		icmpheader = (ICMP_HDR*)(Buffer + iphdrlen);

		fprintf(logfile, "\n\n***********************ICMP Packet*************************\n");
		PrintIpHeader(Buffer);

		fprintf(logfile, "\n");

		fprintf(logfile, "ICMP Header\n");
		fprintf(logfile, " |-Type : %d", (unsigned int)(icmpheader->type));

		if ((unsigned int)(icmpheader->type) == 11)
		{
			fprintf(logfile, " (TTL Expired)\n");
		}
		else if ((unsigned int)(icmpheader->type) == 0)
		{
			fprintf(logfile, " (ICMP Echo Reply)\n");
		}

		fprintf(logfile, " |-Code : %d\n", (unsigned int)(icmpheader->code));
		fprintf(logfile, " |-Checksum : %d\n", ntohs(icmpheader->checksum));
		fprintf(logfile, " |-ID : %d\n", ntohs(icmpheader->id));
		fprintf(logfile, " |-Sequence : %d\n", ntohs(icmpheader->seq));
		fprintf(logfile, "\n");

		fprintf(logfile, "IP Header\n");
		PrintData(Buffer, iphdrlen);

		fprintf(logfile, "UDP Header\n");
		PrintData(Buffer + iphdrlen, sizeof(ICMP_HDR));

		fprintf(logfile, "Data Payload\n");
		PrintData(Buffer + iphdrlen + sizeof(ICMP_HDR), (Size - sizeof(ICMP_HDR) - iphdr->ip_header_len * 4));

		fprintf(logfile, "\n###########################################################");
	}

	/*
	   Print the hex values of the data
	*/
	void PrintData(char* data, int Size)
	{
		char a, line[17], c;
		int j;

		//loop over each character and print
		for (i = 0; i < Size; i++)
		{
			c = data[i];

			//Print the hex value for every character , with a space. Important to make unsigned
			fprintf(logfile, " %.2x", (unsigned char)c);

			//Add the character to data line. Important to make unsigned
			a = (c >= 32 && c <= 128) ? (unsigned char)c : '.';

			line[i % 16] = a;

			//if last character of a line , then print the line - 16 characters in 1 line
			if ((i != 0 && (i + 1) % 16 == 0) || i == Size - 1)
			{
				line[i % 16 + 1] = '\0';

				//print a big gap of 10 characters between hex and characters
				fprintf(logfile, "          ");

				//Print additional spaces for last lines which might be less than 16 characters in length
				for (j = strlen(line); j < 16; j++)
				{
					fprintf(logfile, "   ");
				}

				fprintf(logfile, "%s \n", line);
			}
		}

		fprintf(logfile, "\n");
	}
};










