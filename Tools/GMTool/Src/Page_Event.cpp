// Page_Event.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GMTool.h"
#include "Page_Event.h"


// CPage_Event 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPage_Event, CPropertyPage)

CPage_Event::CPage_Event()
	: CPropertyPage(CPage_Event::IDD)
{

}

CPage_Event::~CPage_Event()
{
}

void CPage_Event::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage_Event, CPropertyPage)
END_MESSAGE_MAP()


// CPage_Event 메시지 처리기입니다.
