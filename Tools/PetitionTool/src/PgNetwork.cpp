#include "StdAfx.h"
#include "PgNetwork.h"
#include "PgRecvFromLoginServer.h"
#include "Lohengrin/Minidump2.h"

void CALLBACK OnRegist(const CEL::SRegistResult &rkArg)//쓰레드가 정상 등록되면 CallBack
{
	if( rkArg.iRet != CEL::CRV_SUCCESS)
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] OnRegist Failed"), __FUNCTIONW__, __LINE__);
	}

	if( CEL::RT_CONNECTOR == rkArg.eType )
	{
		INFO_LOG(BM::LOG_LV8, _T("[%s]-[%d] RT_CONNECTOR"), __FUNCTIONW__, __LINE__);
		CEL::SESSION_KEY KSessionKey(rkArg.guidObj, BM::GUID::NullData());
		g_kNetwork.SessionKey(KSessionKey);
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


PgNetwork::PgNetwork(void)
{
	Connected(false);
}

PgNetwork::~PgNetwork(void)
{
}

bool PgNetwork::Initialize()
{
//	INIT_LOG2(_T("PetitionTool"));
	CMiniDump2::Install(CMiniDump2::DUMP_LEVEL_HEAVY);

	TCHAR chProductVersion[80], chFileVersion[80];
	g_kProcessCfg.Locked_GetVersion(80, chFileVersion, 80, chProductVersion);
	INFO_LOG(BM::LOG_LV7, _T("Product Version : %s"), chProductVersion);
	INFO_LOG(BM::LOG_LV7, _T("File Version : %s"), chFileVersion);
	INFO_LOG(BM::LOG_LV7, _T("Protocol Version : %s"), PACKET_VERSION);

	g_kProcessCfg.Locked_SetServerType(CEL::ST_GMSERVER);
	//if( !g_kProcessCfg.ParseArg(argc, argv) ){return 0;}
	
	CEL::INIT_CENTER_DESC kGMServerInit;
	kGMServerInit.eOT = BM::OUTPUT_ALL;
	kGMServerInit.pOnRegist = OnRegist;
	g_kCoreCenter.Init(kGMServerInit);

	//Login서버에 붙는 코드.
	{
		CEL::INIT_CORE_DESC kInit;
		kInit.OnSessionOpen	= OnConnectLoginServer;
		kInit.OnDisconnect	= OnDisconnectFromLoginServer;
		kInit.OnRecv		= OnRecvFromLoginServer;
		kInit.dwKeepAliveTime	= 600000;
//		kInit.ServiceHandlerType(2);
		Connector(kInit.kOrderGuid);
		g_kCoreCenter.Regist(CEL::RT_CONNECTOR, &kInit);
	}

	CEL::INIT_FINAL_SIGNAL kFinalInit;
	kFinalInit.kIdentity = 0;
	g_kCoreCenter.Regist(CEL::RT_FINAL_SIGNAL, &kFinalInit);

	std::wstring strTitle = L"PetitionTool";
//	g_kProcessCfg.GetConsoleTitle(strTitle);
	::SetConsoleTitle(strTitle.c_str());
	INFO_LOG(BM::LOG_LV7, _T("-- Started --"));
	return true;
}

bool PgNetwork::Terminate()
{
	ConsoleCommander.StopSignal(true);
	DisConnectServer();

	return true;
}

bool PgNetwork::ConnectServer()
{
	if(Connected())
	{
		INFO_LOG(BM::LOG_LV8, _T("Re login error"));
		return false;
	}
	CEL::ADDR_INFO kAddr;
	kAddr.Set(g_kProcessInfoMgr.kLoginServerIP(), (WORD)g_kProcessInfoMgr.dwLoginServerPort());

	Connected(true);

	return g_kCoreCenter.Connect( kAddr, m_kSessionKey);
}

bool PgNetwork::DisConnectServer()
{
	// 서비스 종료
	g_kCoreCenter.Terminate(SessionKey());
	g_kCoreCenter.Close();
	Connected(false);

	return true;
}

bool PgNetwork::SendToLoginServer(CEL::CPacket const &rkPacket)
{
	if(!g_kCoreCenter.Send(SessionKey(), rkPacket))
	{
		ShowMessageBox(NULL, 19997, 10001);		
		return false;
	}
	return  true;
}