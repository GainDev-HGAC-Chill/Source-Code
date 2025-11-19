#pragma once

class PgProcessInfoMgr
{
private:
	bool GetMainDir(LPTSTR lpszPath, int iPathLen);
	void ClearGmUser();
public:
	CONT_GM_AUTH_DATA_ID		m_kGmUsers;
	SAuthInfo					m_kMyInfo;

	bool ReadIniFile(wchar_t* FileName);
	void ReqRefreshGmList();
	unsigned int RecvGmList(CEL::CPacket * const pkPacket);
	void GetServerTime(BM::DBTIMESTAMP_EX &rkOut) const;

	PgProcessInfoMgr(void);
	virtual ~PgProcessInfoMgr(void);
protected:
	mutable Loki::Mutex	m_kMutex;

	CLASS_DECLARATION_S(std::wstring, kLoginServerIP);
	CLASS_DECLARATION_S(DWORD, dwLoginServerPort);

};

#define g_kProcessInfoMgr Loki::SingletonHolder<PgProcessInfoMgr>::Instance()
