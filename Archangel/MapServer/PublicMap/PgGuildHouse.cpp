#include "stdafx.h"
#include "Variant/PgEventView.h"
#include "Variant/PgQuestInfo.h"
#include "Variant/PgMission.h"
#include "Variant/PgMissionQuest.h"
#include "Global.h"
#include "constant.h"
#include "PgAction.h"
#include "PgActionQuest.h"
#include "PgGuildHouse.h"

PgGuildHouse::PgGuildHouse()
{
	Clear();
}

PgGuildHouse::~PgGuildHouse()
{
	Clear();
}

void PgGuildHouse::Clear()
{
	PgGround::Clear();
	m_kGuildGuid.Clear();
	m_kGuildName.clear();
	m_kMasterName.clear();
	m_iDefStringName = 0;

	m_kHoldSiegeWarID.Clear();
	m_i64NextSiegeWarTime = 0;
	m_kWarGroundKey.Clear();
	m_bNotice = false;
}


bool PgGuildHouse::Clone( PgGuildHouse* pkGuildHouse )
{
	m_kGuildGuid = pkGuildHouse->m_kGuildGuid;
	m_kGuildName = pkGuildHouse->m_kGuildName;
	m_kMasterName = pkGuildHouse->m_kMasterName;
	m_iDefStringName = pkGuildHouse->m_iDefStringName;
	m_bNotice = pkGuildHouse->m_bNotice;
	return PgGround::Clone( dynamic_cast<PgGround*>(pkGuildHouse) );
}

bool PgGuildHouse::Clone( PgGround* pkGround )
{
	return this->Clone( dynamic_cast<PgGuildHouse*>(pkGround) );
}

EOpeningState PgGuildHouse::Init( int const iMonsterControlID, bool const bMonsterGen )
{
// 	CONT_GUILDHOUSE_DATA::mapped_type kElement;
// 	if ( g_kGuildHouseMgr.GetGuildHouse( GetKey(), kElement ) )
// 	{
// 		m_iDefStringName = kElement.DefString();
// 		m_kGuildGuid = kElement.Master().kGuildGuid;
// 		m_kGuildName = kElement.Master().wstrGuildName;
// 		m_kMasterName = kElement.Master().wstrGuildMaster;
// 
// 		CONT_SIEGEWAR_LIST::mapped_type kSiegeWar;
// 		if ( g_kGuildHouseMgr.GetSiegeWar( GetKey(), kSiegeWar ) )
// 		{//
// 			m_kHoldSiegeWarID = kSiegeWar.kWarID;
// 			m_i64NextSiegeWarTime = kSiegeWar.i64Time;
// 		}
// 		else
// 		{
// 			m_kHoldSiegeWarID.Clear();
// 			m_i64NextSiegeWarTime = 0;
// 		}
// 		m_kWarGroundKey.Clear();
// 		m_bNotice = false;
		return PgGround::Init( iMonsterControlID, false );
//	}

	VERIFY_INFO_LOG(false, BM::LOG_LV5,_T("[%s] Not Found GuildHouse[%d]"), GetGroundNo() );
	return E_OPENING_ERROR;	
}

void PgGuildHouse::OnTick30s()
{
	BM::CAutoMutex kLock(m_kRscMutex);
// 
// 	PgGround::OnTick30s();
// 
// 	if ( IsHoldSiegeWar() && !IsIngSiegeWar() )
// 	{
// 		__int64 const i64NowTime = g_kEventView.GetLocalSecTime(CGameTime::DEFAULT);
// 		if ( !m_bNotice )
// 		{
// 			__int64 iCheckTime = m_i64NextSiegeWarTime - PgGuildHouseMgr::ms_iNoticeTime;
// 			if ( i64NowTime >= iCheckTime )
// 			{// 공지를 보내야 한다.
// 
// 				__int64 iNoticeTime = m_i64NextSiegeWarTime - (60*5*CGameTime::SECOND);//5분전에
// 				CEL::CPacket kBroadPacket1( PT_M_T_NFY_NOTICE_PACKET_HOLD, iNoticeTime );
// 				kBroadPacket1.Push(NOTICE_BEFORE_BEGIN_SIEGEWAR);
// 				kBroadPacket1.Push(m_iDefStringName);
// 				kBroadPacket1.Push((int)5);
// 
// 				iNoticeTime = m_i64NextSiegeWarTime - (60*CGameTime::SECOND);//1분전에
// 				CEL::CPacket kBroadPacket2( PT_M_T_NFY_NOTICE_PACKET_HOLD, iNoticeTime );
// 				kBroadPacket2.Push(NOTICE_BEFORE_BEGIN_SIEGEWAR);
// 				kBroadPacket2.Push(m_iDefStringName);
// 				kBroadPacket2.Push((int)1);
// 
// 				SendToCenter( kBroadPacket1 );
// 				SendToCenter( kBroadPacket2 );
// 				m_bNotice = true;
// 			}
// 		}
// 		else if ( i64NowTime >= m_i64NextSiegeWarTime )
// 		{	
// 			BeginWar();
// 		}
// 	}
}

bool PgGuildHouse::BeginWar()
{
	BM::CAutoMutex kLock(m_kRscMutex);

// 	if ( IsHoldSiegeWar() && !IsIngSiegeWar() )
// 	{
// 		// 전쟁 시작!!!!
// 		INFO_LOG(BM::LOG_LV5, _T("[SIEGEWAR] BEGIN[%d] SiegeWarID[%s]"), GetKey(), m_kHoldSiegeWarID.str().c_str() );
// 
// 		m_bNotice = false;
// 		m_kWarGroundKey.GroundNo(9930100);
// 		SGroundKey kGndKey( m_kWarGroundKey.GroundNo(), m_kHoldSiegeWarID );

		// 로드벨런싱 해야지.
// 		CEL::CPacket kNPacket( PT_M_T_REQ_CREATE_GROUND, GroundKey() );
// 		kNPacket.Push( kGndKey );
// 		kNPacket.Push( (T_GNDATTR)GATTR_SIEGEWAR );
// 		SendToCenter(kNPacket);
// 		return true;
// 	}

//	INFO_LOG(BM::LOG_LV2, _T("[SIEGEWAR] BEGIN ERROR[%d] SiegeWarID[%s]"), GetKey(), m_kHoldSiegeWarID.str().c_str() );
	return false;
}

bool PgGuildHouse::ReadyWar( SGroundKey const &rkGndKey )
{
// 	BM::CAutoMutex kLock(m_kRscMutex);
// 	INFO_LOG(BM::LOG_LV5, _T("[SIEGEWAR] READY[%d] SiegeWarID[%s]"), GetKey(), m_kHoldSiegeWarID.str().c_str() );
// 
// 	m_kWarGroundKey = rkGndKey;
// 
// 	CONT_GUILDINFO	kContGuildInfo;
// 
// 	CONT_SIEGEWAR_LIST::mapped_type kElement;
// 	if ( g_kGuildHouseMgr.GetSiegeWar( GetKey(), kElement ) )
// 	{
// 		kContGuildInfo.push_back(kElement.kAttackGuildInfo); // 공격자가 RED TEAM
// 		kContGuildInfo.push_back(kElement.kDefenceGuildInfo);// 수비자가 BLUE TEAM

		// 그라운드를 레디 시켜 주어야 한다.
// 		CEL::CPacket kReadyPacket(PT_PM_PM_NFY_GROUND_READY, (EPVPTYPE)WAR_TYPE_SIEGE );
// 		kReadyPacket.Push(true);
// 		kReadyPacket.Push(GroundKey());
// 		kReadyPacket.Push((DWORD)7200000);//2시간
// 		TWriteArray( kReadyPacket, kContGuildInfo );
// 		SendToGround( m_kWarGroundKey, kReadyPacket );

// 		return true;
// 	}

// 	INFO_LOG(BM::LOG_LV2, _T("[SIEGEWAR] READY ERROR[%d] SiegeWarID[%s]"), GetKey(), m_kHoldSiegeWarID.str().c_str() );
// 	FailedWar();
	return false;
}

bool PgGuildHouse::StartWar()
{
	BM::CAutoMutex kLock(m_kRscMutex);
// 	INFO_LOG(BM::LOG_LV5, _T("[SIEGEWAR] START [%d] SiegeWarID[%s]"), GetKey(), m_kHoldSiegeWarID.str().c_str() );
// 
// 	CONT_SIEGEWAR_LIST::mapped_type kElement;
// 	if ( g_kGuildHouseMgr.GetSiegeWar( GetKey(), kElement ) )
// 	{
// 		// 공성전이 시작된다는 것을 알려줘야 한다.
// 		CEL::CPacket kBroadPacket( PT_M_T_NFY_NOTICE_PACKET, NOTICE_START_SIEGEWAR );
// 		kBroadPacket.Push(kElement.kDefenceGuildInfo.wstrGuildName);
// 		kBroadPacket.Push(kElement.kAttackGuildInfo.wstrGuildName);
// 		SendToCenter( kBroadPacket );
// 
// 		// 동기화를 시켜줘야 한다.
// 		CEL::CPacket kPacket(PT_PM_A_NFY_GUILD_HOUSE_UPDATE);
// 		if ( g_kGuildHouseMgr.BeginSiegeWar( GetKey(), m_kWarGroundKey, &kPacket ) )
// 		{
// 			SendToCenter( kPacket );
// 
// 			// DB에 저장하여야 한다.
// 			SYSTEMTIME kNowTime;
// 			g_kEventView.GetLocalTime(&kNowTime);
// 			BM::DBTIMESTAMP_EX kDBTime(kNowTime);
// 
// 			CEL::CPacket kPacket2(PT_PM_T_NFY_DECLARE_SIEGEWAR_DBUPDATE,m_kHoldSiegeWarID);
// 			kPacket2.Push((BYTE)PgGuildHouseMgr::SW_UPDATE_BEGIN);
// 			kPacket2.Push(kDBTime);
// 			if ( !SendToCenter( kPacket2 ) )
// 			{
// 				INFO_LOG(BM::LOG_LV5, _T("[%s] DB Update Failed!![%d]-[%s]"), __FUNCTIONW__, GetKey(), m_kHoldSiegeWarID.str().c_str() );
// 			}
// 
// 			// 현재 여기에 있는 놈들은 공성전 그라운드로 이동 시켜야 한다.
// 			UNIT_PTR_ARRAY kUnitArray;
// 			AddUnitArray( kUnitArray, UT_PLAYER );
// 			SReqMapMove_MT kRMM(MMET_Normal, 1, m_kWarGroundKey);
// 			ReqMapMove( kUnitArray, kRMM );
// 			return true;
// 		}
// 	}
// 
// 	INFO_LOG(BM::LOG_LV2, _T("[SIEGEWAR] START ERROR[%d] SiegeWarID[%s]"), GetKey(), m_kHoldSiegeWarID.str().c_str() );
// 	FailedWar();
	return false;
}

void PgGuildHouse::FailedWar()
{
	BM::CAutoMutex kLock(m_kRscMutex);

// 	INFO_LOG(BM::LOG_LV5, _T("[SIEGEWAR] FAILED [%d] SiegeWarID[%s]"), GetKey(), m_kHoldSiegeWarID.str().c_str() );
// 
// 	BM::GUID const kWarID = m_kHoldSiegeWarID;
// 
// 	m_kWarGroundKey.Clear();
// 	m_kHoldSiegeWarID.Clear();
// 	SetNextTime();
// 
// 	CONT_SIEGEWAR_LIST::mapped_type kElement;
// 	GetBaseSiegeWarinfo(kElement);// 전쟁을 실패했으니까 그냥 원래정보로 셋팅
// 
// 	// 동기화를 시켜줘야 한다.
// 	CEL::CPacket kPacket(PT_PM_A_NFY_GUILD_HOUSE_UPDATE);
// 	if ( g_kGuildHouseMgr.UpdateGuildHouse( GetKey(), kElement, &kPacket ) )
// 	{
// 		SendToCenter( kPacket );
// 
// 		// DB에 저장하여야 한다.
// 		SYSTEMTIME kNowTime;
// 		g_kEventView.GetLocalTime(&kNowTime);
// 		BM::DBTIMESTAMP_EX kDBTime(kNowTime);
// 
// 		CEL::CPacket kPacket2(PT_PM_T_NFY_DECLARE_SIEGEWAR_DBUPDATE,kWarID);
// 		kPacket2.Push((BYTE)PgGuildHouseMgr::SW_UPDATE_ERROR);
// 		kPacket2.Push(kDBTime);
// 		if ( !SendToCenter( kPacket2 ) )
// 		{
// 			INFO_LOG(BM::LOG_LV5, _T("[%s] DB Update Failed!![%d]-[%s]"), __FUNCTIONW__, GetKey(), m_kHoldSiegeWarID.str().c_str() );
// 		}
// 	}
}

bool PgGuildHouse::EndWar( BM::GUID const &kWinGuild )
{
	BM::CAutoMutex kLock(m_kRscMutex);

// 	INFO_LOG(BM::LOG_LV5, _T("[SIEGEWAR] END [%d] SiegeWarID[%s] : Winner[%s]"), GetKey(), m_kHoldSiegeWarID.str().c_str(), kWinGuild.str().c_str() );
// 
// 	if ( IsIngSiegeWar() )
// 	{
// 		CONT_SIEGEWAR_LIST::mapped_type kElement;
// 		if ( g_kGuildHouseMgr.GetSiegeWar( GetKey(), kElement ) )
// 		{
// 			if ( kElement.kWarID == m_kHoldSiegeWarID )
// 			{
// 				if ( kElement.kAttackGuildInfo.kGuildGuid == kWinGuild )
// 				{// Attacker Win
// 					SetGuildMaster( kElement.kAttackGuildInfo, PgGuildHouseMgr::SW_UPDATE_WIN );
// 				}
// 				else
// 				{
// 					SetGuildMaster( kElement.kDefenceGuildInfo, PgGuildHouseMgr::SW_UPDATE_LOST );
// 				}
// 			}
// 			else
// 			{
// 				VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s] SiegeWar ID[%s]-[%s] Error!"), __FUNCTIONW__, m_kHoldSiegeWarID.str().c_str(), kElement.kWarID.str().c_str() );
// 			}
// 		}
// 		return true;
// 	}
	return false;
}

HRESULT PgGuildHouse::RecvDeclareSiegeWar( CEL::CPacket &kPacket, short const nChannelNo )
{
// 	__int64 i64Time = 0;
// 	bool bThrow = false;
// 	SGuildHouseInfo kGuildInfo;
// 	BM::GUID kMemberGuid;
// 	kPacket.Pop(i64Time);
// 	kPacket.Pop(bThrow);
// 	kGuildInfo.ReadFromPacket(kPacket);
// 	kPacket.Pop(kMemberGuid);
// 
// 	BM::CAutoMutex kLock(m_kRscMutex);
// 
// 	if ( ( !IsHoldSiegeWar() || bThrow ) && (kGuildInfo.kGuildGuid != m_kGuildGuid) )
// 	{
// 		if ( IsEmptyMaster() )
// 		{
// 			SetGuildMaster( kGuildInfo );
// 		}
// 		else
// 		{
// 			SYSTEMTIME kSystemTime;
// 			g_kEventView.GetLocalTime(&kSystemTime);
// 			__int64 const iNext64Time = g_kGuildHouseMgr.GetNextTime( kSystemTime, GetKey(), false );
// 
// 			if ( i64Time == iNext64Time )
// 			{
// 				m_i64NextSiegeWarTime = iNext64Time;
// 
// 				CONT_SIEGEWAR_LIST::mapped_type kElement;
// 				CEL::CPacket kDBPacket(PT_PM_T_NFY_DECLARE_SIEGEWAR_DBSAVE,bThrow);
// 				
// 				if ( !bThrow )
// 				{
// 					m_kHoldSiegeWarID.Generate();
// 					
// 					GetBaseSiegeWarinfo(kElement);
// 					kElement.kAttackGuildInfo = kGuildInfo;
// 
// 					SYSTEMTIME kSystemTime;
// 					CGameTime::SecTime2SystemTime( kElement.i64Time, kSystemTime, CGameTime::DEFAULT );
// 					BM::DBTIMESTAMP_EX kDBTime = kSystemTime;
// 
// 					kDBPacket.Push(kElement.kWarID);
// 					kDBPacket.Push(kElement.iGuildHouseNo);
// 					kDBPacket.Push(kElement.kAttackGuildInfo.kGuildGuid);
// 					kDBPacket.Push(kDBTime);
// 				}
// 				else
// 				{
// 					// 3시간 이전에는 포기 할 수가 없다.
// 					__int64 i64NowTime = 0;
// 					CGameTime::SystemTime2SecTime( kSystemTime, i64NowTime, CGameTime::DEFAULT );
// 					__int64 const i64RemainTime = iNext64Time - i64NowTime;
// 					if ( PgGuildHouseMgr::ms_iThrowMinTime > i64RemainTime )
// 					{
// 						SendWarnMessage( kMemberGuid, 71024, nChannelNo );
// 						return E_FAIL;
// 					}
// 
// 					kDBPacket.Push(m_kHoldSiegeWarID);
// 					m_kHoldSiegeWarID.Clear();
// 					GetBaseSiegeWarinfo(kElement);
// 				}
// 
// 				// 동기화를 시켜줘야 한다.
// 				CEL::CPacket kPacket(PT_PM_A_NFY_GUILD_HOUSE_UPDATE);
// 				if ( g_kGuildHouseMgr.UpdateGuildHouse( GetKey(), kElement, &kPacket ) )
// 				{
// 					SendToCenter( kPacket );	
// 					
// 					if ( !SendToCenter( kDBPacket ) )
// 					{
// 						INFO_LOG(BM::LOG_LV5, _T("[%s] GuildHouse Declare SiegeWar Data Save Failed!![%d]-[%s]"), __FUNCTIONW__, GetKey(), kElement.kAttackGuildInfo.kGuildGuid.str().c_str() );
// 					}
// 
// 					// 신청한 유저한테 갱신시켜 주어야 한다.
// 					CEL::CPacket kCPacket( PT_N_C_NFY_GUILD_HOUSE_COMMAND, E_GH_N_C_ANS_INFOMATION );
// 					kCPacket.Push((DWORD)PgGuildHouseMgr::GH_DTYPE_SIEGEWAR);
// 					kCPacket.Push((size_t)1);
// 					GetKey().WriteToPacket(kCPacket);
// 					kElement.WriteToPacket(kCPacket);
// 					SendToClient( kMemberGuid, kCPacket );
// 
// 					SendWarnMessage( kMemberGuid, (bThrow ? 71023 : 71022), nChannelNo );
// 					return S_OK;
// 				}
// 			}
// 		}	
// 	}
// 
// 	CONT_SIEGEWAR_LIST::mapped_type kElement;
// 	g_kGuildHouseMgr.GetSiegeWar( GetKey(), kElement );
// 
// 	CEL::CPacket kCPacket( PT_N_C_NFY_GUILD_HOUSE_COMMAND, E_GH_N_C_ANS_INFOMATION );
// 	kCPacket.Push((DWORD)PgGuildHouseMgr::GH_DTYPE_SIEGEWAR);
// 	kCPacket.Push((size_t)1);
// 	GetKey().WriteToPacket(kCPacket);
// 	kElement.WriteToPacket(kCPacket);
// 	SendToClient( kMemberGuid, kCPacket );
	return E_FAIL;
}

void PgGuildHouse::SetNextTime()
{
	SYSTEMTIME kSystemTime;
	g_kEventView.GetLocalTime(&kSystemTime);
/*	m_i64NextSiegeWarTime = g_kGuildHouseMgr.GetNextTime(kSystemTime, GetKey(), false );*/
}

// void PgGuildHouse::GetBaseSiegeWarinfo( CONT_SIEGEWAR_LIST::mapped_type &kElement )
// {
// 	BM::CAutoMutex kLock(m_kRscMutex);
// 	kElement.kWarID = m_kHoldSiegeWarID;
// 	kElement.i64Time = m_i64NextSiegeWarTime;
// 	kElement.iDefStringName = m_iDefStringName;
// 	kElement.iGuildHouseNo = GetKey();
// 	kElement.kDefenceGuildInfo.kGuildGuid = m_kGuildGuid;
// 	kElement.kDefenceGuildInfo.wstrGuildName = m_kGuildName;
// 	kElement.kDefenceGuildInfo.wstrGuildMaster = m_kMasterName;
// }

//void PgGuildHouse::SetGuildMaster( SGuildHouseInfo const &kGuildInfo, BYTE const kDBType )
//{
//	BM::CAutoMutex kLock(m_kRscMutex);

// 	BM::GUID const kWarID = m_kHoldSiegeWarID;
// 
// 	m_kHoldSiegeWarID.Clear();
// 	m_kWarGroundKey.Clear();
// 	SetNextTime();
// 	m_kGuildGuid = kGuildInfo.kGuildGuid;
// 	m_kGuildName = kGuildInfo.wstrGuildName;
// 	m_kMasterName = kGuildInfo.wstrGuildMaster;
// 
// 	CONT_SIEGEWAR_LIST::mapped_type kElement;
// 	GetBaseSiegeWarinfo(kElement);
// 
// 	// 동기화를 시켜줘야 한다.
// 	CEL::CPacket kPacket(PT_PM_A_NFY_GUILD_HOUSE_UPDATE);
// 	if ( g_kGuildHouseMgr.UpdateGuildHouse( GetKey(), kElement, &kPacket ) )
// 	{
// 		SendToCenter( kPacket );
// 
// 		// Save를 시켜줘야 한다.
// 		CEL::CPacket kGuildHousePacket( PT_PM_T_NFY_GUILD_HOUSE_DBSAVE, GetKey() );
// 		kGuildHousePacket.Push( m_kGuildGuid );
// 		if ( !SendToCenter( kGuildHousePacket ) )
// 		{
// 			INFO_LOG(BM::LOG_LV5, _T("[%s] GuildHouse Data DB Save Failed!![%d]-[%s]"), __FUNCTIONW__, GetKey(), m_kGuildGuid.str().c_str() );
// 		}
// 
// 		if ( kDBType != PgGuildHouseMgr::SW_UPDATE_ERROR )
// 		{
// 			SYSTEMTIME kNowTime;
// 			g_kEventView.GetLocalTime(&kNowTime);
// 
// 			CEL::CPacket kPacket2(PT_PM_T_NFY_DECLARE_SIEGEWAR_DBUPDATE,kWarID);
// 			kPacket2.Push(kDBType);
// 			kPacket2.Push(BM::DBTIMESTAMP_EX(kNowTime));
// 			if ( !SendToCenter( kPacket2 ) )
// 			{
// 				INFO_LOG(BM::LOG_LV5, _T("[%s] DB Update Failed!![%d]-[%s]"), __FUNCTIONW__, GetKey(), kWarID.str().c_str() );
// 			}
// 		}
// 
// 		// 공지를 내보낸다.
// 		CEL::CPacket kBroadPacket( PT_M_T_NFY_NOTICE_PACKET, NOTICE_HAVE_GUILDHOUSE );
// 		kBroadPacket.Push(m_kGuildName);
// 		kBroadPacket.Push(m_iDefStringName);
// 		SendToCenter( kBroadPacket );
// 	}
//}

void PgGuildHouse::FilterGateWay( UNIT_PTR_ARRAY& rkAddUnitArray, UNIT_PTR_ARRAY& kFailedUnitArray, SReqMapMove_MT &rkRMM )
{
	if ( !IsCreateSiwgeWarGround() )
	{
		UNIT_PTR_ARRAY::iterator unit_itr = rkAddUnitArray.begin();
		while( unit_itr != rkAddUnitArray.end() )
		{
			PgPlayer *pkUser = dynamic_cast<PgPlayer*>(unit_itr->pkUnit);
			if ( !pkUser )
			{
				unit_itr = rkAddUnitArray.erase(unit_itr);
				VERIFY_INFO_LOG( false, BM::LOG_LV3,_T("[%s][%d] pkUser Is Null"), __FUNCTIONW__, __LINE__ );
				continue;
			}

			pkUser->SetPos(rkRMM.pt3TargetPos);
			pkUser->LastAreaPos(rkRMM.pt3TargetPos);//에어리어가 이걸로 강제
			pkUser->MapLoading();	// PT_C_M_NFY_MAPLOADED 받을때 까지 어떠한 Action도 금지~

			//미션퀘스트를 삭제
			PgAction_RemoveMissionQuest kRemoveMissionQuest;
			kRemoveMissionQuest.DoAction(pkUser, NULL);

			if (	(pkUser->GuildGuid() != m_kGuildGuid)
				||	!AddUnit( unit_itr->pkUnit, false ) )
			{
				INFO_LOG(BM::LOG_LV5,_T("[%s][%d] AddUnit Failed : Unit Name[%s]"), __FUNCTIONW__, __LINE__, unit_itr->pkUnit->Name().c_str() );
				kFailedUnitArray.swap(rkAddUnitArray, unit_itr);
// 				kFailedUnitArray.Add(unit_itr->pkUnit,true);
// 				unit_itr = rkAddUnitArray.erase(unit_itr);
			}
			else
			{
				unit_itr->bAutoRemove = false;// 자동삭제를 막는다.
				++unit_itr;
			}
		}
	}
	else
	{
		rkRMM.nTargetPortal = 1;
		rkRMM.kTargetKey = m_kWarGroundKey;
 
// 		UNIT_PTR_ARRAY_MAPMOVE_HELPER kMapMoveHelper( rkAddUnitArray, CEL::CPacket(PT_M_T_REQ_MAP_MOVE, rkRMM), WT_MAPMOVE_SERVER, dynamic_cast<PgGround*>(this) );
// 		kMapMoveHelper.SendToCenter();
	}
}

// void PgGuildHouse::Init(SYSTEMTIME const& kNowTime,const CONT_DEF_SIEGEWAR_TIME& kDefSiegeWarTime)
// {
// 	CONT_DEF_SIEGEWAR_TIME::const_iterator timeBegin_itr = kDefSiegeWarTime.lower_bound(m_kKey);
// 	if ( timeBegin_itr != kDefSiegeWarTime.end() )
// 	{
// 		CONT_DEF_SIEGEWAR_TIME::const_iterator timeEnd_itr = kDefSiegeWarTime.upper_bound(m_kKey);
// 		while ( timeBegin_itr != timeEnd_itr )
// 		{
// 			__int64 i64SecTime = GetNextTime(kNowTime,timeBegin_itr->second);
// 			if ( i64SecTime )
// 			{
// 				m_kHoldSiegeWar.insert(std::make_pair(i64SecTime, BM::GUID::NullData()));
// 			}
// 			++timeBegin_itr;
// 		}
// 	}
// }
// 
// void PgGuildHouse::GetGuildHouseInfo(CONT_GUILDHOUSE_INFO::mapped_type& kElement)const
// {
// 	//	kElement.kGuildHouseKey = m_kKey;
// 	kElement.iDefStringName = m_iDefStringName;
// 	kElement.wstrGuildName = m_kGuildName;
// 	kElement.wstrGuildMasterName = m_kMasterName;
// 	if ( m_kHoldSiegeWar.empty() )
// 	{
// 		kElement.iSiegeWarSecTime = 0;
// 	}
// 	else
// 	{
// 		kElement.iSiegeWarSecTime = m_kHoldSiegeWar.begin()->first;
// 	}
// }
// 
// __int64 PgGuildHouse::GetNextTime(SYSTEMTIME const& kNowTime,const CONT_DEF_SIEGEWAR_TIME::mapped_type& kElement)
// {
// 	if ( kElement.nType < EVERY_WEEKCHECK )
// 	{// 주별로 돌아오는 타입
// 
// 		SYSTEMTIME kTime = kNowTime;
// 		kTime.wHour = (WORD)kElement.cHour;
// 		kTime.wMinute = (WORD)kElement.cMin;
// 
// 		__int64 i64SecTime = 0;
// 		CGameTime::SystemTime2SecTime(kTime,i64SecTime);
// 
// 		if ( kNowTime.wDayOfWeek > kElement.nType )
// 		{
// 			i64SecTime += ( ms_i64OneDaySec * (EVERY_WEEKCHECK-(kNowTime.wDayOfWeek-kElement.nType)) );
// 		}
// 		else if( kNowTime.wDayOfWeek < kElement.nType )
// 		{
// 			i64SecTime += ( ms_i64OneDaySec * (kElement.nType-kNowTime.wDayOfWeek) );
// 		}
// 		else
// 		{
// 			if ( kNowTime.wHour > kTime.wHour )
// 			{
// 				i64SecTime += (ms_i64OneDaySec*EVERY_WEEKCHECK);
// 			}
// 			else if ( kNowTime.wHour == kTime.wHour )
// 			{
// 				if ( kNowTime.wMinute >= kTime.wMinute )
// 				{
// 					i64SecTime += (ms_i64OneDaySec*EVERY_WEEKCHECK);
// 				}
// 			}
// 		}
// 		return i64SecTime;
// 	}
// 
// 	// 지원하지 않는 타입이다.
// 	VERIFY_INFO_LOG(false, BM::LOG_LV4,_T("[%s] Bad TBL_DEF_SIEGEWAR_TIME's type[%u]"),__FUNCTIONW__,kElement.nType);
// 	return 0;
// }
// 
// BM::GUID PgGuild constHouse::GetNextSiegeWar()const
// {
// 	if ( m_kHoldSiegeWar.size() > 0 )
// 	{
// 		return m_kHoldSiegeWar.begin()->second;
// 	}
// 	return BM::GUID::NullData();
// }
// 
// HRESULT PgGuildHouse::IsEmptySiegeWarTime(__int64 const i64SecTime)const
// {
// 	ContDeclareWarTime::const_iterator time_itr = m_kHoldSiegeWar.find(i64SecTime);
// 	if ( time_itr != m_kHoldSiegeWar.end() )
// 	{
// 		if ( BM::GUID::IsNotNull(time_itr->second) )
// 		{
// 			return E_FAIL;
// 		}
// 		else if ( time_itr == m_kHoldSiegeWar.begin() )
// 		{
// 			return S_OK;
// 		}
// 		return S_FALSE;
// 	}
// 	return E_FAIL;
// }
// 
// HRESULT PgGuildHouse::RegistSiegeWar(__int64 const i64SecTime, BM::GUID const &kWarID)
// {
// 	ContDeclareWarTime::iterator time_itr = m_kHoldSiegeWar.find(i64SecTime);
// 	if ( time_itr != m_kHoldSiegeWar.end() )
// 	{
// 		if ( BM::GUID::IsNull(time_itr->second) )
// 		{
// 			time_itr->second = kWarID;
// 
// 			if ( time_itr != m_kHoldSiegeWar.begin() )
// 			{
// 				return S_FALSE;
// 			}
// 			return S_OK;
// 		}
// 	}
// 	return E_FAIL;
// }
// 
// bool PgGuildHouse::Update(const SGuildHouseRet& kRet)
// {
// 	if ( m_kGuildGuid != kRet.kVGuildGuid )
// 	{
// 		m_kGuildGuid = kRet.kVGuildGuid;
// 		m_kGuildName = kRet.wstrGuildName;
// 		m_kMasterName = kRet.wstrMasterName;
// 
// 		// DB에 업데이트
// 		CEL::DB_QUERY kQuery(DT_PLAYER, DQT_UPDATE_GUILDHOUSE, L"EXEC [dbo].[UP_UpdateGuildHouse] ?,?,?");
// 		kQuery.PushParam(m_kKey.iGndNo);
// 		kQuery.PushParam(m_kKey.iPortalNo);
// 		kQuery.PushParam(m_kGuildGuid);
// 		g_kCoreCenter.PushQuery(kQuery);
// 
// 		CEL::CPacket kModifyPacket(PT_T_M_NFY_MODIFY_GATEWAY,GATEWAY_MODIFY_ONE);
// 		kModifyPacket.Push(m_kKey);
// 
// 		size_t iWrPos = kModifyPacket.WrPos();
// 		kModifyPacket.Push((WORD)GATEWAY_TYPE_PERMISSION);
// 		kModifyPacket.Push((WORD)GATEWAY_GUILDHOUSE);
// 		VEC_GUID kNewOwnerList;
// 		kNewOwnerList.push_back(m_kGuildGuid);
// 		kModifyPacket.Push(kNewOwnerList);
// 		kModifyPacket.Push(m_kGuildName);
// 		kModifyPacket.RdPos(iWrPos);
// 		GET_DEF_WRITE_LOCK(PgGateWayMgr, kGateWayMgr, kDefLock);
// 		if ( kGateWayMgr.ReadFromGateWay(m_kKey,kModifyPacket,false) )
// 		{
// 			kModifyPacket.PosAdjust();
// 			SendToServerType(CEL::ST_MAP, kModifyPacket);
// 		}
// 
// 		CEL::CPacket kNoticePacket(PT_T_C_NFY_NOTICE_PACKET,NOTICE_HAVE_GUILDHOUSE);
// 		kNoticePacket.Push(m_kGuildName);
// 		kNoticePacket.Push(m_iDefStringName);
// 		SendToServerType(CEL::ST_MAP, kNoticePacket);
// 		return true;
// 	}
// 	return false;
// }
// 
// bool PgGuildHouse::StartSiegeWar(__int64 const i64SiegeWarTime)
// {
// 	if ( m_bSiegeWarIng )
// 	{
// 		VERIFY_INFO_LOG(false, BM::LOG_LV0,_T("[%s] Now SiegeWar ING[%d-%d]"),__FUNCTIONW__,m_kKey.iGndNo,m_kKey.iPortalNo);
// 		return false;
// 	}
// 
// 	__int64 iBeginSiegeWarTime = m_kHoldSiegeWar.begin()->first;
// 	if ( iBeginSiegeWarTime < i64SiegeWarTime )
// 	{
// 		assert(false);
// 		return false;
// 	}
// 
// 	m_bSiegeWarIng = true;
// 
// 	// 새로운 시간을 찾아놔야 한다.
// 	m_kHoldSiegeWar.erase(m_kHoldSiegeWar.begin());
// 	iBeginSiegeWarTime += (ms_i64OneDaySec*7);
// 	m_kHoldSiegeWar.insert(std::make_pair(iBeginSiegeWarTime, BM::GUID::NullData()));
// 	return true;
// }
// 
// bool PgGuildHouse::EndSiegeWar(const SGuildHouseRet& kRet)
// {
// 	if ( !m_bSiegeWarIng )
// 	{
// 		VERIFY_INFO_LOG(false, BM::LOG_LV0,_T("[%s] Now SiegeWar Not ING[%d-%d]"),__FUNCTIONW__,m_kKey.iGndNo,m_kKey.iPortalNo);
// 		return false;
// 	}
// 	m_bSiegeWarIng = false;
// 	Update(kRet);
// 	return true;
// }