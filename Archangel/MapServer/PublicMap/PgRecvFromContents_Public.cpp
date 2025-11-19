#include "stdafx.h"
#include "Variant/PgEventView.h"
#include "Global.h"
#include "PgGuildHouse.h"

bool PgGuildHouse::VUpdate( CUnit* pkUnit, WORD const wType, CEL::CPacket* pkNfy )
{
	switch(wType)
	{
	case PT_C_N_REQ_JOIN_PARTY:
	case PT_C_N_REQ_JOIN_PARTYFIND:
	case PT_C_N_ANS_JOIN_PARTY:
	case PT_C_N_ANS_JOIN_PARTYFIND:
	case PT_C_N_REQ_LEAVE_PARTY:
	case PT_C_N_REQ_KICKOUT_PARTY_USER:
	case PT_C_N_REQ_PARTY_CHANGE_MASTER:
	case PT_C_N_REQ_PARTY_CHANGE_OPTION:
		{
			pkUnit->SendWarnMessage(700034);//파티명령어를 사용할 수 없는 지역입니다.
			INFO_LOG( BM::LOG_LV0, _T("PgGuildHouse : Impossible Party!!! PacketType[%u], Hacking User[%s:%s]"), wType, pkUnit->Name().c_str(), pkUnit->GetID().str().c_str() );
		}break;
	default:
		{
			return PgGround::VUpdate( pkUnit, wType, pkNfy );
		}break;
	}
	return false;
}

bool PgGuildHouse::RecvGndWrapped( unsigned short usType, CEL::CPacket* const pkPacket )
{
	switch(usType)
	{
// 	case PT_N_PM_NFY_DECLARE_SIEGEWAR:
// 		{
// 			RecvDeclareSiegeWar( *pkPacket, 0 );
// 		}break;
	case PT_M_M_ANS_CREATE_GROUND:
		{
			SGroundKey kGndKey;
			pkPacket->Pop(kGndKey);
			ReadyWar( kGndKey );
		}break;
// 	case PT_PM_PM_ANS_GROUND_READY:
// 		{
// 			bool bSuccess = false;
// 			pkPacket->Pop(bSuccess);
// 			if ( bSuccess )
// 			{
// 				StartWar();
// 			}
// 			else
// 			{
// 				FailedWar();
// 			}
// 		}break;
	case PT_T_M_NFY_CREATE_GROUND_FAILED:
		{
			SGroundKey kGndKey;
			pkPacket->Pop(kGndKey);
			FailedWar();
		}break;
//	case PT_M_N_NFY_START_SIEGEWAR_GODCMD:
//		{
// 			BM::GUID kMemberGuid;
// 			int iAfterMin = 0;
// 			pkPacket->Pop(kMemberGuid);
// 			pkPacket->Pop(iAfterMin);
// 
// 			INFO_LOG(BM::LOG_LV5,_T("[SIEGEWAR] God Command Begin SiegeWar[%d] WarID[%s] ReqMemberGuid[%s] After[%d] Min."), GetKey(), m_kHoldSiegeWarID.str().c_str(), kMemberGuid.str().c_str(), iAfterMin ); 
// 			if ( iAfterMin )
// 			{
// 				BM::CAutoMutex kLock(m_kRscMutex);
// 				if ( IsHoldSiegeWar() && !IsIngSiegeWar() )
// 				{
// 					__int64 i64BeginTime = g_kEventView.GetLocalSecTime(CGameTime::DEFAULT);
// 					i64BeginTime += (CGameTime::SECOND * 60 * (__int64)iAfterMin);
// 					m_i64NextSiegeWarTime = i64BeginTime;
// 
// 					// 공성전 시간이 변경 되었다고 알려준다.
// 					CEL::CPacket kBroadPacket( PT_M_T_NFY_NOTICE_PACKET, NOTICE_CHANGE_SIEGEWAR_TIME );
// 					kBroadPacket.Push(m_iDefStringName);
// 					kBroadPacket.Push(m_i64NextSiegeWarTime);
// 					SendToCenter( kBroadPacket );
// 				}
// 			}
// 			else
// 			{
// 				BeginWar();
// 			}		
//		}break;
// 	case PT_PM_PM_NFY_GAME_RESULT:
// 		{
// 			BM::GUID kWinGuildGuid;
// 			pkPacket->Pop(kWinGuildGuid);
// 			EndWar(kWinGuildGuid);
// 		}break;
	default:
		{
			return PgGround::RecvGndWrapped( usType, pkPacket  );
		}break;
	}
	return true;
}