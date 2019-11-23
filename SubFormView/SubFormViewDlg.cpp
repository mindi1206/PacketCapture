
// SubFormViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SubFormView.h"
#include "SubFormViewDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include "CoreUnit.h"
#include <process.h>
#include <tchar.h>

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
//	ON_BN_CLICKED(IDC_BUTTON_START, &CSubFormViewDlg::OnBnClickedButtonStart)
//ON_BN_CLICKED(IDC_BUTTON_START, &CSubFormViewDlg::OnBnClickedButtonStart)
//ON_BN_CLICKED(IDC_BUTTON_START, &CSubFormViewDlg::OnBnClickedButtonStart)
ON_BN_CLICKED(IDC_BUTTON_START, &CSubFormViewDlg::OnBnClickedButtonStart)
ON_BN_CLICKED(IDC_BUTTON_STOP, &CSubFormViewDlg::OnBnClickedButtonStop)
ON_NOTIFY(LVN_INSERTITEM, IDC_LIST_PACKET, &CSubFormViewDlg::OnLvnInsertitemListPacket)
END_MESSAGE_MAP()


//==========================================
unsigned WINAPI listviewUpdater(void* arg) {
	std::cout << "subscribe packetCapture Event!\n";
	int idx = 0;
	CListCtrl* mlist = (CListCtrl*)GetDlgItem(GetParent((HWND)IDD_SUBFORMVIEW_DIALOG), IDC_LIST_PACKET);
	for (;;) {
		WaitForSingleObject(CoreUnit::newItemEventHandle, INFINITE);
		
		LVITEM item;
		item.mask = LVIF_TEXT;
		item.iItem = idx++;
		item.iSubItem = 0;

		SendMessage( (HWND)mlist, LVN_INSERTITEM,0, (LPARAM)&item);

		//mlist->InsertItem(idx++,_T("aa"));

		
		//mlist->InsertItem(idx++, _T("asdf"));

		//std::cout << CoreUnit::packetVector.back();
	}

	//CoreUnit

	return 0;
}
//==========================================

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
	mList.InsertColumn(0, _T("��ȣ"), LVCFMT_CENTER, 50);
	mList.InsertColumn(1, _T("�ð�"), LVCFMT_LEFT, 100);
	mList.InsertColumn(2, _T("�߽��ּ�"), LVCFMT_LEFT, 200);
	mList.InsertColumn(3, _T("�����ּ�"), LVCFMT_LEFT, 200);
	mList.InsertColumn(4, _T("��������"), LVCFMT_LEFT, 100);
	mList.InsertColumn(5, _T("��Ŷ����"), LVCFMT_LEFT, 100);
	mList.InsertColumn(6, _T("��Ŷ����"), LVCFMT_LEFT, rect.Width() - 750);

	


	std::cout << "Testing onInitDialog";

	CoreUnit* core_unit = CoreUnit::getInstance();

	core_unit->initializer();

	(HANDLE)_beginthreadex(NULL, 0, listviewUpdater, NULL, 0, NULL);

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = mCombo.GetCurSel();   //���� ���õ� �׸��� �ε��� ����
	CString str;

	mCombo.GetLBText(index, str); //�ε����� �ش��ϴ� ���ڿ� ����

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

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	switch (nCtlColor) {

	case CTLCOLOR_DLG:   // ���̾�α� ������ white��.
	{
		return (HBRUSH)GetStockObject(WHITE_BRUSH);
		break;
	}
	case CTLCOLOR_BTN:    // ��ư�� ������ ��������...
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);
	}

	case CTLCOLOR_STATIC:

	{
		pDC->SetBkMode(TRANSPARENT);   // static text ���� ����

		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	}

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

unsigned WINAPI startCaptureThread(void* arg) {
	std::cout << "startCapture!\n";

	CoreUnit* core_unit = CoreUnit::getInstance();
	core_unit->startCapture();

	return 0;
}



void CSubFormViewDlg::OnBnClickedButtonStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	CoreUnit::setThreadHandle((HANDLE)_beginthreadex(NULL, 0, startCaptureThread, NULL, 0, NULL));
	if (CoreUnit::captureThread == NULL) {
		std::cout << "capture thread init failed!\n";
		return;
	}
}
int idx = 0;
char* protocolParser(int protocol) {
	switch (protocol) //Check the Protocol and do accordingly...
	{
	case 1: //ICMP Protocol
		std::cout << "ICMP\n";
		return "ICMP";
	case 2: //IGMP Protocol
		std::cout << "IGMP\n";
		return "IGMP";
	case 6: //TCP Protocol
		std::cout << "tcp\n";
		return "TCP";
	case 17: //UDP Protocol
		std::cout << "UDP\n";
		return "UDP";
	default: //Some Other Protocol like ARP etc.
		return "UNKNOWN";
	}
}
void CSubFormViewDlg::OnBnClickedButtonStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	std::cout << "endCapture\n";
	CoreUnit* core_unit = CoreUnit::getInstance();
	core_unit->stopCapture();

	int nItemNum = mList.GetItemCount();

	std::vector<char*>::iterator iter;
	std::vector<char*> v = CoreUnit::packetVector;
	CString strProtocol;
	int i = 1;
	

	for (iter = v.begin(); iter != v.end(); ++iter,i++) {
		char* packet = *iter;
		IPV4_HDR* iphdr = (IPV4_HDR*)packet;
		int protocol = iphdr->ip_protocol;

		strProtocol = protocolParser(protocol);

		if(strProtocol.Compare(_T("UNKNOWN")) != 0 )
		{
			CString idxStr;
			idxStr.Format(_T("%d"), i);
			mList.InsertItem(nItemNum, idxStr);
			mList.SetItemText(nItemNum, 1, _T("time"));
			mList.SetItemText(nItemNum, 2, _T("srcIP"));
			mList.SetItemText(nItemNum, 3, _T("destIP"));
			mList.SetItemText(nItemNum, 4, strProtocol);
			mList.SetItemText(nItemNum, 5, _T("packetLen"));
			mList.SetItemText(nItemNum, 6, _T("packetInfo"));
		}
	}
}




void CSubFormViewDlg::OnLvnInsertitemListPacket(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
	
}
