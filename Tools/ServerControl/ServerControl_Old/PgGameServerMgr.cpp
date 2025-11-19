#include "StdAfx.h"
#include "PgGameServerMgr.h"

PgGameServerMgr::PgGameServerMgr(void)
{
	iControlLevel(0);
	m_bUseBeep = false;
	Clear();
}

PgGameServerMgr::~PgGameServerMgr(void)
{
}

void PgGameServerMgr::Clear()
{
	BM::CAutoMutex kLock(m_kMutex);
	m_kServer.clear();
}

void PgGameServerMgr::SetServerList(CEL::CPacket* const pkPacket)
{
	BM::CAutoMutex kLock(m_kMutex);
	Clear();

	size_t iSize = 0;
	pkPacket->Pop(iSize);
	for (size_t i=0 ; i<iSize ; i++)
	{
		SGameServerInfo kServerInfo;
		kServerInfo.ReadFromPacket(*pkPacket);
/*
		SERVER_IDENTITY kServerIdentity;
		kServerIdentity.nRealm = kServerInfo.nRealm;
		kServerIdentity.nChannel = kServerInfo.nChannel;
		kServerIdentity.nServerNo = kServerInfo.nServerNo;
		kServerIdentity.nServerType = kServerInfo.nServerType;
*/
		m_kServer.insert(std::make_pair((int)i, kServerInfo));
	}

	ContServerID kOnServer, kOffServer;
	TLoadArray(*pkPacket, kOnServer);
	TLoadArray(*pkPacket, kOffServer);

	m_kManagementServerList.clear();

	size_t iCountManagementServer = 0;
	pkPacket->Pop(iCountManagementServer);
	for( size_t iCur = 0; iCountManagementServer > iCur; ++iCur)
	{
		ContManagementServerSet::value_type kNewElement;
		pkPacket->Pop(kNewElement);
		m_kManagementServerList.insert(kNewElement);
	}

	std::wstring kCenterAddr;
	pkPacket->Pop(kCenterAddr);
	m_kManagementServerList.insert(kCenterAddr);
}

bool PgGameServerMgr::GetServerInfo(int iServerIdx, SGameServerInfo& rkOutInfo)const
{
	BM::CAutoMutex kLock(m_kMutex);
	ContServerInfo::const_iterator find_iter = m_kServer.find(iServerIdx);
	if (find_iter != m_kServer.end())
	{
		rkOutInfo = (*find_iter).second;
		return true;
	}
	return false;
}

void PgGameServerMgr::GetServerList(ContServerInfo& rkServerList)const
{
	BM::CAutoMutex kLock(m_kMutex);
	rkServerList = m_kServer;
}

void PgGameServerMgr::GetServerList(ContServerID& rkServerList, bool (*fp_FILTER)(const ContPairServerInfo&) )const
{

	BM::CAutoMutex kLock(m_kMutex);
	ContServerInfo::const_iterator iter = m_kServer.begin();
	while(m_kServer.end() != iter)
	{
		const bool bAdd = (fp_FILTER)? fp_FILTER((*iter)): true;
		if( bAdd )
		{
			const ContServerInfo::mapped_type& rkElement = (*iter).second;
			ContServerID::value_type kNewItem;
			kNewItem.Set(rkElement);
			rkServerList.push_back(kNewItem);
		}
		++iter;
	}
}


bool PgGameServerMgr::IsAliveServer(const std::wstring& rkMachineIP)
{
	BM::CAutoMutex kLock(m_kMutex);

	return m_kManagementServerList.end() != m_kManagementServerList.find(rkMachineIP);
}