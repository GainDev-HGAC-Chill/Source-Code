#include "StdAfx.h"
#include "PgCtrlClient.h"

PgCtrlClient::PgCtrlClient(void)
{
	Init();
}

PgCtrlClient::~PgCtrlClient(void)
{
}

void PgCtrlClient::SetSessionGuid(const BM::GUID& rkSession)
{
	m_kSessionGuid = rkSession;
}

BM::GUID& PgCtrlClient::GetSessionGuid()
{
	return m_kSessionGuid;
}

void PgCtrlClient::Invalidate()
{
	Init();
}

void PgCtrlClient::Init()
{
	m_chLoginID[0] = _T('\0');
	m_chLoginPW[0] = _T('\0');
	m_bLogined = false;
	m_kSessionGuid = BM::GUID();
	m_kConnGuid = BM::GUID();
	m_ulSessionExpireTime = 0;
}

void PgCtrlClient::SetConnectorGuid(const BM::GUID& rkConn)
{
	m_kConnGuid = rkConn;
}

BM::GUID& PgCtrlClient::GetConnGuid()
{
	return m_kConnGuid;
}

bool PgCtrlClient::Send(CEL::CPacket& rkPacket)
{
	return g_kCoreCenter.Send(GetConnGuid(), GetSessionGuid(), rkPacket);
}

void PgCtrlClient::SetSessionExpireTime(unsigned long ulTime)
{
	m_ulSessionExpireTime = ulTime;
}

bool PgCtrlClient::IsExpired(unsigned long ulTime)
{
	if (IsLogined())
	{
		return false;
	}
	return (m_ulSessionExpireTime < ulTime) ? true : false;
}