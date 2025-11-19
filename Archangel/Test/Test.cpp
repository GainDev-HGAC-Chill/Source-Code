
// Test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.

#define WIN32_LEAN_AND_MEAN

#include "stdafx.h"
#include <map>



// Debug.cpp: implementation of the CDebugLog class.
//
//////////////////////////////////////////////////////////////////////
#include <assert.h>
#include <direct.h>
#include <Time.h>
#include <wchar.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <tchar.h>
#include "Loki/Threads.h"
 
#include "bm/guid.h"
#include "bm/PgTask.h"
#include "BM/Threadobject.h"
#include "BM/guid.h"
#include "BM/FileSupport.h"

#include "CEL/ConsoleCommander.h"

#include "Lohengrin/Lohengrin.h"
#include "Lohengrin/LogGroup.h"
#include "PgTestTime.h"

#include "Shellapi.h"

DWORD g_dwGetPeriod = 10000;
PgTestTime g_kTestTime;
bool g_bLoop = true;

DWORD WINAPI GenThread( LPVOID p )
{
	DWORD dwMonsterGenCount = 1;
	DWORD dwLastGenTime = g_kTestTime.GetTime32();
	INFO_LOG( BM::LOG_LV6, L"First Gen NowTime[" << dwLastGenTime << L"]" );
	
	DWORD dwNoGenLoopCount = 0;
	DWORD const dwMaxGenLoopCount = g_dwGetPeriod / 100 + 1;
	while ( g_bLoop )
	{
		Sleep(100);
		DWORD const dwCurTime = g_kTestTime.GetTime32();
		DWORD const dwGap = dwCurTime - dwLastGenTime;
		if ( dwGap < g_dwGetPeriod )
		{
			if ( ++dwNoGenLoopCount > dwMaxGenLoopCount )
			{
				INFO_LOG( BM::LOG_LV6, L"Gen TimeError...... NowTime[" << dwCurTime << L"] LastTime[" << dwLastGenTime << L"] GapTime[" << dwGap << L"]");
			}
		}
		else
		{
			INFO_LOG( BM::LOG_LV6, ++dwMonsterGenCount << L". Gen NowTime[" << dwCurTime << L"] LastTime[" << dwLastGenTime << L"]");
			dwLastGenTime = dwCurTime;
			dwNoGenLoopCount = 0;
		}
	}
 
	return 0;
}

bool CALLBACK OnEscape( unsigned short const &rkInputKey)
{
	std::wcout<< __FUNCTIONW__ << std::endl;
	g_kConsoleCommander.StopSignal(true);
	return true;
}

bool CALLBACK OnF1( unsigned short const &rkInputKey)
{
	INFO_LOG( BM::LOG_LV6, L"NowTime : " << g_kTestTime.GetTime32() );
	return true;
}

bool CALLBACK OnF2( unsigned short const &rkInputKey)
{
	DWORD const dwTime = static_cast<DWORD>(::GetPrivateProfileIntW( L"TIME", L"INITTIME", 0, _T("./Config.ini") ));
	g_kTestTime.InitTime32(dwTime);
	INFO_LOG( BM::LOG_LV6, L"NowTime : " << g_kTestTime.GetTime32() );
	return true;
}



int _tmain(int argc, _TCHAR* argv[])
{
	HINSTANCE hInstance = ShellExecute(NULL, _T("open") , _T("http://www.naver.com"), _T("http://www.naver.com"), NULL, SW_SHOWNORMAL);	

	while (true)
	{
		Sleep(500);
	}
}

