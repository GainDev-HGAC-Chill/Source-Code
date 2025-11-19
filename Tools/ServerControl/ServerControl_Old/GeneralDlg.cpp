// GeneralDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ServerControl.h"
#include "PgNetwork.h"
#include "PgGameServerMgr.h"
#include "PgRecvFromManagementServer.h"
#include "GeneralDlg.h"
#include "PgSendWrapper.h"
#include "Lohengrin/PgRealmManager.h"
// CGeneralDlg 대화 상자입니다.

CGeneralDlg* g_pkGeneralDlg = NULL;


IMPLEMENT_DYNAMIC(CGeneralDlg, CDialog)

CGeneralDlg::CGeneralDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGeneralDlg::IDD, pParent)
{

}

CGeneralDlg::~CGeneralDlg()
{
	g_kNetwork.DisConnectServer();
}

void CGeneralDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SERVER, m_listServer);
	DDX_Control(pDX, IDC_CONFIRM_KILL, m_bKillConfirm);
	DDX_Control(pDX, IDC_BTN_PROCESSKILL, m_KillButton);
	DDX_Control(pDX, IDD_TreeView, m_kTree);
}


BEGIN_MESSAGE_MAP(CGeneralDlg, CDialog)
	ON_WM_TIMER()
	ON_NOTIFY (LVN_COLUMNCLICK, IDC_LIST_SERVER, OnColumnclickServerList)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CGeneralDlg::OnBnClickedBtnRefresh)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_SERVER, &CGeneralDlg::OnNMCustomdrawListServer)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CGeneralDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CGeneralDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_ON, &CGeneralDlg::OnBnClickedBtnOn)
	ON_BN_CLICKED(IDC_BTN_OFF, &CGeneralDlg::OnBnClickedBtnOff)
	ON_BN_CLICKED(IDC_BTN_PROCESSKILL, &CGeneralDlg::OnBnClickedBtnProcesskill)
	ON_BN_CLICKED(IDC_CHECK_USEBEEP, &CGeneralDlg::OnBnClickedCheckUsebeep)
	ON_BN_CLICKED(IDC_CONFIRM_KILL, &CGeneralDlg::OnBnClickedConfirmKill)
	ON_COMMAND(ID_FILE_EXIT, &CGeneralDlg::OnFileExit)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_NOTIFY(TVN_SELCHANGED, IDD_TreeView, &CGeneralDlg::OnTvnSelchangedTreeview)
END_MESSAGE_MAP()

#include <assert.h>
// CGeneralDlg 메시지 처리기입니다.
BOOL CGeneralDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_menu.LoadMenu(IDR_MENU2);
	SetMenu(&m_menu);

	RECT kSize;
	GetWindowRect(&kSize);

	m_listServer.SetExtendedStyle(
		LVS_EX_SIMPLESELECT | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_INFOTIP |
		LVS_EX_LABELTIP | LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);
		//LVS_EX_FULLROWSELECT);

    m_listServer.InsertColumn(0, L"Server Name", LVCFMT_CENTER, 120);
    m_listServer.InsertColumn(1, L"Type", LVCFMT_CENTER, 120);
    m_listServer.InsertColumn(2, L"Machin IP", LVCFMT_CENTER, 100);
    m_listServer.InsertColumn(3, L"Server No", LVCFMT_CENTER, 70);
    m_listServer.InsertColumn(4, L"Channel", LVCFMT_CENTER, 60);
    m_listServer.InsertColumn(5, L"Connect", LVCFMT_CENTER, 60);
    m_listServer.InsertColumn(6, L"Process", LVCFMT_CENTER, 60);
    m_listServer.InsertColumn(7, L"IP", LVCFMT_CENTER, 100);
    m_listServer.InsertColumn(8, L"Port", LVCFMT_CENTER, 40);

	m_kSelectServerList.clear();

	// Create ImageList
	m_kImageList.Create(16, 16, ILC_COLOR16, 2, 0);
	HICON hIcon;
	VERIFY((hIcon = AfxGetApp()->LoadIcon(IDI_STATE_X)) != 0);
	m_kImageList.Add(hIcon);
	VERIFY((hIcon = AfxGetApp()->LoadIcon(IDI_STATE_O)) != 0);
	m_kImageList.Add(hIcon);
	m_kImageList.Add(hIcon);
	m_listServer.SetImageList(&m_kImageList, LVSIL_SMALL);

	// Control Level
	const int iControlLevel = g_kGameServerMgr.iControlLevel();
	if( DEFAULT_VIEWERLELVEL != iControlLevel )
	{
		CWnd* pkWnd = GetDlgItem(IDC_BTN_ON);
		if (pkWnd) pkWnd->ShowWindow(SW_HIDE);
		pkWnd = GetDlgItem(IDC_BTN_ON);
		if (pkWnd) pkWnd->ShowWindow(SW_HIDE);
		pkWnd = GetDlgItem(IDC_BTN_OFF);
		if (pkWnd) pkWnd->ShowWindow(SW_HIDE);
		pkWnd = GetDlgItem(IDC_BTN_PROCESSKILL);
		if (pkWnd) pkWnd->ShowWindow(SW_HIDE);
	}

	m_hSelectTreeItem = NULL;

	SetTreeView();

	return TRUE;
}

void CGeneralDlg::OnTimer(UINT_PTR nIDEvent)
{
	// 시간 지정하면 Refresh
	// 사용 법은 SetTimer(0, 300, 0);
	if (nIDEvent == 0)
	{
		CEL::CPacket kPacket(PT_MCTRL_TERMI_MMS_REQ_SERVERLIST);
		g_kNetwork.Send(kPacket);
	}
	// 자동으로 킬 되는 Refresh
	else if (nIDEvent == 1)
	{
		KillTimer(1);
		CEL::CPacket kPacket(PT_MCTRL_TERMI_MMS_REQ_SERVERLIST);
		g_kNetwork.Send(kPacket);
	}
}

void CGeneralDlg::OnColumnclickServerList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = reinterpret_cast<NM_LISTVIEW*>(pNMHDR);

	SORT_BY sortBy;
	sortBy = (SORT_BY)(pNMListView->iSubItem + 1);

	if (m_sortedBy == sortBy)
		m_sortedBy = static_cast<SORT_BY>(-sortBy);
	else
		m_sortedBy = sortBy;

	m_listServer.SortItems(CompareServerList, m_sortedBy);

	*pResult = 0;
}

int CALLBACK CGeneralDlg::CompareServerList(LPARAM lParam1, LPARAM lParam2, 
                                      LPARAM lParamSort)
{
	bool    bComplementResult;
	int     result = 0;

	if (lParamSort < 0)
	{
		lParamSort = -lParamSort;
		bComplementResult = true;
	}
	else
	{
		bComplementResult = false;
	}


	SGameServerInfo kServerInfo1, kServerInfo2;

	int iServerIdx = (int)lParam1;
	bool bCheck1 = g_kGameServerMgr.GetServerInfo(iServerIdx, kServerInfo1);
	iServerIdx = (int)lParam2;
	bool bCheck2 = g_kGameServerMgr.GetServerInfo(iServerIdx, kServerInfo2);

	// 두개다 찾았으면 깨지지 않은 데이터다.
	// 두개 데이터를 비교하면서 정렬 해주자.
	// 리턴값이 0초과면 왼쪽값이 크고 0이면 같고 0보다 작으면 작다.
	if (bCheck1 && bCheck2)
	{
		int asdf = 0;
		switch (lParamSort)
		{
		case SERVER_NAME:
			result = _tcscmp(kServerInfo1.strName.c_str(), kServerInfo2.strName.c_str());
			break;
		case SERVER_TYPE:
			result = kServerInfo1.nServerType - kServerInfo2.nServerType;
			break;
		case MACHINIP:
			result = _tcscmp(kServerInfo1.strMachinIP.c_str(), kServerInfo2.strMachinIP.c_str());
			break;
		case SERVER_NO:
			result = kServerInfo1.nServerNo - kServerInfo2.nServerNo;
			break;
		case CHANNEL:
			result = kServerInfo1.nChannel - kServerInfo2.nChannel;
			break;
		case CONNECT:
			result = (kServerInfo1.bReadyToService && !kServerInfo2.bReadyToService) ? 1 : -1;
			break;
		case PROCESS:
			result = (kServerInfo1.bProcessHandle && !kServerInfo2.bProcessHandle) ? 1 : -1;
			//result = (kServerInfo1.bRunProcess && !kServerInfo2.bRunProcess) ? 1 : -1;
			break;
		case IP:
			result = _tcscmp(kServerInfo1.addrServerBind.StrIP().c_str(), kServerInfo2.addrServerBind.StrIP().c_str());
			break;
		case PORT:
			result = kServerInfo1.addrServerBind.wPort - kServerInfo2.addrServerBind.wPort;
			break;
		default :
			break;
		}
	}

	if (bComplementResult)
	{
		result = -result;
	}

	return result;
}

std::wstring GetServerTypeName(short nServerType)
{
	std::wstring wstrName = L"";
	switch(nServerType)
	{
	case CEL::ST_NONE : wstrName = L"NONE"; break;
	case CEL::ST_CENTER : wstrName = L"CENTER"; break;
	case CEL::ST_MAP : wstrName = L"MAP"; break;
	case CEL::ST_LOGIN : wstrName = L"LOGIN"; break;
	case CEL::ST_SWITCH : wstrName = L"SWITCH"; break;
	case CEL::ST_MACHINE_CONTROL : wstrName = L"M_CTRL"; break;
//	case CEL::ST_RELAY : wstrName = L"RELAY"; break;
//	case CEL::ST_USER : wstrName = L"USER"; break;
	case CEL::ST_ITEM : wstrName = L"ITEM"; break;
//	case CEL::ST_CONTENTS : wstrName = L"CONTENTS"; break;
	case CEL::ST_LOG : wstrName = L"LOG"; break;
//	case CEL::ST_MMAP : wstrName = L"MMAP"; break;
	case CEL::ST_GMSERVER : wstrName = L"GMSERVER"; break;
	case CEL::ST_IMMIGRATION : wstrName = L"IMM"; break;
	default:
		{
			wstrName = L"UNKNOWN";
		}break;
	}

	return wstrName;
}

//#define USE_SELECT_BACKUP
//bool CGeneralDlg::ServerRefresh()
bool CGeneralDlg::ServerRefresh(const ContServerInfo& rkServerList)
{
	if (!m_listServer)
	{
		return false;
	}
	// 선택 했던놈을 빽업 한다.
#ifdef USE_SELECT_BACKUP
	bool bSelected = false;
	int iSelected = m_listServer.GetSelectionMark();
	SGameServerInfo kSelectedServer;
	if (iSelected != -1)
	{
		SGameServerInfo* pkSelectedServer = (int)m_listServer.GetItemData(iSelected);
		memcpy_s(&kSelectedServer, sizeof(SGameServerInfo), pkSelectedServer, sizeof(SGameServerInfo));
		bSelected = true;
	}

	// 체크 했던놈을 빽업.
	std::vector<SGameServerInfo*> kCheckedList;
	for (int i=0 ; i<m_listServer.GetItemCount() ; i++)
	{
		if (m_listServer.GetCheck(i))
		{
			SGameServerInfo* pkServer = reinterpret_cast<SGameServerInfo*>( m_listServer.GetItemData(i) );
			kCheckedList.push_back(pkServer);
		}
	}
#endif

	// Data Setting
	m_listServer.DeleteAllItems();

	int iRow = 0;

//	ContServerInfo rkServerList;
//	g_kGameServerMgr.GetServerList(rkServerList);

	ContServerInfo::const_iterator iter = rkServerList.begin();
	while(iter != rkServerList.end())
	{
		const SGameServerInfo& rkServerInfo = (*iter).second;
		const int iContIdx = (int)((*iter).first);

		wchar_t wcString[1024] = {0, };
		int iImgIdx = rkServerInfo.bProcessHandle && rkServerInfo.bReadyToService;

		int nItemInserted = m_listServer.InsertItem(
			LVIF_IMAGE | LVIF_PARAM | LVIF_TEXT, iRow + 1, rkServerInfo.strName.c_str(),
			INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK, iImgIdx,
			(LPARAM)iContIdx );

		UINT uiMask = LVIF_TEXT ;

		int iCol = 0;
		// ServerName
		m_listServer.SetItem(nItemInserted, iCol++, uiMask, rkServerInfo.strName.c_str(), 0, 0, 0, 0, 0);
		// ServerTypeName
		m_listServer.SetItem(nItemInserted, iCol++, uiMask, GetServerTypeName(rkServerInfo.nServerType).c_str(), 0, 0, 0, 0, 0);
		//
		m_listServer.SetItem(nItemInserted, iCol++, uiMask, rkServerInfo.strMachinIP.c_str(), 0, 0, 0, 0, 0);
		//
		_ltot_s(rkServerInfo.nServerNo, wcString, 10);
		m_listServer.SetItem(nItemInserted, iCol++, uiMask, wcString, 0, 0, 0, 0, 0);
		//
		_ltot_s(rkServerInfo.nChannel, wcString, 10);
		m_listServer.SetItem(nItemInserted, iCol++, uiMask, wcString, 0, 0, 0, 0, 0);
		//
		wcscpy_s(wcString, rkServerInfo.bReadyToService ? L"O\0": L"X\0");
		m_listServer.SetItem(nItemInserted, iCol++, uiMask, wcString, 0, 0, 0, 0, 0);
		//
		wcscpy_s(wcString, rkServerInfo.bProcessHandle ? L"O\0": L"X\0");
		m_listServer.SetItem(nItemInserted, iCol++, uiMask, wcString, 0, 0, 0, 0, 0);
		//wcscpy_s(wcString, rkServerInfo.bRunProcess ? L"O\0": L"X\0");
		//m_listServer.SetItem(nItemInserted, iCol++, uiMask, wcString, 0, 0, 0, 0, 0);
		//
		m_listServer.SetItem(nItemInserted, iCol++, uiMask, rkServerInfo.addrServerBind.StrIP().c_str(), 0, 0, 0, 0);
		//
		_ltot_s(rkServerInfo.addrServerBind.wPort, wcString, 10);
		m_listServer.SetItem(nItemInserted, iCol++, uiMask, wcString, 0, 0, 0, 0);

		++iter;
	}

#ifdef USE_SELECT_BACKUP
	// 예전에 선택 되었던 녀석을 선택하게 해주자.
	if (bSelected)
	{
		for (int i=0 ; i<m_listServer.GetItemCount() ; i++)
		{
			SGameServerInfo* pkAfterServer = reinterpret_cast<SGameServerInfo*>( m_listServer.GetItemData(i) );

			if (pkAfterServer->nChannel == kSelectedServer.nChannel &&
				pkAfterServer->nServerNo == kSelectedServer.nServerNo)
			{
				m_listServer.SetSelectionMark(i);
				m_listServer.SetItemState(i, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
				m_listServer.SetFocus();
				break;
			}
		}
	}

	// 체크 했던 녀석을 다시 체크하게 해주자.
	std::vector<SGameServerInfo*>::iterator itr_check;
	for (itr_check = kCheckedList.begin() ;
		itr_check != kCheckedList.end() ;
		++itr_check)
	{
		for (int i=0 ; i<m_listServer.GetItemCount() ; i++)
		{
			SGameServerInfo* pkAfterServer = reinterpret_cast<SGameServerInfo*>( m_listServer.GetItemData(i) );

			if (pkAfterServer->nChannel == (*itr_check)->nChannel &&
				pkAfterServer->nServerNo == (*itr_check)->nServerNo)
			{
				m_listServer.SetCheck(i);
				continue;
			}
		}
	}
#endif
	

	return true;
}

bool CGeneralDlg::AddMsg(int nID, std::wstring wstrContent, bool bReturn)
{
	return false;
	std::wstring wstrOut = wstrContent;
	if (bReturn)
	{
		wstrOut += L'\r';
		wstrOut += L'\n';
	}
	CString kString;
	GetDlgItemText(nID, kString);
	kString += wstrOut.c_str();
	SetDlgItemText(nID, kString);
	CEdit* pkEdit = ((CEdit*)GetDlgItem(nID));
	if (pkEdit)
	{
		int iLine = pkEdit->GetLineCount();
		pkEdit->LineScroll(iLine);
	}

	return true;
}

void CGeneralDlg::OnBnClickedBtnRefresh()
{
	KillTimer(0);

	CEL::CPacket kPacket(PT_MCTRL_TERMI_MMS_REQ_SERVERLIST);
	g_kNetwork.Send(kPacket);

	wchar_t wTime[256];
	GetDlgItemText(IDC_EDIT_REFRESH_TIME, wTime, 256);
	long lTime = _tstol(wTime);
	// 1000 = 1초
	if (lTime != 0)
	{
		SetTimer(0, lTime*1000, 0);
	}
	else
	{
		// 0 이면 바로 보낸다.
	}
}

void CGeneralDlg::OnNMCustomdrawListServer(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	DWORD dwItem = (DWORD)pLVCD->nmcd.dwItemSpec;

	*pResult = 0;

    if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
    {
	    *pResult = CDRF_NOTIFYITEMDRAW;
    }
    else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
    {
		COLORREF crTextBG = 0;
	    COLORREF crText = 0;
	
		int iServerIdx = (int)pLVCD->nmcd.lItemlParam;

		SGameServerInfo kServerInfo;
		if (g_kGameServerMgr.GetServerInfo(iServerIdx, kServerInfo))
		{
			const bool bAliveMachine = g_kGameServerMgr.IsAliveServer(kServerInfo.strMachinIP);

			if( bAliveMachine )
			{
				if( kServerInfo.bIsException || kServerInfo.bTickWarning )//Critical
				{
					crTextBG = RGB(99,99,99);//Silver
					crText = RGB(255,255,0); //Yellow
				}
				else if( kServerInfo.bProcessHandle && kServerInfo.bReadyToService )
				{
					crTextBG = RGB(255,255,255); //White
					crText = RGB(0,0,0);//Black
				}
				else if( kServerInfo.bProcessHandle || kServerInfo.bReadyToService )
				{
					crTextBG = RGB(255,255,0); //Yellow
					crText = RGB(0,0,0);//Black
				}
				else
				{
					//서버 작동 가능하고 아무 서버도 안떠있는 기본 상태
					crTextBG = RGB(255,0,0);//Red
					crText = RGB(255,255,255);//white
				}
			}
			else
			{
				crTextBG = RGB(128,0,0);//Dark Red
				crText = RGB(255,255,255);//white
			}
		}

		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crTextBG;
		*pResult = CDRF_DODEFAULT;
    }
}

void CGeneralDlg::OnBnClickedBtnConnect()
{
	g_kNetwork.ConnectServer();
}

void CGeneralDlg::OnBnClickedBtnClose()
{
	g_kNetwork.DisConnectServer();
	m_listServer.DeleteAllItems();
}

void CGeneralDlg::GetCheckedList(ContServerID& rkOutServerID, std::wstring& rkOutText)const
{
	for (int i=0 ; i<m_listServer.GetItemCount() ; i++)
	{
		if (m_listServer.GetCheck(i))
		{
			int iServerIdx = (int)m_listServer.GetItemData(i);
			SGameServerInfo kServerInfo;
			if (g_kGameServerMgr.GetServerInfo(iServerIdx, kServerInfo))
			{
				rkOutText += kServerInfo.strName;
				rkOutText += L"\r\n";

				SERVER_IDENTITY kCheckedServer;
				kCheckedServer.nRealm = kServerInfo.nRealm;
				kCheckedServer.nServerNo = kServerInfo.nServerNo;
				kCheckedServer.nChannel = kServerInfo.nChannel;
				kCheckedServer.nServerType = kServerInfo.nServerType;

				rkOutServerID.push_back(kCheckedServer);
			}
		}
	}
}


//>>
bool FilterOnServer(const ContPairServerInfo& rhs )
{
	const ContPairServerInfo::second_type& rkElement = rhs.second;

	if( !rkElement.bReadyToService
	&&	!rkElement.bProcessHandle )
	{
		return true;
	}
	return false;
}

bool FilterOffServer(const ContPairServerInfo& rhs )
{
	const ContPairServerInfo::second_type& rkElement = rhs.second;

	if( rkElement.bReadyToService )
	{
		return true;
	}
	return false;
}
//<<

void CGeneralDlg::OnBnClickedBtnOn()
{
	ContServerID kCheckedList;
	std::wstring kWarningList;

	GetCheckedList(kCheckedList, kWarningList);
	if( kCheckedList.empty() )
	{
		if(m_kSelectServerList.empty())
		{
			return;
		}
	} else
	{
		m_kSelectServerList = kCheckedList;
	}

	const std::wstring kMessage = _T("Game Server On ?\n") + kWarningList;
	if( IDOK == MessageBox(kMessage.c_str(), L"Server On warning!!", MB_OKCANCEL) )
	{
		// 패킷 전송.
		CEL::CPacket kPacket(PT_MCTRL_TERMI_MMS_REQ_ONSERVER);
		TWriteArray(kPacket, m_kSelectServerList);
		g_kNetwork.Send(kPacket);
		m_kSelectServerList.clear();
	}
	SetTimer(1, 500, 0);// Refresh
}

void CGeneralDlg::OnBnClickedBtnOff()
{
	ContServerID kCheckedList;
	std::wstring kWarningList;
	GetCheckedList(kCheckedList, kWarningList);
	if( kCheckedList.empty() )
	{
		if(m_kSelectServerList.empty())
		{
			return;
		}
	} else
	{
		m_kSelectServerList = kCheckedList;
	}

	// 경고 메시지
	if (IDOK == MessageBox(_T("Game Server Off ?"), L"Server Off warning!!", MB_OKCANCEL))
	{
		// 패킷 전송.
		CEL::CPacket kPacket(PT_MCTRL_TERMI_MMS_REQ_OFFSERVER);
		TWriteArray(kPacket, m_kSelectServerList);
		g_kNetwork.Send(kPacket);
		m_kSelectServerList.clear();
	}
	SetTimer(1, 500, 0);// Refresh
}

void CGeneralDlg::OnBnClickedBtnProcesskill()
{
	m_bKillConfirm.SetCheck(FALSE);
	m_KillButton.EnableWindow(FALSE);

	std::wstring kWarningList;
	ContServerID kCheckedList;
	GetCheckedList(kCheckedList, kWarningList);
	if( kCheckedList.empty() )
	{
		return;
	}

	// 경고 메시지
	if (IDOK == MessageBox(kWarningList.c_str(), L"Process Kill warning!!", MB_OKCANCEL))
	{
		// 패킷 전송.
		CEL::CPacket kPacket(PT_MCTRL_TERMI_MMS_REQ_SHUTDOWN);
		TWriteArray(kPacket, kCheckedList);
		g_kNetwork.Send(kPacket);

		for (int i=0 ; i<m_listServer.GetItemCount() ; i++)
		{
			m_listServer.SetCheck(i, false);
		}

	}

	// Refresh
	SetTimer(1, 500, 0);
}

void CGeneralDlg::OnBnClickedCheckUsebeep()
{
	//g_kGameServerMgr.m_bUseBeep = (bool)IsDlgButtonChecked(IDC_CHECK_USEBEEP);
}

void CGeneralDlg::OnBnClickedBtnLogClear()
{
	CString kString("");
	SetDlgItemText(IDC_EDIT_LOG, kString);
}

void CGeneralDlg::OnBnClickedConfirmKill()
{
	m_KillButton.EnableWindow(m_bKillConfirm.GetCheck());
}

void CGeneralDlg::LogWork(const ContServerID& rkServerVec, TCHAR* szWorkType)
{
	
}
void CGeneralDlg::OnFileExit()
{
	g_kNetwork.DisConnectServer();
	SendMessage(WM_CLOSE, 0, 0);
}

void CGeneralDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CBitmap kNewBitMap;
	const BOOL bLoadBitmap = kNewBitMap.LoadBitmapW(MAKEINTRESOURCE(IDB_BITMAP1));
	if( !bLoadBitmap )
	{
		MessageBox(L"Can't Load Bitmap");
	}

	CDC kBitMapDC;
	const BOOL bCreateDC = kBitMapDC.CreateCompatibleDC(&dc);
	if( !bCreateDC )
	{
		MessageBox(L"Can't Create DC");
	}
	CBitmap* pkOldMap = kBitMapDC.SelectObject(&kNewBitMap);

	int iLeft = 650, iTop = 520;
	int iWidth = 300, iHeight = 90;
	BitBlt(dc, iLeft, iTop, iWidth, iHeight, kBitMapDC, 0, 0, SRCCOPY);

	kBitMapDC.SelectObject(pkOldMap);
}

void CGeneralDlg::OnDestroy()
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	if( GetParent() )
	{
		GetParent()->ShowWindow(SW_SHOW);
	}
	g_kNetwork.DisConnectServer();
}

void CGeneralDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	//PostQuitMessage(0);
	CDialog::OnClose();
}

void CGeneralDlg::SetTreeView()
{
	//초기화
	m_kTree.DeleteAllItems();

	//먼저 최상위 루트를 만들어주자
	TV_INSERTSTRUCT kTvstruct;
	HTREEITEM		hRoot, hCenter, hRealm;

	CONT_REALM kRealm;
	g_kRealmMgr.GetRealmCont(kRealm);
	CONT_REALM::iterator Realm_Itr = kRealm.begin();
	while(Realm_Itr != kRealm.end())
	{
		CONT_REALM::key_type kKey = Realm_Itr->first;
		CONT_REALM::mapped_type kElement = Realm_Itr->second;

		if(kKey == 0)		//site
		{
			kTvstruct.hParent = 0;
			kTvstruct.hInsertAfter = TVI_LAST;
			std::wstring wstrName = kElement.Name();
			kTvstruct.item.pszText = (LPWSTR)wstrName.c_str();
			kTvstruct.item.iImage = -1;
			kTvstruct.item.mask = TVIF_TEXT | TVIF_IMAGE;
			hRoot = m_kTree.InsertItem(&kTvstruct);
			m_kTree.SetItemData(hRoot, (DWORD)kTvstruct.item.iImage);
		} else
		{
			kTvstruct.hParent = hRoot;
			kTvstruct.hInsertAfter = TVI_LAST;
			std::wstring wstrRealmName = kElement.Name();		
			kTvstruct.item.pszText = (LPWSTR)wstrRealmName.c_str();
			kTvstruct.item.iImage = kKey;
			kTvstruct.item.mask = TVIF_TEXT | TVIF_IMAGE;
			hRealm = m_kTree.InsertItem(&kTvstruct);
			m_kTree.SetItemData(hRealm, (DWORD)kKey);
			
			ContServerInfo kServerList;
			
			if(FindRealmMember(kKey, kServerList))
			{
				ContServerInfo::const_iterator Itr = kServerList.begin();
				while(Itr != kServerList.end())
				{
					const SGameServerInfo& rkServerInfo = (*Itr).second;
					const int iContIdx = (int)((*Itr).first);

					if(rkServerInfo.nRealm > 0)
					{

						if(rkServerInfo.nServerType == CEL::ST_CENTER 
							|| ((rkServerInfo.nServerType == CEL::ST_MAP) 
							&& (rkServerInfo.nChannel == 0)))
						{
							kTvstruct.hParent = hRealm;
							kTvstruct.hInsertAfter = TVI_LAST;
							kTvstruct.item.pszText = (LPWSTR)rkServerInfo.strName.c_str();
							kTvstruct.item.iImage = iContIdx;
							kTvstruct.item.mask = TVIF_TEXT | TVIF_IMAGE;
							hCenter = m_kTree.InsertItem(&kTvstruct);
							m_kTree.SetItemData(hCenter, (DWORD)iContIdx);
						}
						else
						{
							kTvstruct.hParent = hCenter;
							kTvstruct.hInsertAfter = TVI_LAST;
							kTvstruct.item.pszText = (LPWSTR)rkServerInfo.strName.c_str();
							kTvstruct.item.iImage = iContIdx;
							kTvstruct.item.mask = TVIF_TEXT | TVIF_IMAGE;
							HTREEITEM hItem = m_kTree.InsertItem(&kTvstruct);
							m_kTree.SetItemData(hItem, (DWORD)iContIdx);

						}
					}
					else
					{
						kTvstruct.hParent = hRoot;
						kTvstruct.hInsertAfter = TVI_LAST;
						kTvstruct.item.pszText = (LPWSTR)rkServerInfo.strName.c_str();
						kTvstruct.item.iImage = iContIdx;
						kTvstruct.item.mask = TVIF_TEXT | TVIF_IMAGE;
						HTREEITEM hItem = m_kTree.InsertItem(&kTvstruct);
						m_kTree.SetItemData(hItem, (DWORD)iContIdx);
					}	
					++Itr;
				}
			}
		}
		++Realm_Itr;
	}

	//랠름과 상관 없는 애들을 등록한다.
	ContServerInfo kServerList;
	g_kGameServerMgr.GetServerList(kServerList);
	ContServerInfo::const_iterator Itr = kServerList.begin();
	while(Itr != kServerList.end())
	{
		const SGameServerInfo& rkServerInfo = (*Itr).second;
		const int iContIdx = (int)((*Itr).first);

		if(rkServerInfo.nRealm == 0)
		{
			kTvstruct.hParent = hRoot;
			kTvstruct.hInsertAfter = TVI_LAST;
			kTvstruct.item.pszText = (LPWSTR)rkServerInfo.strName.c_str();
			kTvstruct.item.iImage = iContIdx;
			kTvstruct.item.mask = TVIF_TEXT | TVIF_IMAGE;
			HTREEITEM hItem = m_kTree.InsertItem(&kTvstruct);
			m_kTree.SetItemData(hItem, (DWORD)iContIdx);
		}
		++Itr;
	}



	if(m_hSelectTreeItem != NULL)
	{
		m_kTree.Expand(m_hSelectTreeItem, TVE_EXPAND);
		m_kTree.SelectItem(m_hSelectTreeItem);
	}
}

void CGeneralDlg::OnTvnSelchangedTreeview(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	m_kSelectServerList.clear();

	HTREEITEM hChild;
	m_hSelectTreeItem = m_kTree.GetSelectedItem();
	DWORD dwData = (DWORD)m_kTree.GetItemData(m_hSelectTreeItem);
	int iData = (int)dwData;
	
	ContServerInfo kServerList, kSelectServerInfo;
	g_kGameServerMgr.GetServerList(kServerList);

	//렐름이면 전체다
	if(iData == -1)
	{
		kSelectServerInfo = kServerList;

		ContServerInfo::const_iterator Itr = kSelectServerInfo.begin();
		while(Itr != kSelectServerInfo.end())
		{
			SGameServerInfo kServerInfo;
			if (g_kGameServerMgr.GetServerInfo((*Itr).first, kServerInfo))
			{
				SERVER_IDENTITY kCheckedServer;
				kCheckedServer.nRealm = kServerInfo.nRealm;
				kCheckedServer.nServerNo = kServerInfo.nServerNo;
				kCheckedServer.nChannel = kServerInfo.nChannel;
				kCheckedServer.nServerType = kServerInfo.nServerType;

				m_kSelectServerList.push_back(kCheckedServer);
			}
			Itr++;
		}
	}
	else
	{
		//자기 자신 정보를 추가한다.
		AddSelectServerList(iData, kServerList, kSelectServerInfo);

		//자식 노드에 대한 정보 검색
		hChild = m_kTree.GetChildItem(m_hSelectTreeItem);
		while(hChild != NULL)
		{
			dwData = (DWORD)m_kTree.GetItemData(hChild);
			iData = (int)dwData;
			AddSelectServerList(iData, kServerList, kSelectServerInfo);
			hChild = m_kTree.GetNextSiblingItem(hChild);
		}
	}
	ServerRefresh(kSelectServerInfo);
}


void CGeneralDlg::AddSelectServerList(const int Idx, const ContServerInfo &rkAllServerInfo, ContServerInfo &rkOutput)
{
	ContServerInfo::const_iterator Itr = rkAllServerInfo.find(Idx);
	if(Itr != rkAllServerInfo.end())
	{
		ContServerInfo::mapped_type rkElement = (*Itr).second;
		rkOutput.insert(std::make_pair(Idx, rkElement));	
	}		

	SGameServerInfo kServerInfo;
	if (g_kGameServerMgr.GetServerInfo(Idx, kServerInfo))
	{
		SERVER_IDENTITY kCheckedServer;
		kCheckedServer.nRealm = kServerInfo.nRealm;
		kCheckedServer.nServerNo = kServerInfo.nServerNo;
		kCheckedServer.nChannel = kServerInfo.nChannel;
		kCheckedServer.nServerType = kServerInfo.nServerType;

		m_kSelectServerList.push_back(kCheckedServer);
	}
}

bool CGeneralDlg::FindRealmMember(const int iRealmNo, ContServerInfo & rkOut) const
{
	ContServerInfo kServerList;
	g_kGameServerMgr.GetServerList(kServerList);
	ContServerInfo::const_iterator Itr = kServerList.begin();
	if(Itr == kServerList.end())
	{
		rkOut.clear();
		return false;		
	}
	
	while(Itr != kServerList.end())
	{
		ContServerInfo::key_type kKey = Itr->first;
		ContServerInfo::mapped_type kElement = Itr->second;
		if(iRealmNo ==  kElement.nRealm)
		{
			rkOut.insert(std::make_pair(kKey, kElement));
		}

		++Itr;
	}

	return true;
}