#pragma once
#include "afxwin.h"



// CFormView1 form view

class CFormView1 : public CFormView
{
	DECLARE_DYNCREATE(CFormView1)

//protected:
//	CFormView1();           // protected constructor used by dynamic creation
//	virtual ~CFormView1();

public:
		CFormView1();           // protected constructor used by dynamic creation
		virtual ~CFormView1();
	enum { IDD = IDD_FORMVIEW1 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit TCP_SRCPORT;
	CEdit TCP_DESTPORT;
	CEdit TCP_SEQ;
	CEdit TCP_ACK;
	CEdit TCP_HL;
	CEdit TCP_U;
	CEdit TCP_A;
	CEdit TCP_P;
	CEdit TCP_R;
	CEdit TCP_S;
	CEdit TCP_F;
	CEdit TCP_WINDOW;
	CEdit TCP_CHEKSUM;
	CEdit TCP_URG;
	int a;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit IPVersion;
	CEdit IHL;
	CEdit TOS;
	CEdit TotalLength;
	CEdit Identification;
	CEdit Flag;
	CEdit FragOffset;
	CEdit TTL;
	CEdit Protocol;
	CEdit HeaderChecksum;
	CEdit SourceAddress;
	CEdit DestinationAddress;
	CEdit ReservedZero;
//	afx_msg void OnEnChangeEditDontFrag();
	CEdit DontFrag;
	CEdit MoreFrag;
};


