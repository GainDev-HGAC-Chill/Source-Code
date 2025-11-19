#include "stdafx.h"
#include "PgMMCMgr.h"
#include "PgImmigrationServerMgr.h"

bool CALLBACK OnEscape( WORD const &InputKey)
{
#ifdef _DEBUG
	ConsoleCommander.StopSignal(true);
#else
	std::cout<< "Can't exit Machine Controller service." << std::endl;
#endif
	return false;
}


bool CALLBACK OnTerminateServer( WORD const &InputKey)
{
	INFO_LOG( BM::LOG_LV6, _T("==========================================================="));
	INFO_LOG( BM::LOG_LV6, _T("[MachineControl] will be shutdown"));
	INFO_LOG( BM::LOG_LV6, _T("\tIt takes some times depens on system....WAITING..."));
	INFO_LOG( BM::LOG_LV6, _T("==========================================================="));
	g_kConsoleCommander.StopSignal(true);
	INFO_LOG( BM::LOG_LV6, _T("=== Shutdonw END ====") );
	return false;
}

bool CALLBACK OnF5(WORD const &InputKey)
{
	INFO_LOG( BM::LOG_LV6, _T("RefreshState Start") );

	g_kMMCMgr.ReadConfigFile();
	g_kMMCMgr.NfyConfig();

	INFO_LOG( BM::LOG_LV6, __FL__ << _T("RefreshState Complete") );
	return false;
}

bool CALLBACK OnF8(WORD const &InputKey)
{
	INFO_LOG( BM::LOG_LV6, __FL__ << _T("ReSync Order Start") );

	g_kMMCMgr.NfyConfig();
	g_kMMCMgr.NfyReSync();

	INFO_LOG( BM::LOG_LV6, __FL__ << _T("ReSync Order Complete") );
	return false;
}

bool RegistKeyEvent()
{
	g_kConsoleCommander.Regist( VK_ESCAPE,	OnEscape );
	g_kConsoleCommander.Regist( VK_F5,		OnF5);
	g_kConsoleCommander.Regist( VK_F8,		OnF8);
	g_kConsoleCommander.Regist( VK_F11,	OnTerminateServer );
	return true;
}
