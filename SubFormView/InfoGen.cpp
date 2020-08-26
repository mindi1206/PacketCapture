#include "stdafx.h"
#include "InfoGen.h"

CString InfoGen::tcpInfo(IPV4_HDR* iphdr) {
	unsigned short iphdrlen;
	TCP_HDR* tcpheader;
	CString infoText = _T("");
	iphdrlen = iphdr->ip_header_len * 4;
	tcpheader = (TCP_HDR*)((char*)iphdr + iphdrlen);

	infoText += tcpPort(tcpheader);
	infoText += _T(" ");
	infoText += tcpFlag(tcpheader);
	infoText += _T(" ");
	infoText += tcpSeq(ntohl(tcpheader->sequence));
	infoText += _T(" ");
	infoText += tcpAck(ntohl(tcpheader->acknowledge));

	return infoText;
}

CString InfoGen::udpInfo(IPV4_HDR* iphdr)
{
	CString buffer;
	unsigned short iphdrlen;
	UDP_HDR* udpheader;
	CString infoText = _T("");
	iphdrlen = iphdr->ip_header_len * 4;
	udpheader = (UDP_HDR*)((char*)iphdr + iphdrlen);

	infoText += udpPort(udpheader);
	infoText += _T(" ");
	buffer.Format(_T(", UDP Length : %d"), ntohs(udpheader->udp_length));
	infoText += buffer;

	return infoText;
}

CString InfoGen::dnsReqInfo(DNS_HDR* dnshdr)
{
	CString buffer;
	CString infoText = _T("");
	_DNSPayload DNSPayload = DNSParser::parse(dnshdr);

	infoText += _T("Request ID : ");
	buffer.Format(_T("%d"), ntohs(dnshdr->transaction_id));
	infoText += buffer;
	infoText += _T(", Query : ");
	infoText += DNSPayload.dnsqry.name;

	return infoText;
}

CString InfoGen::dnsResInfo(DNS_HDR* dnshdr)
{
	CString buffer;
	CString infoText = _T("");
	_DNSPayload DNSPayload = DNSParser::parse(dnshdr);

	infoText += _T("Response ID : ");
	buffer.Format(_T("%d"), ntohs(dnshdr->transaction_id));
	infoText += buffer;
	infoText += _T(", Query : ");
	infoText += DNSPayload.dnsqry.name;
	for (int i = 0; i < DNSPayload.dnsans.size(); i++) {
		buffer.Format(_T(", Answer[%d] : "), i + 1);
		infoText += buffer;
		infoText += DNSPayload.dnsans[i]->rdata;
	}

	return infoText;
}

CString InfoGen::dnsReqData(DNS_HDR* dnshdr)
{
	CString buffer;
	CString infoText = _T("");
	_DNSPayload DNSPayload = DNSParser::parse(dnshdr);

	infoText += _T("Request ID : ");
	buffer.Format(_T("%d\r\n"), ntohs(dnshdr->transaction_id));
	infoText += buffer;
	infoText += _T("\r\nQuery : ");
	infoText += DNSPayload.dnsqry.name;
	infoText += _T("\r\nType : ");
	infoText += DNSPayload.dnsqry.type;
	infoText += _T("\r\nClass : ");
	infoText += DNSPayload.dnsqry._class;
	infoText += _T("\r\n");

	return infoText;
}

CString InfoGen::dnsResData(DNS_HDR* dnshdr)
{
	CString buffer;
	CString infoText = _T("");
	_DNSPayload DNSPayload = DNSParser::parse(dnshdr);

	infoText += _T("Response ID : ");
	buffer.Format(_T("%d\r\n"), ntohs(dnshdr->transaction_id));
	infoText += buffer;
	infoText += _T("\r\nQuery : ");
	infoText += DNSPayload.dnsqry.name;
	infoText += _T("\r\nType : ");
	infoText += DNSPayload.dnsqry.type;
	infoText += _T("\r\nClass : ");
	infoText += DNSPayload.dnsqry._class;
	infoText += _T("\r\n");

	for (int i = 0; i < DNSPayload.dnsans.size(); i++) {
		infoText += _T("\r\nAnswer : ");
		infoText += DNSPayload.dnsans[i]->name;
		infoText += _T("\r\nType : ");
		infoText += DNSPayload.dnsans[i]->type;
		infoText += _T("\r\nClass : ");
		infoText += DNSPayload.dnsans[i]->_class;
		infoText += _T("\r\nTTL : ");
		buffer.Format(_T("%d\r\n"), DNSPayload.dnsans[i]->ttl);
		infoText += buffer;
		infoText += _T("Data Length : ");
		buffer.Format(_T("%d\r\n"), DNSPayload.dnsans[i]->data_len);
		infoText += buffer;

		infoText += DNSPayload.dnsans[i]->type;
		infoText += _T(" : ");
		infoText += DNSPayload.dnsans[i]->rdata;
		infoText += _T("\r\n");
	}

	return infoText;
}

CString InfoGen::udpData(UDP_HDR* udphdr)
{
	CString buffer;
	CString infoText = _T("");

	char* udppayload = (char*)udphdr + sizeof(UDP_HDR);

	for (int i = 0; i < ntohs(udphdr->udp_length) - sizeof(UDP_HDR); i++) {
		buffer.Format(_T("%.2x "), (unsigned char)udppayload[i]);
		infoText += buffer;

		if ((i + 1) % 8 == 0) {
			infoText += "\r\n";
		}
	}

	return infoText;
}

CString InfoGen::tcpFlag(TCP_HDR* tcpheader) {
	std::vector<CString> string;
	CString tcpFlagString = _T("");

	if (tcpheader->fin == (unsigned char)1) {
		string.push_back(_T("FIN"));
	}
	if (tcpheader->syn == (unsigned char)1) {
		string.push_back(_T("SYN"));
	}
	if (tcpheader->ack == (unsigned char)1) {
		string.push_back(_T("ACK"));
	}
	if (tcpheader->psh == (unsigned char)1) {
		string.push_back(_T("PSH"));
	}

	for (int i = 0; i < string.size(); i++) {
		if (i == 0) {
			tcpFlagString += _T("[");
		}
		if (i != 0 && i != string.size()) {
			tcpFlagString += _T(", ");
		}
		tcpFlagString += string.at(i);
		if (i == string.size() - 1) {
			tcpFlagString += _T("]");
		}
	}

	return tcpFlagString;
}

CString InfoGen::tcpPort(TCP_HDR* tcpheader)
{
	CString buffer, tcpPortString;
	buffer.Format(_T("%u"), ntohs(tcpheader->source_port));
	tcpPortString += buffer;
	tcpPortString += _T(" -> ");
	buffer.Format(_T("%u"), ntohs(tcpheader->dest_port));
	tcpPortString += buffer;

	return tcpPortString;
}

CString InfoGen::udpPort(UDP_HDR* udpheader)
{
	CString buffer, tcpPortString;
	buffer.Format(_T("%u"), ntohs(udpheader->source_port));
	tcpPortString += buffer;
	tcpPortString += _T(" -> ");
	buffer.Format(_T("%u"), ntohs(udpheader->dest_port));
	tcpPortString += buffer;

	return tcpPortString;
}

CString InfoGen::tcpSeq(unsigned int seqNum)
{
	CString buffer, tcpSeqString;
	tcpSeqString += _T("Seq=");
	buffer.Format(_T("%u"), seqNum);
	tcpSeqString += buffer;

	return tcpSeqString;
}

CString InfoGen::tcpAck(unsigned int ackNum)
{
	CString buffer, tcpAckString;
	tcpAckString += _T("Ack=");
	buffer.Format(_T("%u"), ackNum);
	tcpAckString += buffer;

	return tcpAckString;
}

CString InfoGen::icmpInfo(IPV4_HDR* iphdr) {
	unsigned short iphdrlen;
	iphdrlen = iphdr->ip_header_len * 4;
	ICMP_HDR* icmpHdr = (ICMP_HDR*)((char *)iphdr + iphdrlen);
	
	CString infoText = _T("");
	CString temp;

	
	
	if ((unsigned int)(icmpHdr->type) == 11)
	{
		temp.Format(_T("TTL Expired "));
		infoText += temp;
		return infoText;
	}
	else if ((unsigned int)(icmpHdr->type) == 0)
	{
		temp.Format(_T("ICMP Echo REply  "));
		infoText += temp;
	}
	else if ((unsigned int)(icmpHdr->type) == 8)
	{
		temp.Format(_T("Echo (ping) request "));
		infoText += temp;
	}

	infoText += _T("ID : ");
	temp.Format(_T("%u"), ntohs(icmpHdr->id));
	infoText += temp;

	infoText += _T(" ");
	infoText += _T("SEQ : ");
	temp.Format(_T("%u"), ntohs(icmpHdr->seq));
	infoText += temp;
	infoText += _T(" ");

	return infoText;
}