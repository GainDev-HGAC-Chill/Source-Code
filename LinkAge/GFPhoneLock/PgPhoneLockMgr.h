#pragma once

typedef struct tagLockWait
{
	tagLockWait( BM::GUID const &_kSessionID )
		:	kSessionID(_kSessionID)
		,	dwReqTime( BM::GetTime32() + 50000 )
	{}

	BM::GUID	kSessionID;
	DWORD		dwReqTime;
}SLockWait;

class PgPhoneLockMgr
{
	typedef std::map< std::wstring, SLockWait >			CONT_LOCK_WAIT;

public:
	PgPhoneLockMgr(void);
	~PgPhoneLockMgr(void);

	bool Lock( std::wstring const &wstrID, BM::GUID const &kSessionID );
	bool UnLock( std::wstring const &wstrID );
	void UnLockAll();
	void DisplayAll();

	void OnTick( DWORD const dwCurTime );

	void SetSession( CEL::CSession_Base *pkSession ){m_pkSession=pkSession;}
	bool Send( BM::CPacket const &kPacket )const
	{
		if ( m_pkSession )
		{
			return m_pkSession->VSend( kPacket );
		}
		return false;
	}
private:
	Loki::Mutex			m_kMutex;
	CONT_LOCK_WAIT		m_kContWait;

	CEL::CSession_Base *m_pkSession;
};

#define g_kPhoneLockMgr SINGLETON_STATIC(PgPhoneLockMgr)
