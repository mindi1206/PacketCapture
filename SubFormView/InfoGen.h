#pragma once

#include <atlstr.h>
#include <tchar.h>
#include <vector>
#include <string>
#include "HeaderType.h"
#include "DNSParser.h"

class InfoGen
{
private:
	static CString tcpFlag(TCP_HDR* tcpheader);
	static CString tcpPort(TCP_HDR* tcpheader);
	static CString udpPort(UDP_HDR* udpheader);
	static CString tcpSeq(unsigned int seqNum);
	static CString tcpAck(unsigned int ackNum);
public:
	static CString tcpInfo(IPV4_HDR* iphdr);
	static CString udpInfo(IPV4_HDR* iphdr);
	static CString dnsReqInfo(DNS_HDR* dnshdr);
	static CString dnsResInfo(DNS_HDR* dnshdr);
	static CString dnsReqData(DNS_HDR* dnshdr);
	static CString dnsResData(DNS_HDR* dnshdr);
	static CString udpData(UDP_HDR* udphdr);

	static CString icmpInfo(IPV4_HDR* iphdr);
};