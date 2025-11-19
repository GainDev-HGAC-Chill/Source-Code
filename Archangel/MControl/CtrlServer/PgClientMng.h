#pragma once

#include "BM/objectpool.h"
#include "PgCtrlClient.h"
#include "Lohengrin/LockUtil.h"

class PgClientMng
{
public:
	PgClientMng(void);
	~PgClientMng(void);

	bool AddClient(const BM::GUID& rkConnGuid, const BM::GUID& rkSessionGuid);
	void DeleteClient(const BM::GUID& rkSessionGuid);
	bool Send(const BM::GUID& rkSession, CEL::CPacket& rkPacket);
	void GetClient(const BM::GUID& rkSession, ObjectLock<PgCtrlClient*>* pkNpc);
	void Disconnect(const BM::GUID& rkSession);
	void SetAcceptorGuid(const BM::GUID& rkGuid);
	void SetAcceptorOrderGuid(const BM::GUID& rkGuid) { m_kAcceptorOrderGuid = rkGuid; }
	BM::GUID& GetAcceptorOrderGuid() { return m_kAcceptorOrderGuid; }
	void CheckUserSession(unsigned long ulNow);

protected:
	void GetFirstClient(ObjectMapIterLoc<BM::GUID, PgCtrlClient*>& kFind);
	bool GetNextClient(ObjectMapIterLoc<BM::GUID, PgCtrlClient*>& kFind);

private:
	typedef std::map<BM::GUID, PgCtrlClient*> CTRL_CLIENT_MAP;
	CTRL_CLIENT_MAP m_kClientMap;
	OBJLOCK_REFCOUNT m_kClientLock;
	BM::TObjectPool< PgCtrlClient > m_kClientPool;

	BM::GUID m_kAcceptorGuid;
	BM::GUID m_kAcceptorOrderGuid;
};

#define g_kClientMng Loki::SingletonHolder<PgClientMng>::Instance()