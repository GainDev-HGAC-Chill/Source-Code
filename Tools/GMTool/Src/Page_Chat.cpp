// Page_Chat.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GMTool.h"
#include "GMServer.h"
#include "Page_Chat.h"


// CPage_Chat 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPage_Chat, CPropertyPage)

CPage_Chat::CPage_Chat()
	: CPropertyPage(CPage_Chat::IDD)
{

}

CPage_Chat::~CPage_Chat()
{
}

void CPage_Chat::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage_Chat, CPropertyPage)
	ON_BN_CLICKED(IDC_PAGE_CHAT_CHAT_SEND, &CPage_Chat::OnBnClickedPageChatChatSend)
END_MESSAGE_MAP()


// CPage_Chat 메시지 처리기입니다.

void CPage_Chat::OnBnClickedPageChatChatSend()
{
#ifdef USE_OLD_GMSERVER
	wchar_t wString[SCPacket_STRING_SIZE];
	GetDlgItemText(IDC_PAGE_CHAT_CONTENTS, wString, SCPacket_STRING_SIZE);
	g_pkGMServer->Send_Chat(wString);
#endif
}
