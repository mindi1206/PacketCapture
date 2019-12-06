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
}

BEGIN_MESSAGE_MAP(CFormView3, CFormView)
	ON_WM_CTLCOLOR()
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
