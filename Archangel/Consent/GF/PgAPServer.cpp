#include "stdafx.h"
#include "PgAPServer.h"
#include "PgGFBillingAP.h"
#include "PgGFMobileLock.h"

PgAPServer_Base::PgAPServer_Base( CEL::CSession_Base * const pkSession, SLinkageServerInfo const &kServerInfo )
:	m_pkSession(pkSession)
,	m_kServerInfo(kServerInfo)
{
}

PgAPServer_Base::PgAPServer_Base( PgLinkAgeServer_Base const &rhs )
:	m_pkSession(rhs.m_pkSession)
,	m_kServerInfo(rhs.m_kServerInfo)
{
}

PgAPServer::PgAPServer(void)
:	m_kServiceHandlerType(CEL::SHT_SERVER)
{
}

PgAPServer::~PgAPServer(void)
{
	CONT_LINKAGE_SERVER_ACCESSLIST::iterator access_itr = m_kContAccessList.begin();
	for ( ; access_itr != m_kContAccessList.end() ; ++access_itr )
	{
		SAFE_DELETE( access_itr->second );
	}
	m_kContAccessList.clear();
}

void PgAPServer::ReadFromConfig( LPCTSTR lpszFileName )
{

}

HRESULT	PgAPServer::Locked_Add( SLinkageServerInfo const &kInfo )
{
	BM::CAutoMutex kWLock( m_kRWMutex, true );
	return Add( kInfo );
}

HRESULT PgAPServer::Locked_Connected( CEL::CSession_Base * const pkSession, CEL::ADDR_INFO const &kAddr, bool const bAccept )
{
	BM::CAutoMutex kWLock( m_kRWMutex, true );
	CONT_LINKAGE_SERVER_LIST::iterator link_itr = m_kContList.begin();
	for ( ; link_itr!=m_kContList.end() ; ++link_itr )
	{
		if ( bAccept == link_itr->bAccept )
		{
			if ( true == link_itr->bAccept )
			{
				// 다른 서버가 나에게 연결을 해온 경우는 포트는 체크 할 필요 없다.
				if ( link_itr->kAddr.ip.s_addr == kAddr.ip.s_addr )
				{
					if ( link_itr->wstrID.empty() && link_itr->wstrPW.empty() )
					{
						// 인증을 받을 필요가 없네.
						link_itr->kAddr.wPort = kAddr.wPort;
						if ( S_OK == Connected( pkSession, *link_itr ) )
						{
							m_kContList.erase( link_itr );
							return S_OK;
						}
					}
					else
					{
						// 인증패킷을 통해 인증을 받아야 한다.
						return S_OK;
					}
				}
			}
			else
			{
				if ( link_itr->kAddr == kAddr )
				{
					if ( S_OK == Connected( pkSession, *link_itr ) )
					{
						m_kContList.erase( link_itr );
						return S_OK;
					}
				}
			}
		}
	}

	return E_FAIL;
}

HRESULT	PgAPServer::Locked_Logined( CEL::CSession_Base * const pkSession, SLinkageServerInfo const &kInfo )
{
	BM::CAutoMutex kWLock( m_kRWMutex, true );
	
	// 혹시 이미 인증된놈 일 수도 있으니 먼저 찾아보자
	if ( S_OK == IsConnected( pkSession->SessionKey().SessionGuid() ) )
	{
		return S_FALSE;
	}

	CONT_LINKAGE_SERVER_LIST::iterator link_itr = m_kContList.begin();
	for ( ; link_itr!=m_kContList.end() ; ++link_itr )
	{
		if ( true == link_itr->bAccept )
		{
			if ( kInfo.kType == link_itr->kType )
			{
				if ( kInfo.kAddr.ip.s_addr == link_itr->kAddr.ip.s_addr )
				{
					if ( kInfo.wstrID == link_itr->wstrID )
					{
						if ( kInfo.wstrPW == link_itr->wstrPW )
						{
							link_itr->kAddr.wPort = kInfo.kAddr.wPort;
							if ( S_OK == Connected( pkSession, *link_itr ) )
							{
								m_kContList.erase( link_itr );
								return S_OK;
							}
						}
					}
				}
			}
		}
	}
	return E_FAIL;
}

HRESULT PgAPServer::Locked_DisConnected( BM::GUID const &kSessionID, bool &bOutIsAccept )
{
	BM::CAutoMutex kWLock( m_kRWMutex, true );
	return DisConnected( kSessionID, bOutIsAccept );
}

HRESULT PgAPServer::Locked_IsConnected( BM::GUID const &kSessionID )const
{
	BM::CAutoMutex kRLock( m_kRWMutex, false );
	return IsConnected( kSessionID );
}

HRESULT PgAPServer::Locked_GetServeInfo( BM::GUID const &kSessionID, SLinkageServerInfo &rkOutInfo )const
{
	BM::CAutoMutex kRLock( m_kRWMutex, false );

	CONT_LINKAGE_SERVER_ACCESSLIST::const_iterator access_itr = m_kContAccessList.find( kSessionID );
	if ( access_itr != m_kContAccessList.end() )
	{
		rkOutInfo = access_itr->second->GetServerInfo();
		return S_OK;
	}
	return E_FAIL;
}

void PgAPServer::Locked_ConnectToAllLinkAgeServer( BM::GUID const &kConnectorGuid )
{
	BM::CAutoMutex kWLock( m_kRWMutex, true );

	if ( kConnectorGuid.IsNotNull() )
	{
		m_kConnectWorkGuid = kConnectorGuid;
	}
	
	if ( m_kConnectWorkGuid.IsNull() )
	{
		return;
	}

	CONT_LINKAGE_SERVER_LIST::const_iterator link_itr = m_kContList.begin();
	for ( ; link_itr!=m_kContList.end() ; ++link_itr )
	{
		if ( !(link_itr->bAccept) )
		{
			g_kCoreCenter.Connect( link_itr->kAddr, CEL::SESSION_KEY( m_kConnectWorkGuid, BM::GUID::NullData() ) );
		}
	}
}

bool PgAPServer::Locked_IsConnectToServer( CEL::ADDR_INFO const &kAddrInfo )const
{
	BM::CAutoMutex kRLock( m_kRWMutex, false );
	CONT_LINKAGE_SERVER_LIST::const_iterator link_itr = m_kContList.begin();
	for ( ; link_itr!=m_kContList.end() ; ++link_itr )
	{
		if ( link_itr->kAddr == kAddrInfo )
		{
			return true;
		}
	}
	return false;
}

HRESULT PgAPServer::Add( SLinkageServerInfo const &kInfo )
{
	m_kContList.push_back( kInfo );
	return S_OK;
}

HRESULT PgAPServer::Connected( CEL::CSession_Base * const pkSession, SLinkageServerInfo const &kInfo )
{
	if ( NULL == pkSession )
	{
		return E_FAIL;
	}

	PgLinkAgeServer_Base *pkServer = NULL;

	switch( kInfo.kType )
	{
	case LST_BILLING_AP:
		{
			PgGFBillingAP *pkBillingAP = new PgGFBillingAP( pkSession, kInfo );
			pkServer = dynamic_cast<PgLinkAgeServer_Base*>( pkBillingAP );
		}break;
	case LST_MOBILE_LOCK:
		{
			PgGFMobileLock *pkMobileLock = new PgGFMobileLock( pkSession, kInfo );
			pkServer = dynamic_cast<PgLinkAgeServer_Base*>(pkMobileLock);
		}break;
	default:
		{
			return E_FAIL;
		}break;
	}

	if ( pkServer )
	{
		CONT_LINKAGE_SERVER_ACCESSLIST::_Pairib kPair = m_kContAccessList.insert( std::make_pair( pkSession->SessionKey().SessionGuid(), pkServer ) );
		if ( true == kPair.second )
		{
			if ( true == kInfo.bAccept )
			{
				// 인증에 성공했다고 보내 주어야 한다.
				BM::CPacket kAnsPacket( PT_AP_GF_ANS_SERVER_LOGIN_SUCCESS );
				pkServer->Send( kAnsPacket );
			}
			return S_OK;
		}

		SAFE_DELETE( pkServer );
	}
	return E_FAIL;
}

HRESULT PgAPServer::DisConnected( BM::GUID const &kSessionID, bool &bOutIsAccept )
{
	CONT_LINKAGE_SERVER_ACCESSLIST::iterator access_itr = m_kContAccessList.find( kSessionID );
	if ( access_itr != m_kContAccessList.end() )
	{
		PgLinkAgeServer_Base* pkServer = access_itr->second;
		Add( pkServer->GetServerInfo() );
		bOutIsAccept = pkServer->GetServerInfo().bAccept;

		SAFE_DELETE(pkServer);
		m_kContAccessList.erase( access_itr );
		return S_OK;
	}
	return E_FAIL;
}

HRESULT PgAPServer::IsConnected( BM::GUID const &kSessionID )const
{
	CONT_LINKAGE_SERVER_ACCESSLIST::const_iterator access_itr = m_kContAccessList.find( kSessionID );
	if ( access_itr != m_kContAccessList.end() )
	{
		return S_OK;
	}
	return E_FAIL;
}

HRESULT PgAPServer::Locked_ProcessPacket( BM::GUID const &kSessionID, BM::CPacket::DEF_PACKET_TYPE const kType, BM::CPacket &rkPacket )const
{
	BM::CAutoMutex kRLock( m_kRWMutex, false );

	CONT_LINKAGE_SERVER_ACCESSLIST::const_iterator access_itr = m_kContAccessList.find( kSessionID );
	if ( access_itr != m_kContAccessList.end() )
	{
		access_itr->second->ProcessPacket( kType, rkPacket );
		return S_OK;
	}
	return E_FAIL;
}

void PgAPServer::Locked_Tick(void)
{
	BM::CAutoMutex kRLock( m_kRWMutex, false );

	CONT_LINKAGE_SERVER_ACCESSLIST::iterator access_itr = m_kContAccessList.begin();
	for ( ; access_itr!=m_kContAccessList.end() ; ++access_itr )
	{
		access_itr->second->Update();
	}
}

