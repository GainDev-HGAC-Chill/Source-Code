#include "stdafx.h"
#include "Global.h"
#include "PgNetwork.h"
#include "Lohengrin/PacketType.h"
#include "PgChannelMgr.h"
#include "PgControlServerMgr.h"
#include "SuperVw.h"

PgClientNetwork::~PgClientNetwork()
{
	REGIST_MAP::iterator itor = m_mapRegist.begin();
	while (m_mapRegist.end() != itor)
	{
		if (itor->second != NULL)
		{
			delete itor->second;
		}
		itor++;
	}
	m_mapRegist.end();
}

bool PgClientNetwork::Init()
{
	CEL::INIT_CENTER_DESC Init;
	Init.eOT = BM::OUTPUT_JUST_TRACE;
	Init.pOnRegist = PgClientNetwork::OnRegist;

	if (!g_kCoreCenter.Init(Init))
	{
		::MessageBox(NULL, _T("CoreCenter init failure"), _T("ERROR"), MB_OK);
		return false;
	}

	RegisterMCtrolConnector();

	return true;
}

void CALLBACK PgClientNetwork::OnRegist(const CEL::SRegistResult& rArg)
{
	if (rArg.guidOrder == g_kNetwork.m_kOrderGuid)
	{
		g_kNetwork.m_kObjGuid = rArg.guidObj;
	}
	g_kCoreCenter.SvcStart();
}

bool PgClientNetwork::RegisterMCtrolConnector()
{
	CEL::INIT_CORE_DESC Init;
	Init.OnSessionOpen = PgClientNetwork::OnConnectMControl;
	Init.OnDisconnect = PgClientNetwork::OnDisconnectMControl;
	Init.OnRecv = PgClientNetwork::OnRecvMContrl;
	Init.dwKeepAliveTime = 600000;

	m_kOrderGuid = g_kCoreCenter.Regist(CEL::RT_CONNECTOR, &Init, sizeof(Init));
	return true;
}

void PgClientNetwork::OnConnectMControl(CEL::CSession_Base* pkSession)
{
	const bool bIsSucc = pkSession->IsDeadConnection();
	if (bIsSucc)
	{
		SRegistState kReg;
		kReg.guidObj = pkSession->ParentKey();
		kReg.guidSession = pkSession->Key();
		kReg.kAddr.wstrIP = pkSession->Addr().wstrIP;
		kReg.kAddr.wPort = pkSession->Addr().wPort;
		g_kNetwork.AddRegist(&kReg);

		SAddrInfo kAddr(kReg.kAddr.wstrIP, kReg.kAddr.wPort);
		g_kServerMgr.Connected(true, pkSession->Key(), &kAddr);

		// Login
		SClientTryLogin kLogin;
		kLogin.guidVersion = BM::GUID();
		kLogin.SetID(g_kChannelMgr.GetLoginID());
		kLogin.SetPW(g_kChannelMgr.GetLoginPassword());
		CEL::CPacket kLPacket(PT_CC_CS_REQ_LOGIN, kLogin);
		//pkSession->VSend(kLPacket);
		g_kCoreCenter.Send(pkSession->ParentKey(), pkSession->Key(), kLPacket);
	}
	else
	{
		CC_SHOW_LOG(5, _T("Cannot Connect MControl...."));
	}
}

void PgClientNetwork::OnDisconnectMControl(CEL::CSession_Base* pkSession)
{
	CC_SHOW_LOG(7, _T("Machine Control Server disconnected"));

	SAddrInfo kAddr(pkSession->Addr().wstrIP, pkSession->Addr().wPort);
	g_kServerMgr.Connected(false, pkSession->Key(), &kAddr);
	g_kNetwork.DeleteRegist(pkSession->Key());
}

void PgClientNetwork::OnRecvMContrl(CEL::CSession_Base* pkSession, CEL::CPacket* const pkPacket)
{
	unsigned short usType = 0;
	pkPacket->Pop(usType);
	switch( usType )
	{
	case PT_CS_CC_RES_LOGIN:
		{
			STryLoginResult kLoginR;
			pkPacket->Pop(kLoginR);
			g_kChannelMgr.Login(pkSession, &kLoginR);
		}break;
	case PT_CS_CC_RES_SERVERSTATUS://TODO: 클라이언트 (수동업데이트만 가능하게)
		{
			g_kChannelMgr.ResServerStatus(pkPacket);
		}break;
	default:
		{
		}break;
	}

}

BM::GUID PgClientNetwork::ConnectTo(const CEL::ADDR_INFO& addr)
{
	BM::GUID kGuid = GetSession(addr);
	if (kGuid == BM::GUID())
	{
		g_kCoreCenter.Connect(m_kObjGuid, addr, kGuid);
		return BM::GUID();
	}
	return kGuid;
}

BM::GUID PgClientNetwork::GetSession(const CEL::ADDR_INFO& rkAddr)
{
	REGIST_MAP::iterator itor = m_mapRegist.begin();
	while (m_mapRegist.end() != itor)
	{
		if (itor->second->kAddr == rkAddr)
		{
			return itor->second->guidSession;
		}
		itor++;
	}
	return BM::GUID();
}


bool PgClientNetwork::AddRegist(SRegistState* pkReg)
{
	if (pkReg == NULL)
	{
		return false;
	}
	SRegistState* pkNew = new SRegistState;
	*pkNew = *pkReg;
	m_mapRegist.insert(std::make_pair(pkReg->guidSession, pkNew));
	return true;
}

BM::GUID PgClientNetwork::GetObjGuid()
{
	return m_kObjGuid;
}

bool PgClientNetwork::Send(const BM::GUID& rkSession, CEL::CPacket& rkPacket)
{
	REGIST_MAP::iterator itor = m_mapRegist.find(rkSession);
	if (m_mapRegist.end() != itor)
	{
		return g_kCoreCenter.Send(itor->second->guidObj, itor->second->guidSession, rkPacket);
	}
	return false;
}

void PgClientNetwork::DeleteRegist(const BM::GUID& rkSession)
{
	REGIST_MAP::iterator itor = m_mapRegist.find(rkSession);
	if (m_mapRegist.end() != itor)
	{
		SRegistState* pkDelete = itor->second;
		m_mapRegist.erase(itor);
		if (pkDelete != NULL)
		{
			delete pkDelete;
		}
	}
}

