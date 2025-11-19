//!  MachineController.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//! 
#include "stdafx.h"
#include <Mmsystem.h>
#include "Global.h"
#include "PgRecvFromCenter.h"
#include "PgRecvFromServer.h"
#include "PgKeyEvent.h"
#include "PgClientMng.h"
#include "PgServerController.h"

void CALLBACK OnRegist(const CEL::SRegistResult &rkArg)
{
	if( CEL::CRV_SUCCESS == rkArg.iRet )
	{
		g_kProcessCfg.SetRegistComplete( rkArg.guidOrder );
	}
	else
	{
		assert( NULL );
	}

	if (rkArg.guidOrder == g_kController.m_kConnectorOrderGuid)
	{
		g_kController.m_kConnectorObjGuid = rkArg.guidObj;
	}
	else if (rkArg.guidOrder == g_kClientMng.GetAcceptorOrderGuid())
	{
		g_kClientMng.SetAcceptorOrderGuid(rkArg.guidObj);
	}

	if( g_kProcessCfg.IsRegistAllComplete() )
	{//추가 등록 완료
		INFO_LOG( BM::LOG_LV6, _T("[%s]-[%d] 등록 대기 목록 모두 완료"), _T(__FUNCTION__), __LINE__ );

		g_kCoreCenter.SvcStart();
	
		INFO_LOG( BM::LOG_LV6, _T("[%s]-[%d] 서비스 스타트"), _T(__FUNCTION__), __LINE__ );
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	SET_GLOBAL_EXCEPTION_FILTER();

	TCHAR chLog[20];
	_stprintf_s(chLog, 20, _T("MCONTROL%04d"), g_kProcessCfg.ServerNo());
	INIT_LOG2(chLog);

	if (!ReadConfigFile())
	{
		return 0;
	}
	//TBL_SERVERLIST kMyInfo;
	{
		std::vector<TBL_SERVERLIST> kVec;
		if (!g_kProcessCfg.GetServerInfo(CEL::ST_MACHINE_CONTROL, kVec))
		{
			return 0;
		}
	}

	//g_kProcessCfg.SetProcessIndex(kVec[0].iServerNo); 보류 <070730 육정범>
	g_kProcessCfg.SetServerType(CEL::ST_MACHINE_CONTROL);
	if( !g_kProcessCfg.ParseArg(argc, argv) ){return 0;}
	

	CEL::INIT_CENTER_DESC kCenterInit;
	kCenterInit.eOT = BM::OUTPUT_ALL;
	kCenterInit.pOnRegist = OnRegist;
	g_kCoreCenter.Init(kCenterInit);
	{// TIMER Register
		//CEL::REGIST_TIMER_DESC kInit;
		//kInit.pFunc = TimerTick;	// TickTimer
		//kInit.dwInterval = 100;		// 10 frames/sec
		//g_kProcessCfg.AddRegist( g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &kInit, sizeof(kInit) ) );
	}

	{// Connector Register
		CEL::INIT_CORE_DESC kInit;
		kInit.OnSessionOpen	= OnConnectToCenter;
		kInit.OnDisconnect	= OnDisconnectFromCenter;
		kInit.OnRecv		= OnRecvFromCenter;
		kInit.dwKeepAliveTime	= 600000;
		g_kController.m_kConnectorOrderGuid = g_kCoreCenter.Regist(CEL::RT_CONNECTOR, &kInit, sizeof(kInit));
		g_kProcessCfg.AddRegist(g_kController.m_kConnectorOrderGuid);
	}
	{// Acceptor Register
		std::vector<TBL_SERVERLIST> kVec;
		if (!g_kProcessCfg.GetServerInfo(CEL::ST_MACHINE_CONTROL, kVec))
		{
			return 0;
		}
		TBL_SERVERLIST kServer = kVec[0];

		CEL::INIT_CORE_DESC kInit;
		kInit.BindAddr.Set( kServer.addrUserNat.StrIP() , kServer.addrUserNat.wPort );
		kInit.OnSessionOpen	= OnConnectFromManager;
		kInit.OnDisconnect	= OnDisconnectFromManager;
		kInit.OnRecv			= OnRecvFromManager;
		kInit.dwKeepAliveTime		= 600000;
		g_kClientMng.SetAcceptorOrderGuid(g_kCoreCenter.Regist( CEL::RT_ACCEPTOR, &kInit, sizeof( kInit ) ));
		g_kProcessCfg.AddRegist( g_kClientMng.GetAcceptorOrderGuid() );
	}
	{// Timer
		CEL::REGIST_TIMER_DESC kInit;
		kInit.pFunc = TimerTick;	// TickTimer
		kInit.dwInterval = 3000;
		g_kProcessCfg.AddRegist(kInit.kOrderGuid);
		g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &kInit, sizeof(kInit));
	}

	if(!RegistKeyEvent()){ return 0; }

	{//
		TCHAR chTitle[100];
		std::vector<TBL_SERVERLIST> kVec;
		if (!g_kProcessCfg.GetServerInfo(CEL::ST_MACHINE_CONTROL, kVec))
		{
			return 0;
		}
		TBL_SERVERLIST kServer = kVec[0];
		_stprintf_s(chTitle, 100, _T("MachineController IP[%s], Port[%hd]"), kServer.addrUserNat.StrIP().c_str(), kServer.addrUserNat.wPort);
		::SetConsoleTitle(chTitle);
	}

	std::cout<< "== Start Server Process ==" << std::endl;
	ConsoleCommander.MainLoof();

	g_kCoreCenter.Close();
	return 0;
}

void CALLBACK TimerTick(DWORD dwUserData)
{
	unsigned long ulNow = ::timeGetTime();
	g_kClientMng.CheckUserSession(ulNow);
}
