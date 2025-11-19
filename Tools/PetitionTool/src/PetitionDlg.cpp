#include "stdafx.h"
#include "PetitionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_COMBO_ITEM	8
#define MAX_LIST_COLUMN	4
#define MAX_SYSTEM_TEXT	8
#define MAX_INFO_LABEL	3

#define STRING_TABLE_PETITIONDLG	40000
#define STRING_LIST_COLUMN			40100
#define STRING_TABLE_INFO_LABEL		40200
#define STRING_TABLE_CB_ITEM		40300
#define STRING_TABLE_POPUPMENU		40400
#define STRING_TABLE_MENU			40500


CPetitionDlg::CPetitionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPetitionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	m_kChatDlg = NULL;
}

void CPetitionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALL_PETITION_LIST, m_ListAll);
	DDX_Control(pDX, IDC_MY_PETITON_LIST, m_ListMine);
	DDX_Control(pDX, IDC_KIND_COMBO, m_KindCombo);
	DDX_Control(pDX, IDC_STATIC_TIME, m_kDateTime);
	DDX_Control(pDX, IDC_STATIC_ALL, m_kAllNumber);
	DDX_Control(pDX, IDC_STATIC_COMPLITE, m_kCompleteNum);
	DDX_Control(pDX, IDC_STATIC_ASSIGN, m_kAssignNum);
	DDX_Control(pDX, IDC_EDIT_NOTE, m_kNote);
	DDX_Control(pDX, IDC_NAME_STATIC, m_kNameLabel);
	DDX_Control(pDX, IDC_TITLE_STATIC, m_kTitle);
	DDX_Control(pDX, IDC_CHAT_BTN, m_kChatBtn);
	DDX_Control(pDX, IDC_LETTER_BTN, m_kMessageBtn);
	DDX_Control(pDX, IDC_EXIT_BTN, m_kExitBtn);
}

BEGIN_MESSAGE_MAP(CPetitionDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT_BTN, &CPetitionDlg::OnBnClickedExitBtn)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_CHAT_BTN, &CPetitionDlg::OnBnClickedChatBtn)
	ON_COMMAND(ID_POPUP_ASSING_ME, &CPetitionDlg::OnPopupAssingMe)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_MY_PETITON_LIST, &CPetitionDlg::OnLvnItemchangingMyPetitonList)
	ON_COMMAND(ID_MENU_EXIT, &CPetitionDlg::OnMenuExit)
	ON_WM_ACTIVATE()
	ON_WM_CLOSE()
	ON_REGISTERED_MESSAGE(g_nRegMsg, OnRegMsg)
END_MESSAGE_MAP()

void CPetitionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CPetitionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CPetitionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);		
	SetIcon(m_hIcon, FALSE);	

	g_nRegMsg = ::RegisterWindowMessage(L"Message Test");

	InitDlg();

	return TRUE; 
}

void CPetitionDlg::StartPetitionDlg()
{
	m_ListAll.DeleteAllItems();
	m_ListMine.DeleteAllItems();

	g_kProcessInfoMgr.ReqRefreshGmList();
	g_kPetitionDataMgr.ReqPetitionData();

	theApp.m_pkLoginDlg->ShowWindow(SW_HIDE);
	theApp.m_pMainWnd = theApp.m_pkPetitionDlg;
	ShowWindow(SW_SHOW);
	SetFocus();
}

void CPetitionDlg::InitDlg()
{
	//Menu, Button Text Setting
	CWnd *pkWnd;
	CString kString;
	STRING_TABLE::iterator Itr;

	for(int i = 1; i <= MAX_SYSTEM_TEXT; i++)
	{
		Itr =  g_kXmlMgr.m_kStrTable.find(STRING_TABLE_PETITIONDLG + i);
		kString = UNI(Itr->second.c_str());
		pkWnd = GetDlgItem(IDD_PETITION_FRM + i);
		pkWnd->SetWindowText(kString);
	}

    CMenu menu;
    menu.LoadMenu(IDR_MENU1);

	for(int i = 1; i <= 2; i++)
	{
		Itr =  g_kXmlMgr.m_kStrTable.find(STRING_TABLE_MENU + i);
		kString = UNI(Itr->second.c_str());
		menu.ModifyMenuW(IDR_MENU1 + i, MF_BYCOMMAND | MF_STRING, IDR_MENU1 + i, kString);
	}

	//Info Label Text Setting
	for(int i = 1; i <= MAX_INFO_LABEL; i++)
	{
		Itr =  g_kXmlMgr.m_kStrTable.find(STRING_TABLE_INFO_LABEL + i);
		kString = UNI(Itr->second.c_str());
		pkWnd = GetDlgItem(STRING_TABLE_INFO_LABEL + i);
		pkWnd->SetWindowText(kString);
	}

	//ComboBox Item Setting
	for(int i = 1; i <= MAX_COMBO_ITEM; i++)
	{
		Itr =  g_kXmlMgr.m_kStrTable.find(STRING_TABLE_CB_ITEM + i);
		kString = UNI(Itr->second.c_str());
		m_KindCombo.InsertString(i-1, kString);
	}
	m_KindCombo.SetCurSel(0);


	//ListControl Setting
	m_ListAll.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListMine.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListMine.ModifyStyle(0, LVS_SHOWSELALWAYS); 

	int iColWidth[MAX_LIST_COLUMN] = {70, 140, 210, 70};
	LV_COLUMN lvColumn;

	for(int i = 1; i <= MAX_LIST_COLUMN; i++)
	{
		Itr =  g_kXmlMgr.m_kStrTable.find(STRING_LIST_COLUMN + i);
		kString = UNI(Itr->second.c_str());
		lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_CENTER;
		lvColumn.pszText = (LPWSTR)(LPCTSTR)kString;
		lvColumn.iSubItem = i-1;
		lvColumn.cx = iColWidth[i-1];
		m_ListAll.InsertColumn(i-1, &lvColumn);
		m_ListMine.InsertColumn(i-1, &lvColumn);
	}
	bReady = true;
}

void CPetitionDlg::OnClose()
{
	ClearGmChatDlg();
	theApp.m_pkLoginDlg->OnClose();
}

void CPetitionDlg::OnBnClickedExitBtn()
{
	OnClose();
}

void CPetitionDlg::OnMenuExit()
{
	OnClose();
}

void CPetitionDlg::PostNcDestroy()
{
	delete this;
	CDialog::PostNcDestroy();
}

void CPetitionDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rc1, rc2;

    // 스크린 좌표계를 기준으로 한 각 ListControl의 사각형 정보
	m_ListAll.GetWindowRect(rc1); 
	m_ListMine.GetWindowRect(rc2); 
   
    // 마우스 커서가 컨트롤 내에 있는지 판단
    if(rc1.PtInRect(point)) 
	{
        CMenu menu;
		CString kString;
		STRING_TABLE::iterator Itr;

        menu.LoadMenu(IDR_MENU2); // 메뉴 리소스 로드 

		for(int i = 1; i <= 2; i++)
		{
			Itr =  g_kXmlMgr.m_kStrTable.find(STRING_TABLE_POPUPMENU + i);
			kString = UNI(Itr->second.c_str());
			menu.ModifyMenuW(ID_POPUP_ASSING_ME + i -1, MF_STRING, ID_POPUP_ASSING_ME + i -1, kString);
		}

        // 사용할 서브 메뉴의 객체 포인터
        CMenu* pPopup = menu.GetSubMenu(0);  

        pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
                point.x, point.y, this);
    }
/*
    if(rc2.PtInRect(point)) 
	{
        CMenu menu;
        menu.LoadMenu(IDR_MENU2); // 메뉴 리소스 로드 
        
        // 사용할 서브 메뉴의 객체 포인터
        CMenu* pPopup = menu.GetSubMenu(0);  

        pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
                point.x, point.y, this);
    }	
*/
}

void CPetitionDlg::OnPopupAssingMe()
{
	POSITION pos = m_ListAll.GetFirstSelectedItemPosition();

	CONT_PETITION_DATA rkAllData;
	g_kPetitionDataMgr.GetAllPetitionData(rkAllData);
	CONT_PETITION_DATA::iterator itr = rkAllData.begin();
	while (pos)
	{
		int iPos =  m_ListAll.GetNextSelectedItem(pos);

		SPetitionData kSelectData;
		kSelectData = *(itr + iPos);
		kSelectData.m_State = EPSTATE_ASSIGN;
		kSelectData.m_GmId = g_kProcessInfoMgr.m_kMyInfo.kMemberGuid;
//		BM::DBTIMESTAMP_EX kTime;
//		g_kProcessInfoMgr.GetServerTime(kTime);
//		kSelectData.m_dtStartTime = kTime;
//		kSelectData.m_dtEndTime = kTime;

		g_kPetitionDataMgr.UpdatePetitionData(kSelectData);
	}
}

void CPetitionDlg::OnBnClickedChatBtn()
{//WinProc
	//일단 유저가 접속중인지 확인해보기 위해서 컨탠츠로 패킷을 날린다.~~

	CONT_PETITION_DATA rkAssingnData;
	g_kPetitionDataMgr.GetMyAssignData(rkAssingnData);

	CONT_PETITION_DATA::iterator itr = rkAssingnData.begin();
	SPetitionData kData = *(itr + m_MyListSelectItem);

	CEL::CPacket kPacket(PT_O_N_REQ_CHECK_LOGINED_USER);
	kPacket.Push(kData.m_RealmNo);
	kPacket.Push(kData.m_szCharacterName);
	kPacket.Push(kData.m_GmId);
	kPacket.Push(kData.m_PetitionId);
	g_kNetwork.SendToLoginServer(kPacket);	
}

void CPetitionDlg::CreateChatDlg(CONT_PETITION_DATA::value_type * const pkData)
{
	pkData->m_Kind = (short)m_KindCombo.GetCurSel();
	BM::DBTIMESTAMP_EX kTime;
	g_kProcessInfoMgr.GetServerTime(kTime);
	pkData->m_dtStartTime = kTime;
	pkData->m_dtEndTime = kTime;
	pkData->m_Answerkind = EANSWER_CHATTING;

	CChattingDlg * pkChatDlg = new CChattingDlg;
	CONT_CHAT::_Pairib Ret = m_kChatDlg.insert(std::make_pair(pkData->m_PetitionId, pkChatDlg));
	if(Ret.second)
	{
		//채팅창 생성
		CWnd* pWnd = FromHandle(m_hWnd);
		Ret.first->second->ExecuteDlg(pWnd, *pkData);
	}
	else
	{
		delete pkChatDlg;
		Ret.first->second->SetFocus();
	}
}

void CPetitionDlg::OnLvnItemchangingMyPetitonList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_MyListSelectItem = pNMLV->iItem;
	ReflashDetailInfo();
	*pResult = 0;
}

bool CPetitionDlg::InsertSel(CListCtrl *List, SPetitionData &Data)
{

	if(List == NULL)
		return false;

	int iCount = List->GetItemCount();

	LVITEM lvitem;
	CString strNo;

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = iCount;
	lvitem.iSubItem = 0;
	strNo.Format(L"%07d", Data.m_ReceiptIndex);
	lvitem.pszText = (LPWSTR)(LPCTSTR)strNo;
	List->InsertItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = iCount;
	lvitem.iSubItem = 1;
	lvitem.pszText = (LPWSTR)Data.m_szCharacterName.c_str();
	List->SetItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = iCount;
	lvitem.iSubItem = 2;
	lvitem.pszText = (LPWSTR)Data.m_szTitle.c_str();
	List->SetItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = iCount;
	lvitem.iSubItem = 3;
	strNo.Format(L"%02d:%02d", Data.m_dtReceiptTime.hour, Data.m_dtReceiptTime.minute);
	lvitem.pszText = (LPWSTR)(LPCTSTR)strNo;
	List->SetItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = iCount;
	lvitem.iSubItem = 4;

	return true;
}

void CPetitionDlg::ReflashListControl(CListCtrl* pListControl)
{

	CONT_PETITION_DATA	kListData;
	POSITION		pPosition;
	CDWordArray		kDragIndexes;

	if(pListControl == NULL)
		return ;

	//이전에 선택된것이 있으면 그 영역을 저장한다.
	if(pListControl->GetSelectedCount() > 0)
	{
		pPosition = pListControl->GetFirstSelectedItemPosition();
		while(pPosition)
		{
			kDragIndexes.Add( pListControl->GetNextSelectedItem(pPosition) );
		}
	}

	//리스트 리셋
	pListControl->DeleteAllItems();
	if(pListControl == &m_ListAll)
	{
		g_kPetitionDataMgr.GetAllPetitionData(kListData);
	} else
	{
		g_kPetitionDataMgr.GetMyAssignData(kListData);
	}
	CONT_PETITION_DATA::iterator itr = kListData.begin();
	while( itr != kListData.end() )
	{
		InsertSel(pListControl, *itr);
		itr++;
	}

	//자동 스크롤
	if(pListControl->GetItemCount() > 0)
		pListControl->EnsureVisible(pListControl->GetItemCount() - 1, FALSE);

	//이전에 선택된 아이템이 있으면 Selection을 복구한다.
	int iSelSize = (int)kDragIndexes.GetSize();
	for(int i = 0; i <iSelSize; ++i)
	{
		pListControl->SetSelectionMark(kDragIndexes[i]);
		pListControl->SetItemState(kDragIndexes[i], LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	}

	//시간 표시
}

void CPetitionDlg::ReflashDetailInfo()
{

	m_KindCombo.SetCurSel(0);

	if(m_ListMine.GetItemCount() > 0)
		m_kChatBtn.EnableWindow();
	else m_kChatBtn.EnableWindow(0);

	if(m_MyListSelectItem < 0)
	{
		m_kTitle.SetWindowTextW(L"");
		m_kNameLabel.SetWindowTextW(L"");
		m_kNote.SetWindowTextW(L"");
		return;
	}
	CONT_PETITION_DATA rkAssignData;
	g_kPetitionDataMgr.GetMyAssignData(rkAssignData);
	CONT_PETITION_DATA::iterator itr = rkAssignData.begin();
	if(itr != rkAssignData.end())
	{
		SPetitionData kData = *(itr + m_MyListSelectItem);

		m_kNameLabel.SetWindowTextW(kData.m_szCharacterName.c_str());
		m_kTitle.SetWindowTextW(kData.m_szTitle.c_str());
	/*
		std::wstring kNote;
		for(int i = 0; i < kData.m_szPetition.size(); i++)
		{
			std::basic_string<wchar_t> kTemp = kData.m_szPetition.substr(i, 1);
			if(wcscmp(kTemp.c_str(), L"\n") != 0)
			{
				kNote += kTemp.c_str();
			}
		}*/
		m_kNote.SetWindowTextW(kData.m_szPetition.c_str());
	}
}

void CPetitionDlg::ReflashLabels()
{

	//전체상담 수
	CString strLabel;
	int iTotal = m_ListAll.GetItemCount() + m_ListMine.GetItemCount();
	strLabel.Format(L"%d", iTotal);
	m_kAllNumber.SetWindowTextW(strLabel);

	//처리한 상담 수



	//내게 할당된 상담 수
	strLabel.Format(L"%d", m_ListMine.GetItemCount() );
	m_kAssignNum.SetWindowTextW(strLabel);	

	//남은 상담 수

}

void CPetitionDlg::ReflashAll()
{
	ReflashListControl(&m_ListAll);
	ReflashListControl(&m_ListMine);
	ReflashDetailInfo();
	ReflashLabels();
}

void CPetitionDlg::ClearGmChatDlg()
{

	CONT_CHAT::iterator Itr = m_kChatDlg.begin();
	while(Itr != m_kChatDlg.end())
	{
		Itr->second->DestroyWindow();
		++Itr;
	}
	m_kChatDlg.clear();

}

void CPetitionDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	SetFocus();
}

LRESULT CPetitionDlg::OnRegMsg(WPARAM wParam, LPARAM lParam)
{
	int iType = (int)wParam;

	switch(iType)
	{
	case MSG_CREATE_CHAT:
		{
			CONT_PETITION_DATA::value_type * pkElement = (CONT_PETITION_DATA::value_type *)lParam;
			CreateChatDlg(pkElement);
		}break;
	case MSG_DISCONNECTED_SERVER:
		{
			ClearGmChatDlg();
			ShowWindow(SW_HIDE);
			theApp.m_pMainWnd = theApp.m_pkLoginDlg;
			theApp.m_pkLoginDlg->ShowWindow(SW_SHOW);		
			theApp.m_pkLoginDlg->SetFocus();
		}break;
	case MSG_DESTROY_CHATDLG:
		{
			BM::GUID * kGuid = (BM::GUID *)lParam;

			CONT_CHAT::iterator Itr = m_kChatDlg.find(*kGuid);
			if(Itr != m_kChatDlg.end())
			{
				CONT_CHAT::mapped_type kElement = Itr->second;
				m_kChatDlg.erase(Itr);
			}			
		}break;
	case MSG_PETITION_REFLASH:
		{
			ReflashAll();
		}break;
	default:break;
	}
	UpdateData(false);
	return S_OK;
}

void CPetitionDlg::SendChatMessage(const BM::GUID &kPetitionGuid, std::wstring &kMsg)
{

	CONT_CHAT::iterator Itr = m_kChatDlg.find(kPetitionGuid);
	if(Itr != m_kChatDlg.end())
	{
		CONT_CHAT::mapped_type kElement = Itr->second;
		kElement->AddMsg(kMsg);
	}			
}