#pragma once



// CFormView2 form view

class CFormView2 : public CFormView
{
	DECLARE_DYNCREATE(CFormView2)

protected:
	CFormView2();           // protected constructor used by dynamic creation
	virtual ~CFormView2();

public:
	enum { IDD = IDD_FORMVIEW2 };
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
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


