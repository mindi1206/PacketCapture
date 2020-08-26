#include "stdafx.h"
#include "DNSParser.h"


_DNSPayload DNSParser::parse(DNS_HDR* dnsheader)
{
	std::string temp;
	char* qname = (char*)dnsheader + sizeof(DNS_HDR);

	// DNS Query Name
	_DNSQuery dnsqry;
	char flag = false;
	if (ReadDNSName(dnsheader, &qname, &temp, &flag) < 0) {
		temp = "DNS Name Parse Error";
	}
	dnsqry.name = temp.c_str();

	// DNS Query Info
	DNS_QUERY_DATA* qinfo = (DNS_QUERY_DATA*)qname;
	dnsqry.type = getTypeString(ntohs(qinfo->qtype));
	dnsqry._class = getClassString(ntohs(qinfo->qclass));

	// DNS 응답 데이터 시작
	std::vector<_DNSAnswer*> dnsans;

	DNS_ANSWER_DATA* ainfo = NULL;
	char* aname = NULL;
	char* rdata = NULL;
	for (int i = 0; i < ntohs(dnsheader->ans_count); i++) {
		_DNSAnswer* answer = new _DNSAnswer;
		// 초기값
		if (i == 0)
		{
			aname = (char*)qinfo + sizeof(DNS_QUERY_DATA);	// name
		}
		else {
			aname = (char*)rdata;	// name
		}

		// 응답 name 읽기
		temp.clear();
		flag = false;

		// test code
		if (*aname == (char)0xcd) {
			int l = 0;
		}

		if (ReadDNSName(dnsheader, &aname, &temp, &flag) < 0) {
			temp = "DNS Name Parse Error";
		}
		answer->name = temp.c_str();

		ainfo = (DNS_ANSWER_DATA*)aname;
		answer->type = getTypeString(ntohs(ainfo->type));
		answer->_class = getClassString(ntohs(ainfo->_class));
		answer->ttl = ntohl(ainfo->ttl);
		answer->data_len = ntohs(ainfo->data_len);

		unsigned short datalen = ntohs(ainfo->data_len);
		// 응답 rdata 읽기
		rdata = (char*)ainfo + sizeof(DNS_ANSWER_DATA) - 2;	// rdata, 구조체 실제크기 12, 패킷 길이 10
		if (ntohs(ainfo->type) == 1) {	// ipv4 주소
			struct in_addr addr;
			addr.s_addr = *((unsigned long*)rdata);
			answer->rdata = inet_ntoa(addr);
			(char*)rdata = (char*)rdata + ntohs(ainfo->data_len);
		}
		else if (ntohs(ainfo->type) == 28) {	// ipv6 주소
			answer->rdata = _T("IPv6 Address");
		}
		else {							// CNAME
			temp.clear();
			flag = false;
			if (ReadDNSName(dnsheader, &rdata, &temp, &flag) < 0) {
				temp = "DNS Rdata Parse Error";
			}
			answer->rdata = temp.c_str();
		}

		dnsans.push_back(answer);
	}

	_DNSPayload Payload;
	Payload.dnsans = dnsans;
	Payload.dnsqry = dnsqry;

	return Payload;
}

int ReadDNSName(DNS_HDR* dnshdr, char** namePtr, std::string* buffer, char* flag)
{
	// http://www.tcpipguide.com/free/t_DNSNameNotationandMessageCompressionTechnique.htm

	while (1) {
		int dotLen = **namePtr;
		if (**namePtr == (char)0xc0) {
			char* p = (char*)dnshdr + (unsigned char)(**namePtr & 0x0f) + (unsigned char)(*((*namePtr) + 1));
			ReadDNSName(dnshdr, &p, buffer, flag);
			*namePtr += 2;
			if (*flag == true) {
				return buffer->length();
			}

		}
		else {
			buffer->append(*namePtr, 1, dotLen);
			*namePtr += (dotLen + 1);
		}
		if (**namePtr == 0) {
			(*namePtr)++;
			*flag = true;
			return buffer->length();
		}
		buffer->append(".");
	}
}

CString getTypeString(u_short type) {
	switch (type) {
	case 1:
		return _T("A");
	case 2:
		return _T("NS");
	case 3:
		return _T("MD");
	case 4:
		return _T("MF");
	case 5:
		return _T("CNAME");
	case 6:
		return _T("SOA");
	case 7:
		return _T("MB");
	case 8:
		return _T("MG");
	case 9:
		return _T("MR");
	case 10:
		return _T("NULL");
	case 11:
		return _T("WKS");
	case 12:
		return _T("PTR");
	case 13:
		return _T("HINFO");
	case 14:
		return _T("MINFO");
	case 15:
		return _T("MX");
	case 16:
		return _T("TXT");
	case 28:
		return _T("AAAA(IPv6)");
	default:
		return _T("Unknown Type");
	}
}

CString getClassString(u_short _class) {
	switch (_class) {
	case 1:
		return _T("IN");
	default:
		return _T("Unknown Class");
	}
}