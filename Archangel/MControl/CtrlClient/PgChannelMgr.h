#pragma once
#include "PgChannel.h"
#include "loki/Singleton.h"
#include "Lohengrin/LockUtil.h"

typedef std::map<int, PgChannel*> CHANNEL_MAP;

class PgChannelMgr
{
public:
	PgChannelMgr(void);
	~PgChannelMgr(void);
	bool Init();
	void GetFirstChannel(ObjectMapIterLoc<int, PgChannel*>& itor);
	bool GetNextChannel(ObjectMapIterLoc<int, PgChannel*>& itor);
	void StartChannel(int iID);
	LPCTSTR GetLoginID();
	LPCTSTR GetLoginPassword();
	void GetChannel(int iChannel, ObjectLock<PgChannel*>& kFind);

	// Packet Handler
	void Login(CEL::CSession_Base* pkSession, STryLoginResult* pkResult);
	void ResServerStatus(CEL::CPacket* const pkPacket);

protected:
	void Clear();
	bool ReadChannel();
	bool AddServer(TBL_SERVERLIST* pkInfo);
private:
	CHANNEL_MAP m_kChannelMap;
	OBJLOCK_REFCOUNT m_kChannelLock;
	std::wstring m_wstrID;
	std::wstring m_wstrPassword;

};

typedef Loki::SingletonHolder< PgChannelMgr, ::Loki::CreateStatic > Singleton_ChannelMgr;

#define g_kChannelMgr Singleton_ChannelMgr::Instance()
