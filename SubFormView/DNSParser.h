#pragma once

#include <vector>
#include "HeaderType.h"
#include "InfoGen.h"

typedef struct dnsQuery {
	CString name;
	CString type;
	CString _class;
} _DNSQuery;

typedef struct dnsAnswer {
	CString name;
	CString type;
	CString _class;
	unsigned int ttl;
	int data_len;
	CString rdata;
} _DNSAnswer;

typedef struct dns {
	_DNSQuery dnsqry;
	std::vector<_DNSAnswer*> dnsans;
} _DNSPayload;

class DNSParser
{
private:

public:
	static _DNSPayload parse(DNS_HDR* dnsheader);
};

int ReadDNSName(DNS_HDR* dnshdr, char** namePtr, std::string* buffer, char* flag);
CString getTypeString(u_short type);
CString getClassString(u_short _class);