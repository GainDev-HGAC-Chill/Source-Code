#include "stdafx.h"
#include "GMTool.h"
#include "PgUserListMgr.h"
#include "PgNetwork.h"
#include "GMToolDlg.h"
#include "Page_QA.h"


// CPage_QA 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPage_QA, CPropertyPage)

CPage_QA::CPage_QA()
	: CPropertyPage(CPage_QA::IDD)
{

}

CPage_QA::~CPage_QA()
{
}

void CPage_QA::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USERLIST, m_listUserList);
}


BEGIN_MESSAGE_MAP(CPage_QA, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_QA_REFRESH, &CPage_QA::OnBnClickedBtnQaRefresh)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_QA_CONNECT, &CPage_QA::OnBnClickedBtnQaConnect)
END_MESSAGE_MAP()


// CPage_QA 메시지 처리기입니다.
BOOL CPage_QA::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	m_listUserList.SetExtendedStyle(
		LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_INFOTIP |
		LVS_EX_LABELTIP | LVS_EX_GRIDLINES);// | LVS_EX_SUBITEMIMAGES);
	m_listUserList.InsertColumn(0, L"ID", LVCFMT_CENTER, 80);
	m_listUserList.InsertColumn(1, L"Character", LVCFMT_CENTER, 80);

	SetTimer(0, 200, 0);

	return true;
}

void CPage_QA::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0)
	{
		if (m_guidRefresh != g_kUserListMgr.m_guidRefresh)
		{
			m_guidRefresh = g_kUserListMgr.m_guidRefresh;

			// 데이터 받기.
			m_listUserList.DeleteAllItems();

			int iRow = 0;
			MAP_PLAYERDATA::iterator itr;
			for (itr = g_kUserListMgr.m_kPlayerData.begin() ; 
				itr != g_kUserListMgr.m_kPlayerData.end() ;
				++itr, ++iRow)
			{
				SOutsidePlayerData kInfo = itr->second;
				
				int nItemInserted = m_listUserList.InsertItem(
					LVIF_PARAM | LVIF_TEXT, iRow, kInfo.szAccountID,
					INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK, 0,
					(LPARAM)&(itr->second) );

				UINT uiMask = LVIF_TEXT;
				int iCol = 1;
				m_listUserList.SetItem(nItemInserted, iCol++, uiMask, kInfo.szCharName, 0, 0, 0, 0, 0);
			}
		}
	}
}

void CPage_QA::OnBnClickedBtnQaRefresh()
{
	g_kUserListMgr.ReqRefreshUserList();
}


void CPage_QA::OnBnClickedBtnQaConnect()
{
	int iSelected = m_listUserList.GetSelectionMark();
	if (iSelected != -1)
	{
		SOutsidePlayerData* pkSelectedUser = reinterpret_cast<SOutsidePlayerData*>( m_listUserList.GetItemData(iSelected) );

		std::wstring wstrContents;
		wstrContents.resize(256);
		if ( GetDlgItemText(IDC_EDIT_QA_CHAT, &wstrContents.at(0), 256) == 0 )
		{
			return;
		}
		size_t iZero = wstrContents.find(L'\0');
		if (iZero > 0)
		{
			wstrContents.resize(iZero);
		}

		// 진정 요청.
		CEL::CPacket kPacket(PT_O_G_REQ_GMCOMMAND, EGMC_SENDMSG_TO_USER);
		kPacket.Push(g_kNetwork.m_usChannel);
		std::wstring wstrGMID = g_kNetwork.m_wGMID;
		kPacket.Push(wstrGMID);		// GM ID
		kPacket.Push(wstrContents);				// Contents
		kPacket.Push(*pkSelectedUser);			// UserData

		g_kNetwork.SendToChannel(kPacket);

		std::wstring wstrOut = wstrGMID;
		wstrOut += L": ";
		wstrOut += wstrContents;
		AddMsg(wstrOut);
	}
}

void CPage_QA::AddMsg(std::wstring wstrContent, bool bReturn)
{
	std::wstring wstrOut = wstrContent;
	if (bReturn)
	{
		wstrOut += L'\r';
		wstrOut += L'\n';
	}
	CString kString;
	GetDlgItemText(IDC_EDIT_QA_LOG, kString);
	kString += wstrOut.c_str();
	SetDlgItemText(IDC_EDIT_QA_LOG, kString);
	CEdit* pkEdit = ((CEdit*)GetDlgItem(IDC_EDIT_QA_LOG));
	if (pkEdit)
	{
		int iLine = pkEdit->GetLineCount();
		pkEdit->LineScroll(iLine);
	}
}
