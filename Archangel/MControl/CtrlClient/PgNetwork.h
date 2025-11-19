#pragma once

#include "BM/Guid.h"
#include "loki/Singleton.h"
#include "CEL/corecenter.h"

class PgClientNetwork
{
public:
	PgClientNetwork()
	{
		m_mapRegist.clear();
		m_kOrderGuid = BM::GUID();
		m_kObjGuid = BM::GUID();
	}
	virtual ~PgClientNetwork();

protected:
	typedef struct tagRegistState
	{
		tagRegistState()
		{
			guidObj = BM::GUID();
			guidSession = BM::GUID();
		}
		tagRegistState(const tagRegistState& rhs)
		{
			guidObj = rhs.guidObj;
			guidSession = rhs.guidSession;
			kAddr.wstrIP = rhs.kAddr.wstrIP;
			kAddr.wPort = rhs.kAddr.wPort;
		}

		BM::GUID guidObj;
		BM::GUID guidSession;
		CEL::ADDR_INFO kAddr;
	}SRegistState;

	static void CALLBACK OnRegist(const CEL::SRegistResult& rArg);
	bool RegisterMCtrolConnector();
	
	static void CALLBACK OnConnectMControl(CEL::CSession_Base* pkSession);
	static void CALLBACK OnDisconnectMControl(CEL::CSession_Base* pkSession);
	static void CALLBACK OnRecvMContrl(CEL::CSession_Base* pkSession, CEL::CPacket* const pPacket);

public:
	bool Init();
	BM::GUID GetSession(const CEL::ADDR_INFO& rkAddr);
	BM::GUID ConnectTo(const CEL::ADDR_INFO& addr);
	BM::GUID GetObjGuid();
	bool AddRegist(SRegistState* pkReg);
	bool Send(const BM::GUID& rkSession, CEL::CPacket& rkPacket);
	void DeleteRegist(const BM::GUID& rkSession);

private:
	typedef std::map<BM::GUID, SRegistState*> REGIST_MAP;
	REGIST_MAP m_mapRegist;
	BM::GUID m_kOrderGuid;
	BM::GUID m_kObjGuid;

};

typedef Loki::SingletonHolder<PgClientNetwork> Singleton_ClientNetwork;

#define g_kNetwork Singleton_ClientNetwork::Instance()
