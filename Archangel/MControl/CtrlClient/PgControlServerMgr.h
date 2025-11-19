#pragma once

typedef struct
{
	BM::GUID kSessionGuid;
	bool bConnected;
	//SAddrInfo addrServerNat;
	SAddrInfo addrUserNat;
	std::vector<int> kRelatedChannel;
} CTRL_SERVER;

class PgControlServerMgr
{
public:
	PgControlServerMgr(void);
	~PgControlServerMgr(void);

public:
	void AddServer(TBL_SERVERLIST* pkInfo);
	void Connected(bool bConnected, const BM::GUID& rkSessionGuid, SAddrInfo* pkAddr);
	CTRL_SERVER* GetController(SAddrInfo* pkAddr, bool bOnlyIPCheck = true);
	void AddRelatedChannel(SAddrInfo* pkAddr, int iChannel);
	void DeleteRelatedChannel(SAddrInfo* pkAddr, int iChannel);
	void DoJob(SAddrInfo* pkCtrlAddr);

private:
	typedef std::vector<CTRL_SERVER*> CTRL_SERVER_VECTOR;
	CTRL_SERVER_VECTOR m_kServerVec;
};

#define g_kServerMgr Loki::SingletonHolder<PgControlServerMgr>::Instance()