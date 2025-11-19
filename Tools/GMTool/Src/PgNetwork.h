#pragma once

//typedef struct tagSingleServerIdentity
//{
//	SERVER_IDENTITY kIdentity;
//	CEL::ADDR_INFO kAddrInfo;
//} SINGLE_SERVER;

class PgNetwork
{
public:
	PgNetwork(void);
	virtual ~PgNetwork(void);

	bool Initialize();
	bool Terminate();
	bool ConnectServer();
	bool DisConnectServer();
	//int ParseArg_Sub( SINGLE_SERVER &rkSingleServer, const std::wstring &wstrText );

	bool SendToChannel(CEL::CPacket& rkPacket);
	bool ConnectGMServer(); //중앙 머신컨트롤러로 연결 시도

public:
	//typedef std::map< int, SINGLE_SERVER> GameServerMap;

protected:
	//GameServerMap m_kGameServerList;

public:
	bool m_bConnected;
	BM::GUID m_kConnectorGuid; //Connector Guid
	BM::GUID m_kSessionGuid;
	BM::GUID m_kRegistGuid; //쓰레드 Guid

	std::wstring m_wstrGMServerIP;
	DWORD m_dwGMServerPort;

	// GM ID, PW
	TCHAR m_wGMID[128];
	TCHAR m_wGMPW[128];
	unsigned short m_usChannel;
};

#define g_kNetwork SINGLETON_STATIC(PgNetwork)
