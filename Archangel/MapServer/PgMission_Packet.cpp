#include "stdafx.h"
#include "BM/PgTask.h"
#include "BM/PgFilterString.h"
#include "Global.h"
#include "Variant/PgMission.h"
#include "Variant/PgPartyMgr.h"
#include "PgLocalPartyMgr.h"
#include "PgTask_MapServer.h"
#include "PgMissionGround.h"
#include "PgAction.h"
#include "PgStoneMgr.h"
#include "PgRequest.h"
#include "Variant/PgMissionInfo.h"
#include "PgMissionMan.h"

bool PgMissionGround::VUpdate( CUnit* pkUnit, WORD const wType, BM::Stream* pkNfy )
{
	switch(wType)
	{
	case PT_C_N_ANS_MISSION_RANK_INPUTMEMO:
		{
			BM::GUID kMemoID;
			std::wstring wstrMemo;
			pkNfy->Pop(kMemoID);
			pkNfy->Pop(wstrMemo);

			if( false == g_kUnicodeFilter.IsCorrect(UFFC_MISSION_RANK_COMMENT, wstrMemo) )
			{
				pkUnit->SendWarnMessage(700406);
				wstrMemo.clear(); // 클라이언트로 메시지를 돌려 줄 수 없다.
			}
			
			BM::Stream kNPacket(PT_C_N_ANS_MISSION_RANK_INPUTMEMO, kMemoID);
			kNPacket.Push(wstrMemo);
			SendToRankMgr(kNPacket);
		}break;
	case PT_C_M_REQ_MISSION_ROULETTE_STOP:
		{
			PgPlayer *pkUser = dynamic_cast<PgPlayer*>(pkUnit);
			if ( pkUser )
			{
				BM::CAutoMutex kLock(m_kMissionMutex);
				for( PgMission::ConUser::const_iterator itr=m_kConUser.begin();itr!=m_kConUser.end();++itr )
				{
					PgMission::ConUser::key_type const& rkGuid = (itr->first);
					if ( pkUser->GetID() != rkGuid )
					{
						CUnit* pkSendUnit = GetUnit(rkGuid);
						if( pkSendUnit )
						{
							PgPlayer *pkSendUser = dynamic_cast<PgPlayer*>(pkSendUnit);
							if( pkSendUser )
							{
								pkSendUser->Send(BM::Stream(PT_M_C_REQ_MISSION_ROULETTE_STOP, pkUser->GetID()));	
							}
						}
					}
				}
			}
		}break;
	case PT_C_M_REQ_MISSION_RESTART:
		{
			PgPlayer *pkUser = dynamic_cast<PgPlayer*>(pkUnit);
			if ( pkUser )
			{
				if ( m_eState == INDUN_STATE_CLOSE )
				{
					if ( S_OK == PgMission::RestartUser(pkUser->GetID()) )
					{
						/*
						// 이벤트 맵은 재시작을 하지 않는다.
						int iType = PgMission::GetTriggerType();
						if( MT_MISSION != static_cast<EMissionTypeKind>(iType) )
						{
							int const iMissionEventAllClear = 0x000F;
							if( iMissionEventAllClear == (iMissionEventAllClear & pkUser->GetAbil(AT_MISSION_EVENT)) )
							{
								// 미션 이벤트 맵을 모두 "SSS" 등급으로 클리어 했다. 히든 맵이 등장한다.
								iType = static_cast<int>(MT_EVENT_HIDDEN);
							}
						}
						PgRequest_MissionInfo kReq(PgMission::GetKey(), GroundKey(), iType);
						kReq.DoAction(pkUser);
						*/

						int const iType = PgMission::GetTriggerType();
						if( MT_MISSION_EASY == static_cast<EMissionTypeKind>(iType) )
						{
							// Easy 모드 같은 경우 UI가 달라지기 때문에 Type을 전달
							PgRequest_MissionInfo kReq(PgMission::GetKey(), GroundKey(), iType);
							kReq.DoAction(pkUser);
						}
						else
						{
							PgRequest_MissionInfo kReq(PgMission::GetKey(), GroundKey());
							kReq.DoAction(pkUser);
						}

						if( true == IsDefenceGameMode() )
						{
							Broadcast(BM::Stream(PT_M_C_ANS_DEFENCE_RESTART));
						}
					}
					else
					{
						if ( pkUser->GetID() == PgMission::GetOwner() )
						{
							VEC_GUID kReasonUser;

							BM::CAutoMutex kLock(m_kMissionMutex);
							for( PgMission::ConUser::const_iterator itr=m_kConUser.begin();itr!=m_kConUser.end();++itr )
							{
								if ( pkUser->GetID() != itr->first )
								{
									kReasonUser.push_back(itr->first);
								}
							}
							pkUser->Send(BM::Stream(PT_M_C_ANS_MISSION_RESTART_FAILED,kReasonUser));	
						}
						else if ( PgMission::GetOwner() == BM::GUID::NullData() )
						{// 오너가 없으면 쫒아내야 한다.
							this->RecvRecentMapMove(pkUser);
						}
					}
				}
				else
				{
					INFO_LOG(BM::LOG_LV0, __FL__<<L"[PT_C_N_REQ_MISSION_RESTART] RecvPacket But MissionState["<<m_eState<<L"] BadUser["<<pkUser->Name()<<L"]");
				}
			}
		}break;
	case PT_C_M_REQ_ENTER_MISSION://여기서 이게 오면 다시 새로 시작하는 거다.
		{
			PgPlayer* pkUser = dynamic_cast<PgPlayer*>(pkUnit);//맵서버가 받아서 셋팅한다
			if(pkUser)
			{
				if ( (m_eState == INDUN_STATE_CLOSE) && (pkUser->GetAbil(AT_HP) > 0) )
				{
					if ( S_OK == PgMission::RestartUser(pkUser->GetID()) )
					{
						int iLevel = 0;
						pkNfy->Pop(iLevel);

						if ( iLevel < 1 )
						{
							INFO_LOG( BM::LOG_LV5, __FUNCTIONW__ << _T("Bad Level : ") << iLevel << _T(" [User ") << pkUser->Name() << _T(",") << pkUser->GetID() << _T("]") );
							LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Wrong iLevel!"));
							break;
						}

						SMissionKey kMissionKey( PgMission::GetKey(), --iLevel );//Client에서는 레벨이 1부터온다

						PgPlayer_MissionData const *pkMissionData = pkUser->GetMissionData( (unsigned int)kMissionKey.iKey );
						if ( !pkMissionData )
						{
							VERIFY_INFO_LOG( false, BM::LOG_LV0, __FL__<<L"pkMissionData is NULL MissionKey["<<kMissionKey.iKey<<L"] User["<<pkUser->Name()<<L"]" );
							LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("pkMissionData is NULL"));
							break;
						}

						PgMissionInfo const * pkMissionInfo = NULL;
						bool bRet = g_kMissionMan.GetMissionKey( kMissionKey.iKey, pkMissionInfo);
						if( bRet )
						{
							SMissionOptionMissionOpen const *pkMissionOpen = NULL;
							pkMissionInfo->GetMissionOpen(iLevel, pkMissionOpen);

							if( (NULL != pkMissionOpen) && (MAX_MISSION_LEVEL > iLevel) )
							{
								if ( !pkMissionData->IsPlayingLevel( pkMissionOpen->m_kLimit_PreLevelValue ) )
								{
									pkUser->SendWarnMessage(400225);
									break;
								}

								PgMyQuest const *pkMyQuest = pkUser->GetMyQuest();
								if(!pkMyQuest)
								{
									pkUser->SendWarnMessage(400225);
									break;
								}

								if( false == pkMissionData->IsClearLevel(iLevel) )
								{
									if( DEFENCE7_MISSION_LEVEL == (iLevel+1) )
									{
										VEC_INT	VecClearQuestValue;
										VecClearQuestValue.clear();
										pkMissionOpen->GetClearQuestIDVec(VecClearQuestValue);
										bool const bClearRet = pkMyQuest->IsEndedQuestVec(VecClearQuestValue);
										if( (false == bClearRet) && ( VecClearQuestValue.size() != 0) )
										{
											pkUser->SendWarnMessage(8016);
											break;
										}
									}

									VEC_INT	VecIngQuestValue;
									VecIngQuestValue.clear();
									pkMissionOpen->GetIngQuestIDVec(VecIngQuestValue);
									bool const bIngRet = pkMyQuest->IsIngQuestVec(VecIngQuestValue);
									bool const bEndRet = pkMyQuest->IsEndedQuestVec(VecIngQuestValue);

									if(false == (bIngRet || bEndRet) && (VecIngQuestValue.size() != 0))
									{
										int const iErrorTTW = pkMissionInfo->GetErrorText();

										pkUser->SendWarnMessage(iErrorTTW);
										break;
									}
								}
							}
							else if( !IsDefenceMissionLevelCheck(pkUser,this,pkMissionInfo->ID(),iLevel) )
							{
								break;
							}

							PgRequest_MissionReStart kReq(PgMission::GetID(), kMissionKey, pkNfy);
							kReq.DoAction(pkUser);
						}
					}
				}
				else
				{
					INFO_LOG(BM::LOG_LV0,__FL__<<L"[PT_C_M_REQ_ENTER_MISSION] RecvPacket But MissionState["<<m_eState<<L"] BadUser["<<pkUser->Name()<<L"]");
				}
			}
		}break;
	case PT_C_C_NFY_MISSION_CLOSE:
		{
			if ( pkUnit )
			{
				if ( PgMission::GetOwner() == BM::GUID::NullData() )
				{// 미션 오너가 없으면 쫒아내야 한다.
					this->RecvRecentMapMove(dynamic_cast<PgPlayer*>(pkUnit));
				}
				else
				{
					if( true == IsDefenceGameMode() )
					{
						if( S_OK == PgMission::ReqNextStageUser(pkUnit->GetID()) )
						{
							Broadcast(BM::Stream(PT_M_C_ANS_DEFENCE_RESTART));
						}
						break;
					}
					Broadcast(BM::Stream(PT_C_C_NFY_MISSION_CLOSE,pkUnit->GetID()),pkUnit);
				}

//				if ( US_DEAD == pkUnit->GetState() )// hwoarang 위에서 맵이동 해버리면 필요 없어 보임.
//				{
//					pkUnit->SetState(US_DEADREADY);
//					pkUnit->DeathTime(BM::GetTime32());
//				}
			}	
		}break;
	case PT_C_N_REQ_LEAVE_PARTY:
		{// 미션에서는 사용 할 수 없음
			pkUnit->SendWarnMessage(700118);
		}break;
	case PT_U_G_NFY_ADD_MISSION_SCORE:
		{
			AddMissionScore(pkNfy);
		}break;
// 	case PT_C_M_NFY_SELECTED_BOX:
// 		{
// 			BM::Stream kNPacket(wType, GroundKey() );
// 			kNPacket.Push( pkUnit->GetID() );
// 			kNPacket.Push( *pkNfy );
// 			SendToContents(kNPacket);
// 		}break;
	case PT_C_M_REQ_MISSION_GADACOIN_ITEM:
		{
			int iRetContNo = GadaCoin_SendItemCheck(pkUnit->GetID());
			//if( 0 != iRetContNo )
			{
				GadaCoin_SendItem(pkUnit, iRetContNo);
			}
		}break;
	case PT_C_M_NFY_DEFENCE_STAGE:
		{
			if( true == IsDefenceGameMode() )
			{
				PgPlayer* pkUser = dynamic_cast<PgPlayer*>(pkUnit);
				if(pkUser)
				{
					BM::CAutoMutex kLock(m_kMissionMutex);
					if( pkUser->GetID() == PgMission::GetOwner() )
					{
						m_bGameOwnerStart = true;
					}
				}
			}
		}break;
	case PT_C_M_NFY_DEFENCE_WAVE:
		{
			if( true == IsDefenceGameMode() )
			{
				PgPlayer* pkUser = dynamic_cast<PgPlayer*>(pkUnit);
				if(pkUser)
				{
					BM::CAutoMutex kLock(m_kMissionMutex);
					if(IsDefenceNextStage())
					{
						if( pkUser->GetID() == PgMission::GetOwner() )
						{
							m_bGameOwnerStartWave = true;
						}
					}
				}
			}
		}break;
	case PT_C_M_NFY_DEFENCE_ENDSTAGE:
		{
			if( (true == IsDefenceGameMode()) )
			{
				// 마지막 스테이지면...
				if( true == IsDefenceLastStage() )
				{
					PgPlayer* pkUser = dynamic_cast<PgPlayer*>(pkUnit);
					if(pkUser)
					{
						// 모든 스테이지 끝
						//if ( PgMission::GetOwner() == BM::GUID::NullData() )
						{// 오너가 없으면 쫒아내야 한다.
							this->RecvRecentMapMove(pkUser);
						}
					}					
				}
				else
				{					
					// 마지막 아니면 다음 스테이지 이동
					if( S_OK == ReqNextStageUser(pkUnit->GetID()) )
					{
						// 모두 다 통보가 오면...
						NextStageSend();
					}
				}
			}
		}break;
	case PT_C_M_NFY_DEFENCE_FAILSTAGE:
		{
		}break;
	case PT_C_M_REQ_DEFENCE_INFALLIBLE_SELECTION:
		{
			ReqUseInfallibleSelection(pkUnit, pkNfy);
		}break;
	case PT_U_G_NFY_DEFENCE_INFALLIBLE_SELECTION:
		{
			SetDirection(pkUnit, pkNfy);
		}break;
	case PT_C_M_NFY_DEFENCE_DIRECTION:
		{
			SelectDirection(pkUnit, pkNfy);
		}break;
	case PT_C_M_REQ_DEFENCE_POTION:
		{
			//ReqUseDefenceHpPlus(pkUnit, pkNfy);
		}break;
	case PT_U_G_NFY_DEFENCE_POTION:
		{
			SetDefenceHpPlus(pkUnit, pkNfy);
		}break;
	case PT_C_M_REQ_DEFENCE_TIMEPLUS:
		{
			ReqUseDefenceTimePlus(pkUnit, pkNfy);
		}break;
	case PT_U_G_NFY_DEFENCE_TIMEPLUS:
		{
			SetDefenceTimePlus(pkUnit, pkNfy);
		}break;
	case PT_C_M_REQ_DEFENCE_SELECT_CLOSE:
		{
			//if( true == CloseSelectDirection() )
			PgPlayer* pkUser = dynamic_cast<PgPlayer*>(pkUnit);
			if(pkUser)
			{
				if ( pkUser->GetID() == PgMission::GetOwner() )
				{
					if( true == IsDefenceGameMode() )
					{
						Broadcast(BM::Stream(PT_M_C_ANS_DEFENCE_SELECT_CLOSE));
					}
				}
			}
		}break;
	case PT_C_M_REQ_GUARDIAN_SET:
		{
			bool bRet = InsertGuardian(pkUnit, pkNfy);
		}break;
	case PT_C_M_REQ_GUARDIAN_UPGRADE:
		{
			bool bRet = UpGradeGuardian(pkUnit, pkNfy);
		}break;
	case PT_C_M_REQ_GUARDIAN_REMOVE:
		{
			RemoveGuardian(pkUnit, pkNfy);
		}break;
	case PT_C_M_REQ_DEFENCE_SKILL_USE:
		{
			Defence7SkillLearn(pkUnit, pkNfy);
		}break;
    case PT_C_M_REQ_MISSION_START:
        {
            if( S_OK == ReqNextStageUser(pkUnit->GetID()) )
            {
                Broadcast(BM::Stream(PT_M_C_ANS_MISSION_START));
            }
        }break;
	case PT_C_M_MISSION_NEXT_STAGE:
		{
			PgPlayer* pkUser = dynamic_cast<PgPlayer*>(pkUnit);
			if(pkUser)
			{
				if ( pkUser->GetID() == PgMission::GetOwner() )
				{
					size_t const iNowStage = GetStage();
					return SwapStage_Before( iNowStage + 1, NULL );
				}
			}
		}break;
	case PT_C_M_REQ_EXCHANGE_ACCUMPOINT_TO_STRATEGICPOINT:
		{	// 현재 누적포인트를 전략포인트로 전환 요청.
			PgPlayer * pPlayer = dynamic_cast<PgPlayer*>(pkUnit);
			if( pPlayer )
			{
				if( pPlayer->HaveParty() )
				{
					BM::GUID MasterGuid;
					m_kLocalPartyMgr.GetPartyMasterGuid(pPlayer->PartyGuid(), MasterGuid);
					if( pPlayer->GetID() != MasterGuid )		// 파티에 속해 있을때는 파티장만 전략포인트로 교체 가능.
					{
						pPlayer->SendWarnMessage(799397); // 파티장만 전략포인트로 전환이 가능합니다.
					}
				}
				AccumPointToStrategyPoint(); // 누적포인트를 전략포인트로 전환(포인트 복제기).
			}
		}break;
	case PT_C_M_REQ_POINT_COPY:
		{
			PgPlayer * pPlayer = dynamic_cast<PgPlayer*>(pkUnit);
			if( pPlayer )
			{
				if( pPlayer->HaveParty() )
				{	// 파티에 속해 있다면.
					BM::GUID MasterGuid;
					m_kLocalPartyMgr.GetPartyMasterGuid(pPlayer->PartyGuid(), MasterGuid);
					if( pPlayer->GetID() == MasterGuid )
					{	// 파티장만 요청 할 수 있다.
						OccupiedPointCopy();	// 포인트 복제기 점수 누적.
					}
				}
				else
				{	// 아니라면 아무나 가능(혼자있으니까 가능).
					OccupiedPointCopy();	// 포인트 복제기 점수 누적.
				}
			}
		}break;
	case PT_C_M_REQ_KILL_MONSTER_BY_ACCUMPOINT:
		{
			PgPlayer * pPlayer = dynamic_cast<PgPlayer*>(pkUnit);
			if( pPlayer )
			{
				int MonsterCount = PgObjectMgr::GetUnitCount( UT_MONSTER );
				if( 0 == MonsterCount )
				{
					pPlayer->SendWarnMessage(750047);
				}
				else
				{
					if( pPlayer->HaveParty() )
					{
						BM::GUID MasterGuid;
						m_kLocalPartyMgr.GetPartyMasterGuid(pPlayer->PartyGuid(), MasterGuid);
						if( pPlayer->GetID() != MasterGuid )		// 파티에 속해 있을때는 파티장만 몬스터 킬을 요청할 수 있다.
						{
							pPlayer->SendWarnMessage(750043); // 파티장만 몬스터 제거를 요청 할수 있습니다.
						}
					}
					KillMonsterByAccumPoint();
				}
			}
		}break;
	case PT_C_N_REQ_KICKOUT_PARTY_USER:
		{
			if ( IsLastStage() )
			{
				pkUnit->SendWarnMessage(700119);
				break;
			}
//			return PgGround::VUpdate( pkUnit, wType, pkNfy );
		} // No Break
	//case PT_C_M_REQ_MISSION_QUEST:
	//	{
	//		BYTE cCmd = MQC_None;
	//		pkNfy->Pop(cCmd);

	//		return ProcessMissionQuestCmd((EMissionQuestCommand)cCmd, *pkNfy, pkUnit);
	//	}break;
	default:
		{
			return PgIndun::VUpdate( pkUnit, wType, pkNfy );
		}break;
	}

	return true;
}
