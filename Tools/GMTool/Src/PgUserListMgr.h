#pragma once

typedef std::map<unsigned int, SOutsidePlayerData> MAP_PLAYERDATA;

class PgUserListMgr
{
public:
	PgUserListMgr(void);
	virtual ~PgUserListMgr(void);

	void ReqRefreshUserList();
	unsigned int RefreshUserList(CEL::CPacket * const pkPacket);

	BM::GUID m_guidRefresh;			// 이거 기준으로 서버로부터 리스트가 받아졌는지 알수 있다.
	MAP_PLAYERDATA m_kPlayerData;
};

#define g_kUserListMgr Loki::SingletonHolder<PgUserListMgr>::Instance()
