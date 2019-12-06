// FormViewMain.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SubFormView.h"
#include "FormViewMain.h"


// CFormViewMain

IMPLEMENT_DYNCREATE(CFormViewMain, CFormView)

CFormViewMain::CFormViewMain()
	: CFormView(IDD_FORMMAIN)
{

}

CFormViewMain::~CFormViewMain()
{
}

void CFormViewMain::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormViewMain, CFormView)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CFormViewMain 진단입니다.

#ifdef _DEBUG
void CFormViewMain::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormViewMain::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormViewMain 메시지 처리기입니다.


HBRUSH CFormViewMain::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	HBRUSH hbr = CreateSolidBrush(RGB(255, 255, 255));
	return hbr;
}
