#include "g_column.h"

CGridColumn::CGridColumn()
{
}

CGridColumn::~CGridColumn()
{
}

VT_TYPE CGridColumn::GetType(int nColumn)
{
	if(nColumn >= m_column.GetSize())
		return MYVT_NONE;
	else
		return m_column.GetAt(nColumn);
}

void CGridColumn::SetType(int nColumn, VT_TYPE type, int nCount)
{
	int nOldSize = m_column.GetSize();
	if(nColumn > nOldSize) {
		m_column.InsertAt(nOldSize, MYVT_NONE, nColumn - nOldSize);
		m_column.InsertAt(nColumn, type, nCount);
	}
	else if((nColumn + nCount) <= m_column.GetSize()) {
		for(int i = 0; i < nCount; ++ i)
			m_column[nColumn + i] = type;
	}
	else {
		m_column.SetSize(nColumn + nCount);
		for(int i = nColumn; i < nColumn + nCount; ++ i) {
			m_column[i] = type;
		}
	}
}

HWND CGridColumn::GetEditHandle(int nColumn)
{
	VT_TYPE type = GetType(nColumn);
	if(type == MYVT_NONE || 
		type == MYVT_CHAR || 
		type == MYVT_UCHAR || 
		type == MYVT_SHORT || 
		type == MYVT_USHORT || 
		type == MYVT_INT || 
		type == MYVT_UINT || 
		type == MYVT_LONG || 
		type == MYVT_ULONG || 
		type == MYVT_FLOAT || 
		type == MYVT_DOUBLE || 
		type == MYVT_PTCHAR) {

		return m_editBox.m_hWnd;
	}
	else {
		return NULL;
	}
}

bool CGridColumn::Init(HWND hWnd, HINSTANCE hInst)
{
	m_hParent = hWnd;
	HWND h = m_editBox.CreateEdit(WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, hInst);
	return h != NULL;
}

void CGridColumn::Uninit()
{
}

HWND CGridColumn::EditCell(int nColumn, RECT& rcCell, void* pCellInfo, UINT nChar)
{
	CGridCell* pGridCell = (CGridCell*)pCellInfo;
	VT_TYPE type;
	if(pGridCell && pGridCell->type != MYVT_NONE) {
		type = pGridCell->type;
	}
	else {
		type = GetType(nColumn);
	}

	HWND hWnd = GetEditHandle(nColumn);
	if(!hWnd) return NULL;

	TCHAR sz[50];
	switch(type) {
	case MYVT_NONE:
		::SetWindowText(hWnd, _TEXT(""));
		break;
	case MYVT_BOOL:
		return NULL;
		break; 
	case MYVT_CHAR:
		if(pCellInfo)
			_stprintf(sz, _TEXT("%d"), pGridCell->vt.vt_char);
		else
			_tcscpy(sz, _TEXT(""));
		::SetWindowText(hWnd, sz);
		break;
	case MYVT_UCHAR:
		if(pCellInfo)
			_stprintf(sz, _TEXT("%d"), pGridCell->vt.vt_uchar);
		else
			_tcscpy(sz, _TEXT(""));
		::SetWindowText(hWnd, sz);
		break;
	case MYVT_SHORT:
		if(pCellInfo)
			_stprintf(sz, _TEXT("%d"), pGridCell->vt.vt_short);
		else
			_tcscpy(sz, _TEXT(""));
		::SetWindowText(hWnd, sz);
		break;
	case MYVT_USHORT:
		if(pCellInfo)
			_stprintf(sz, _TEXT("%d"), pGridCell->vt.vt_ushort);
		else
			_tcscpy(sz, _TEXT(""));
		::SetWindowText(hWnd, sz);
		break;
	case MYVT_INT:
		if(pCellInfo)
			_stprintf(sz, _TEXT("%d"), pGridCell->vt.vt_int);
		else
			_tcscpy(sz, _TEXT(""));
		::SetWindowText(hWnd, sz);
		break;
	case MYVT_UINT:
		if(pCellInfo)
			_stprintf(sz, _TEXT("%d"), pGridCell->vt.vt_uint);
		else
			_tcscpy(sz, _TEXT(""));
		::SetWindowText(hWnd, sz);
		break;
	case MYVT_LONG:
		if(pCellInfo)
			_stprintf(sz, _TEXT("%d"), pGridCell->vt.vt_long);
		else
			_tcscpy(sz, _TEXT(""));
		::SetWindowText(hWnd, sz);
		break;
	case MYVT_ULONG:
		if(pCellInfo)
			_stprintf(sz, _TEXT("%d"), pGridCell->vt.vt_ulong);
		else
			_tcscpy(sz, _TEXT(""));
		::SetWindowText(hWnd, sz);
		break;
	case MYVT_FLOAT:
		if(pCellInfo)
			_stprintf(sz, _TEXT("%.3f"), pGridCell->vt.vt_float);
		else
			_tcscpy(sz, _TEXT(""));
		::SetWindowText(hWnd, sz);
		break;
	case MYVT_DOUBLE:
		if(pCellInfo)
			_stprintf(sz, _TEXT("%.3f"), pGridCell->vt.vt_double);
		else
			_tcscpy(sz, _TEXT(""));
		::SetWindowText(hWnd, sz);
		break;
	case MYVT_PTCHAR:
		if(pCellInfo)
			::SetWindowText(hWnd, pGridCell->vt.vt_ptchar);
		else
			::SetWindowText(hWnd, _TEXT(""));
		break;
	case MYVT_LPARAM:
		return NULL;
		break;
	}

	::MoveWindow(hWnd, rcCell.left, rcCell.top, rcCell.right - rcCell.left, rcCell.bottom - rcCell.top, false);
	::SendMessage(hWnd, EM_SETSEL, (WPARAM)0, (LPARAM)-1);
	if(nChar != 0)
		::SendMessage(hWnd, WM_CHAR, (WPARAM)nChar, 0);
	::ShowWindow(hWnd, SW_SHOW);
	::SetFocus(hWnd);
	return hWnd;
}

void CGridColumn::SetFont(HFONT hFont)
{
	::SendMessage(m_editBox.m_hWnd, WM_SETFONT, (WPARAM)hFont, 0);
}
/*
void CGridColumn::OnHide()
{
	HWND hWnd = GetEditHandle(m_cellID.x);
	if(m_cellInfo) {
		CMyVariant *pGridCell = (CMyVariant*)m_cellInfo;

		int n = ::SendMessage(m_hWnd, WM_GETTEXTLENGTH, 0, 0);
		if(n <= 10) {
			TCHAR szTmp[11];
			::GetWindowText(m_hWnd, szTmp, 10);

			VT_TYPE type = CMyVariant::GetType(szTmp);
			unsigned long ul;
			long l;
			double d;

			switch(type) {
			case MYVT_NONE:
				pGridCell->Clear();
				break;
			case MYVT_ULONG:
				ul = _ttol(szTmp);
				(*pGridCell) << ul;
				break;
			case MYVT_LONG:
				l = _ttol(szTmp);
				(*pGridCell) << l;
				break;
			case MYVT_DOUBLE:
				d = atof(szTmp);
				(*pGridCell) << d;
				break;
			case MYVT_PTCHAR:
				(*pGridCell) << szTmp;
				break;
			}
		}
		else {
			TCHAR *p = (TCHAR*)malloc(sizeof(TCHAR) * (n + 1));
			::GetWindowText(m_hWnd, p, n);
			(*pGridCell) << p;
			free(p);
		}
	}
}
*/