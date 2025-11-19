// MFCGrid.cpp : implementation file
//

#include "stdafx.h"
#include "MFCGrid.h"

///////////////////////////////////////////////////////////////////////////////
//// CMFCGrid
//
//CMFCGrid::CMFCGrid()
//{
//	InitGrid(::AfxGetInstanceHandle());
//}
//
//CMFCGrid::~CMFCGrid()
//{
//}
//
//
//BEGIN_MESSAGE_MAP(CMFCGrid, CWnd)
//	//{{AFX_MSG_MAP(CMFCGrid)
//	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()
//
//
///////////////////////////////////////////////////////////////////////////////
//// CMFCGrid message handlers
//
//void CMFCGrid::PreSubclassWindow() 
//{
//	// TODO: Add your specialized code here and/or call the base class
//	ModifyStyleEx(0, WS_EX_CLIENTEDGE);
//
//	CGrid *pGrid = new CGrid();
//	pGrid->m_hWnd = m_hWnd;
//	pGrid->OnSize(0, 1, 1);
//	::SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)pGrid);
//	pGrid->GetColumnInfo()->Init(m_hWnd, ::AfxGetInstanceHandle());
//	pGrid->SetFont((HFONT)::GetStockObject(ANSI_FIXED_FONT));
//
//	pGrid->SetColumnType(1, MYVT_BOOL);
//	pGrid->SetRows(5);
//	pGrid->SetCols(5);
//
//	CWnd::PreSubclassWindow();
//}
//
//BOOL CMFCGrid::PreTranslateMessage(MSG* pMsg) 
//{
//	// TODO: Add your specialized code here and/or call the base class
//	if(pMsg->hwnd == m_hWnd && pMsg->message == WM_CHAR) {
//		SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
//		return TRUE;
//	}
//	else if(pMsg->hwnd == m_hWnd && pMsg->message == WM_KEYDOWN) {
//		::SendMessage(pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam);
//		if(pMsg->wParam == VK_ESCAPE || 
//			pMsg->wParam == VK_RETURN || 
//			pMsg->wParam == VK_LEFT || 
//			pMsg->wParam == VK_RIGHT || 
//			pMsg->wParam == VK_UP || 
//			pMsg->wParam == VK_DOWN) {
//			return TRUE;
//		}
//	}
//	return CWnd::PreTranslateMessage(pMsg);
//}
//
//LRESULT CMFCGrid::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
//{
//	// TODO: Add your specialized code here and/or call the base class
//	if(message == WM_GRID_SELECTCHANGED) {
//		int x, y, cx, cy;
//		x = LOWORD(wParam);
//		y = HIWORD(wParam);
//		cx = LOWORD(lParam);
//		cy = HIWORD(lParam);
//
//		CGrid* pGrid = GetGrid(m_hWnd);
//		if(pGrid) {
//			CMergeCell* pMerge = pGrid->GetMergeInfo(x, y);
//			if(pMerge) {
//				//GetParent()->GetDlgItem(IDC_BUTTON9)->EnableWindow();
//			}
//			else {
//				//GetParent()->GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE);
//			}
//		}
//
//		if(cx != 1 || cy != 1) {
//			//GetParent()->GetDlgItem(IDC_BUTTON8)->EnableWindow();
//		}
//		else {
//			//GetParent()->GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
//		}
//		return 0;
//	}
//	else
//		return GridWindowProc(m_hWnd, message, wParam, lParam);
////	return CWnd::DefWindowProc(message, wParam, lParam);
//}
