// MCtrlServer.cpp : Defines the entry point for the console application.
//
//GameServerMgr	(중앙이 전체 게임 서버 정보 관리용도)
//	게임 서버 정보
//	서브 들의 정보로 부터 -> On/Off 라인 판독 및 Tool에 정보 제공
//
//MCtrlServerMgr	(서브/중앙 용도의 게임서버 컨트롤러)
//	서버 프로세스 생성
//	관리
//	종료
//	긴급 종료 처리

#include "stdafx.h"

#include "PgKeyEvent.h"
#include "PgMMCMgr.h"
#include "PgImmigrationServerMgr.h"
#include "PgRecvFromSMC.h"
#include "PgRecvFromImmigration.h"
#include "PgRecvFromMonTool.h"
#include "Lohengrin/MiniDump2.h"
#include "Lohengrin/DB.h"
#include "DataPack/Common.h"

#include "PgSiteMgr.h"

bool RegistAcceptor(TBL_SERVERLIST const &rkServerInfo)
{
{
	CEL::ADDR_INFO const &rkBindAddr= rkServerInfo.addrUserBind;
	CEL::ADDR_INFO const &rkNATAddr = rkServerInfo.addrUserNat;

	if(rkBindAddr.wPort)
	{
		if(g_kCoreCenter.IsExistAcceptor(rkBindAddr))
		{
			return false;//Already In Use
		}

		CEL::INIT_CORE_DESC kInit;
		kInit.kBindAddr = rkBindAddr;
		kInit.kNATAddr = rkNATAddr;

		kInit.OnSessionOpen		= OnAcceptMonTool;
		kInit.OnDisconnect		= OnDisConnectToMonTool;
		kInit.OnRecv			= OnRecvFromMonTool;
		kInit.bIsImmidiateActivate	= true;
		kInit.IdentityValue(CEL::ST_NONE);
		kInit.ServiceHandlerType(CEL::SHT_SERVER);
		
		INFO_LOG(BM::LOG_LV6, __FL__ << _T("Try Regist Acceptor [") << rkBindAddr.ToString().c_str() << _T("]") );
//		INFO_LOG(BM::LOG_LV6, _T("[%s] Try Regist Acceptor [%s]"), __FUNCTIONW__, rkBindAddr.ToString().c_str());

		g_kCoreCenter.Regist(CEL::RT_ACCEPTOR, &kInit);
	}
	else
	{
		ASSERT_LOG(false, BM::LOG_LV1, __FL__ << _T("Incorrect Acceptor Addr [") << rkBindAddr.ToString().c_str() << _T("]") );
//		VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Incorrect Acceptor Addr [%s]"), __FUNCTIONW__, __LINE__, rkBindAddr.ToString().c_str());
	}
}
{
	CEL::ADDR_INFO const &rkBindAddr= rkServerInfo.addrServerBind;
	CEL::ADDR_INFO const &rkNATAddr = rkServerInfo.addrServerNat;

	if(rkBindAddr.wPort)
	{
		if(g_kCoreCenter.IsExistAcceptor(rkBindAddr))
		{
			return false;//Already In Use
		}

		CEL::INIT_CORE_DESC kInit;
		kInit.kBindAddr = rkBindAddr;
		kInit.kNATAddr = rkNATAddr;

		//SMS Acceptor
		kInit.OnSessionOpen		= OnAcceptFromSMC;
		kInit.OnDisconnect		= OnDisConnectToSMC;
		kInit.OnRecv			= OnRecvFromSMC;
		kInit.bIsImmidiateActivate	= true;
		kInit.IdentityValue(CEL::ST_SUB_MACHINE_CONTROL);
		kInit.ServiceHandlerType(CEL::SHT_FILE_SERVER);//MMC는 압축 때문에 

		INFO_LOG(BM::LOG_LV6, __FL__ << _T("Try Regist Acceptor [") << rkBindAddr.ToString().c_str() << _T("]") );
//		INFO_LOG(BM::LOG_LV6, _T("[%s] Try Regist Acceptor [%s]"), __FUNCTIONW__, rkBindAddr.ToString().c_str());

		g_kCoreCenter.Regist(CEL::RT_ACCEPTOR, &kInit);

		return true;
	}
	else
	{
		ASSERT_LOG(false, BM::LOG_LV1, __FL__ << _T("Incorrect Acceptor Addr [") << rkBindAddr.ToString().c_str() << _T("]") );
//		VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] Incorrect Acceptor Addr [%s]"), __FUNCTIONW__, __LINE__, rkBindAddr.ToString().c_str());
	}
}
	return false;
}

void CALLBACK Timer_ServerState(DWORD dwUserData)
{
	if(!g_kMMCMgr.IsSyncIng()
		&& g_kMMCMgr.IsConnectionTool())
	{
		g_kMMCMgr.CheckServerStatus();
	}
}

HRESULT CALLBACK OnDB_EXECUTE( CEL::DB_RESULT &rkResult )
{
	DWORD const dwStart = ::timeGetTime();
	switch(rkResult.QueryType())
	{
	case DQT_LOAD_SITE_CONFIG:
		{
			g_kSiteMgr.Q_DQT_LOAD_SITE_CONFIG(rkResult);
		}break;
	case DQT_LOAD_REALM_CONFIG:
		{
			g_kSiteMgr.Q_DQT_LOAD_REALM_CONFIG(rkResult);
		}break;
	}
	return S_OK;
}

HRESULT CALLBACK OnDB_EXECUTE_TRAN( CEL::DB_RESULT_TRAN &)
{
	return S_OK;
}

bool LoadDB()
{
	g_kSiteMgr.LoadFromDB();

	CONT_SERVER_HASH kContServer;
	g_kProcessCfg.Locked_GetServerInfo(CEL::ST_NONE, kContServer);
//	g_kServerSessionMgr.Init(kContServer);

	SERVER_IDENTITY const &kSI = g_kProcessCfg.ServerIdentity();
	
	CONT_REALM_CANDIDATE kContRealmCandi;
	g_kSiteMgr.GetRealmCandi(kContRealmCandi);
	
	if(g_kRealmMgr.Init(kContRealmCandi, kContServer))//렐름 정보 빌드
	{
		TBL_SERVERLIST kTblServer;
		if(S_OK == g_kProcessCfg.Locked_GetServerInfo(kSI, kTblServer))//자신 정보로 서버엑셉터 등록함. DB로드는 SvcStart 전이라.
		{
			g_kMMCMgr.PrepareStateCont();
			RegistAcceptor(kTblServer);
		}
		else
		{
			ASSERT_LOG(false, BM::LOG_LV0, __FL__ << _T("None Server Identity Type[") << kSI.nServerType << _T("] Chn[") << kSI.nChannel << _T("] No[") << kSI.nServerNo << _T("]") );
//			VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("None Server Identity Type[%d] Chn[%d] No[%d]"),kSI.nServerType, kSI.nChannel, kSI.nServerNo);
			return false;
		}
	}

	return true;
}

void CALLBACK OnRegist(CEL::SRegistResult const &rkArg)//쓰레드가 정상 등록되면 CallBack
{
	if( rkArg.iRet != CEL::CRV_SUCCESS)
	{
		ASSERT_LOG(false, BM::LOG_LV1, __FL__ << _T("OnRegist Failed") );
//		VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] OnRegist Failed"), __FUNCTIONW__, __LINE__);
	}

	if( CEL::RT_CONNECTOR == rkArg.eType )
	{
		switch(rkArg.iIdentityValue)
		{
		case CEL::ST_IMMIGRATION:
			{
				g_kProcessCfg.ImmigrationConnector(rkArg.guidObj);
				g_kProcessCfg.Locked_ConnectImmigration();

				INFO_LOG(BM::LOG_LV8, __FL__ << _T("Regist Connector From ImmigrationServer") );
//				INFO_LOG(BM::LOG_LV8, _T("[%s]-[%d] Regist Connector From ImmigrationServer"), __FUNCTIONW__, __LINE__);
			}break;
		default:
			{
				ASSERT_LOG(false, BM::LOG_LV0, _T("============ Connector!!!! ======================") );
//				VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("============ Connector!!!! ======================"));
			}break;
		}
	}

	if( CEL::RT_ACCEPTOR == rkArg.eType )
	{
		switch(rkArg.iIdentityValue)
		{
		case CEL::ST_NONE://For Tool 
		case CEL::ST_SUB_MACHINE_CONTROL:// SUb Machine
			{
			}break;
		default:
			{
				ASSERT_LOG( false, BM::LOG_LV0, _T("============ Incorrect Acceptor!!!! ======================") );
//				VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("============ Incorrect Acceptor!!!! ======================"));
			}break;
		}
	}
	
	if( CEL::RT_DB_WORKER == rkArg.eType )
	{// SiteServer 만 읽어온다.
		if(LoadDB())
		{
			CONT_SERVER_HASH kServer;
			g_kProcessCfg.Locked_GetServerInfo(CEL::ST_IMMIGRATION, kServer);

			if(1 == kServer.size())
			{
				CONT_SERVER_HASH::const_iterator server_itor = kServer.begin();
				g_kProcessCfg.ImmigrationServerAddr(server_itor->second.addrServerNat);
			}
		}
	}

	if( CEL::RT_FINAL_SIGNAL == rkArg.eType )
	{
		if(g_kCoreCenter.SvcStart())
		{
			INFO_LOG(BM::LOG_LV6, _T("==================================================") );
			INFO_LOG(BM::LOG_LV6, _T("============ CoreCenter Run ======================") );
			INFO_LOG(BM::LOG_LV6, _T("==================================================") );

//			INFO_LOG(BM::LOG_LV6, _T("=================================================="));
//			INFO_LOG(BM::LOG_LV6, _T("============ CoreCenter Run ======================"));
//			INFO_LOG(BM::LOG_LV6, _T("=================================================="));
		}
		else
		{
			ASSERT_LOG(false, BM::LOG_LV0, _T("============ CoreCenter Cannot Run!!!! ======================") );
//			VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("============ CoreCenter Cannot Run!!!! ======================"));
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if(!g_kLocal.LoadFromINI())
	{
		std::cout << "Can't Load Local.ini" << std::endl;
		system("pause");
		return 0;
//		VERIFY_INFO_LOG(false, BM::LOG_LV0, __FL__ << _T("Can't Load Local.ini") );
//		INFO_LOG( BM::LOG_LV0, _T("[%s]-[%d] Can't Load Local.ini"), __FUNCTIONW__, __LINE__);
//		return false;
	}
#ifndef _DEBUG
	SET_GLOBAL_EXCEPTION_FILTER();
	CMiniDump2::Install(CMiniDump2::DUMP_LEVEL_HEAVY);
#endif
	::CoInitialize(NULL);

	if(!g_kMMCMgr.ReadConfigFile() )//Read config
	{
		std::cout << "Can't Load MMC.ini" << std::endl;
		system("pause");
		return 0;
	}

	g_kProcessCfg.Locked_SetServerType(CEL::ST_MACHINE_CONTROL);
	if( !g_kProcessCfg.Locked_ParseArg(argc, argv) )
	{
		std::cout << "Error Arg" << std::endl;
		system("pause");
		return 0;
	}

	TCHAR chLog[MAX_PATH] = {0,};
	_stprintf_s(chLog, _countof(chLog), _T("R%dC%d_MMC%04d"), g_kProcessCfg.RealmNo(), g_kProcessCfg.ChannelNo(), g_kProcessCfg.ServerNo());
	std::wstring kLogFolder;
	InitLog(kLogFolder, chLog, BM::OUTPUT_ALL, _T("../LogFiles/"));

	TCHAR chProductVersion[80] = {0, }, chFileVersion[80] = {0, };
	g_kProcessCfg.Locked_GetVersion(80, chFileVersion, 80, chProductVersion);

	INFO_LOG(BM::LOG_LV7, _T("==================== Server Initialize Start ====================") );
	INFO_LOG(BM::LOG_LV7, _T("Product Version : ") << chProductVersion );
	INFO_LOG(BM::LOG_LV7, _T("File Version : ") << chFileVersion );
	INFO_LOG(BM::LOG_LV7, _T("Protocol Version : ") << PACKET_VERSION_S);

/*
	INFO_LOG(BM::LOG_LV7, _T("==================== Server Initialize Start ===================="));
	INFO_LOG(BM::LOG_LV7, _T("Product Version : %s"), chProductVersion);
	INFO_LOG(BM::LOG_LV7, _T("File Version : %s"), chFileVersion);
	INFO_LOG(BM::LOG_LV7, _T("Protocol Version : %s"), PACKET_VERSION);
*/

	BM::CPackInfo kPackInfo;
	kPackInfo.Init();
	if(!BM::PgDataPackManager::Init(kPackInfo))
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__ << _T("BM::PgDataPackManager Init Failed") );
	}

	CEL::INIT_CENTER_DESC kManagementServerInit;
	kManagementServerInit.eOT = BM::OUTPUT_ALL;
	kManagementServerInit.pOnRegist = OnRegist;
	kManagementServerInit.bIsUseDBWorker = true;
	kManagementServerInit.m_kCelLogFolder = kLogFolder;

	g_kCoreCenter.Init(kManagementServerInit);

	CONT_DB_INIT_DESC kContDBInit;

	if(g_kProcessCfg.RunMode() == CProcessConfig::E_RunMode_ReadIni)
	{
		if(!ReadDBConfig( EConfigType_Ini, L"", g_kProcessCfg.ServerIdentity(), kContDBInit ) )
		{
			CAUTION_LOG( BM::LOG_LV0, _T("Load From \"DB_Config.ini\" Error!!") );
			system("pause");
			return 0;
		}
	}
	else
	{
		if(!ReadDBConfig( EConfigType_Inb, L"", g_kProcessCfg.ServerIdentity(), kContDBInit ) )
		{
			CAUTION_LOG( BM::LOG_LV0, _T("Load From \"DB_Config.inb\" Error!!") );
			system("pause");
			return 0;
		}
	}

	CONT_DB_INIT_DESC::iterator dbinit_itor = kContDBInit.begin();
	while(dbinit_itor != kContDBInit.end())
	{
		CEL::INIT_DB_DESC &kDBInit = (*dbinit_itor);
		
		kDBInit.bUseConsoleLog = false;
		kDBInit.OnDBExecute = OnDB_EXECUTE;
		kDBInit.OnDBExecuteTran = OnDB_EXECUTE_TRAN;
		kDBInit.dwThreadCount = 1;
		kDBInit.m_kLogFolder = kLogFolder;

		g_kCoreCenter.Regist(CEL::RT_DB_WORKER, &kDBInit);
		++dbinit_itor;
	}

	CEL::INIT_CORE_DESC kImmConnectorInit;
	kImmConnectorInit.OnSessionOpen	= OnConnectToImmigration;
	kImmConnectorInit.OnDisconnect	= OnDisConnectToImmigration;
	kImmConnectorInit.OnRecv			= OnRecvFromImmigration;
	kImmConnectorInit.IdentityValue(CEL::ST_IMMIGRATION);
	kImmConnectorInit.ServiceHandlerType(CEL::SHT_SERVER);
	
	g_kCoreCenter.Regist(CEL::RT_CONNECTOR, &kImmConnectorInit);

	//서버 상태 받아올 타이머 설정
	CEL::REGIST_TIMER_DESC kTimerInit;
	kTimerInit.pFunc = Timer_ServerState;
	kTimerInit.dwInterval = g_kMMCMgr.IntervalTime() * 1000;

	g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &kTimerInit);

	CEL::INIT_FINAL_SIGNAL kFinalInit;
	kFinalInit.kIdentity = 0;
	g_kCoreCenter.Regist(CEL::RT_FINAL_SIGNAL, &kFinalInit);

	if( !RegistKeyEvent() ){ return 0; }

	g_kProcessCfg.Locked_SetConsoleTitle();

	g_kConsoleCommander.MainLoof();

	// 서비스 종료
	g_kCoreCenter.Close();
	::CoUninitialize();

	return 0;
}
