#include "stdafx.h"
#include "variant/Global.h"
#include "PgPortalMgr.h"

PgPortalMgr::PgPortalMgr()
:	m_dwOldCheckTime(0)
{
}

PgPortalMgr::~PgPortalMgr()
{

}

bool PgPortalMgr::ProcessMsg(SEventMessage *pkMsg)
{
	PACKET_ID_TYPE usType = 0;
	pkMsg->Pop( usType );
	switch( usType )
	{
	case PT_A_T_REQ_INDUN_CREATE:
		{
			SPortalWaiter *pkWaiter = m_kPoolWaiter.New();
			if ( pkWaiter )
			{
				pkWaiter->ReadFromPacket( *pkMsg );
				pkWaiter->dwRegistTime = BM::GetTime32();
				if ( S_OK != Regist( pkWaiter ) )
				{
					m_kPoolWaiter.Delete( pkWaiter );
				}
			}
		}break;
	case PT_M_T_ANS_CREATE_GROUND:
		{
			SGroundKey kGndKey;
			HRESULT hRet = E_FAIL;
			kGndKey.ReadFromPacket( *pkMsg );
			pkMsg->Pop( hRet );
			Respone( kGndKey, hRet );
		}break;
	default:
		{
			VERIFY_INFO_LOG( false, BM::LOG_LV0, __FL__ << _T("Bad PacketType[") << usType << _T("]") );
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Warning!! Invalid CaseType"));
			return false;
		}break;
	}
	return true;
}

HRESULT PgPortalMgr::Regist( SPortalWaiter *pkWaiter, BM::Stream * const pkAddPacket )
{
	BM::CAutoMutex kLock(m_kMutex);

	// 먼저 찾아보자~
	CONT_CREATE_WAITER::iterator wait_itr = m_kContCreateWaiter.find( pkWaiter->kRMM.kTargetKey );
	if ( wait_itr != m_kContCreateWaiter.end() )
	{
		// 찾았다면 중간에 끼워 넣어주어야 한다~
		INFO_LOG( BM::LOG_LV5, __FL__ << _T("Overap GroundKey<") << pkWaiter->kRMM.kTargetKey.GroundNo() << _T("/") << pkWaiter->kRMM.kTargetKey.Guid() << _T(">") );
		wait_itr->second->Add( *pkWaiter );
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return S_FAILS"));
		return S_FALSE;
	}

	// 이미 등록되어 있는 그라운드면 TimeWaiter에만 넣어둔다.
	if ( g_kServerSetMgr.Locked_IsAliveGround( pkWaiter->kRMM.kTargetKey ) )
	{
		m_kContTimeWaiter.push( pkWaiter );
		return S_OK;
	}

	T_GNDATTR kGndAttr = GATTR_DEFAULT;
	{
		CONT_DEFMAP const *pkContDefMap = NULL;
		g_kTblDataMgr.GetContDef( pkContDefMap );

		// 속성을 찾아
		CONT_DEFMAP::const_iterator defmap_itr = pkContDefMap->find( pkWaiter->kRMM.kTargetKey.GroundNo() );
		if ( defmap_itr == pkContDefMap->end() )
		{
			CAUTION_LOG( BM::LOG_LV0, __FL__ << _T("Error GroundNo =") << pkWaiter->kRMM.kTargetKey.GroundNo() );
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return E_FAIL"));
			return E_FAIL;
		}

		kGndAttr = (T_GNDATTR)(defmap_itr->second.iAttr);
	}
		
	m_kContCreateWaiter.insert( std::make_pair( pkWaiter->kRMM.kTargetKey, pkWaiter ) );
	if ( PORTAL_MISSION != pkWaiter->byType )
	{
		switch ( kGndAttr )
		{
		case GATTR_EMPORIA:
			{
				BM::Stream kNPacket( PT_T_N_REQ_PUBLIC_MAP_INFO, pkWaiter->kRMM.kTargetKey );
				SendToRealmContents( PMET_EMPORIA, kNPacket );
			}break;
		default:
			{
				LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Warning!! Invalid CaseType"));
				if ( FAILED(ReqCreateGround( pkWaiter, pkAddPacket )) )
				{
					Respone( pkWaiter->kRMM.kTargetKey, E_FAIL );
				}
			}break;
		}
	}

	return S_OK;
}

HRESULT PgPortalMgr::Respone( SGroundKey const &kKey, HRESULT const hResult )
{
	BM::CAutoMutex kLock(m_kMutex);

	CONT_CREATE_WAITER::iterator wait_itr = m_kContCreateWaiter.find(kKey);
	if ( wait_itr != m_kContCreateWaiter.end() )
	{
		SPortalWaiter *pkWaiter = wait_itr->second;
		m_kContCreateWaiter.erase( wait_itr );// 지웠다!

		switch ( pkWaiter->byType )
		{
		case PORTAL_DELAY:
		case PORTAL_MISSION:
		case PORTAL_SUPERGND:
			{
				if ( SUCCEEDED( hResult ) )
				{
					m_kContTimeWaiter.push( pkWaiter );

					// 메모리 해제 하면 안된다!!
					return S_OK;
				}
			} // break 사용 안함.
		case PORTAL_NODELAY:
			{
				if ( SUCCEEDED( hResult ) )
				{
					// 이동 GoGO
					BM::Stream kMovePacket( PT_T_T_REQ_MAP_MOVE, pkWaiter->kRMM );
					pkWaiter->constellationMission.WriteToPacket(kMovePacket);
					PU::TWriteTable_AA( kMovePacket, pkWaiter->kWaiterList );
					PU::TWriteTable_AM( kMovePacket, pkWaiter->m_kContPetMoveData );
					PU::TWriteTable_AM( kMovePacket, pkWaiter->m_kContUnitSummonedMoveData );
					pkWaiter->m_kModifyOrder.WriteToPacket(kMovePacket);
					SendToCenter( kMovePacket );
				}
				else
				{// 실패했으면 돌려보내야 한다.
					LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Warning!! Result isn't Success"));

					if ( pkWaiter->kRMM.SetBackHome(MMET_Login==pkWaiter->kRMM.cType ? MMET_Failed_Login : MMET_Failed) )
					{
						BM::Stream kBackPacket( PT_T_T_REQ_MAP_MOVE, pkWaiter->kRMM );
						pkWaiter->constellationMission.WriteToPacket(kBackPacket);
						PU::TWriteTable_AA( kBackPacket, pkWaiter->kWaiterList );
						PU::TWriteTable_AM( kBackPacket, pkWaiter->m_kContPetMoveData );
						PU::TWriteTable_AM( kBackPacket, pkWaiter->m_kContUnitSummonedMoveData );
						kBackPacket.Push( static_cast<size_t>(0) );
						SendToCenter( kBackPacket );
					}
					else
					{
						// 이것도 안되면 어쩌지?

					}
					
				}
			}break;
		case PORTAL_PVP:
			{
				::GUID const &kGuid = pkWaiter->kRMM.kCasterKey.Guid();

				BM::Stream kPvPPacket( PT_M_T_ANS_CREATE_GROUND, kKey );
				kPvPPacket.Push( hResult );
				kPvPPacket.Push( static_cast<int>(kGuid.Data1) );// 여기에 방의 Index가 저장 되어 있다.
				SendToPvPLobby( kPvPPacket, pkWaiter->kRMM.kCasterKey.GroundNo() );
			}break;
		}

		m_kPoolWaiter.Delete(pkWaiter);
		return S_OK;
	}
	else
	{
		if ( SUCCEEDED(hResult) )
		{
			INFO_LOG( BM::LOG_LV7, __FL__ << _T("Found Ground=") << kKey.GroundNo() << _T("/") << kKey.Guid() << _T("[SUCCEEDED]"));
		}
		else
		{
			INFO_LOG( BM::LOG_LV0, __FL__ << _T("Not Found Ground") << kKey.GroundNo() << _T("/") << kKey.Guid() << _T("[FAILED]") );
		}	
	}
	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return E_FAIL"));
	return E_FAIL;
}

HRESULT PgPortalMgr::ReqCreateGround( SGroundKey const &kGndKey, BM::Stream * const pkAddPacket )
{
	BM::CAutoMutex kLock(m_kMutex);
	CONT_CREATE_WAITER::iterator wait_itr = m_kContCreateWaiter.find(kGndKey);
	if ( wait_itr != m_kContCreateWaiter.end() )
	{
		return ReqCreateGround( wait_itr->second, pkAddPacket );
	}

	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return E_FAIL"));
	return E_FAIL;
}

HRESULT PgPortalMgr::ReqCreateGround( SPortalWaiter *pkWaiter, BM::Stream * const pkAddPacket )
{
	if ( pkWaiter->bReq )
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return S_FALSE"));
		return S_FALSE;
	}

	SGroundMakeOrder kOrder( pkWaiter->kRMM.kTargetKey );
	kOrder.iOwnerLv = pkWaiter->iOwnerLv;
	kOrder.bIndunPartyDie = pkWaiter->kRMM.bIndunPartyDie;
	kOrder.constellationMission = pkWaiter->constellationMission;

	BM::Stream kReqPacket( PT_T_M_REQ_CREATE_GROUND );
	kOrder.WriteToPacket( kReqPacket );

	if ( pkAddPacket )
	{
		kReqPacket.Push( true );
		kReqPacket.Push( *pkAddPacket );
	}
	else
	{
		kReqPacket.Push( false );
	}
	
	if ( SendToServer( pkWaiter->kRMM.kTargetSI, kReqPacket ) )
	{
		pkWaiter->bReq = true;
		return S_OK;
	}

	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return E_FAIL"));
	return E_FAIL;
}

void PgPortalMgr::OnTick( DWORD const dwCurTime )
{
	BM::CAutoMutex kLock(m_kMutex);

	while ( m_kContTimeWaiter.size() )
	{
		SPortalWaiter *pkWaiter = m_kContTimeWaiter.front();

		// 이동 GoGO
		BM::Stream kMovePacket( PT_T_T_REQ_MAP_MOVE, pkWaiter->kRMM );
		pkWaiter->constellationMission.WriteToPacket(kMovePacket);
		PU::TWriteTable_AA( kMovePacket, pkWaiter->kWaiterList );
		PU::TWriteTable_AM( kMovePacket, pkWaiter->m_kContPetMoveData );
		PU::TWriteTable_AM( kMovePacket, pkWaiter->m_kContUnitSummonedMoveData );
		pkWaiter->m_kModifyOrder.WriteToPacket( kMovePacket );
		SendToCenter( kMovePacket );

		m_kPoolWaiter.Delete(pkWaiter);
		m_kContTimeWaiter.pop();
	}

	if ( 10000 < ::DifftimeGetTime( m_dwOldCheckTime, dwCurTime ) )
	{
		// 10초에 한번씩 TimeOut을 확인해주자.
		CONT_CREATE_WAITER::iterator wait_itr = m_kContCreateWaiter.begin();
		while ( wait_itr!= m_kContCreateWaiter.end() )
		{
			SPortalWaiter *pkWaiter = wait_itr->second;

			if ( pkWaiter )
			{
				if ( m_dwOldCheckTime > pkWaiter->dwRegistTime )
				{
					INFO_LOG( BM::LOG_LV5, __FL__ << _T("TimeOut GroundKey[") << pkWaiter->kRMM.kTargetKey.GroundNo() << _T("/") << pkWaiter->kRMM.kTargetKey.Guid() << _T("]") );

					switch ( pkWaiter->byType )
					{
					case PORTAL_PVP:
						{
							::GUID const &kGuid = pkWaiter->kRMM.kCasterKey.Guid();

							BM::Stream kPvPPacket( PT_M_T_ANS_CREATE_GROUND, wait_itr->first );
							kPvPPacket.Push( (HRESULT)E_FAIL );
							kPvPPacket.Push( static_cast<int>(kGuid.Data1) );// 여기에 방의 Index가 저장 되어 있다.
							SendToPvPLobby( kPvPPacket, pkWaiter->kRMM.kCasterKey.GroundNo() );
						}break;
					case PORTAL_MISSION:
						{
							BM::Stream kMissionFailedPacket( PT_M_T_ANS_PREPARE_MISSION, pkWaiter->kRMM.kTargetKey.Guid() );
							kMissionFailedPacket.Push( (bool)false );
							SendToMissionMgr( kMissionFailedPacket );
						}break;
					}

					// 타임아웃임.
					if ( pkWaiter->kRMM.SetBackHome(MMET_TimeOut) )
					{
						BM::Stream kBackPacket( PT_T_T_REQ_MAP_MOVE, pkWaiter->kRMM );
						pkWaiter->constellationMission.WriteToPacket(kBackPacket);
						PU::TWriteTable_AA( kBackPacket, pkWaiter->kWaiterList );
						PU::TWriteTable_AM( kBackPacket, pkWaiter->m_kContPetMoveData );
						PU::TWriteTable_AM( kBackPacket, pkWaiter->m_kContUnitSummonedMoveData );
						kBackPacket.Push( static_cast<size_t>(0) );
						SendToCenter( kBackPacket );
					}
					else
					{// 이러면 어쩌지...

					}

					m_kPoolWaiter.Delete(pkWaiter);
					wait_itr = m_kContCreateWaiter.erase( wait_itr );
				}
				else
				{
					++wait_itr;
				}
			}
			else
			{
				VERIFY_INFO_LOG( false, BM::LOG_LV0, __FL__ << _T("Critical Error!! Pointer NULL") );
				wait_itr = m_kContCreateWaiter.erase( wait_itr );
				LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Warning!! pkWaiter is NULL"));
			}
		}

		m_dwOldCheckTime = dwCurTime;
	}
}