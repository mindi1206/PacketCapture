
// SubFormViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SubFormView.h"
#include "SubFormViewDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include "CoreUnit.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSubFormViewDlg dialog



CSubFormViewDlg::CSubFormViewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSubFormViewDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSubFormViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO, mCombo);
	DDX_Control(pDX, IDC_LIST_PACKET, mList);
}

BEGIN_MESSAGE_MAP(CSubFormViewDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CSubFormViewDlg::OnBnClickedButton1)
	//ON_BN_CLICKED(IDC_BUTTON2, &CSubFormViewDlg::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO, &CSubFormViewDlg::OnCbnSelchangeCombo)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSubFormViewDlg message handlers

BOOL CSubFormViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	CRect rc;
	GetClientRect(&rc);
	rc.top += 400;
	rc.left += 50;

	CCreateContext cc;

	CView* pView = (CView*)RUNTIME_CLASS(CFormView1)->CreateObject();
	ZeroMemory(&cc, sizeof(cc));
	pView->Create(nullptr, nullptr, WS_CHILD, rc, this, IDD_FORMVIEW1, &cc);
	pView->OnInitialUpdate();
	m_pFormView1 = pView;

	pView = (CView*)RUNTIME_CLASS(CFormView2)->CreateObject();
	ZeroMemory(&cc, sizeof(cc));
	pView->Create(nullptr, nullptr, WS_CHILD, rc, this, IDD_FORMVIEW2, &cc);
	pView->OnInitialUpdate();
	m_pFormView2 = pView;

	pView = (CView*)RUNTIME_CLASS(CFormView3)->CreateObject();
	ZeroMemory(&cc, sizeof(cc));
	pView->Create(nullptr, nullptr, WS_CHILD, rc, this, IDD_FORMVIEW3, &cc);
	pView->OnInitialUpdate();
	m_pFormView3 = pView;


	m_pFormView1->ShowWindow(SW_SHOW);
	mCombo.InsertString(0, _T("HTTP"));
	mCombo.InsertString(1, _T("DNS"));
	mCombo.InsertString(2, _T("ICMP"));
	mCombo.SetCurSel(0);
	
	CRect rect;
	mList.GetClientRect(&rect);
	mList.InsertColumn(0, _T("번호"), LVCFMT_CENTER, 50);
	mList.InsertColumn(1, _T("시각"), LVCFMT_LEFT, 100);
	mList.InsertColumn(2, _T("발신주소"), LVCFMT_LEFT, 200);
	mList.InsertColumn(3, _T("수신주소"), LVCFMT_LEFT, 200);
	mList.InsertColumn(4, _T("프로토콜"), LVCFMT_LEFT, 100);
	mList.InsertColumn(5, _T("패킷길이"), LVCFMT_LEFT, 100);
	mList.InsertColumn(6, _T("패킷정보"), LVCFMT_LEFT, rect.Width() - 750);

	std::cout << "Testing onInitDialog";

	CoreUnit* core_unit = new CoreUnit();

	core_unit->initializer();
	
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSubFormViewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSubFormViewDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSubFormViewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSubFormViewDlg::OnBnClickedButton1()

{
	//m_pFormView1->ShowWindow(SW_SHOW);
	//m_pFormView2->ShowWindow(SW_HIDE);
}

void CSubFormViewDlg::OnBnClickedButton2()
{
	//	m_pFormView2->ShowWindow(SW_SHOW);
	//m_pFormView1->ShowWindow(SW_HIDE);
}

void CSubFormViewDlg::OnCbnSelchangeCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = mCombo.GetCurSel();   //현재 선택된 항목의 인덱스 얻어옴
	CString str;

	mCombo.GetLBText(index, str); //인덱스에 해당하는 문자열 얻어옴

	switch (index)
	{
	case 0:
		m_pFormView1->ShowWindow(SW_SHOW);
		m_pFormView2->ShowWindow(SW_HIDE);
		m_pFormView3->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_pFormView2->ShowWindow(SW_SHOW);
		m_pFormView1->ShowWindow(SW_HIDE);
		m_pFormView3->ShowWindow(SW_HIDE);
		break;
	case 2:
		m_pFormView3->ShowWindow(SW_SHOW);
		m_pFormView2->ShowWindow(SW_HIDE);
		m_pFormView1->ShowWindow(SW_HIDE);
		break;
	default:
		break;
	}
}


HBRUSH CSubFormViewDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

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

	case CTLCOLOR_STATIC:

	{
		pDC->SetBkMode(TRANSPARENT);   // static text 배경색 투명

		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
