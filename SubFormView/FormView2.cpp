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
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (nCtlColor) {

	case CTLCOLOR_DLG:   // 다이얼로그 배경색을 white로.
	{
		return (HBRUSH)GetStockObject(WHITE_BRUSH);
		break;
	}
	case CTLCOLOR_BTN:    // 버튼의 배경색을 투명으로...
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);
	}



	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
