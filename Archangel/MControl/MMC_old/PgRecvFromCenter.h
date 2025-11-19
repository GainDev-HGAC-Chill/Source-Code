#pragma once

typedef std::map< CEL::ADDR_INFO, CEL::SESSION_KEY > ContCenter;

class PgCenterMgr
{
public:
	PgCenterMgr();
	~PgCenterMgr();

	bool ConnectCenterServer(CEL::ADDR_INFO const &rkAddr);
	bool ConnectCenterServer();
	bool RecvManagementServerCommand(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket);

	bool Send(CEL::CPacket const& rkPacket);

	CLASS_DECLARATION_S(BM::GUID, RegistGuid);
	CLASS_DECLARATION_S(CEL::ADDR_INFO, CenterServer);
//	CLASS_DECLARATION_S(CEL::SESSION_KEY, SessionKey);
	CEL::SESSION_KEY m_kSessionKey;
	//CLASS_DECLARATION_S(GAME_SERVER_STATUS, ServerIdentify);
//	ContCenter m_kCenterServer;
protected:
};
#define g_kCenterMgr Loki::SingletonHolder<PgCenterMgr>::Instance()


void CALLBACK OnConnectToCenter(CEL::CSession_Base *pkSession);
void CALLBACK OnDisConnectToCenter(CEL::CSession_Base *pkSession);
void CALLBACK OnRecvFromCenter(CEL::CSession_Base *pkSession, CEL::CPacket * const pkPacket);
