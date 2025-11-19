//-----------------------------------------------------------------------------
//	API - Dialog Programing Base Window Framework 					
//-----------------------------------------------------------------------------
#pragma	warning ( disable : 4996 )

#include	"defines.h"
#include "BM/ExceptionFilter.h"

//-----------------------------------------------------------------------------
//  Area Variable
//-----------------------------------------------------------------------------
HWND		g_hWnd, g_hDlgWnd;	//핸들윈도우 전역변수 설정 편하지만 과연 옳은 일일까?
HINSTANCE	g_hInst;			//인스턴스 생성

CPackProcess	g_PackProcess;
std::wstring	g_CmdLine;
//-----------------------------------------------------------------------------
//  08-01-24, 함수의 프로토 타입 써주는 곳
//-----------------------------------------------------------------------------
LRESULT	CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);	//윈도우 프로시저
BOOL	CALLBACK	MainDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam);
void SetLocation();
//-----------------------------------------------------------------------------
//  08-01-24, 윈도우 메인 함수
//-----------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	PgExceptionFilter::Install( PgExceptionFilter::DUMP_LEVEL_HEAVY );

	g_hInst = hInstance;
	g_CmdLine = UNI(lpszCmdParam);
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MPPACK), g_hWnd, MainDlgProc);

	return 0;
}

//-----------------------------------------------------------------------------
//  08-01-24, 메인 대화상자 프로시저
//-----------------------------------------------------------------------------
BOOL CALLBACK MainDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage)
	{
		case WM_INITDIALOG:
			g_hDlgWnd	= hDlg;
			SetLocation();
			g_PackProcess.Init(g_CmdLine);
		return TRUE;
		case WM_COMMAND:
			SetLocation();
			if(g_PackProcess.CommandAction(wParam, lParam))
			{
				return TRUE;
			}
		break;
	}

	return FALSE;
}

//	Set Work Directory
void SetLocation()
{
	char path[MAX_PATH];

	GetModuleFileNameA(GetModuleHandle(0), path, MAX_PATH);

	if (strlen(path)==0)
	{
		return;
	}

	strrchr( path, '\\' )[1] = 0;
	SetCurrentDirectoryA(path);
}
//-----------------------------------------------------------------------------
//  08-01-24, End
//-----------------------------------------------------------------------------
