#include "StdAfx.h"
#include "PgNetwork.h"
#include "PgUserListMgr.h"

PgUserListMgr::PgUserListMgr(void)
{
}

PgUserListMgr::~PgUserListMgr(void)
{
}

void PgUserListMgr::ReqRefreshUserList()
{
	m_guidRefresh.Generate();
	m_kPlayerData.clear();

	// 캐릭 리스트 요청.
	CEL::CPacket kPacket(PT_O_G_REQ_GMCOMMAND, EGMC_GET_USERLIST);
	kPacket.Push(g_kNetwork.m_usChannel);
	g_kNetwork.SendToChannel(kPacket);
}

unsigned int PgUserListMgr::RefreshUserList(CEL::CPacket * const pkPacket)
{
	// 패킷으로 유저 리스트를 받았다!
	unsigned int iCount = 0;
	pkPacket->Pop(iCount);

	m_guidRefresh.Generate();
	for (unsigned int i=0 ; i<iCount ; i++)
	{
		SOutsidePlayerData kOutInfo;
		pkPacket->Pop(kOutInfo);

		// TODO : ListCtrl 에 추가해주자.
		m_kPlayerData.insert(std::make_pair(i, kOutInfo));
	}

	m_guidRefresh.Generate();

	return iCount;
}
