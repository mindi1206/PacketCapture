// CNicSelector.cpp: 구현 파일
//

#include "stdafx.h"
#include "SubFormView.h"
#include "CNicSelector.h"
#include "afxdialogex.h"


// CNicSelector 대화 상자

IMPLEMENT_DYNAMIC(CNicSelector, CDialogEx)

CNicSelector::CNicSelector(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NIC_SELECTOR, pParent)
{

}


CNicSelector::~CNicSelector()
{
}

void CNicSelector::setLocal(struct hostent* param) {
	this->local = param;
}
BOOL CNicSelector::OnInitDialog() {
	CDialogEx::OnInitDialog();
	//TODO 초기화 작업 실시
	CRect rect;
	mNicList.GetClientRect(&rect);

	mNicList.InsertColumn(0, _T("인터페이스 번호"), LVCFMT_CENTER, 100);
	mNicList.InsertColumn(1, _T("IP주소"), LVCFMT_LEFT, 300);
	mNicList.SetExtendedStyle(mNicList.GetExtendedStyle() | LVS_EX_GRIDLINES);
	mNicList.SetExtendedStyle(mNicList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	//========NIC Selector
	struct in_addr addr;
	
	for (int i = 0; local->h_addr_list[i] != 0; ++i)
	{//감지 가능한 인터페이스 목록을 출력
		memcpy(&addr, local->h_addr_list[i], sizeof(struct in_addr));
		CString idxStr;
		idxStr.Format(_T("%d"), i);
		mNicList.InsertItem(i,idxStr);
		CString addrStr = (CString)inet_ntoa(addr);
		mNicList.SetItemText(i, 1, addrStr);
	}

	//scanf_s("%d", &in);//감지할 인터페이스를 사용자로부터 입력받음
	//========

	return true;
}

void CNicSelector::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_NIC, mNicList);
	DDX_Control(pDX, IDC_EDIT1, mEditUserDecision);
}


BEGIN_MESSAGE_MAP(CNicSelector, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_NIC, &CNicSelector::OnLvnItemchangedListNic)
	ON_BN_CLICKED(IDOK, &CNicSelector::OnBnClickedOk)
END_MESSAGE_MAP()


// CNicSelector 메시지 처리기


void CNicSelector::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CNicSelector::OnLvnItemchangedListPacket(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CNicSelector::OnLvnItemchangedListNic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nItem = pNMLV->iItem;
	// 해당 아이템 번호의 서브 아이템이 0인 항목 (= 번호)를 얻어옴
	// 이 번호를 이용해 벡터 접근
	int v_index = _ttoi(mNicList.GetItemText(nItem, 0)) - 1;
	v_index++;
	CString idx;
	idx.Format(_T("%d"),v_index);
	mEditUserDecision.SetWindowTextW( idx );
	*pResult = 0;
}


void CNicSelector::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int decision = 0;
	CString decisionStr;
	mEditUserDecision.GetWindowTextW(decisionStr);
	decision = _ttoi(decisionStr);
	parentDialog->setNicDecision(decision);
	CDialogEx::OnOK();
}
void CNicSelector::setParent(CSubFormViewDlg* parent) {
	this->parentDialog = parent;
}
