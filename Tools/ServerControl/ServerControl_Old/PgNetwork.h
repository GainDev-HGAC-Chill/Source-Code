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

	bool ConnectServer();
	bool DisConnectServer();

	bool Send(const CEL::CPacket& rkPacket);

protected:
	bool ConnectMMS();
	bool Terminate();

	CLASS_DECLARATION_S(bool, Connected);
	//CLASS_DECLARATION_S(BM::GUID, ServerConnectorGuid);
	//CLASS_DECLARATION_S(BM::GUID, ServerSessionGuid);
	CLASS_DECLARATION_S(CEL::SESSION_KEY, SessionKey);
	CLASS_DECLARATION_S(BM::GUID, ServerRegistGuid);
};

#define g_kNetwork SINGLETON_STATIC(PgNetwork)
