#pragma once



// CFormView3 폼 뷰입니다.

class CFormView3 : public CFormView
{
	DECLARE_DYNCREATE(CFormView3)

protected:
	CFormView3();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnEnChangeFoffset();
	CEdit IPVersion;
	CEdit IHL;
	CEdit TOS;
	CEdit TotalLength;
	CEdit Identification;
	CEdit MoreFrag;
	CEdit DontFrag;
	CEdit ReservedZero;
	CEdit FragOffset;
	CEdit TTL;
	CEdit Protocol;
	CEdit HeaderChecksum;
	CEdit SourceAddress;
	CEdit DestinationAddress;
	CEdit Type;
	CEdit Code;
	CEdit CheckSum;
	CEdit id;
	CEdit seq;

	CEdit IPVersion2;
	CEdit IHL2;
	CEdit TOS2;
	CEdit TotalLength2;
	CEdit Identification2;
	CEdit MoreFrag2;
	CEdit DontFrag2;
	CEdit ReservedZero2;
	CEdit FragOffset2;
	CEdit TTL2;
	CEdit Protocol2;
	CEdit HeaderChecksum2;
	CEdit SourceAddress2;
	CEdit DestinationAddress2;
	CEdit Type2;
	CEdit Code2;
	CEdit CheckSum2;
	CEdit id2;
	CEdit seq2;
};


