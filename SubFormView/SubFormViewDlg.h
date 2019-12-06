
// SubFormViewDlg.h : header file
//

#pragma once

#include "FormViewMain.h"
#include "FormView1.h"
#include "FormView2.h"
#include "FormView3.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "HeaderType.h"
#include <vector>

using namespace std;

typedef struct ListData {
	CString idx;
	CString time;
	CString destip;
	CString srcip;
	CString protocol;
	CString packetlen;
	CString packetinfo;

	ListData(CString idx, CString time, CString srcip, CString destip, CString protocol, CString packetlen, CString packetinfo) {
		this->idx = idx;
		this->time = time;
		this->srcip = srcip;
		this->destip = destip;		
		this->protocol = protocol;
		this->packetlen = packetlen;
		this->packetinfo = packetinfo;
	}
}ListData;

typedef struct NicDecisionParam {
	struct hostent* local;
	int decision;
}NicDecisionParam;


// CSubFormViewDlg dialog
class CSubFormViewDlg : public CDialogEx
{
	// Construction
public:
	CSubFormViewDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_SUBFORMVIEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	/*CView* m_pFormView1;
	CView* m_pFormView2;
	CView* m_pFormView3;*/
	

	CFormViewMain* m_pFormViewMain;
	CFormView1* m_pFormView1;
	CFormView2* m_pFormView2;
	CFormView3* m_pFormView3;

	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	void httpPayloadPrinter(char* packet, unsigned short iphdrlen, TCP_HDR* tcpheader, IPV4_HDR* iphdr, CFormView1* m_pFormView1);
	

	CComboBox mCombo;
	afx_msg void OnCbnSelchangeCombo();
	CListCtrl mList;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnLvnInsertitemListPacket(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListPacket(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSearch();
	
	CEdit m_EditIP;
	CEdit m_EditPORT;
	afx_msg void OnBnClickedButtonReset();

	std::vector<ListData> listdata;
	int nicDecision;
	void setNicDecision(int decision);
	CEdit TcpCounter;
	CEdit UdpCounter;
	CEdit IcmpCounter;
	CEdit DnsCounter;
};
