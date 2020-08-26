// FormView2.cpp : implementation file
//

#include "stdafx.h"
#include "SubFormView.h"
#include "FormView2.h"


// CFormView2

IMPLEMENT_DYNCREATE(CFormView2, CFormView)

CFormView2::CFormView2()
	: CFormView(CFormView2::IDD)
{

}

CFormView2::~CFormView2()
{
}

void CFormView2::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT59, udp_srcPort);
	DDX_Control(pDX, IDC_EDIT51, udp_destPort);
	DDX_Control(pDX, IDC_EDIT39, udp_length);
	DDX_Control(pDX, IDC_EDIT38, udp_checksum);
	DDX_Control(pDX, IDC_EDIT4, udp_data);

	DDX_Control(pDX, IDC_UDP_VER, IPVersion);
	DDX_Control(pDX, IDC_UDP_IHL, IHL);
	DDX_Control(pDX, IDC_UDP_TOS, TOS);
	DDX_Control(pDX, IDC_UDP_TL, TotalLength);
	DDX_Control(pDX, IDC_UDP_IDENTIFICATION, Identification);
	DDX_Control(pDX, IDC_UDP_MF, MoreFrag);
	DDX_Control(pDX, IDC_UDP_DF, DontFrag);
	DDX_Control(pDX, IDC_UDP_RZ, ReservedZero);
	DDX_Control(pDX, IDC_UDP_FOFFSET, FragOffset);
	DDX_Control(pDX, IDC_UDP_TTL, TTL);
	DDX_Control(pDX, IDC_UDP_PROTOCOL, Protocol);
	DDX_Control(pDX, IDC_UDP_HCHECKSUM, HeaderChecksum);
	DDX_Control(pDX, IDC_UDP_SRCADDR, SourceAddress);
	DDX_Control(pDX, IDC_UDP_DESTADDR, DestinationAddress);
}

BEGIN_MESSAGE_MAP(CFormView2, CFormView)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CFormView2 diagnostics

#ifdef _DEBUG
void CFormView2::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormView2::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormView2 message handlers


HBRUSH CFormView2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	HBRUSH hbr = CreateSolidBrush(RGB(255, 255, 255));

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
