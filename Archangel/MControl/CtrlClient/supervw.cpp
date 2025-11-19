// SuperVw.cpp : implementation file
//

#include "stdafx.h"
#include "SuperGrid.h"
#include "SuperVw.h"
#include "TestTreeDlg.h"
#include "NewItem.h"
#include "SuperGridCtrl.h"
#include "PgChannelMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperVw

CView* g_pkView = NULL;


IMPLEMENT_DYNCREATE(CSuperVw, CView)

CSuperVw::CSuperVw()
{
	m_bDrag=TRUE;
}

CSuperVw::~CSuperVw()
{
}


BEGIN_MESSAGE_MAP(CSuperVw, CView)
	//{{AFX_MSG_MAP(CSuperVw)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_COMMAND(ID_TOOLS_VIEWINADIALOG, Ondialog)
	ON_COMMAND(IDD_DIALOG1, OnDialog1)
	ON_COMMAND(ID_TOOLS_COLLAPSE, OnToolsCollapse)
	ON_COMMAND(ID_TOOLS_DELETE, OnToolsDelete)
	ON_COMMAND(ID_TOOLS_EXPAND, OnToolsExpand)
	ON_COMMAND(ID_TOOLS_EXPANDALL, OnToolsExpandall)
	ON_COMMAND(ID_TOOLS_SEARCH, OnToolsSearch)
	ON_COMMAND(ID_TOOLS_SORT, OnToolsSort)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_DRAGDROP, OnUpdateToolsDragdrop)
	ON_COMMAND(ID_TOOLS_DRAGDROP, OnToolsDragdrop)
	ON_COMMAND(ID_TOOLS_DELETEALL, OnToolsDeleteall)
	ON_COMMAND(ID_TOOLS_DYNAMICUPDATEITEM, OnToolsDynamicupdateitem)
	ON_COMMAND(ID_TOOLS_SETIMAGE, OnToolsSetimage)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(IDM_STARTALLCHANNEL, CSuperVw::OnStartAllChannel)
	ON_COMMAND(IDM_STARTCHECKEDCHANNEL, CSuperVw::OnStartCheckedChannel)
	ON_COMMAND(IDM_STOPALLCHANNEL, CSuperVw::OnStopAllChannel)
	ON_COMMAND(IDM_STOPCHECKEDCHANNEL, CSuperVw::OnStopCheckedChannel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperVw drawing

void CSuperVw::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

BOOL CSuperVw::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSuperVw::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	
}

void CSuperVw::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


void CSuperVw::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	CView::OnPrepareDC(pDC, pInfo);
}


void CSuperVw::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if(m_List.GetExtendedStyle() & LVS_EX_CHECKBOXES)
		m_List.HowToLoopThroughAllItems_that_has_a_checkmark_and_print_them_or_what_ever(pDC);
	else
		m_List.HowToLoopThroughAllItems_if_we_wanted_to_print_them_or_what_ever(pDC);	
	
	CView::OnPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CSuperVw diagnostics

#ifdef _DEBUG
void CSuperVw::AssertValid() const
{
	CView::AssertValid();
}

void CSuperVw::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSuperVw message handlers

void CSuperVw::OnSize(UINT nType, int cx, int cy) 
{
	if (cy < (LOGBOX_HEIGHT+LOGBOX_GAP))
	{
		return;
	}
	CView::OnSize(nType, cx, cy);

	if(m_List.GetSafeHwnd())
		m_List.SetWindowPos(0,-1,-1,cx,cy-(LOGBOX_HEIGHT+LOGBOX_GAP),SWP_SHOWWINDOW);
	if (m_LogBox.GetSafeHwnd())
		m_LogBox.SetWindowPos(NULL, 0, cy-(LOGBOX_HEIGHT+LOGBOX_GAP), cx, LOGBOX_HEIGHT, SWP_SHOWWINDOW);
}



int CSuperVw::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_List.Create(WS_CHILD | WS_VISIBLE,CRect(0,0,0,0),this,0x100);	
	m_List.InitializeGrid();

	m_LogBox.Create(LBS_HASSTRINGS | LBS_OWNERDRAWVARIABLE | WS_VSCROLL | WS_TABSTOP, CRect(0, 0, 0, 0), this, IDC_LOGBOX);

	g_pkView = this;
	return 0;
}

void CSuperVw::Ondialog() 
{
	
	CTestTreeDlg dlg;
	dlg.DoModal();
}


void CSuperVw::OnDialog1() 
{
	if(m_List.GetSafeHwnd())
	{
		int nIndex = m_List.GetSelectedItem();
		if(nIndex!=-1)
		{
			CNewItem dlg;
			if(dlg.DoModal()==IDOK)
				m_List.HowToInsertItemsAfterTheGridHasBeenInitialized(nIndex, dlg.m_strItem);
		}
	}
}


//Yes I know this is so cheap programming, but let's all get on with our lifes :)
void CSuperVw::OnToolsCollapse() 
{
	m_List.SendMessage(WM_KEYDOWN,(WPARAM)VK_SUBTRACT,0);
}

void CSuperVw::OnToolsDelete() 
{
	m_List.SendMessage(WM_KEYDOWN,(WPARAM)VK_DELETE,0);
}

void CSuperVw::OnToolsExpand() 
{
	m_List.SendMessage(WM_KEYDOWN,(WPARAM)VK_ADD,0);
}

void CSuperVw::OnToolsExpandall() 
{
	m_List.SendMessage(WM_KEYDOWN,(WPARAM)VK_MULTIPLY,0);
}



void CSuperVw::OnToolsSearch() 
{
	m_List.HowToSearch_I_am_using_hardcoded_values_here_cause_I_am_tired_now();	
}

void CSuperVw::OnToolsSort() 
{
	m_List.SortData();
}


void CSuperVw::OnUpdateToolsDragdrop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bDrag);
}


void CSuperVw::OnToolsDragdrop() 
{
	m_bDrag = !m_bDrag;	
	m_List.m_bDrag=m_bDrag;
}

void CSuperVw::OnToolsDeleteall() 
{
	m_List._DeleteAll();	
}

void CSuperVw::OnToolsDynamicupdateitem() 
{
	int nItem = m_List.GetSelectedItem();
	m_List.DynamicUpdateSomeItems(nItem);	
}

void CSuperVw::OnToolsSetimage() 
{
	int nItem = m_List.GetSelectedItem();
	m_List.SetNewImage(nItem);	
}

void CSuperVw::OnStartAllChannel()
{
	POSITION pos = m_List.GetRootHeadPosition();
	while (pos != NULL)
	{
		CSuperGridCtrl::CTreeItem* pkTree = (CSuperGridCtrl::CTreeItem*) m_List.GetNextRoot(pos);
		CItemInfo* pkItem = m_List.GetData(pkTree);
		CString strID = pkItem->GetSubItem(1);
		int iID = 0;
		_stscanf_s((LPCTSTR)strID, _T("%d"), &iID);
		g_kChannelMgr.StartChannel(iID);
	}

}

void CSuperVw::OnStartCheckedChannel()
{
}

void CSuperVw::OnStopAllChannel()
{
}

void CSuperVw::OnStopCheckedChannel()
{
}

void CSuperVw::OutputLog(int iLevel, LPCTSTR fmt, ...)
{
	TCHAR log_str[2028];
	va_list vararg;

	va_start( vararg, fmt );

	if ( _vsnwprintf_s( log_str, 2028, 2028, fmt, vararg) == -1 )
	{
		_tcscpy_s(log_str, 2028, _T("[ERROR] too long log message"));
	}
	va_end( vararg );

	COLORREF col = RGB(0, 0, 0);
	if (iLevel < 6)	// ERROR
	{
		col = RGB(255, 0, 0);
	}
	m_LogBox.AddItem(log_str, RGB(255, 255, 255), col);

	if (m_LogBox.GetCount() > 980)
	{
		for (int i=0; i<100; i++)
		{
			m_LogBox.RemoveAt(0);
		}
	}
}

void CSuperVw::UpdateServerList()
{
	// Reading Server information and update view
}