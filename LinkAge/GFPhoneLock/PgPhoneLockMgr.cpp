#include "stdafx.h"
#include "Lohengrin/PacketStruct_GFAP.h"
#include "GFMobileLockPacketDef.h"
#include "PgPhoneLockMgr.h"

PgPhoneLockMgr::PgPhoneLockMgr(void)
:	m_pkSession(NULL)
{

}

PgPhoneLockMgr::~PgPhoneLockMgr(void)
{

}

bool PgPhoneLockMgr::Lock( std::wstring const &wstrID, BM::GUID const &kSessionID )
{
	BM::CAutoMutex kLock( m_kMutex );

	SLockWait kWait( kSessionID );
	CONT_LOCK_WAIT::_Pairib kPair = m_kContWait.insert( std::make_pair( wstrID, kWait ) );

	if ( !kPair.second )
	{
		S_PT_GF_AP_ANS_MOBILE_AUTH kData;
		::swprintf_s( kData.wszAccount, MAX_STRING_LEN_MOBILELOCK, L"%s", wstrID.c_str() );
		kData.kSessionID = kSessionID;
		kData.byRet = GFAP_FUNCTION::GF_MOBILE_AUTH_OVERLAPPING;

		BM::CPacket kPacket( PT_GF_AP_ANS_MOBILE_AUTH );
		kPacket.Push( kData );
		Send( kPacket );
	}
	else
	{
		std::wcout << L"[LockID] " << wstrID.c_str() << std::endl; 
	}

	return kPair.second;
}

bool PgPhoneLockMgr::UnLock( std::wstring const &wstrID )
{
	BM::CAutoMutex kLock( m_kMutex );
	CONT_LOCK_WAIT::iterator itr = m_kContWait.find( wstrID );
	if ( itr != m_kContWait.end() )
	{
		S_PT_GF_AP_ANS_MOBILE_AUTH kData;
		::swprintf_s( kData.wszAccount, MAX_STRING_LEN_MOBILELOCK, L"%s", wstrID.c_str() );
		kData.kSessionID = itr->second.kSessionID;
		kData.byRet = GFAP_FUNCTION::GF_MOBILE_AUTH_SUCCESS;

		BM::CPacket kPacket( PT_GF_AP_ANS_MOBILE_AUTH );
		kPacket.Push( kData );
		Send( kPacket );

		std::wcout << L"[UnLockID] " << wstrID.c_str() << std::endl; 
		m_kContWait.erase( itr );
		return true;
	}

	std::wcout << L"[UnLockID] NotFound : " << wstrID.c_str() << std::endl; 
	return false;
}

void PgPhoneLockMgr::UnLockAll()
{
	BM::CAutoMutex kLock( m_kMutex );

	CONT_LOCK_WAIT::iterator itr = m_kContWait.begin();
	for ( ; itr!=m_kContWait.end() ; ++itr )
	{
		S_PT_GF_AP_ANS_MOBILE_AUTH kData;
		::swprintf_s( kData.wszAccount, MAX_STRING_LEN_MOBILELOCK, L"%s", itr->first.c_str() );
		kData.kSessionID = itr->second.kSessionID;
		kData.byRet = GFAP_FUNCTION::GF_MOBILE_AUTH_SUCCESS;

		BM::CPacket kPacket( PT_GF_AP_ANS_MOBILE_AUTH );
		kPacket.Push( kData );
		Send( kPacket );

		std::wcout << L"[UnLockID] " << itr->first.c_str() << std::endl; 
	}
	m_kContWait.clear();
}

void PgPhoneLockMgr::DisplayAll()
{
	BM::CAutoMutex kLock( m_kMutex );

	CONT_LOCK_WAIT::iterator itr = m_kContWait.begin();
	for ( ; itr!=m_kContWait.end() ; ++itr )
	{
		std::wcout << L" *" << itr->first.c_str() << std::endl; 
	}
}

void PgPhoneLockMgr::OnTick( DWORD const dwCurTime )
{
	BM::CAutoMutex kLock( m_kMutex );
	CONT_LOCK_WAIT::iterator itr = m_kContWait.begin();
	for ( ; itr!=m_kContWait.end() ; ++itr )
	{
		if ( dwCurTime > itr->second.dwReqTime )
		{
			S_PT_GF_AP_ANS_MOBILE_AUTH kData;
			::swprintf_s( kData.wszAccount, MAX_STRING_LEN_MOBILELOCK, L"%s", itr->first.c_str() );
			kData.kSessionID = itr->second.kSessionID;
			kData.byRet = GFAP_FUNCTION::GF_MOBILE_AUTH_TIMEOUT;

			BM::CPacket kPacket( PT_GF_AP_ANS_MOBILE_AUTH );
			kPacket.Push( kData );
			Send( kPacket );

			std::wcout << L"[UnLockID] TimeOut : " << itr->first.c_str() << std::endl; 

			m_kContWait.erase( itr );
		}
	}
}
