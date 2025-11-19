#include "stdafx.h"
#include "Lohengrin/PacketStructLog.h"
#include "BM/ObjectPool.h"

#include "src/PgKeyEvent.h"
#include "src/PgTimer.h"
#include "PgLog.h"
#include "Variant/PgLogAction.h"
#include "Lohengrin/MiniDump2.h"

#include "Variant/PgMCtrl.h"
#include "PgDBProcess.h"


extern HRESULT Q_DQT_TEST( CEL::DB_RESULT &rkResult );
extern HRESULT Q_DQT_TEST2( CEL::DB_RESULT &rkResult );

//로그 서버 룰.
//다른 서버가 로그서버로 붙어라. -> 개별서버가 다 붙을꺼냐?.
//로그서버는 따로 로그 DB를 사용.
//로그를 DB에 박는거는 다른 Task 를 이용.
bool Q_DQT_LOG_TYPE( CEL::DB_RESULT &rkResult )
{
	CEL::DB_DATA_ARRAY::const_iterator itr = rkResult.vecArray.begin();
	CONT_LOG_TYPE kContLogType;
	

	while ( itr != rkResult.vecArray.end() )
	{
		int iType = 0;	
		short nMode = 0;
		itr->Pop( iType);		++itr;
		itr->Pop( nMode );		++itr;
		
		CONT_LOG_TYPE::_Pairib ret = kContLogType.insert(std::make_pair(iType,nMode));
		if(ret.second)
		{
			INFO_LOG(BM::LOG_LV7, _T("[ON_LOG_TYPE] %d / Mode : %d"), iType, nMode );
		}
		else
		{
			VERIFY_INFO_LOG(false, BM::LOG_LV7, _T("[ON_LOG_TYPE] %d / Mode : %d"), iType, nMode );
		}
	}

	g_kLog.Init( kContLogType );
	return true;
}

HRESULT Q_DQT_WRITE_LOG( CEL::DB_RESULT &rkResult )
{
	if(CEL::DR_SUCCESS != rkResult.eRet )
	{//실패로그는 파일로 남겨.
		CAUTION_LOG(BM::LOG_LV5,_T("[%s] Query Failed."),__FUNCTIONW__);
		return E_FAIL;
	}
	return S_OK;
}

bool Q_DQT_GET_ACTIVE_USER( CEL::DB_RESULT &rkResult)
{
	if(CEL::DR_SUCCESS != rkResult.eRet )
	{
		INFO_LOG(BM::LOG_LV5,_T("[%s] Query Failed."),__FUNCTIONW__);
		return false;
	}
	CEL::DB_DATA_ARRAY::const_iterator itr = rkResult.vecArray.begin();
	int iError = 0;
	int iActiveAccount = 0;
	while ( itr != rkResult.vecArray.end() )
	{
		itr->Pop( iError );			++itr;
		itr->Pop( iActiveAccount);	++itr;
		if( iError == 1)
			INFO_LOG(BM::LOG_LV7, _T("[%s] Sucess Get Active User Count : [%d]"), __FUNCTIONW__, iActiveAccount );
		else
			INFO_LOG(BM::LOG_LV7, _T("[%s] Failed Get Active User Count"), __FUNCTIONW__ );
	}
	return true;
}

LONG const MAX_TEST_QUERY_COUNT = 500;
LONG g_lCount = 0;
DWORD g_dwTickCount = 0;

bool Q_DQT_TEST_PROC1( CEL::DB_RESULT &rkResult)
{
	CEL::DB_DATA_ARRAY::iterator iter = rkResult.vecReturnArray.begin();
	int ival = 0;
	std::wstring wstrString;
	std::string strString;

	(*iter).Pop(ival); ++iter;
	(*iter).Pop(wstrString);++iter;
	(*iter).Pop(strString);++iter;
	(*iter).Pop(ival);++iter;

	return true;
}

LONG g_lCount2 = 0;
DWORD g_dwTickCount2 = 0;

bool Q_DQT_TEST_PROC2( CEL::DB_RESULT &rkResult)
{
	if(CEL::DR_SUCCESS != rkResult.eRet && CEL::DR_NO_RESULT != rkResult.eRet)
	{
		INFO_LOG(BM::LOG_LV5,_T("[%s] Query Failed."),__FUNCTIONW__);
		return false;
	}
	CEL::DB_DATA_ARRAY::const_iterator itr = rkResult.vecArray.begin();
	while ( itr != rkResult.vecArray.end() )
	{
		++itr;
	}

	InterlockedIncrement(&g_lCount2);

	LONG lTemp;
	InterlockedExchange(&lTemp,g_lCount2);

	if(lTemp == 1)
	{
		g_dwTickCount2 = GetTickCount();
	}
	else if(lTemp == MAX_TEST_QUERY_COUNT)
	{
		INFO_LOG(BM::LOG_LV5,_T("[%s] QUREY COMPLETE:%d ms"),__FUNCTIONW__,GetTickCount() - g_dwTickCount2);
		InterlockedExchange(&g_lCount2,0);
	}
	return true;
}

LONG g_lCount3 = 0;
DWORD g_dwTickCount3 = 0;

bool Q_DQT_TEST_PROC3( CEL::DB_RESULT &rkResult)
{
	if(CEL::DR_SUCCESS != rkResult.eRet )
	{
		INFO_LOG(BM::LOG_LV5,_T("[%s] Query Failed."),__FUNCTIONW__);
		return false;
	}
	CEL::DB_DATA_ARRAY::const_iterator itr = rkResult.vecArray.begin();
	while ( itr != rkResult.vecArray.end() )
	{
		++itr;
	}

	InterlockedIncrement(&g_lCount3);

	LONG lTemp;
	InterlockedExchange(&lTemp,g_lCount3);

	if(lTemp == 1)
	{
		g_dwTickCount3 = GetTickCount();
	}
	else if(lTemp == MAX_TEST_QUERY_COUNT)
	{
		INFO_LOG(BM::LOG_LV5,_T("[%s] QUREY COMPLETE:%d ms"),__FUNCTIONW__,GetTickCount() - g_dwTickCount3);
		InterlockedExchange(&g_lCount3,0);
	}
	return true;
}

LONG g_lCount4 = 0;
DWORD g_dwTickCount4 = 0;

bool Q_DQT_TEST_PROC4( CEL::DB_RESULT &rkResult)
{
	if(CEL::DR_SUCCESS != rkResult.eRet )
	{
		INFO_LOG(BM::LOG_LV5,_T("[%s] Query Failed."),__FUNCTIONW__);
		return false;
	}
	CEL::DB_DATA_ARRAY::const_iterator itr = rkResult.vecArray.begin();
	while ( itr != rkResult.vecArray.end() )
	{
		++itr;
	}

	InterlockedIncrement(&g_lCount4);

	LONG lTemp;
	InterlockedExchange(&lTemp,g_lCount4);

	if(lTemp == 1)
	{
		g_dwTickCount4 = GetTickCount();
	}
	else if(lTemp == MAX_TEST_QUERY_COUNT)
	{
		INFO_LOG(BM::LOG_LV5,_T("[%s] QUREY COMPLETE:%d ms"),__FUNCTIONW__,GetTickCount() - g_dwTickCount4);
		InterlockedExchange(&g_lCount4,0);
	}
	return true;
}

LONG g_lCount5 = 0;
DWORD g_dwTickCount5 = 0;

bool Q_DQT_TEST_PROC5( CEL::DB_RESULT &rkResult)
{
	if(CEL::DR_SUCCESS != rkResult.eRet )
	{
		INFO_LOG(BM::LOG_LV5,_T("[%s] Query Failed."),__FUNCTIONW__);
		return false;
	}
	CEL::DB_DATA_ARRAY::const_iterator itr = rkResult.vecArray.begin();
	while ( itr != rkResult.vecArray.end() )
	{
		++itr;
	}

	InterlockedIncrement(&g_lCount5);

	LONG lTemp;
	InterlockedExchange(&lTemp,g_lCount5);

	if(lTemp == 1)
	{
		g_dwTickCount5 = GetTickCount();
	}
	else if(lTemp == MAX_TEST_QUERY_COUNT)
	{
		INFO_LOG(BM::LOG_LV5,_T("[%s] QUREY COMPLETE:%d ms"),__FUNCTIONW__,GetTickCount() - g_dwTickCount5);
		InterlockedExchange(&g_lCount5,0);
	}
	return true;
}

HRESULT CALLBACK OnDB_EXECUTE(CEL::DB_RESULT &rkResult)
{
	switch(rkResult.QueryType())
	{
	case DQT_TEST:				{ return Q_DQT_TEST( rkResult); }break;//		{ Q_DQT_WRITE_LOG( rkResult );	}break;
	case DQT_TEST2:				{ return Q_DQT_TEST2( rkResult); }break;//		{ Q_DQT_WRITE_LOG( rkResult );	}break;
	case DQT_WRITE_LOG:			{ return Q_DQT_WRITE_LOG( rkResult); }break;//		{ Q_DQT_WRITE_LOG( rkResult );	}break;
	case DQT_LOG_TYPE:			{ return Q_DQT_LOG_TYPE( rkResult );	}break;
	case DQT_GET_ACTIVE_USER:	{ return Q_DQT_GET_ACTIVE_USER(rkResult); }break;
	case DQT_TEST_PROC1:		{ return Q_DQT_TEST_PROC1( rkResult);}break;
	case DQT_TEST_PROC2:		{ return Q_DQT_TEST_PROC2( rkResult);}break;
	case DQT_TEST_PROC3:		{ return Q_DQT_TEST_PROC3( rkResult);}break;
	case DQT_TEST_PROC4:		{ return Q_DQT_TEST_PROC4( rkResult);}break;
	case DQT_TEST_PROC5:		{ return Q_DQT_TEST_PROC5( rkResult);}break;
	default:
		{
		}break;
	}
	return S_OK;
}

HRESULT CALLBACK OnDB_EXECUTE_TRAN(CEL::DB_RESULT_TRAN &rkResult)
{
	return S_OK;
}


void CALLBACK OnRegist(CEL::SRegistResult const &rkArg)
{
	if( rkArg.iRet != CEL::CRV_SUCCESS)
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] OnRegist Failed"), __FUNCTIONW__, __LINE__);
	}

	if( CEL::RT_CONNECTOR == rkArg.eType )
	{
		switch(rkArg.iIdentityValue)
		{
		case CEL::ST_IMMIGRATION:
			{
				g_kProcessCfg.ImmigrationConnector(rkArg.guidObj);
				g_kProcessCfg.Locked_ConnectImmigration();
			}break;
		default:
			{
				VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("============ Connector!!!! ======================"));
			}break;
		}
	}

	if( CEL::RT_FINAL_SIGNAL == rkArg.eType )
	{//추가 등록 완료
		if(g_kCoreCenter.SvcStart())
		{
			INFO_LOG(BM::LOG_LV6, _T("=================================================="));
			INFO_LOG(BM::LOG_LV6, _T("============ CoreCenter Run ======================"));
			INFO_LOG(BM::LOG_LV6, _T("=================================================="));

//			CEL::DB_QUERY kQuery(DT_LOG, DQT_LOG_TYPE, L"EXEC [dbo].[UP_Log_Mode]");
//			g_kCoreCenter.PushQuery(kQuery);
		}
		else
		{
			VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("============ CoreCenter Cannot Run!!!! ======================"));
		}
	}
}

void GlobalInit()
{
	g_kTerminateFunc = OnTerminateServer;//Init MCtrl
}

int _tmain(int argc, _TCHAR* argv[])
{
#ifndef _DEBUG
	SET_GLOBAL_EXCEPTION_FILTER();
	CMiniDump2::Install(CMiniDump2::DUMP_LEVEL_HEAVY);
#endif

	GlobalInit();

	g_kProcessCfg.Locked_SetConfigDirectory();
	if(!g_kLocal.LoadFromINI(g_kProcessCfg.ConfigDir() + L"Local.ini"))
	{
		INFO_LOG( BM::LOG_LV0, _T("[%s]-[%d] Can't Load Local.ini"), __FUNCTIONW__, __LINE__);
		return false;
	}

	::CoInitialize( NULL );


//	{
//		CEL::CDBSession::CONT_DBBINDDATA kData;
//		kData.resize(100);
//	}



	g_kProcessCfg.Locked_SetServerType(CEL::ST_LOG);
//	if( !g_kProcessCfg.Locked_ParseArg(argc, argv) ){return 0;}

	TCHAR chLog[20];
	_stprintf_s(chLog, 20, _T("LOG%04d"), g_kProcessCfg.ServerNo());
	INIT_LOG2(chLog);

	TCHAR chProductVersion[80], chFileVersion[80];
	g_kProcessCfg.Locked_GetVersion(80, chFileVersion, 80, chProductVersion);
	INFO_LOG(BM::LOG_LV7, _T("Product Version : %s"), chProductVersion);
	INFO_LOG(BM::LOG_LV7, _T("File Version : %s"), chFileVersion);
	INFO_LOG(BM::LOG_LV7, _T("Protocol Version : %s"), PACKET_VERSION);

	//! 들어온 인자를 파싱해서.
	//! Connector와 Acceptor를 만든다.
	//! Conenctor로 Center로 접근.
	//! 본인의 서버타입을 보내고.
	//! 필요한 맵 혹은 기타 데이터를 요청한다.
	//! 이후 서비스 시작.

	CEL::INIT_CENTER_DESC kCenterInit;
	kCenterInit.eOT = BM::OUTPUT_JUST_TRACE;
	kCenterInit.pOnRegist = OnRegist;
	kCenterInit.bIsUseDBWorker = true;
	kCenterInit.dwProactorThreadCount = __min(kCenterInit.dwProactorThreadCount, 8);//서버가 있긴한데 뭐 빠를 필요는 없고 하니까.

	g_kCoreCenter.Init( kCenterInit );

	CONT_DB_INIT_DESC kContDBInit;


	ReadDBConfig( EConfigType_Ini, g_kProcessCfg.ConfigDir(), g_kProcessCfg.ServerIdentity(), kContDBInit );
/*
	CEL::REGIST_TIMER_DESC kInitHeartBeat;
	kInitHeartBeat.pFunc = Timer_HeartBeat;
	kInitHeartBeat.dwInterval = 5 * 1000;	// 10sec
	kInitHeartBeat.kOrderGuid.Generate();
*/
	CEL::REGIST_TIMER_DESC kInitTestDB;
	kInitTestDB.pFunc = Timer_TestDB;
	kInitTestDB.dwInterval = 1000;	// 10sec
	kInitTestDB.kOrderGuid.Generate();

	SYSTEM_INFO kSystemInfo;
	::GetSystemInfo(&kSystemInfo);

	CONT_DB_INIT_DESC::iterator dbinit_itor = kContDBInit.begin();
	while(dbinit_itor != kContDBInit.end())
	{
		CEL::INIT_DB_DESC &kDBInit = (*dbinit_itor);
		
		kDBInit.dwThreadCount = (kSystemInfo.dwNumberOfProcessors *2 +1);//로그 서버만.
		kDBInit.bUseConsoleLog = true;
		kDBInit.OnDBExecute = OnDB_EXECUTE;
		kDBInit.OnDBExecuteTran = OnDB_EXECUTE_TRAN;
		
		//1: 6200 개 남음	25000 개.
		//2: 6100 개 남음	19000 ~ 22000
			// 2번이 약간 더 빠름.
		g_kCoreCenter.Regist(CEL::RT_DB_WORKER, &kDBInit);
		++dbinit_itor;
	}


	CEL::INIT_FINAL_SIGNAL kFinalInit;
	g_kCoreCenter.Regist(CEL::RT_FINAL_SIGNAL, &kFinalInit);

	if(!RegistKeyEvent()){ return 0; }

	g_kProcessCfg.Locked_SetConsoleTitle();
	std::cout<< "== Start Server Process ==" << std::endl;
/*
	CEL::DB_QUERY kQuery(DT_LOG, DQT_TEST_PROC1, L"{?=call dbo.testproc(?,?,?,?)}");
	kQuery.PushParam(100);
	kQuery.PushParam(std::wstring(L""));
	kQuery.PushParam(std::string(""));
	kQuery.PushParam(100);
	g_kCoreCenter.PushQuery(kQuery,true);
*/
	ConsoleCommander.MainLoof();

	g_kCoreCenter.Close();
	return 0;
}


