// FormViewMain.cpp : ���� �����Դϴ�.
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


// CFormViewMain �����Դϴ�.

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


// CFormViewMain �޽��� ó�����Դϴ�.


HBRUSH CFormViewMain::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	HBRUSH hbr = CreateSolidBrush(RGB(255, 255, 255));
	return hbr;
}
