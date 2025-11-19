// MainSheet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GMTool.h"
#include "MainSheet.h"


// CMainSheet

IMPLEMENT_DYNAMIC(CMainSheet, CPropertySheet)

CMainSheet::CMainSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	InitPage();
}

CMainSheet::CMainSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	InitPage();
}

void CMainSheet::InitPage()
{
	AddPage(&m_kPage_Notice);
	AddPage(&m_kPage_Chat);
	AddPage(&m_kPage_Control);
#ifdef GM_USE_EVENT_PAGE
	AddPage(&m_kPage_Event);
#endif
	AddPage(&m_kPage_Extra);
	AddPage(&m_kPage_QA);	
}

CMainSheet::~CMainSheet()
{
}


BEGIN_MESSAGE_MAP(CMainSheet, CPropertySheet)
END_MESSAGE_MAP()

// CMainSheet 메시지 처리기입니다.
#define PG_PAGE_MAX_WIDTH	(8)
#define PG_PAGE_MAX_HEIGHT	(25)
void CMainSheet::SetSize(int cx, int cy)
{
	if (cx < PG_PAGE_MAX_WIDTH)
		cx = PG_PAGE_MAX_WIDTH;
	if (cy < PG_PAGE_MAX_HEIGHT)
		cy = PG_PAGE_MAX_HEIGHT;

	ModifyStyle(0, WS_THICKFRAME);

	// Page들 사이즈 변경
	for (int i=0 ; i<GetPageCount() ; i++)
	{
		CPropertyPage *pkPage = GetPage(i);
		
		if (pkPage)
		{
			pkPage->SetWindowPos(0, 0, 0, cx-PG_PAGE_MAX_WIDTH, cy-PG_PAGE_MAX_HEIGHT,
				SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		}
	}

	// 시트 사이즈 변경
    CTabCtrl* pTabCtrl = GetTabControl();
    if(!pTabCtrl)
	{
        return;
	}
    if ( !pTabCtrl->SetWindowPos(NULL, 0, 0, cx, cy,
        SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE) )
	{
		assert(0);
	}
}

#define PG_PAGE_WIDTH	(3)
#define PG_PAGE_HEIGHT	(22)
void CMainSheet::SetSize(int x, int y, int cx, int cy)
{
	int iPageMaxX = 0;
	int iPageMaxY = 0;

	if (cx < PG_PAGE_MAX_WIDTH)
		cx = PG_PAGE_MAX_WIDTH;
	if (cy < PG_PAGE_MAX_HEIGHT)
		cy = PG_PAGE_MAX_HEIGHT;

	ModifyStyle(0, WS_THICKFRAME);

	// Page 사이즈 변경
	{
		CPropertyPage *pkPage = GetActivePage();
		if (pkPage)
		{
			RECT rtPage;
			pkPage->GetClientRect(&rtPage);

			if (iPageMaxX < rtPage.right)
			{
				iPageMaxX = rtPage.right;
			}
			if (iPageMaxY < rtPage.bottom)
			{
				iPageMaxY = rtPage.bottom;
			}

			int iPageX = x + PG_PAGE_WIDTH;
			int iPageY = y + PG_PAGE_HEIGHT;
			int iPageCX = //cx-PG_PAGE_MAX_WIDTH;
				rtPage.right < cx-PG_PAGE_MAX_WIDTH ? rtPage.right : cx-PG_PAGE_MAX_WIDTH;
			int iPageCY = //cx-PG_PAGE_MAX_HEIGHT;
				rtPage.bottom < cy-PG_PAGE_MAX_HEIGHT ? rtPage.bottom : cx-PG_PAGE_MAX_HEIGHT;

			pkPage->SetWindowPos(
				0,
				0,
				0,
				iPageCX,
				iPageCY,
				SWP_NOMOVE|SWP_NOZORDER);
		}
	}

	// 시트 사이즈 변경
    CTabCtrl* pTabCtrl = GetTabControl();
    if(!pTabCtrl)
	{
        return;
	}
	// 텝의 크기
	int iTabCX = //cx;
		iPageMaxX < cx ? iPageMaxX+PG_PAGE_MAX_WIDTH : cx;
	int iTabCY = //cy;
		iPageMaxY < cy ? iPageMaxY+PG_PAGE_MAX_HEIGHT : cy;
	if ( !pTabCtrl->SetWindowPos(NULL, 0, 0, iTabCX, iTabCY,
		SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW) )
	{
		assert(0);
	}
	// 좌표
	if ( !SetWindowPos(NULL, x, y, 0, 0,
		SWP_NOSIZE|SWP_NOZORDER|SWP_SHOWWINDOW) )
	{
		assert(0);
	}

}






