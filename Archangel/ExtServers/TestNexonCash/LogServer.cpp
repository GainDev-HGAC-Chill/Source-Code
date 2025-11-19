#include "stdafx.h"
#include "BM/ExceptionFilter.h"
#include "BM/LocalMgr.h"
#include "CEL\ConsoleCommander.h"
#include "Lohengrin/MiniDump2.h"
#include "Variant/PgMCtrl.h"
#include "constant.h"

#include "PgKeyEvent.h"
#include "PgRecvFromImmigration.h"
#include "PgTimer.h"

//로그 서버 룰.
//다른 서버가 로그서버로 붙어라. -> 개별서버가 다 붙을꺼냐?.
//로그서버는 따로 로그 DB를 사용.
//로그를 DB에 박는거는 다른 Task 를 이용.

void CALLBACK OnRegist(CEL::SRegistResult const &rkArg)
{
	if( rkArg.iRet != CEL::CRV_SUCCESS)
	{
		VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T(" OnRegist Failed") );
	}

	if( CEL::RT_ACCEPTOR == rkArg.eType )
	{
		INFO_LOG( BM::LOG_LV0, _T("Acceptor Init") );
	}

	if( CEL::RT_FINAL_SIGNAL == rkArg.eType )
	{//추가 등록 완료
		if(g_kCoreCenter.SvcStart())
		{
			INFO_LOG( BM::LOG_LV6, _T("==================================================") );
			INFO_LOG( BM::LOG_LV6, _T("============ CoreCenter Run ======================") );
			INFO_LOG( BM::LOG_LV6, _T("==================================================") );

			CEL::DB_QUERY kQuery(DT_LOG, DQT_DEF_WRITEMODE, L"EXEC [dbo].[up_LoadDefWriteMode]");
			g_kCoreCenter.PushQuery(kQuery);
		}
		else
		{
			VERIFY_INFO_LOG( false, BM::LOG_LV0, _T("============ CoreCenter Cannot Run!!!! ======================") );
		}
	}
}

void GlobalInit()
{
	g_kTerminateFunc = OnTerminateServer;//Init MCtrl
}

int CALLBACK ExceptionTerminate(void)
{
	g_kLogWorker.VDeactivate();
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	short kZ = 16;

	BYTE abyAA[2] = {0x00,0x10};
	short kX  = MAKEWORD(abyAA[1], abyAA[0]);


	g_kCoreCenter;//인스턴스 생성.

#ifndef _DEBUG
	PgExceptionFilter::Install( PgExceptionFilter::DUMP_LEVEL_HEAVY, PgExceptionFilter::DUMP_OP_Exit_Program|PgExceptionFilter::DUMP_OP_UseTimeInDumpFile, ExceptionTerminate );
#endif

	GlobalInit();

	g_kProcessCfg.Locked_SetConfigDirectory();
	if(!g_kLocal.LoadFromINI(g_kProcessCfg.ConfigDir() + L"Local.ini"))
	{
		ASSERT_LOG(false, BM::LOG_LV0, __FL__ << L"[%s]-[%d] Can't Load Local.ini");
		return false;
	}

	std::wstring kLogFolder;
	{
		TCHAR chLog[MAX_PATH] = {0,};
		_stprintf_s( chLog, _countof(chLog), _T("R%dC%d_LOG%04d"), g_kProcessCfg.RealmNo(), g_kProcessCfg.ChannelNo(), g_kProcessCfg.ServerNo() );
		InitLog( kLogFolder, chLog, BM::OUTPUT_ALL );
	}

	TCHAR chProductVersion[80], chFileVersion[80];
	g_kProcessCfg.Locked_GetVersion(80, chFileVersion, 80, chProductVersion);
	INFO_LOG( BM::LOG_LV6, _T("==================== Server Initialize Start ====================") );
	INFO_LOG( BM::LOG_LV6, _T("Product Version : ") << chProductVersion );
	INFO_LOG( BM::LOG_LV6, _T("File Version : ") << chFileVersion );
	INFO_LOG( BM::LOG_LV6, _T("Packet Version S : ") << PACKET_VERSION_S );

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
	kCenterInit.m_kCelLogFolder = kLogFolder;

	g_kCoreCenter.Init( kCenterInit );

	CEL::REGIST_TIMER_DESC kInit5sTimer;
	kInit5sTimer.pFunc = Timer5s;
	kInit5sTimer.dwInterval = 5000;
	kInit5sTimer.kOrderGuid.Generate();

	CEL::INIT_CORE_DESC kCashAcceptor;
	kCashAcceptor.kBindAddr.Set(L"127.0.0.1", 12345);
	kCashAcceptor.kNATAddr.Set(L"127.0.0.1", 12345);

	kCashAcceptor.OnSessionOpen		= OnConnectFromGame;
	kCashAcceptor.OnDisconnect		= OnDisConnectFromGame;
	kCashAcceptor.OnRecv			= OnRecvFromGame;
	kCashAcceptor.IdentityValue(CEL::ST_EXTERNAL1);
	kCashAcceptor.ServiceHandlerType(CEL::SHT_JAPAN);

	SYSTEM_INFO kSystemInfo;
	::GetSystemInfo(&kSystemInfo);
	
	g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &kInit5sTimer);
	g_kCoreCenter.Regist(CEL::RT_ACCEPTOR, &kCashAcceptor);
	
	CEL::INIT_FINAL_SIGNAL kFinalInit;
	g_kCoreCenter.Regist(CEL::RT_FINAL_SIGNAL, &kFinalInit);

	if(!RegistKeyEvent()){ return 0; }

	g_kProcessCfg.Locked_SetConsoleTitle();
	std::cout<< "== Start Server Process ==" << std::endl;
	//if (!g_kLogMgr.Locked_ReadConfigFile())
	//{
	//	ASSERT_LOG(false, BM::LOG_LV1, __FL__ << _T("Cannot read Config files"));
	//	return 0;
	//}

//	59.128.93.158 TCP 9006


	g_kConsoleCommander.MainLoof();
	g_kLogWorker.VDeactivate();
	g_kCoreCenter.Close();
	return 0;
}