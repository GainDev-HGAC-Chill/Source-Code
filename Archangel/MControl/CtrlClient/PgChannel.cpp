#include "StdAfx.h"
#include "Global.h"
#include "PgChannel.h"
#include "PgNetwork.h"
#include "PgControlServerMgr.h"
#include "Lohengrin/PacketType.h"
#include "SuperVw.h"


PgChannel::PgChannel(int iChannel)
{
	m_iChannelNo = iChannel;
	m_kCurrentJob = CTRLJ_NONE;
}

PgChannel::~PgChannel(void)
{
	Clear();
}

bool PgChannel::AddServer(ERIC_SERVERINFO* pkInfo)
{
	if (pkInfo == NULL)
	{
		return false;
	}
	ERIC_SERVERINFO* pkNew = new ERIC_SERVERINFO;
	*pkNew = *pkInfo;

	m_kServer.insert(std::make_pair(pkInfo->kInfo.iServerNo, pkNew));
	return true;
}

void PgChannel::Clear()
{
	SERVERINFO_MAP::iterator itor = m_kServer.begin();
	while (m_kServer.end() != itor)
	{
		if (itor->second != NULL)
		{
			delete itor->second;
		}
		itor++;
	}

	m_kServer.clear();
}

void PgChannel::GetFirstServer(ObjectMapIterLoc<int, ERIC_SERVERINFO*>& itor)
{
	itor.m_kItor = m_kServer.end();
	itor.SetLock(&m_kServerLock);
}

bool PgChannel::GetNextServer(ObjectMapIterLoc<int, ERIC_SERVERINFO*>& itor)
{
	if (m_kServer.end() == itor.m_kItor)
	{
		itor.m_kItor = m_kServer.begin();
	}
	else
	{
		itor.m_kItor++;
	}

	if (m_kServer.end() == itor.m_kItor)
	{
		return false;
	}

	return true;	
}

void PgChannel::StartAllServer()
{
	SetJob(CTRLJ_STARTCHANNEL);

	DoNextJob();
	/*
	ObjectMapIterLoc<int, ERIC_SERVERINFO> kServer;
	GetFirstServerWithType(kServer);
	if (!GetNextServerWithType(CEL::ST_MACHINE_CONTROL, kServer))
	{
		return;
	}
	SetJob(CTRLJ_STARTCHANNEL);
	g_kServerMgr.AddReleatedChannel(&(kServer.m_kItor->second->kInfo.addrUserNat), GetChannelNo());

	ERIC_SERVERINFO* pkInfo = kServer.m_kItor->second;
	CEL::ADDR_INFO addr(pkInfo->kInfo.addrUserNat.StrIP(), pkInfo->kInfo.addrUserNat.wPort);
	BM::GUID kSessionGuid = g_kNetwork.ConnectTo(addr);
	if (kSessionGuid != BM::GUID())	// connected already
	{
		DoNextJob(kSessionGuid);
	}
	*/
}

void PgChannel::GetFirstServerWithType(ObjectMapIterLoc<int, ERIC_SERVERINFO*>& itor)
{
	itor.m_kItor = m_kServer.end();
	itor.SetLock(&m_kServerLock);
}

bool PgChannel::GetNextServerWithType(int iType, ObjectMapIterLoc<int, ERIC_SERVERINFO*>& itor)
{
	bool bFind = false;
	while (!bFind)
	{
		if (m_kServer.end() == itor.m_kItor)
		{
			itor.m_kItor = m_kServer.begin();
		}
		else
		{
			itor.m_kItor++;
		}
		if (m_kServer.end() == itor.m_kItor)
		{
			return false;
		}
		if (itor.m_kItor->second->kInfo.nServerType == iType)
		{
			bFind = true;
		}
	}

	return true;	
}

void PgChannel::SetJob(ECtrlServerJob kJob)
{
	m_kCurrentJob = kJob;
}

ECtrlServerJob PgChannel::GetJob()
{
	return m_kCurrentJob;
}

bool PgChannel::DoNextJob()
{
	bool bFinished = false;
	switch(GetJob())
	{
	case CTRLJ_STARTCHANNEL:
		bFinished = DoNextJob_StartChannel();
		break;
	default:
		bFinished = true;
		break;
	}

	if (bFinished)
	{
		SetJob(CTRLJ_NONE);
	}

	return bFinished;
}

bool PgChannel::DoNextJob_StartChannel()
{
	// SERVER STARTING:
	//	CENTER -> Switch -> Contents -> Map -> Login
	CEL::E_SESSION_TYPE eType[] = { CEL::ST_CENTER, CEL::ST_SWITCH, CEL::ST_CONTENTS, CEL::ST_MAP, CEL::ST_LOGIN, (CEL::E_SESSION_TYPE)0 };
	int iPos = 0;

	while (eType[iPos] != 0)
	{
		ObjectMapIterLoc<int, ERIC_SERVERINFO*> kServer;
		GetFirstServerWithType(kServer);
		while (GetNextServerWithType((int)eType[iPos], kServer))
		{
			CTRL_SERVER* pkCtrlServer = g_kServerMgr.GetController(&(kServer.m_kItor->second->kInfo.addrUserNat));
			if (pkCtrlServer == NULL)
			{
				CC_SHOW_LOG(5, _T("[%s] ERROR: Cannot find MController Server information....Channel[%d], Addr[%s:%hd]"), _T(__FUNCTION__), GetChannelNo(),
					kServer.m_kItor->second->kInfo.addrUserNat.StrIP().c_str(), kServer.m_kItor->second->kInfo.addrUserNat.wPort);
				return true;
			}
			if (!pkCtrlServer->bConnected)
			{
				ConnectToController(pkCtrlServer);
				return false;
			}
			if (kServer.m_kItor->second->eStatus == SSTATUS_UNKNOWN)
			{
				QueryServerState(kServer.m_kItor->second);
				return false;
			}
			if (kServer.m_kItor->second->eStatus != SSTATUS_RUNNING)
			{
				StartServer(kServer.m_kItor->second);
				return false;
			}
		}

		iPos++;
	}
	SetJob(CTRLJ_NONE);
	CC_SHOW_LOG(7, _T("Starting Channel completed...ChannelID[%d]"), GetChannelNo());

	return true;
}

bool PgChannel::StartServer(ERIC_SERVERINFO* pkInfo)
{
	TBL_SERVERLIST kInfo;
	kInfo.nChannel = pkInfo->kInfo.nChannel;
	kInfo.iServerNo = pkInfo->kInfo.iServerNo;
	kInfo.nServerType = pkInfo->kInfo.nServerType;

	ObjectMapIterLoc<int, ERIC_SERVERINFO*> kCenter;
	GetFirstServerWithType(kCenter);
	if (!GetNextServerWithType((int)CEL::ST_CENTER, kCenter))
	{
		return false;
	}

	CTRL_SERVER* pkCtrl = g_kServerMgr.GetController(&(pkInfo->kInfo.addrUserNat));
	if (pkCtrl == NULL)
	{
		CC_SHOW_LOG(5, _T("[%s] ERROR: Cannot find MController Server information....Channel[%d], Addr[%s:%hd]"), _T(__FUNCTION__), GetChannelNo(),
			pkInfo->kInfo.addrUserNat.StrIP().c_str(), pkInfo->kInfo.addrUserNat.wPort);
		return false;
	}
	CEL::CPacket kSPacket(PT_CC_CS_REQ_STARTSERVER, kInfo);
	kSPacket.Push(kCenter.m_kItor->second->kInfo.addrServerNat);
	g_kNetwork.Send(pkCtrl->kSessionGuid, kSPacket);
	return true;
}

bool PgChannel::QueryServerState(ERIC_SERVERINFO* pkInfo)
{
	TBL_SERVERLIST kInfo;
	kInfo.nChannel = pkInfo->kInfo.nChannel;
	kInfo.iServerNo = pkInfo->kInfo.iServerNo;
	kInfo.nServerType = pkInfo->kInfo.nServerType;

	ObjectMapIterLoc<int, ERIC_SERVERINFO*> kCenter;
	GetFirstServerWithType(kCenter);
	if (!GetNextServerWithType((int)CEL::ST_CENTER, kCenter))
	{
		return false;
	}

	CTRL_SERVER* pkCtrl = g_kServerMgr.GetController(&(pkInfo->kInfo.addrUserNat));
	if (pkCtrl == NULL)
	{
		CC_SHOW_LOG(5, _T("[%s] ERROR: Cannot find MController Server information....Channel[%d], Addr[%s:%hd]"), _T(__FUNCTION__), GetChannelNo(),
			pkInfo->kInfo.addrUserNat.StrIP().c_str(), pkInfo->kInfo.addrUserNat.wPort);
		return false;
	}
	CEL::CPacket kQPacket(PT_CC_CS_REQ_SERVERSTATUS, kInfo);
	kQPacket.Push(kCenter.m_kItor->second->kInfo.addrServerNat);
	g_kNetwork.Send(pkCtrl->kSessionGuid, kQPacket);
	return true;
}


bool PgChannel::ConnectToController(CTRL_SERVER* pkCtrl)
{
	if (pkCtrl->bConnected)
	{
		return false;
	}
	g_kServerMgr.AddRelatedChannel(&(pkCtrl->addrUserNat), GetChannelNo());

	CEL::ADDR_INFO kAddr;
	kAddr.Set(pkCtrl->addrUserNat.StrIP(), pkCtrl->addrUserNat.wPort);
	BM::GUID kSession = g_kNetwork.ConnectTo(kAddr);
	assert(kSession == BM::GUID());	// 이미 접속되어 있으면 안된다......

	return true;
}

void PgChannel::GetServer(int iServerNo, ObjectLock<ERIC_SERVERINFO*>& kFind)
{
	m_kServerLock.IncRefCount();

	SERVERINFO_MAP::iterator itor = m_kServer.find(iServerNo);
	if (m_kServer.end() != itor)
	{
		kFind.SetValue(&m_kServerLock, itor->second);
	}
	else
	{
		kFind.SetValue(NULL, NULL);
	}

	m_kServerLock.DecRefCount();
}