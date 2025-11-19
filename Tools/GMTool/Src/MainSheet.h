#pragma once

//#define GM_USE_EVENT_PAGE

// Pages
#include "Page_Notice.h"
#include "Page_Chat.h"
#include "Page_Control.h"
#ifdef GM_USE_EVENT_PAGE
#include "Page_Event.h"
#endif
#include "Page_Extra.h"
#include "Page_QA.h"

// CMainSheet

class CMainSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMainSheet)

public:
	void InitPage();
	CMainSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMainSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CMainSheet();

public:
	CPage_Notice		m_kPage_Notice;
	CPage_Chat			m_kPage_Chat;
	CPage_Control		m_kPage_Control;
#ifdef GM_USE_EVENT_PAGE
	CPage_Event			m_kPage_Event;
#endif
	CPage_Extra			m_kPage_Extra;
	CPage_QA			m_kPage_QA;
	
public:
	void SetSize(int x, int y, int cx, int cy);
	void SetSize(int cx, int cy);

protected:
	DECLARE_MESSAGE_MAP()
};