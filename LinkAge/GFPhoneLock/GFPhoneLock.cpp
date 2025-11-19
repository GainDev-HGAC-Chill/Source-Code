// GFPhoneLock.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "PgRecvFromServer.h"
#include "PgPhoneLockMgr.h"

void CALLBACK OnRegist(CEL::SRegistResult const &rkArg)
{
	if( rkArg.iRet != CEL::CRV_SUCCESS)
	{
		std::cout << "OnRegist Error" << std::endl;
	}

	switch ( rkArg.eType )
	{
	case CEL::RT_ACCEPTOR:
		{
		}break;
	case CEL::RT_FINAL_SIGNAL:
		{//추가 등록 완료
			if( true == g_kCoreCenter.SvcStart() )
			{
				std::cout << "==================================================" << std::endl;
				std::cout << "============ CoreCenter Run ======================" << std::endl;
				std::cout << "==================================================" << std::endl;
			}
		}break;
	default:
		{
		}break;
	}
}

bool CALLBACK OnTerminateServer(WORD const& wExitCode)
{
	g_kConsoleCommander.StopSignal(true);
	return true;
}

bool CALLBACK OnF1( WORD const &InputKey)
{
	std::cout << "[Display Lock ID List] -------------------------" << std::endl;
	g_kPhoneLockMgr.DisplayAll();
	std::cout << "[Display Lock ID List] =========================" << std::endl;
	return true;
}

bool CALLBACK OnF2( WORD const &InputKey)
{
	std::cout << " * Input UnLock ID : ";

	wchar_t wszTemp[100] = {0,};
	std::wcin >> wszTemp;

	std::wstring wstrID(wszTemp);
	UPR(wstrID);

	g_kPhoneLockMgr.UnLock( wstrID );
	return true;
}

bool CALLBACK OnF3( WORD const &InputKey)
{
	std::cout << "[Start All ID UnLock]-------------------------" << std::endl;
	g_kPhoneLockMgr.UnLockAll();
	std::cout << "[End All ID UnLock]-------------------------" << std::endl;
	return true;
}

bool CALLBACK OnF11( WORD const &InputKey)
{
	return OnTerminateServer(E_Terminate_By_Console);
}

void RegistKeyEvent()
{
	g_kConsoleCommander.Regist( VK_F1,		OnF1 );
	g_kConsoleCommander.Regist( VK_F2,		OnF2 );
	g_kConsoleCommander.Regist( VK_F3,		OnF3 );
	g_kConsoleCommander.Regist( VK_F11,		OnF11 );
}

int _tmain(int argc, _TCHAR* argv[])
{
	::CoInitialize( NULL );

	TCHAR chLog[20];
	_stprintf_s(chLog, 20, _T("GFPhoneLock"), g_kProcessCfg.ServerNo() );

	{
		CEL::INIT_CENTER_DESC kCenterInit;
		kCenterInit.eOT = BM::OUTPUT_ALL;
		kCenterInit.pOnRegist = OnRegist;
		kCenterInit.dwProactorThreadCount = __min( kCenterInit.dwProactorThreadCount, 5);
		kCenterInit.m_kCelLogFolder = chLog;
		g_kCoreCenter.Init(kCenterInit);
	}

	{
		TCHAR wszIP[MAX_PATH] = {0,};
		::GetPrivateProfileString( _T("PHONELOCK"), _T("IP"), _T("0.0.0.0"), wszIP, MAX_PATH, _T("./Config.ini") );

		WORD const nPort = static_cast<WORD>(::GetPrivateProfileInt( _T("PHONELOCK"), _T("PORT"), 0, _T("./Config.ini") ));
		
		CEL::INIT_CORE_DESC kAcceptorInit;
		kAcceptorInit.kBindAddr.Set( std::wstring(wszIP), nPort );
		kAcceptorInit.kNATAddr = kAcceptorInit.kBindAddr;

		kAcceptorInit.OnSessionOpen		= OnAcceptFromServer;
		kAcceptorInit.OnDisconnect		= OnDisConnectFromServer;
		kAcceptorInit.OnRecv			= OnRecvFromServer;
		kAcceptorInit.bIsImmidiateActivate = true;
		kAcceptorInit.IdentityValue( CEL::ST_AP );
		kAcceptorInit.ServiceHandlerType( CEL::SHT_GF );
		g_kCoreCenter.Regist( CEL::RT_ACCEPTOR, &kAcceptorInit);
	}

	{
		CEL::REGIST_TIMER_DESC kInitTimer;
		kInitTimer.pFunc = Timer;
		kInitTimer.dwInterval = 1000;
		g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &kInitTimer);
	}

	{
		CEL::INIT_FINAL_SIGNAL kFinalInit;
		g_kCoreCenter.Regist(CEL::RT_FINAL_SIGNAL, &kFinalInit);
	}

	RegistKeyEvent();

	std::cout<< "-- Started --" << std::endl;

	g_kConsoleCommander.MainLoof();

	// 서비스 종료
	g_kCoreCenter.Close();
	::CoUninitialize();

	return 0;
}

