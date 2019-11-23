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
