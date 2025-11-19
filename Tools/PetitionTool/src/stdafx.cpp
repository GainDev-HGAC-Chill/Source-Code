// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// PetitionTool.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"


//메시지 박스 ID로 띄우기
void ShowMessageBox(HWND hWnd, UINT TextId, UINT CaptionId)
{
	CString kString, kCaption;
	STRING_TABLE::iterator Itr;
	Itr = g_kXmlMgr.m_kStrTable.find(TextId);
	kString = Itr->second.c_str();
	Itr = g_kXmlMgr.m_kStrTable.find(CaptionId);
	kCaption = Itr->second.c_str();
	MessageBox(hWnd, kString, (LPCTSTR)kCaption, MB_OK);
}
