#pragma once

#include "Lohengrin/PacketStruct.h"
#include "Lohengrin/LockUtil.h"
#include "PgControlServerMgr.h"


typedef struct tagERIC_SERVERINFO
{
	tagERIC_SERVERINFO()
	{
		eStatus = SSTATUS_UNKNOWN;
		sUserCount = 0;
	}
	tagERIC_SERVERINFO(const tagERIC_SERVERINFO& rhs)
	{
		kInfo = rhs.kInfo;
		eStatus = rhs.eStatus;
		sUserCount = rhs.sUserCount;
	}

	tagERIC_SERVERINFO(const TBL_SERVERLIST& rhs)
	{
		kInfo = rhs;
		eStatus = SSTATUS_UNKNOWN;
		sUserCount = 0;
	}
	TBL_SERVERLIST kInfo;
	EServerStatus eStatus;
	short int sUserCount;
} ERIC_SERVERINFO;


typedef enum {
	CTRLJ_NONE	= 0,
	CTRLJ_STARTCHANNEL = 1,		// Starting All server in the channel
	CTRLJ_STOPCHANNEL = 2		// Stop All server in the channel
} ECtrlServerJob;

typedef std::map<int, ERIC_SERVERINFO*> SERVERINFO_MAP;

class PgChannel
{
public:
	PgChannel(int iChannel);
	~PgChannel(void);

	bool AddServer(ERIC_SERVERINFO* pkInfo);
	int GetChannelNo() { return m_iChannelNo; }
	void GetFirstServer(ObjectMapIterLoc<int, ERIC_SERVERINFO*>& itor);
	bool GetNextServer(ObjectMapIterLoc<int, ERIC_SERVERINFO*>& itor);
	void StartAllServer();
	void GetFirstServerWithType(ObjectMapIterLoc<int, ERIC_SERVERINFO*>& itor);
	bool GetNextServerWithType(int iType, ObjectMapIterLoc<int, ERIC_SERVERINFO*>& itor);
	void SetJob(ECtrlServerJob kJob);
	ECtrlServerJob GetJob();
	bool DoNextJob();
	bool DoNextJob_StartChannel();
	void GetServer(int iServerNo, ObjectLock<ERIC_SERVERINFO*>& kFind);

protected:
	void Clear();
	bool StartServer(ERIC_SERVERINFO* pkInfo);
	bool QueryServerState(ERIC_SERVERINFO* pkInfo);
	bool ConnectToController(CTRL_SERVER* pkCtrl);

private:
	int m_iChannelNo;
	SERVERINFO_MAP m_kServer;
	OBJLOCK_REFCOUNT m_kServerLock;
	ECtrlServerJob m_kCurrentJob;
};
