#pragma once



// CFormViewMain �� ���Դϴ�.

class CFormViewMain : public CFormView
{
	DECLARE_DYNCREATE(CFormViewMain)

protected:
	CFormViewMain();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CFormViewMain();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMMAIN };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


