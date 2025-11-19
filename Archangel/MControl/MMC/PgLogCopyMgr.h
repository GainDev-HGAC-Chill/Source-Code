#pragma once


typedef struct tagLogCopyer
{
	tagLogCopyer(){}
	~tagLogCopyer(){}

	typedef std::map< std::wstring, __int64 >				CONT_LOG_FILE_INFO;
	typedef std::map< std::wstring, CONT_LOG_FILE_INFO >	CONT_DOWNLOAD;

	CONT_DOWNLOAD	m_kContDownLoad;
}SLogCopyer;

class PgLogCopyMgr
{
public:
	
	typedef std::map< CEL::SESSION_KEY, SLogCopyer >	CONT_SMC_DOWNLOAD;
	
public:
	PgLogCopyMgr(void);
	~PgLogCopyMgr(void);

	void Locked_ReadFromConfig( LPCWSTR lpFileName );
	void Locked_Init( ContServerSiteID const &kServerList );
	void Locked_Tick();

	void Locked_Connect( CEL::SESSION_KEY const &kSessionKey );
	void Locked_Disconnect( CEL::SESSION_KEY const &kSessionKey );

	void Locked_Recv_PT_SMC_MMC_ANS_LOG_FILE_INFO( CEL::SESSION_KEY const &kSessionkey, BM::CPacket * pkPacket );
	void Locked_Recv_PT_MMC_SMC_ANS_GET_FILE( CEL::SESSION_KEY const &kSessionkey, BM::CPacket * pkPacket );

private:
	void ProcessDownLoad( CONT_SMC_DOWNLOAD::iterator itr, std::wstring const &wstrOldfile = std::wstring() );

private:
	void GetPath( std::wstring const &wstrPath, std::wstring &rkOutPath )const;

private:
	mutable Loki::Mutex		m_kMutex;

	CONT_SMC_DOWNLOAD		m_kContCopyer;
	CEL::SESSION_KEY		m_kTickCheckID;
	DWORD					m_dwLastUpdateTime;

	std::wstring			m_wstrPath;
	DWORD					m_dwHackLogIntervalTime;
	DWORD					m_dwUpdateTickTime;
};

inline void PgLogCopyMgr::GetPath( std::wstring const &wstrPath, std::wstring &rkOutPath )const
{
	BM::CAutoMutex kLock( m_kMutex );
	SYSTEMTIME kSystemTime;
	GetLocalTime( &kSystemTime );

	wchar_t wszPath[MAX_PATH] = {0,};
	::swprintf_s( wszPath, MAX_PATH, L"%s%04u%02u%02u\\", m_wstrPath.c_str(), kSystemTime.wYear, kSystemTime.wMonth, kSystemTime.wDay );

	rkOutPath = wszPath;
	rkOutPath += wstrPath;
	BM::ConvFolderMark(rkOutPath);
	BM::ReserveFolder( rkOutPath );
}

#define g_kLogCopyMgr SINGLETON_STATIC(PgLogCopyMgr)
