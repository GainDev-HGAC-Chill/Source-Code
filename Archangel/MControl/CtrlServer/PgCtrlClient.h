#pragma once

class PgCtrlClient
{
public:
	PgCtrlClient(void);
	~PgCtrlClient(void);

	void SetSessionGuid(const BM::GUID& rkSession);
	BM::GUID& GetSessionGuid();
	void Invalidate();
	void Init();
	void SetConnectorGuid(const BM::GUID& rkConn);
	BM::GUID& GetConnGuid();
	bool Send(CEL::CPacket& rkPacket);
	bool IsLogined() { return m_bLogined; }
	void SetSessionExpireTime(unsigned long ulTime);
	bool IsExpired(unsigned long ulTime);
	void Logined() { m_bLogined = true; }

private:
	TCHAR m_chLoginID[21];
	TCHAR m_chLoginPW[21];
	bool m_bLogined;
	BM::GUID m_kSessionGuid;
	BM::GUID m_kConnGuid;
	unsigned long m_ulSessionExpireTime;
};


