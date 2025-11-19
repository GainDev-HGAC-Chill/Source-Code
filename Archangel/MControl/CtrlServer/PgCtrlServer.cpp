#include "StdAfx.h"
#include "PgCtrlServer.h"

PgCtrlServer::PgCtrlServer(void)
: m_kCenterJobPool(1, 1)
{
}

PgCtrlServer::~PgCtrlServer(void)
{
}

void PgCtrlServer::Invalidate()
{
	m_iChannelID = m_iServerNo = 0;
	m_eType = CEL::ST_NONE;
	m_eStatus = SSTATUS_UNKNOWN;
	m_sUserCount = 0;
}

bool PgCtrlServer::Set(SERVER_IDENTITY* pkInfo)
{
	m_iChannelID = pkInfo->nChannel;
	m_iServerNo = pkInfo->iServerNo;
	m_eType = (CEL::E_SESSION_TYPE) pkInfo->nServerType;
	m_eStatus = SSTATUS_UNKNOWN;

	return true;
}

void PgCtrlServer::AddJob(ECenterJobType eType, const BM::GUID& rkSessionGuid)
{
	CENTER_JOB_LIST::iterator itor = m_pkJobList.begin();
	while (itor != m_pkJobList.end())
	{
		if (((*itor)->eType == eType) && ((*itor)->kFromSessionGuid == rkSessionGuid))
		{
			return;	// exist already
		}
		itor++;
	}

	CENTER_JOB* pkJob = m_kCenterJobPool.New();
	pkJob->eType = eType;
	pkJob->kFromSessionGuid = rkSessionGuid;

	{
		BM::CAutoMutex kLock(m_kJobLock.kObjectLock);
		m_pkJobList.push_back(pkJob);
	}
}

void PgCtrlServer::DeleteJob(const BM::GUID& rkSessionGuid)
{
	BM::CAutoMutex kLock(m_kJobLock.kObjectLock);
	CENTER_JOB_LIST::iterator itor = m_pkJobList.begin();
	while (itor != m_pkJobList.end())
	{
		if ((*itor)->kFromSessionGuid == rkSessionGuid)
		{
			CENTER_JOB* pkJob = (*itor);
			m_pkJobList.erase(itor);
			itor = m_pkJobList.begin();
			m_kCenterJobPool.Delete(pkJob);
			continue;
		}
		itor++;
	}

}