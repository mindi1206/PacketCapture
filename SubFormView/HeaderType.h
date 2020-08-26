#pragma once
	typedef struct ip_hdr//ip헤더
	{
		unsigned char ip_header_len : 4; // 4-bit header length (in 32-bit words) normally=5 (Means 20 Bytes may be 24 also)
		unsigned char ip_version : 4; // 4-bit IPv4 version
		unsigned char ip_tos; // IP type of service
		unsigned short ip_total_length; // Total length
		unsigned short ip_id; // Unique identifier

		unsigned char ip_frag_offset : 5; // Fragment offset field

		unsigned char ip_more_fragment : 1;
		unsigned char ip_dont_fragment : 1;
		unsigned char ip_reserved_zero : 1;

		unsigned char ip_frag_offset1; //fragment offset

		unsigned char ip_ttl; // Time to live
		unsigned char ip_protocol; // Protocol(TCP,UDP etc)
		unsigned short ip_checksum; // IP checksum
		unsigned int ip_srcaddr; // Source address
		unsigned int ip_destaddr; // Source address
	} IPV4_HDR;
	typedef struct udp_hdr
	{
		unsigned short source_port; // Source port no.
		unsigned short dest_port; // Dest. port no.
		unsigned short udp_length; // Udp packet length
		unsigned short udp_checksum; // Udp checksum (optional)
	} UDP_HDR;
	// TCP header
	typedef struct tcp_header//tcp 헤더
	{
		unsigned short source_port; // source port
		unsigned short dest_port; // destination port
		unsigned int sequence; // sequence number - 32 bits
		unsigned int acknowledge; // acknowledgement number - 32 bits

		unsigned char ns : 1; //Nonce Sum Flag Added in RFC 3540.
		unsigned char reserved_part1 : 3; //according to rfc
		unsigned char data_offset : 4; /*The number of 32-bit words in the TCP header.
		This indicates where the data begins.
		The length of the TCP header is always a multiple
		of 32 bits.*/

		unsigned char fin : 1; //Finish Flag
		unsigned char syn : 1; //Synchronise Flag
		unsigned char rst : 1; //Reset Flag
		unsigned char psh : 1; //Push Flag
		unsigned char ack : 1; //Acknowledgement Flag
		unsigned char urg : 1; //Urgent Flag

		unsigned char ecn : 1; //ECN-Echo Flag
		unsigned char cwr : 1; //Congestion Window Reduced Flag

		////////////////////////////////

		unsigned short window; // window
		unsigned short checksum; // checksum
		unsigned short urgent_pointer; // urgent pointer
	} TCP_HDR;
	typedef struct icmp_hdr//icmp 헤더
	{
		BYTE type; // ICMP Error type
		BYTE code; // Type sub code
		USHORT checksum;
		USHORT id;
		USHORT seq;
	} ICMP_HDR;

	typedef struct payload_dns
	{
		// DNS 헤더
		unsigned short transaction_id; // identification number

		unsigned char recur_desired : 1; // recursion desired
		unsigned char truncated_message : 1; // truncated message
		unsigned char authoritive_answer : 1; // authoritive answer
		unsigned char opcode : 4; // purpose of message
		unsigned char qry_res_flag : 1; // query/response flag

		unsigned char response_code : 4; // response code
		unsigned char checking_disabled : 1; // checking disabled
		unsigned char authenticated_data : 1; // authenticated data
		unsigned char z : 1; // its z! reserved
		unsigned char recursion_available : 1; // recursion available

		unsigned short q_count; // number of question entries
		unsigned short ans_count; // number of answer entries
		unsigned short auth_count; // number of authority entries
		unsigned short add_count; // number of resource entries
	} DNS_HDR;

	typedef struct dns_question
	{
		unsigned short qtype;
		unsigned short qclass;
	} DNS_QUERY_DATA;

	//Constant sized fields of the resource record structure
	typedef struct dns_res_data
	{
		unsigned short type;
		unsigned short _class;
		unsigned int ttl;
		unsigned short data_len;
	} DNS_ANSWER_DATA;
	typedef struct ethernet_header
	{
		UCHAR dest[6];
		UCHAR source[6];
		USHORT type;
	}   ETHER_HDR, *PETHER_HDR, FAR* LPETHER_HDR, ETHERHeader;

	typedef struct TLS_HEADER
	{
		unsigned char contentType; // Time to live
		unsigned short version;
		unsigned short length;
	}TLS_HDR;