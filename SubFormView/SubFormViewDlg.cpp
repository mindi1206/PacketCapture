
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
#include "CNicSelector.h"
#include <malloc.h>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About
//typedef struct ListData {
//	CString idx;
//	CString time;
//	CString destip;
//	CString srcip;
//	CString protocol;
//	CString packetlen;
//	CString packetinfo;
//
//	ListData(CString idx, CString time, CString destip, CString srcip, CString protocol, CString packetlen, CString packetinfo) {
//		this->idx = idx;
//		this->time = time;
//		this->destip = destip;
//		this->srcip = srcip;
//		this->protocol = protocol;
//		this->packetlen = packetlen;
//		this->packetinfo = packetinfo;
//	}
//}ListData;

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
	DDX_Control(pDX, IDC_EDIT_IP, m_EditIP);
	DDX_Control(pDX, IDC_EDIT_PORT, m_EditPORT);
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
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PACKET, &CSubFormViewDlg::OnLvnItemchangedListPacket)
ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CSubFormViewDlg::OnBnClickedButtonSearch)
ON_BN_CLICKED(IDC_BUTTON_RESET, &CSubFormViewDlg::OnBnClickedButtonReset)
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
	ZeroMemory(&cc, sizeof(cc));

	//m_pFormViewMain
	CView* pView = (CView*)RUNTIME_CLASS(CFormViewMain)->CreateObject();
	ZeroMemory(&cc, sizeof(cc));
	pView->Create(nullptr, nullptr, WS_CHILD, rc, this, IDD_FORMMAIN, &cc);
	pView->OnInitialUpdate();
	m_pFormViewMain = (CFormViewMain*)pView;

	pView = (CView*)RUNTIME_CLASS(CFormView1)->CreateObject();
	ZeroMemory(&cc, sizeof(cc));
	pView->Create(nullptr, nullptr, WS_CHILD, rc, this, IDD_FORMVIEW1, &cc);
	pView->OnInitialUpdate();
	m_pFormView1 = (CFormView1*)pView;


	pView = (CView*)RUNTIME_CLASS(CFormView2)->CreateObject();
	ZeroMemory(&cc, sizeof(cc));
	pView->Create(nullptr, nullptr, WS_CHILD, rc, this, IDD_FORMVIEW2, &cc);
	pView->OnInitialUpdate();
	m_pFormView2 = (CFormView2*)pView;

	pView = (CView*)RUNTIME_CLASS(CFormView3)->CreateObject();
	ZeroMemory(&cc, sizeof(cc));
	pView->Create(nullptr, nullptr, WS_CHILD, rc, this, IDD_FORMVIEW3, &cc);
	pView->OnInitialUpdate();
	m_pFormView3 = (CFormView3*)pView;
	
	m_pFormViewMain->ShowWindow(SW_SHOW);
	/*CView* pView = (CView*)RUNTIME_CLASS(CFormView1)->CreateObject();
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
	
	*/

	mCombo.InsertString(0, _T("---------"));
	mCombo.InsertString(1, _T("HTTP"));
	mCombo.InsertString(2, _T("DNS"));
	mCombo.InsertString(3, _T("ICMP"));
	mCombo.SetCurSel(0);
	
	CRect rect;
	mList.GetClientRect(&rect);
	mList.InsertColumn(0, _T("번호"), LVCFMT_CENTER, 50);
	mList.InsertColumn(1, _T("시각"), LVCFMT_LEFT, 100);
	mList.InsertColumn(2, _T("발신주소(출발)"), LVCFMT_LEFT, 200);
	mList.InsertColumn(3, _T("수신주소(도착)"), LVCFMT_LEFT, 200);
	mList.InsertColumn(4, _T("프로토콜"), LVCFMT_LEFT, 100);
	mList.InsertColumn(5, _T("패킷길이"), LVCFMT_LEFT, 100);
	mList.InsertColumn(6, _T("패킷정보"), LVCFMT_LEFT, rect.Width() - 750);
	// 보고서 보기에서 격자무늬를 출력한다.
	mList.SetExtendedStyle(mList.GetExtendedStyle() | LVS_EX_GRIDLINES);
	// 항목을 선택하면 줄 전체가 선택되도록 한다.
	mList.SetExtendedStyle(mList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	//initializer of main program
	/*CRect winRect;
	this->GetWindowRect(winRect);

	this->SetWindowPos(NULL, 0, 0, winRect.Width(), 720, SWP_NOREPOSITION);*/

	std::cout << "Testing onInitDialog";

	CoreUnit* core_unit = CoreUnit::getInstance();

	core_unit->initializer();

	CButton* stop = (CButton*)GetDlgItem(IDC_BUTTON_STOP);
	stop->EnableWindow(FALSE);


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

// 콤보박스 이벤트
void CSubFormViewDlg::OnCbnSelchangeCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = mCombo.GetCurSel();   //현재 선택된 항목의 인덱스 얻어옴
	CString str;

	mCombo.GetLBText(index, str); //인덱스에 해당하는 문자열 얻어옴
	
	std::vector<char*> v = CoreUnit::packetVector;
	std::vector<ListData> sList;
	std::vector<ListData>::iterator iter;

	CListCtrl select_List;
	int nItemNum;

	int cnt;
	int i = 0;
	// cnt = mList.GetItemCount();
	cnt = listdata.size();

	switch (index) {
		// HTTP 필터링
	case 0:
		m_pFormViewMain->ShowWindow(SW_SHOW);
		m_pFormView1->ShowWindow(SW_HIDE);
		m_pFormView2->ShowWindow(SW_HIDE);
		m_pFormView3->ShowWindow(SW_HIDE);

		mList.DeleteAllItems();

		nItemNum = mList.GetItemCount();
		
		i = 0;
		for (iter = listdata.begin(); iter != listdata.end(); iter++, i++) {
			ListData s = *iter;
			mList.InsertItem(i, s.idx);
			mList.SetItemText(i, 1, s.time);
			mList.SetItemText(i, 2, s.srcip);
			mList.SetItemText(i, 3, s.destip);
			mList.SetItemText(i, 4, s.protocol);
			mList.SetItemText(i, 5, s.packetlen);
			mList.SetItemText(i, 6, s.packetinfo);
		}

		Invalidate();
		break;

	case 1:
		m_pFormViewMain->ShowWindow(SW_HIDE);
		m_pFormView1->ShowWindow(SW_SHOW);
		m_pFormView2->ShowWindow(SW_HIDE);
		m_pFormView3->ShowWindow(SW_HIDE);

		for (int i = 0; i < cnt; i++) {
			CString s_num = listdata[i].idx; 
			CString s_time = listdata[i].time;
			CString s_destip = listdata[i].destip;
			CString s_srcip = listdata[i].srcip;
			CString s_protocol = listdata[i].protocol;
			CString s_packetlen = listdata[i].packetlen;
			CString s_packetinfo = listdata[i].packetinfo;

			int v_index = _ttoi(mList.GetItemText(i, 0)) - 1;

			// ip와 port 검색
			if (s_protocol == "TCP") {
				sList.push_back(ListData(s_num, s_time, s_srcip,s_destip, s_protocol, s_packetlen, s_packetinfo));
			}
		}

		mList.DeleteAllItems();
	
		nItemNum = mList.GetItemCount();
		i = 0;
		for (iter = sList.begin(); iter != sList.end(); iter++, i++) {
			ListData s = *iter;
			mList.InsertItem(i, s.idx);
			mList.SetItemText(i, 1, s.time);
			mList.SetItemText(i, 2, s.srcip);
			mList.SetItemText(i, 3, s.destip);
			mList.SetItemText(i, 4, s.protocol);
			mList.SetItemText(i, 5, s.packetlen);
			mList.SetItemText(i, 6, s.packetinfo);
		}

		Invalidate();

		break;

		// DNS 필터링
	case 2:
		m_pFormView2->ShowWindow(SW_SHOW);
		m_pFormViewMain->ShowWindow(SW_HIDE);
		m_pFormView1->ShowWindow(SW_HIDE);
		m_pFormView3->ShowWindow(SW_HIDE);


		for (int i = 0; i < cnt; i++) {
			CString s_num = listdata[i].idx;
			CString s_time = listdata[i].time;
			CString s_destip = listdata[i].destip;
			CString s_srcip = listdata[i].srcip;
			CString s_protocol = listdata[i].protocol;
			CString s_packetlen = listdata[i].packetlen;
			CString s_packetinfo = listdata[i].packetinfo;

			int v_index = _ttoi(mList.GetItemText(i, 0)) - 1;

			// ip와 port 검색
			if (s_protocol == "UDP") {
				sList.push_back(ListData(s_num, s_time, s_srcip, s_destip, s_protocol, s_packetlen, s_packetinfo));
			}
		}

		mList.DeleteAllItems();

		nItemNum = mList.GetItemCount();

		i = 0;

		for (iter = sList.begin(); iter != sList.end(); iter++, i++) {
			ListData s = *iter;
			mList.InsertItem(i, s.idx);
			mList.SetItemText(i, 1, s.time);
			mList.SetItemText(i, 2, s.srcip);
			mList.SetItemText(i, 3, s.destip);
			mList.SetItemText(i, 4, s.protocol);
			mList.SetItemText(i, 5, s.packetlen);
			mList.SetItemText(i, 6, s.packetinfo);
		}

		Invalidate();

		break;
		// ICMP 필터링
	case 3:
		m_pFormView3->ShowWindow(SW_SHOW);
		m_pFormViewMain->ShowWindow(SW_HIDE);
		m_pFormView2->ShowWindow(SW_HIDE);
		m_pFormView1->ShowWindow(SW_HIDE);

		for (int i = 0; i < cnt; i++) {
			CString s_num = listdata[i].idx;
			CString s_time = listdata[i].time;
			CString s_destip = listdata[i].destip;
			CString s_srcip = listdata[i].srcip;
			CString s_protocol = listdata[i].protocol;
			CString s_packetlen = listdata[i].packetlen;
			CString s_packetinfo = listdata[i].packetinfo;

			int v_index = _ttoi(mList.GetItemText(i, 0)) - 1;

			// ip와 port 검색
			if (s_protocol == "ICMP") {
				sList.push_back(ListData(s_num, s_time, s_srcip, s_destip, s_protocol, s_packetlen, s_packetinfo));
			}
		}

		mList.DeleteAllItems();

		nItemNum = mList.GetItemCount();
		i = 0;
		for (iter = sList.begin(); iter != sList.end(); iter++, i++) {
			ListData s = *iter;
			mList.InsertItem(i, s.idx);
			mList.SetItemText(i, 1, s.time);
			mList.SetItemText(i, 2, s.srcip);
			mList.SetItemText(i, 3, s.destip);
			mList.SetItemText(i, 4, s.protocol);
			mList.SetItemText(i, 5, s.packetlen);
			mList.SetItemText(i, 6, s.packetinfo);
		}

		Invalidate();
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

unsigned WINAPI startCaptureThread(void* arg) {
	std::cout << "startCapture!\n";
	NicDecisionParam* param = (NicDecisionParam*)arg;

	std::cout << "param.decision : " << param->decision << std::endl;
	std::cout << "param.local : " << param->local << std::endl;

	CoreUnit* core_unit = CoreUnit::getInstance();
	core_unit->startCapture(param->local, param->decision);

	return 0;
}



void CSubFormViewDlg::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//startBtn
	CoreUnit* coreUnit = CoreUnit::getInstance();
	coreUnit->clearPackerVector();
	mList.DeleteAllItems();
	listdata.clear();
	CButton* start = (CButton*)GetDlgItem(IDC_BUTTON_START);
	start->EnableWindow(FALSE);
	CButton* stop = (CButton*)GetDlgItem(IDC_BUTTON_STOP);
	stop->EnableWindow(TRUE);
	CNicSelector nicSelectorModal;

	//==
	struct hostent* local;
	char hostname[100];
	//Retrive the local hostname
	if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR)
	{
		printf("Error : %d", WSAGetLastError());
		return;
	}
	printf("\nHost name : %s \n", hostname);//현재 컴퓨터의 이름

	//Retrive the available IPs of the local host
	local = gethostbyname(hostname);
	printf("\nAvailable Network Interfaces : \n");
	if (local == NULL)
	{
		printf("Error : %d.\n", WSAGetLastError());
		return;
	}
	nicSelectorModal.setLocal(local);
	nicSelectorModal.setParent(this);
	//==
	nicDecision = -1;
	nicSelectorModal.DoModal();

	NicDecisionParam* param = (NicDecisionParam*)malloc(sizeof(NicDecisionParam));

	if (nicDecision == -1) {
		CButton* start = (CButton*)GetDlgItem(IDC_BUTTON_START);
		start->EnableWindow(TRUE);
		CButton* stop = (CButton*)GetDlgItem(IDC_BUTTON_STOP);
		stop->EnableWindow(FALSE);
		return;
	}
	param->local = local;
	param->decision = nicDecision;


	CoreUnit::setThreadHandle((HANDLE)_beginthreadex(NULL, 0, startCaptureThread, (void*)param, 0, NULL));
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::cout << "endCapture\n";
	CoreUnit* core_unit = CoreUnit::getInstance();
	core_unit->stopCapture();

	int nItemNum = mList.GetItemCount();

	std::vector<char*>::iterator iter;
	std::vector<char*> v = CoreUnit::packetVector;
	CString strProtocol;
	int i = 1;
	struct sockaddr_in sourceAddr;
	struct sockaddr_in destAddr;
	char buffer[65536];
	for (iter = v.begin(); iter != v.end(); ++iter,i++) {
		char* packet = *iter;
		IPV4_HDR* iphdr = (IPV4_HDR*)packet;
		//IPV4_HDR* myIphdr = (IPV4_HDR*)packet;
		int protocol = iphdr->ip_protocol;
		short length = ntohs(iphdr->ip_total_length);
		strProtocol = protocolParser(protocol);

		if(strProtocol.Compare(_T("UNKNOWN")) != 0 )
		{
			CString idxStr;
			idxStr.Format(_T("%d"), i);
			mList.InsertItem(i - 1, idxStr);
			// 시
			mList.SetItemText(i - 1, 1, _T("time"));

			//==================
			unsigned short iphdrlen = iphdr->ip_header_len * 4;

			TCP_HDR* tcpheader = (TCP_HDR*)(packet + iphdrlen);
			//==================
			memset(&sourceAddr, 0, sizeof(sourceAddr));
			sourceAddr.sin_addr.s_addr = iphdr->ip_srcaddr;
			const char* chPtrsrcIp = inet_ntoa(sourceAddr.sin_addr);
			CString srcIp = (CString)chPtrsrcIp;

			memset(&destAddr, 0, sizeof(destAddr));
			destAddr.sin_addr.s_addr = iphdr->ip_destaddr;
			const char* chPtrdestIp = inet_ntoa(destAddr.sin_addr);
			CString destIp = (CString)chPtrdestIp;
	
			mList.SetItemText(i - 1, 2, srcIp);
			mList.SetItemText(i - 1, 3, destIp);

			mList.SetItemText(i - 1, 4, strProtocol);

			memset(buffer, 0, sizeof(buffer));
			sprintf_s(buffer, sizeof(buffer), "%d", length);
			CString total_length = (CString)buffer;

			mList.SetItemText(i - 1, 5, total_length);
			mList.SetItemText(i - 1, 6, _T("packetInfo"));

			listdata.push_back(ListData(idxStr, _T("time"), srcIp, destIp, strProtocol, total_length, _T("packetInfo")));
		}
	}

	CButton* start = (CButton*)GetDlgItem(IDC_BUTTON_START);
	start->EnableWindow(TRUE);
	CButton* stop = (CButton*)GetDlgItem(IDC_BUTTON_STOP);
	stop->EnableWindow(FALSE);
}


void CSubFormViewDlg::OnLvnInsertitemListPacket(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 현재 선택된 아이템 번호를 얻어와서
	
	
	*pResult = 0;
	
}


void CSubFormViewDlg::OnLvnItemchangedListPacket(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nItem = pNMLV->iItem;
	// 해당 아이템 번호의 서브 아이템이 0인 항목 (= 번호)를 얻어옴
	// 이 번호를 이용해 벡터 접근
	int v_index = _ttoi(mList.GetItemText(nItem, 0)) - 1;
	unsigned short iphdrlen;


	std::vector<char*>::iterator iter;
	std::vector<char*> v = CoreUnit::packetVector;

	char* packet = v[v_index];
	IPV4_HDR* iphdr = (IPV4_HDR*)packet;
	iphdrlen = iphdr->ip_header_len * 4;

	TCP_HDR* tcpheader = (TCP_HDR*)(packet + iphdrlen);
	//m_pFormView1->TCP_SRCPORT.SetWindowTextW((CString)(char)ntohs(tcpheader->source_port));
	
	// 만약 콤보박스 선택이 HTTP 이면
	// m_pFormView1 에 출력

	int index = mCombo.GetCurSel();   //현재 선택된 항목의 인덱스 얻어옴
	
	CString str;

	CString destport;
	
	//WORD srcport;
	switch (index) {
		//MAIN
	case 0:
		break;
		// HTTP
	case 1:		
		str.Format(_T("%u"), ntohs(tcpheader->source_port));
		m_pFormView1->TCP_SRCPORT.SetWindowTextW(str);
		
		str.Format(_T("%u"), ntohs(tcpheader->dest_port));
		m_pFormView1->TCP_DESTPORT.SetWindowTextW(str);
		
		str.Format(_T("%u"), ntohl(tcpheader->sequence));
		m_pFormView1->TCP_SEQ.SetWindowTextW(str);
		
		str.Format(_T("%u"), ntohl(tcpheader->acknowledge));
		m_pFormView1->TCP_ACK.SetWindowTextW(str);
		
		str.Format(_T("%d BYTE"), (unsigned int)tcpheader->data_offset*4);
		m_pFormView1->TCP_HL.SetWindowTextW(str);

		str.Format(_T("%d"), (unsigned int)tcpheader->urg);
		m_pFormView1->TCP_U.SetWindowTextW(str);

		str.Format(_T("%d"), (unsigned int)tcpheader->ack);
		m_pFormView1->TCP_A.SetWindowTextW(str);
		str.Format(_T("%d"), (unsigned int)tcpheader->psh);
		m_pFormView1->TCP_P.SetWindowTextW(str);
		str.Format(_T("%d"), (unsigned int)tcpheader->rst);
		m_pFormView1->TCP_R.SetWindowTextW(str);
		str.Format(_T("%d"), (unsigned int)tcpheader->syn);
		m_pFormView1->TCP_S.SetWindowTextW(str);
		str.Format(_T("%d"), (unsigned int)tcpheader->fin);
		m_pFormView1->TCP_F.SetWindowTextW(str);

		str.Format(_T("%d"), ntohs(tcpheader->window));
		m_pFormView1->TCP_WINDOW.SetWindowTextW(str);

		str.Format(_T("%d"), ntohs(tcpheader->checksum));
		m_pFormView1->TCP_CHEKSUM.SetWindowTextW(str);

		str.Format(_T("%d"),tcpheader->urgent_pointer);
		m_pFormView1->TCP_URG.SetWindowTextW(str);

		//IP Header
		str.Format(_T("%d"), iphdr->ip_version);
		m_pFormView1->IPVersion.SetWindowTextW(str);

		str.Format(_T("%d"), iphdr->ip_header_len);
		m_pFormView1->IHL.SetWindowTextW(str);
		
		str.Format(_T("%d"), iphdr->ip_tos);
		m_pFormView1->TOS.SetWindowTextW(str);
		
		str.Format(_T("%d"), iphdr->ip_total_length);
		m_pFormView1->TotalLength.SetWindowTextW(str);

		str.Format(_T("%d"), iphdr->ip_id);
		m_pFormView1->Identification.SetWindowTextW(str);

		str.Format(_T("%d"), iphdr->ip_more_fragment);
		m_pFormView1->MoreFrag.SetWindowTextW(str);

		str.Format(_T("%d"), iphdr->ip_dont_fragment);
		m_pFormView1->DontFrag.SetWindowTextW(str);

		str.Format(_T("%d"), iphdr->ip_reserved_zero);
		m_pFormView1->ReservedZero.SetWindowTextW(str);

		str.Format(_T("%d"), iphdr->ip_frag_offset1);
		m_pFormView1->FragOffset.SetWindowTextW(str);

		str.Format(_T("%d"), iphdr->ip_ttl);
		m_pFormView1->Protocol.SetWindowTextW(str);

		str.Format(_T("%d"), iphdr->ip_checksum);
		m_pFormView1->HeaderChecksum.SetWindowTextW(str);

		str.Format(_T("%d"), iphdr->ip_srcaddr);
		m_pFormView1->SourceAddress.SetWindowTextW(str);

		str.Format(_T("%d"), iphdr->ip_destaddr);
		m_pFormView1->DestinationAddress.SetWindowTextW(str);
		

		break;
		// DNS
	case 2:
		//m_pFormView2->ShowWindow(SW_SHOW);

		break;
		// ICMP
	case 3:
		//m_pFormView3->ShowWindow(SW_SHOW);
	
		break;
	default:
		break;
	}

	CString strProtocol;
	int i = 1;
	struct sockaddr_in source, dest;
	
	*pResult = 0;
}


void CSubFormViewDlg::OnBnClickedButtonSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString ip_str, port_str;
	
	std::vector<char*> v = CoreUnit::packetVector;
	std::vector<char*> search_v;
	std::vector<int> filter;

	m_EditIP.GetWindowTextW(ip_str);
	m_EditPORT.GetWindowTextW(port_str);

	int cnt;
	CString strSearch_destip, strSearch_srcip;
	cnt = mList.GetItemCount();
	printf("cnt: %d\n", cnt);

	std::vector<ListData> sList;

	CListCtrl select_List;
	
	if (ip_str != "" || port_str != "") {
		for (int i = 0; i < cnt; i++) {
			CString s_num = mList.GetItemText(i, 0);
			CString s_time = mList.GetItemText(i, 1);
			CString s_srcip = mList.GetItemText(i, 2);
			CString s_destip = mList.GetItemText(i, 3);			
			CString s_protocol = mList.GetItemText(i, 4);
			CString s_packetlen = mList.GetItemText(i, 5);
			CString s_packetinfo = mList.GetItemText(i, 6);
			CString s_destport, s_srcport;
			

			int v_index = _ttoi(mList.GetItemText(i, 0)) - 1;
			unsigned short iphdrlen;

			std::vector<char*> v = CoreUnit::packetVector;

			char* packet = v[v_index];

			IPV4_HDR* iphdr = (IPV4_HDR*)packet;
			iphdrlen = iphdr->ip_header_len * 4;
			TCP_HDR* tcpheader = (TCP_HDR*)(packet + iphdrlen);

			s_srcport.Format(_T("%u"), ntohs(tcpheader->source_port));
			s_destport.Format(_T("%u"), ntohs(tcpheader->dest_port));

			// ip와 port 검색
			if (ip_str != "" && port_str != "") {
				if ( (s_destip == ip_str || s_srcip == ip_str) && (s_srcport == port_str || s_destport == port_str)) {
					sList.push_back(ListData(s_num, s_time, s_srcip, s_destip, s_protocol, s_packetlen, s_packetinfo));
				}
			}
			// ip 또는 port 검색
			else {
				if (s_destip == ip_str || s_srcip == ip_str) {
					//printf("%d: %s %s %s\n", _ttoi(s_num), s_destip, s_srcip, s_protocol);
					sList.push_back(ListData(s_num, s_time, s_srcip, s_destip, s_protocol, s_packetlen, s_packetinfo));
				}
				else if (s_srcport == port_str || s_destport == port_str) {
					sList.push_back(ListData(s_num, s_time, s_srcip, s_destip, s_protocol, s_packetlen, s_packetinfo));
				}
			}
		}
	}

	
	mList.DeleteAllItems();
	std::vector<ListData>::iterator iter;

	int nItemNum = mList.GetItemCount();
	int i = 0;

	for (iter = sList.begin(); iter != sList.end(); iter++, i++) {
		ListData s = *iter;
		
		printf("%d: %s %s %s\n", _ttoi(s.idx), s.destip, s.srcip, s.protocol);
		mList.InsertItem(i, s.idx);
		
		mList.SetItemText(i, 1, s.time);

		mList.SetItemText(i, 2, s.srcip);
		mList.SetItemText(i, 3, s.destip);

		mList.SetItemText(i, 4, s.protocol);
		mList.SetItemText(i, 5, s.packetlen);
		mList.SetItemText(i, 6, s.packetinfo);
		
	}
	Invalidate();
	
}


void CSubFormViewDlg::OnBnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mList.DeleteAllItems();
	
	m_EditIP.SetWindowTextW(_T(""));
	m_EditPORT.SetWindowTextW(_T(""));
																	
	OnCbnSelchangeCombo();

	//int nItemNum = mList.GetItemCount();

	//std::vector<char*>::iterator iter;
	//std::vector<char*> v = CoreUnit::packetVector;

	//CString strProtocol;

	//int i = 1;
	//struct sockaddr_in source, dest, sourceAddr, destAddr;
	//char buffer[65536];
	//for (iter = v.begin(); iter != v.end(); ++iter, i++) {
	//	char* packet = *iter;
	//	IPV4_HDR* iphdr = (IPV4_HDR*)packet;
	//	//IPV4_HDR* myIphdr = (IPV4_HDR*)packet;
	//	int protocol = iphdr->ip_protocol;
	//	short length = ntohs(iphdr->ip_total_length);

	//	strProtocol = protocolParser(protocol);

	//	if (strProtocol.Compare(_T("UNKNOWN")) != 0)
	//	{
	//		CString idxStr;
	//		idxStr.Format(_T("%d"), i);
	//		mList.InsertItem(nItemNum, idxStr);
	//		// 시
	//		mList.SetItemText(nItemNum, 1, _T("time"));
	//	
	//		unsigned short iphdrlen = iphdr->ip_header_len * 4;

	//		TCP_HDR* tcpheader = (TCP_HDR*)(packet + iphdrlen);
	//		memset(&sourceAddr, 0, sizeof(sourceAddr));
	//		sourceAddr.sin_addr.s_addr = iphdr->ip_srcaddr;
	//		const char* chPtrsrcIp = inet_ntoa(sourceAddr.sin_addr);
	//		CString srcIp = (CString)chPtrsrcIp;

	//		mList.SetItemText(nItemNum, 2, srcIp);
	//
	//		memset(&destAddr, 0, sizeof(destAddr));
	//		destAddr.sin_addr.s_addr = iphdr->ip_destaddr;
	//		const char* chPtrdestIp = inet_ntoa(destAddr.sin_addr);
	//		CString destIp = (CString)chPtrdestIp;
	//		
	//
	//		mList.SetItemText(nItemNum, 3, destIp);

	//		mList.SetItemText(nItemNum, 4, strProtocol);

	//		memset(&buffer, 0, sizeof(buffer));
	//		sprintf_s(buffer, sizeof(buffer), "%d", length);
	//		CString total_length = (CString)buffer;
	//		mList.SetItemText(nItemNum, 5, total_length);

	//		mList.SetItemText(nItemNum, 6, _T("packetInfo"));
	//	}
	//}
}
void CSubFormViewDlg::setNicDecision(int decision) {
	this->nicDecision = decision;
}