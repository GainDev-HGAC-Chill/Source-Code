#include <tchar.h>
#include <stdio.h>
#include <windows.h>

#include "array.h"
#include "gridcell.h"

#include "g_editbox.h"
#include "g_checkbox.h"

#ifndef _CGRIDCOLUMN_H
#define _CGRIDCOLUMN_H

class CGridColumn
{
public:
	CGridColumn();
	virtual ~CGridColumn();
	
	bool						Init(HWND hWnd, HINSTANCE hInst);
	void						Uninit();
	VT_TYPE						GetType(int nColumn);
	void						SetType(int nColumn, VT_TYPE type, int nCount = 1);
	HWND						GetEditHandle(int nColumn);
	void						SetFont(HFONT hFont);


	virtual HWND				EditCell(int nColumn, RECT& rcCell, void* pCellInfo, UINT nChar = 0);

protected:
	CMyArray<VT_TYPE>			m_column;
	CGridEditBox				m_editBox;
	HWND						m_hParent;
};

#endif