#include "StdAfx.h"
#include "PgRecvFromGMServer.h"
#include "PgNetwork.h"

void CALLBACK OnRegist(const CEL::SRegistResult &rkArg);

PgNetwork::PgNetwork(void)
{
	m_bConnected = false;
	m_usChannel = 0;
}

PgNetwork::~PgNetwork(void)
{
}

bool PgNetwork::Initialize()
{
	INIT_LOG2(_T("GMTool"));

	TCHAR chProductVersion[80], chFileVersion[80];
	g_kProcessCfg.GetVersion(80, chFileVersion, 80, chProductVersion);
	INFO_LOG(BM::LOG_LV7, _T("Product Version : %s"), chProductVersion);
	INFO_LOG(BM::LOG_LV7, _T("File Version : %s"), chFileVersion);
	INFO_LOG(BM::LOG_LV7, _T("Protocol Version : %s"), PACKET_VERSION);

	g_kProcessCfg.SetServerType(CEL::ST_GMSERVER);
	//if( !g_kProcessCfg.ParseArg(argc, argv) ){return 0;}
	
	CEL::INIT_CENTER_DESC kGMServerInit;
	kGMServerInit.eOT = BM::OUTPUT_ALL;
	kGMServerInit.pOnRegist = OnRegist;
	g_kCoreCenter.Init(kGMServerInit);

	// GM서버에 붙는 코드.
	{
		CEL::INIT_CORE_DESC kInit;
		kInit.OnSessionOpen	= OnConnectToGMServer;
		kInit.OnDisconnect	= OnDisconnectFromGMServer;
		kInit.OnRecv		= OnRecvFromGMServer;
		kInit.dwKeepAliveTime	= 600000;

		CEL::ERegistType eRegType = CEL::RT_NONE;

		m_kRegistGuid = kInit.kOrderGuid;
		g_kProcessCfg.AddRegist( m_kRegistGuid );
		eRegType = CEL::RT_CONNECTOR;

		g_kProcessCfg.AddRegist(g_kCoreCenter.Regist(eRegType, &kInit, sizeof(kInit)));
	}


	std::wstring strTitle = L"GM_Tool";
	//g_kProcessCfg.GetConsoleTitle(strTitle);
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
	if(m_bConnected)
	{
		INFO_LOG(BM::LOG_LV8, _T("Re login error"));
		return false;
	}
	g_kNetwork.ConnectGMServer();
	m_bConnected = true;

	return true;
}

bool PgNetwork::DisConnectServer()
{
	// 서비스 종료
	g_kCoreCenter.Close();
	g_kCoreCenter.Terminate(false, g_kNetwork.m_kConnectorGuid, g_kNetwork.m_kSessionGuid);
	m_bConnected = false;

	return true;
}

bool PgNetwork::SendToChannel(CEL::CPacket& rkPacket)
{
	return g_kCoreCenter.Send( m_kConnectorGuid, m_kSessionGuid, rkPacket);
}

bool PgNetwork::ConnectGMServer() //지엠 서버로 연결 시도
{
	CEL::ADDR_INFO kAddr;

	kAddr.Set(m_wstrGMServerIP, (WORD)m_dwGMServerPort);
	return g_kCoreCenter.Connect( m_kConnectorGuid, kAddr, m_kSessionGuid);

	return true;
}

void CALLBACK OnRegist(const CEL::SRegistResult &rkArg)//쓰레드가 정상 등록되면 CallBack
{
	if(CEL::CRV_SUCCESS == rkArg.iRet)
	{
		g_kProcessCfg.SetRegistComplete( rkArg.guidOrder );
	}
	else
	{
		//assert(0);
	}

	//서브
	if( CEL::RT_CONNECTOR == rkArg.eType )
	{
		INFO_LOG(BM::LOG_LV8, _T("[%s]-[%d] RT_CONNECTOR"), __FUNCTIONW__, __LINE__);
		g_kNetwork.m_kConnectorGuid = rkArg.guidObj;
		g_kNetwork.ConnectGMServer();
	}

	if( g_kProcessCfg.IsRegistAllComplete() )//Acceptor 등록 후에 또 Add 되기 때문에 AllComplete 는 한번 호출됨
	{
		g_kCoreCenter.SvcStart();
		//INFO_LOG( BM::LOG_LV6, _T("======================================================"));
		//INFO_LOG( BM::LOG_LV6, _T("==  [%s] 서비스 스타트"), _T(__FUNCTION__));
		//INFO_LOG( BM::LOG_LV6, _T("======================================================"));
	}
}