// FormView1.cpp : implementation file
//

#include "stdafx.h"
#include "SubFormView.h"
#include "FormView1.h"


// CFormView1

IMPLEMENT_DYNCREATE(CFormView1, CFormView)

CFormView1::CFormView1()
	: CFormView(CFormView1::IDD)
{

}

CFormView1::~CFormView1()
{
}

void CFormView1::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCP_SRCPORT, TCP_SRCPORT);
	DDX_Control(pDX, IDC_TCP_DESTPORT, TCP_DESTPORT);
	DDX_Control(pDX, IDC_TCP_SEQ, TCP_SEQ);
	DDX_Control(pDX, IDC_TCP_ACK, TCP_ACK);
	DDX_Control(pDX, IDC_TCP_HL, TCP_HL);
	DDX_Control(pDX, IDC_TCP_U, TCP_U);
	DDX_Control(pDX, IDC_TCP_A, TCP_A);
	DDX_Control(pDX, IDC_TCP_P, TCP_P);
	DDX_Control(pDX, IDC_TCP_R, TCP_R);
	DDX_Control(pDX, IDC_TCP_S, TCP_S);
	DDX_Control(pDX, IDC_TCP_F, TCP_F);
	DDX_Control(pDX, IDC_TCP_WINDOW, TCP_WINDOW);
	DDX_Control(pDX, IDC_TCP_CHECKSUM, TCP_CHEKSUM);
	DDX_Control(pDX, IDC_TCP_URG, TCP_URG);
	DDX_Control(pDX, IDC_TCP_VER, IPVersion);
	DDX_Control(pDX, IDC_TCP_IHL, IHL);
	DDX_Control(pDX, IDC_TCP_TOS, TOS);
	DDX_Control(pDX, IDC_TCP_TL, TotalLength);
	DDX_Control(pDX, IDC_TCP_IDENTIFICATION, Identification);
	//DDX_Control(pDX, IDC_TCP_FLAG, Flag);
	DDX_Control(pDX, IDC_FragOffset, FragOffset);
	DDX_Control(pDX, IDC_TCP_TTL, TTL);
	DDX_Control(pDX, IDC_TCP_PROTOCOL, Protocol);
	DDX_Control(pDX, IDC_TCP_HCHECKSUM, HeaderChecksum);
	DDX_Control(pDX, IDC_TCP_SRCADDR, SourceAddress);
	DDX_Control(pDX, IDC_TCP_DESTADDR, DestinationAddress);
	DDX_Control(pDX, IDC_EDIT_Reserved_ZERO, ReservedZero);
	DDX_Control(pDX, IDC_EDIT_DONT_FRAG, DontFrag);
	DDX_Control(pDX, IDC_EDIT_MORE_FRAG, MoreFrag);
}

BEGIN_MESSAGE_MAP(CFormView1, CFormView)
	ON_WM_CTLCOLOR()
//	ON_EN_CHANGE(IDC_EDIT_DONT_FRAG, &CFormView1::OnEnChangeEditDontFrag)
END_MESSAGE_MAP()


// CFormView1 diagnostics

#ifdef _DEBUG
void CFormView1::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormView1::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormView1 message handlers


HBRUSH CFormView1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	HBRUSH hbr = CreateSolidBrush(RGB(255, 255, 255));
	return hbr;
}


//void CFormView1::OnEnChangeEditDontFrag()
//{
//	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
//	// CFormView::OnInitDialog() �Լ��� ������ 
//	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
//	// �� �˸� �޽����� ������ �ʽ��ϴ�.
//
//	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//}
