#pragma once

#include "Lohengrin/PacketType.h"
#include "Lohengrin/LockUtil.h"

typedef enum
{
	CJOG_TYPE_QUERY_NONE = 0,
	CJOG_TYPE_QUERY_SERVER_STATUS = 1
} ECenterJobType;

typedef struct
{
	void Clear()
	{
		eType = CJOG_TYPE_QUERY_NONE;
		kFromSessionGuid = BM::GUID();
	}
	ECenterJobType eType;
	BM::GUID kFromSessionGuid;
} CENTER_JOB;


class PgCtrlServer
{
public:
	PgCtrlServer(void);
	~PgCtrlServer(void);

	void Invalidate();
	bool Set(SERVER_IDENTITY* pkInfo);
	int GetChannelID() { return m_iChannelID; }
	int GetServerNo() { return m_iServerNo; }
	EServerStatus GetStatus() { return m_eStatus; }
	void AddJob(ECenterJobType eType, const BM::GUID& rkSessionGuid);
	void DeleteJob(const BM::GUID& rkSessionGuid);
	CEL::E_SESSION_TYPE GetType() { return m_eType; }
	void SetStatus(EServerStatus eStatus) { m_eStatus = eStatus; }
	short int GetUserCount() { return m_sUserCount; }
	void SetUserCount(short int sCount) { m_sUserCount = sCount; }

private:
	int m_iChannelID;
	int m_iServerNo;
	CEL::E_SESSION_TYPE m_eType;
	EServerStatus m_eStatus;
	short int m_sUserCount;

	typedef std::list<CENTER_JOB*> CENTER_JOB_LIST;
	CENTER_JOB_LIST m_pkJobList;
	BM::TObjectPool< CENTER_JOB > m_kCenterJobPool;
	OBJLOCK_REFCOUNT m_kJobLock; //Lock(m_pkJobList)
};
