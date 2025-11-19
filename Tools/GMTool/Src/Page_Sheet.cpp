// Page_Sheet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GMTool.h"
#include "Page_Sheet.h"


// CPage_Sheet 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPage_Sheet, CPropertyPage)

CPage_Sheet::CPage_Sheet()
	: CPropertyPage(CPage_Sheet::IDD)
{

}

CPage_Sheet::~CPage_Sheet()
{
}

void CPage_Sheet::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage_Sheet, CPropertyPage)
END_MESSAGE_MAP()


// CPage_Sheet 메시지 처리기입니다.
