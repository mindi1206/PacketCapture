// FormView3.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SubFormView.h"
#include "FormView3.h"


// CFormView3

IMPLEMENT_DYNCREATE(CFormView3, CFormView)

CFormView3::CFormView3()
	: CFormView(IDD_FORMVIEW3)
{

}

CFormView3::~CFormView3()
{
}

void CFormView3::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ICMP_VER, IPVersion);
	DDX_Control(pDX, IDC_ICMP_IHL , IHL);
	DDX_Control(pDX, IDC_ICMP_TOS, TOS);
	DDX_Control(pDX, IDC_ICMP_TL, TotalLength);
	DDX_Control(pDX, IDC_ICMP_IDENTIFICATION, Identification);
	DDX_Control(pDX, IDC_ICMP_MF, MoreFrag);
	DDX_Control(pDX, IDC_ICMP_DF, DontFrag);
	DDX_Control(pDX, IDC_ICMP_RZ, ReservedZero);
	DDX_Control(pDX, IDC_ICMP_FOFFSET, FragOffset);
	DDX_Control(pDX, IDC_ICMP_TTL, TTL);
	DDX_Control(pDX, IDC_ICMP_PROTOCOL, Protocol);
	DDX_Control(pDX, IDC_ICMP_HCHECKSUM, HeaderChecksum);
	DDX_Control(pDX, IDC_ICMP_SRCADDR, SourceAddress);
	DDX_Control(pDX, IDC_ICMP_DESTADDR, DestinationAddress);
	DDX_Control(pDX, IDC_ICMP_TYPE, Type);
	DDX_Control(pDX, IDC_ICMP_CODE, Code);
	DDX_Control(pDX, IDC_ICMP_CHECKSUM, CheckSum);
	DDX_Control(pDX, IDC_ICMP_ID, id);
	DDX_Control(pDX, IDC_ICMP_SEQ, seq);

	DDX_Control(pDX, IDC_ICMP_VER2, IPVersion2);
	DDX_Control(pDX, IDC_ICMP_IHL2, IHL2);
	DDX_Control(pDX, IDC_ICMP_TOS2, TOS2);
	DDX_Control(pDX, IDC_ICMP_TL2, TotalLength2);
	DDX_Control(pDX, IDC_ICMP_IDENTIFICATION2, Identification2);
	DDX_Control(pDX, IDC_ICMP_MF2, MoreFrag2);
	DDX_Control(pDX, IDC_ICMP_DF2, DontFrag2);
	DDX_Control(pDX, IDC_ICMP_RZ2, ReservedZero2);
	DDX_Control(pDX, IDC_ICMP_FOFFSET2, FragOffset2);
	DDX_Control(pDX, IDC_ICMP_TTL2, TTL2);
	DDX_Control(pDX, IDC_ICMP_PROTOCOL2, Protocol2);
	DDX_Control(pDX, IDC_ICMP_HCHECKSUM2, HeaderChecksum2);
	DDX_Control(pDX, IDC_ICMP_SRCADDR2, SourceAddress2);
	DDX_Control(pDX, IDC_ICMP_DESTADDR2, DestinationAddress2);
	DDX_Control(pDX, IDC_ICMP_TYPE2, Type2);
	DDX_Control(pDX, IDC_ICMP_CODE2, Code2);
	DDX_Control(pDX, IDC_ICMP_CHECKSUM2, CheckSum2);
	DDX_Control(pDX, IDC_ICMP_ID2, id2);
	DDX_Control(pDX, IDC_ICMP_SEQ2, seq2);



	DDX_Control(pDX, IDC_ICMP_TOS, TOS);
	DDX_Control(pDX, IDC_ICMP_TOS2, TOS2);
}

BEGIN_MESSAGE_MAP(CFormView3, CFormView)
	ON_WM_CTLCOLOR()
//	ON_EN_CHANGE(IDC_FOFFSET, &CFormView3::OnEnChangeFoffset)
END_MESSAGE_MAP()


// CFormView3 진단입니다.

#ifdef _DEBUG
void CFormView3::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormView3::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormView3 메시지 처리기입니다.


HBRUSH CFormView3::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	HBRUSH hbr = CreateSolidBrush(RGB(255, 255, 255));

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


//void CFormView3::OnEnChangeFoffset()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CFormView::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}
