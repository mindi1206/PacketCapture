#pragma once

#include "SubFormViewDlg.h"
#include <vector>

// CNicSelector 대화 상자

class CNicSelector : public CDialogEx
{
	DECLARE_DYNAMIC(CNicSelector)

public:
	CNicSelector(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNicSelector();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NIC_SELECTOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListPacket(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl mNicList;
	afx_msg void OnLvnItemchangedListNic(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit mEditUserDecision;
	afx_msg void OnBnClickedOk();
	struct hostent* local;
	void setLocal(struct hostent* param);
	void setParent(CSubFormViewDlg* parent);
	CSubFormViewDlg* parentDialog;
};
