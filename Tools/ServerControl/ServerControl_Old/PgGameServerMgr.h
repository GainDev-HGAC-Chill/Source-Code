#pragma once

typedef std::map< int, SGameServerInfo > ContServerInfo;
typedef std::pair< ContServerInfo::key_type, ContServerInfo::mapped_type > ContPairServerInfo;
//typedef std::list< SGameServerInfo > ContListServerInfo;
typedef std::set< std::wstring > ContManagementServerSet;

class PgGameServerMgr
{
	typedef std::vector< SERVER_IDENTITY > ContServerIDList;
public:
	PgGameServerMgr(void);
	virtual ~PgGameServerMgr(void);

	void Clear();

	void SetServerList(CEL::CPacket* const pkPacket);
	bool GetServerInfo(int iServerIdx, SGameServerInfo& rkOutInfo)const;
	void GetServerList(ContServerInfo& rkServerList)const;
	void GetServerList(ContServerID& rkServerList, bool (*fp_FILTER)(const ContPairServerInfo&) =NULL )const;

	bool IsAliveServer(const std::wstring& rkMachineIP);

public:
	CLASS_DECLARATION_S(int, iControlLevel);
	std::wstring m_wstrCenterManagementServerIP;
	DWORD m_dwCenterManagementServerPort;

protected:
	bool m_bUseBeep;

	ContServerInfo m_kServer;
	ContManagementServerSet m_kManagementServerList;

	mutable Loki::Mutex m_kMutex;
};

#define g_kGameServerMgr Loki::SingletonHolder<PgGameServerMgr>::Instance()

