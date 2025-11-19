#pragma once

class PgNetwork
{
public:
	PgNetwork(void);
	virtual ~PgNetwork(void);

	bool Initialize();
	bool Terminate();
	bool ConnectServer();
	bool DisConnectServer();
	bool SendToLoginServer(CEL::CPacket const &rkPacket);

protected:
	SERVER_IDENTITY m_kLoginSI;
	CLASS_DECLARATION_S(bool, Connected);
	CLASS_DECLARATION_S(CEL::SESSION_KEY, SessionKey);
	CLASS_DECLARATION_S(BM::GUID, Connector);
};

#define g_kNetwork SINGLETON_STATIC(PgNetwork)
