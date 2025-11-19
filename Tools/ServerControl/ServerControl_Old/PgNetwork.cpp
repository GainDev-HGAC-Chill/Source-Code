#include "StdAfx.h"
#include "PgRecvFromManagementServer.h"
#include "PgGameServerMgr.h"
#include "PgNetwork.h"

void CALLBACK OnRegist(const CEL::SRegistResult &rkArg);

PgNetwork::PgNetwork(void)
{
	Connected(false);
}

PgNetwork::~PgNetwork(void)
{
}

bool PgNetwork::Initialize()
{
	INIT_LOG2(_T("ManagementServer_Terminal"));

	//::CoInitialize( NULL );

	//if (!ReadConfigFile())
	//{
	//	return 0;
	//}

	TCHAR chProductVersion[80], chFileVersion[80];
	g_kProcessCfg.GetVersion(80, chFileVersion, 80, chProductVersion);
	INFO_LOG(BM::LOG_LV7, _T("==================== Server Initialize Start ===================="));
	INFO_LOG(BM::LOG_LV7, _T("Product Version : %s"), chProductVersion);
	INFO_LOG(BM::LOG_LV7, _T("File Version : %s"), chFileVersion);
	INFO_LOG(BM::LOG_LV7, _T("Protocol Version : %s"), PACKET_VERSION);

	g_kProcessCfg.SetServerType(CEL::ST_MACHINE_CONTROL);
	//if( !g_kProcessCfg.ParseArg(argc, argv) ){return 0;}
	
	CEL::INIT_CENTER_DESC kManagementServerInit;
	kManagementServerInit.eOT = BM::OUTPUT_ALL;
	kManagementServerInit.pOnRegist = OnRegist;

	g_kCoreCenter.Init(kManagementServerInit);

	// 중앙 머신 컨트롤러에 붙는 코드.
	{
		CEL::INIT_CORE_DESC kInit;
		kInit.kBindAddr.Set(g_kGameServerMgr.m_wstrCenterManagementServerIP, g_kGameServerMgr.m_dwCenterManagementServerPort);
		kInit.OnSessionOpen	= OnConnectToManagementServer;
		kInit.OnDisconnect	= OnDisconnectFromManagementServer;
		kInit.OnRecv		= OnRecvFromManagementServer;
		kInit.dwKeepAliveTime	= 600000;
		ServerRegistGuid(kInit.kOrderGuid);
		g_kCoreCenter.Regist(CEL::RT_CONNECTOR, &kInit);
	}

	CEL::INIT_FINAL_SIGNAL kFinalInit;
	kFinalInit.kIdentity = 0;
	g_kCoreCenter.Regist(CEL::RT_FINAL_SIGNAL, &kFinalInit);

	std::wstring strTitle;
	g_kProcessCfg.GetConsoleTitle(strTitle, 0, 0, 0, L"", 0);
	::SetConsoleTitle(strTitle.c_str());

	INFO_LOG(BM::LOG_LV7, _T("-- Started --"));

	return true;
}

bool PgNetwork::Terminate()
{
	DisConnectServer();
	ConsoleCommander.StopSignal(true);

	return true;
}

bool PgNetwork::Send(const CEL::CPacket& rkPacket)
{
	return g_kCoreCenter.Send(SessionKey(), rkPacket);
}

bool PgNetwork::ConnectServer()
{
	if( Connected() )
	{
		INFO_LOG(BM::LOG_LV8, _T("Re login error"));
		return false;
	}
	else
	{
		ConnectMMS();
		Connected(true);
	}
	return true;
}

bool PgNetwork::DisConnectServer()
{
	// 서비스 종료
	//g_kCoreCenter.Close();
	g_kCoreCenter.Terminate(SessionKey());
	Connected(false);

	return true;
}

bool PgNetwork::ConnectMMS() //중앙 머신컨트롤러로 연결 시도
{
	CEL::ADDR_INFO kAddr;
	kAddr.Set(g_kGameServerMgr.m_wstrCenterManagementServerIP, (WORD)g_kGameServerMgr.m_dwCenterManagementServerPort);
	return g_kCoreCenter.Connect( kAddr, m_kSessionKey);
}

void CALLBACK OnRegist(const CEL::SRegistResult &rkArg)//쓰레드가 정상 등록되면 CallBack
{
	if( rkArg.iRet != CEL::CRV_SUCCESS)
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] OnRegist Failed"), __FUNCTIONW__, __LINE__);
	}

	if( CEL::RT_CONNECTOR == rkArg.eType )
	{
		INFO_LOG(BM::LOG_LV8, _T("[%s]-[%d] RT_CONNECTOR"), __FUNCTIONW__, __LINE__);
		CEL::SESSION_KEY kSessionKey(rkArg.guidObj, BM::GUID::NullData());
		g_kNetwork.SessionKey(kSessionKey);
	}

	if( CEL::RT_FINAL_SIGNAL == rkArg.eType )
	{
		if(g_kCoreCenter.SvcStart())
		{
			INFO_LOG(BM::LOG_LV6, _T("=================================================="));
			INFO_LOG(BM::LOG_LV6, _T("============ CoreCenter Run ======================"));
			INFO_LOG(BM::LOG_LV6, _T("=================================================="));
		}
		else
		{
			VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("============ CoreCenter Cannot Run!!!! ======================"));
		}
	}
}