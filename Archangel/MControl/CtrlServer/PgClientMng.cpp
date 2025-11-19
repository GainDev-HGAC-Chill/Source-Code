#include "StdAfx.h"
#include "PgClientMng.h"
#include "PgServerController.h"

PgClientMng::PgClientMng(void)
: m_kClientPool(1, 1)
{
}

PgClientMng::~PgClientMng(void)
{
}

bool PgClientMng::AddClient(const BM::GUID& rkConnGuid, const BM::GUID& rkSessionGuid)
{
	if (rkSessionGuid == BM::GUID())
	{
		INFO_LOG(BM::LOG_LV5, _T("[%s] - Cannot add ManagerClient : SessionGuid is NULL"), _T(__FUNCTION__));
		return false;
	}
	PgCtrlClient* pkNew = m_kClientPool.New();
	pkNew->Init();
	pkNew->SetSessionGuid(rkSessionGuid);
	pkNew->SetConnectorGuid(rkConnGuid);

	{
		BM::CAutoMutex kLock(m_kClientLock.kObjectLock);
		m_kClientMap.insert(std::make_pair(rkSessionGuid, pkNew));
	}
	return true;
}

void PgClientMng::DeleteClient(const BM::GUID& rkSessionGuid)
{
	CTRL_CLIENT_MAP::iterator itor = m_kClientMap.find(rkSessionGuid);
	if (m_kClientMap.end() == itor)
	{
		INFO_LOG(BM::LOG_LV5, _T("[%s] - Cannot delete ManagerClient : because of not existing SessionGuid[%s]"), _T(__FUNCTION__), rkSessionGuid.str().c_str());
		return;
	}

	// Release Job related with this client
	BM::GUID& rkSession = itor->second->GetSessionGuid();
	g_kController.DeleteJob(rkSession);

	PgCtrlClient* pkDelete = itor->second;
	{
		BM::CAutoMutex kLock(m_kClientLock.kObjectLock);
		m_kClientMap.erase(itor);
	}

	m_kClientPool.Delete(pkDelete);
}

bool PgClientMng::Send(const BM::GUID& rkSession, CEL::CPacket& rkPacket)
{
	ObjectLock<PgCtrlClient*> kClient;
	GetClient(rkSession, &kClient);
	if (kClient.m_pkObject != NULL)
	{
		return kClient.m_pkObject->Send(rkPacket);
		//return g_kCoreCenter.Send(m_kConnectorGuid, rkSession, rkPacket);
	}
	return false;
}

void PgClientMng::GetClient(const BM::GUID& rkSession, ObjectLock<PgCtrlClient*>* pkFind)
{
	if (pkFind == NULL)
	{
		return;
	}

	m_kClientLock.IncRefCount();

	CTRL_CLIENT_MAP::iterator itor = m_kClientMap.find(rkSession);
	if (m_kClientMap.end() != itor)
	{
		pkFind->SetValue(&m_kClientLock, itor->second);
	}
	else
	{
		pkFind->SetValue(NULL, NULL);
	}

	m_kClientLock.DecRefCount();
}

void PgClientMng::Disconnect(const BM::GUID& rkSession)
{
	g_kCoreCenter.Terminate(true, m_kAcceptorGuid, rkSession);
	DeleteClient(rkSession);
}


void PgClientMng::SetAcceptorGuid(const BM::GUID& rkGuid)
{
	m_kAcceptorGuid = rkGuid;
}

void PgClientMng::CheckUserSession(unsigned long ulNow)
{
	std::vector<BM::GUID> kDelete;
	{
		ObjectMapIterLoc<BM::GUID, PgCtrlClient*> kFind;
		GetFirstClient(kFind);
		while (GetNextClient(kFind))
		{
			if (!kFind.m_kItor->second->IsExpired(ulNow))
			{
				kDelete.push_back(kFind.m_kItor->second->GetSessionGuid());
			}
		}
	}

	int iSize = kDelete.size();
	for (int i=0; i<iSize; i++)
	{
		Disconnect(kDelete.at(i));
	}

}

void PgClientMng::GetFirstClient(ObjectMapIterLoc<BM::GUID, PgCtrlClient*>& kFind)
{
	m_kClientLock.IncRefCount();

	kFind.m_kItor = m_kClientMap.end();
	kFind.SetLock(&m_kClientLock);

	m_kClientLock.DecRefCount();
}

bool PgClientMng::GetNextClient(ObjectMapIterLoc<BM::GUID, PgCtrlClient*>& kFind)
{
	if (m_kClientMap.end() == kFind.m_kItor)
	{
		kFind.m_kItor = m_kClientMap.begin();
	}
	else
	{
		kFind.m_kItor++;
	}

	if (m_kClientMap.end() == kFind.m_kItor)
	{
		return false;
	}
	return true;
}
