#include "stdafx.h"
#include "Global.h"
#include "PgControlServerMgr.h"
#include "SuperVw.h"

PgControlServerMgr::PgControlServerMgr(void)
{
}

PgControlServerMgr::~PgControlServerMgr(void)
{
	int iSize = m_kServerVec.size();
	for (int i=0; i<iSize; i++)
	{
		if (m_kServerVec.at(i) != NULL)
		{
			delete m_kServerVec.at(i);
		}
	}

	m_kServerVec.clear();
}

void PgControlServerMgr::AddServer(TBL_SERVERLIST* pkInfo)
{
	CTRL_SERVER* pkNew = new CTRL_SERVER;
	pkNew->kSessionGuid = BM::GUID();
	pkNew->bConnected = false;
	pkNew->kRelatedChannel.clear();
	pkNew->addrUserNat = pkInfo->addrUserNat;

	m_kServerVec.push_back(pkNew);
}

// (Connected to)or(Disconnected from) Controller Server
// [PARAMETER]
//	bConnected : true(connected), false(disconnected)
//	rkSessionGuid : Session guid or controller server
//	pkAddr : controller server address
void PgControlServerMgr::Connected(bool bConnected, const BM::GUID& rkSessionGuid, SAddrInfo* pkAddr)
{
	CTRL_SERVER* pkServer = GetController(pkAddr);
	if (pkServer == NULL)
	{
		return;
	}
	if (bConnected)
	{
		CC_SHOW_LOG(7, _T("[%s] CONNECTED....SessionGuid[%s], Addr[%s:%hd]"), _T(__FUNCTION__), rkSessionGuid.str().c_str(), pkAddr->StrIP().c_str(), pkAddr->wPort);
		pkServer->bConnected = true;
		pkServer->kSessionGuid = rkSessionGuid;
	}
	else
	{
		CC_SHOW_LOG(7, _T("[%s] DISconnected....SessionGuid[%s], Addr[%s:%hd]"), _T(__FUNCTION__), rkSessionGuid.str().c_str(), pkAddr->StrIP().c_str(), pkAddr->wPort);
		pkServer->bConnected = false;
		pkServer->kSessionGuid = BM::GUID();
		pkServer->kRelatedChannel.clear();
	}
}

CTRL_SERVER* PgControlServerMgr::GetController(SAddrInfo* pkAddr, bool bOnlyIPCheck)
{
	if (pkAddr == NULL)
	{
		return NULL;
	}
	int iSize = m_kServerVec.size();

	for (int i=0; i<iSize; i++)
	{
		CTRL_SERVER* pkServer = m_kServerVec.at(i);
		if (bOnlyIPCheck)
		{
			if (pkServer->addrUserNat.ip.S_un.S_addr == pkAddr->ip.S_un.S_addr)
			{
				return pkServer;
			}
		}
		else
		{
			if (pkServer->addrUserNat == *pkAddr)
			{
				return pkServer;
			}
		}
	}
	return NULL;
}

void PgControlServerMgr::AddRelatedChannel(SAddrInfo* pkAddr, int iChannel)
{
	if (pkAddr == NULL)
	{
		return;
	}

	CTRL_SERVER* pkServer = GetController(pkAddr);
	if (pkServer == NULL)
	{
		return;
	}

	bool bFound = false;
	int iSize = pkServer->kRelatedChannel.size();
	for (int i=0; i<iSize; i++)
	{
		if (pkServer->kRelatedChannel.at(i) == iChannel)
		{
			bFound = true;
		}
	}
	if (!bFound)
	{
		pkServer->kRelatedChannel.push_back(iChannel);
	}
}

void PgControlServerMgr::DeleteRelatedChannel(SAddrInfo* pkAddr, int iChannel)
{
	if (pkAddr == NULL)
	{
		return;
	}

	CTRL_SERVER* pkServer = GetController(pkAddr);
	if (pkServer == NULL)
	{
		return;
	}

	std::vector<int>::iterator itor = pkServer->kRelatedChannel.begin();
	while (pkServer->kRelatedChannel.end() != itor)
	{
		if (*itor == iChannel)
		{
			pkServer->kRelatedChannel.erase(itor);
			return;
		}
		itor++;
	}
}


void PgControlServerMgr::DoJob(SAddrInfo* pkCtrlAddr)
{
	CTRL_SERVER* pkServer = GetController(pkCtrlAddr);
	if (pkServer == NULL)
	{
		CC_SHOW_LOG(5, _T("Logined but cannot fine Control Server information....aborted....CtrlServer IP[%s], Port[%hd]"), pkCtrlAddr->StrIP().c_str(), pkCtrlAddr->wPort);
		return;
	}
	std::vector<int> kDeleteChannel;
	int iSize = pkServer->kRelatedChannel.size();
	for (int i=0; i<iSize; i++)
	{
		ObjectLock<PgChannel*> kChannel;
		g_kChannelMgr.GetChannel(pkServer->kRelatedChannel.at(i), kChannel);
		if (kChannel.m_pkObject != NULL)
		{
			if(kChannel.m_pkObject->DoNextJob())	// All Job finished
			{
				kDeleteChannel.push_back(pkServer->kRelatedChannel.at(i));
			}
		}
	}

	// Deleting Finished Job
	{
		iSize = kDeleteChannel.size();
		for (int i=0; i<iSize; i++)
		{
			DeleteRelatedChannel(pkCtrlAddr, kDeleteChannel.at(i));
		}
	}

}