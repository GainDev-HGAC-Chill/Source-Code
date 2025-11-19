#include "stdafx.h"
#include "ChattingDlg.h"

#define STRING_TABLE_CHATDLG		50000
#define MAX_SYSTEM_TEXT	2

//IMPLEMENT_DYNAMIC(CChattingDlg, CDialog)

CChattingDlg::CChattingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChattingDlg::IDD, pParent)
{

}

CChattingDlg::~CChattingDlg()
{
}

void CChattingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHAT_EDIT, m_kChattingWindow);
	DDX_Control(pDX, IDC_SEND_EDIT, m_kSendEdit);
}


BEGIN_MESSAGE_MAP(CChattingDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_COMPLETE_BTN, &CChattingDlg::OnBnClickedCompleteBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CChattingDlg::OnBnClickedSendBtn)
	ON_WM_NCDESTROY()
END_MESSAGE_MAP()

BOOL CChattingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CWnd *pkWnd;
	CString kString;
	STRING_TABLE::iterator Itr;

	for(int i = 1; i <= MAX_SYSTEM_TEXT; i++)
	{
		Itr =  g_kXmlMgr.m_kStrTable.find(STRING_TABLE_CHATDLG + i);
		kString = UNI(Itr->second.c_str());
		pkWnd = GetDlgItem(IDD_CHATTING_FRM + i);
		pkWnd->SetWindowText(kString);
	}

	m_kSendEdit.SetWindowTextW(L"");
	m_kChattingWindow.SetWindowTextW(L"");
	m_bChatNow = true;

	return TRUE; 
}

void CChattingDlg::ExecuteDlg(CWnd* pParent, SPetitionData &Data)
{
	m_kData = Data;
	Create(IDD_CHATTING_FRM, pParent);
	ShowWindow(SW_SHOW);
//	DoModal();
}

void CChattingDlg::AddMsg(std::wstring &kMsg, bool bReturn)
{
	if (bReturn)
	{
		kMsg += L'\r';
		kMsg += L'\n';
	}

	CString kString;
	m_kChattingWindow.GetWindowTextW(kString);
	kString += kMsg.c_str();
	m_kChattingWindow.SetWindowTextW(kString);
	int iLine = m_kChattingWindow.GetLineCount();
	m_kChattingWindow.LineScroll(iLine);
}

void CChattingDlg::OnBnClickedCompleteBtn()
{
	m_kData.m_State = EPSTATE_COMPLETE;
	BM::DBTIMESTAMP_EX kTime;
	g_kProcessInfoMgr.GetServerTime(kTime);
	m_kData.m_dtEndTime = kTime;
	g_kPetitionDataMgr.UpdatePetitionData(m_kData);

	//갱신하기 위해 메시지 보낸다.
	SendMessageA(HWND_BROADCAST, g_nRegMsg,  (WPARAM)MSG_PETITION_REFLASH, (LPARAM)&m_kData.m_PetitionId);

	CEL::CPacket kPacket(PT_O_C_REQ_GM_CHAT_END);
	kPacket.Push(m_kData.m_RealmNo);		
	kPacket.Push(m_kData.m_szCharacterName);
	g_kNetwork.SendToLoginServer(kPacket);	
	theApp.m_pkPetitionDlg->m_MyListSelectItem = -1;

	OnClose();

}
void CChattingDlg::OnBnClickedSendBtn()
{
	CString kMsg;
	m_kSendEdit.GetWindowTextW(kMsg);
	if(wcscmp(kMsg, L"") == 0)
		return ;
	std::wstring kGmName = g_kProcessInfoMgr.m_kMyInfo.szName;
	std::wstring wstrMsg = kMsg;
	CEL::CPacket kPacket(PT_O_C_REQ_SEND_GM_CHAT);
	kPacket.Push(m_kData.m_RealmNo);
	kPacket.Push(m_kData.m_szCharacterName);
	kPacket.Push(m_kData.m_GmId);
	kPacket.Push(m_kData.m_PetitionId);
	kPacket.Push(kGmName);																//GMName
	kPacket.Push(wstrMsg);																//Message;
	if(g_kNetwork.SendToLoginServer(kPacket))
	{
		std::wstring kSend = kGmName;
		kSend += + L":";
		kSend +=  kMsg;
		AddMsg(kSend);

		m_kSendEdit.SetWindowTextW(L"");
	} else
	{
		ShowMessageBox(m_hWnd, 10010, 10001);
	}
}

void CChattingDlg::OnClose()
{
//	SendMessageA(HWND_BROADCAST, g_nRegMsg, (WPARAM)MSG_DESTROY_CHATDLG, (LPARAM)&m_kData.m_PetitionId);
	DestroyWindow();
}

void CChattingDlg::OnNcDestroy()
{
	SendMessageA(HWND_BROADCAST, g_nRegMsg, (WPARAM)MSG_DESTROY_CHATDLG, (LPARAM)&m_kData.m_PetitionId);
	delete this;
//	CDialog::OnNcDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CChattingDlg::OnPaint()
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
//		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}
