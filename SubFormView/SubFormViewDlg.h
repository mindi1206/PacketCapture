
// SubFormViewDlg.h : header file
//

#pragma once

#include "FormView1.h"
#include "FormView2.h"
#include "FormView3.h"
#include "afxwin.h"
#include "afxcmn.h"

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
	CView* m_pFormView1;
	CView* m_pFormView2;
	CView* m_pFormView3;

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
	

	CComboBox mCombo;
	afx_msg void OnCbnSelchangeCombo();
	CListCtrl mList;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnLvnInsertitemListPacket(NMHDR *pNMHDR, LRESULT *pResult);
};
