#pragma once



// CFormView3 �� ���Դϴ�.

class CFormView3 : public CFormView
{
	DECLARE_DYNCREATE(CFormView3)

protected:
	CFormView3();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CFormView3();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW3 };
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
};

