#include "stdafx.h"
#include <NiCollision.h>
#include "Lohengrin/VariableContainer.h"
#include "Lohengrin/PacketStruct4Map.h"
#include "FCS/AntiHack.h"
#include "Variant/constant.h"
#include "Variant/PgPartyMgr.h"
#include "Variant/PgEntity.h"
#include "Variant/PgControlDefMgr.h"
#include "Variant/PgActionResult.h"
#include "Variant/PgQuestInfo.h"
#include "Variant/PgMission.h"
#include "Variant/PgEventView.h"
#include "Variant/PgQuestInfo.h"
#include "Variant/AlramMissionMgr.h"
#include "Global.h"
#include "PgLocalPartyMgr.h"
#include "PgGround.h"
#include "PgAction.h"
#include "PgActionQuest.h"
#include "AI/PgAISkillChooser.h"
#include "AI/EnemySelector.h"
#include "PgStoneMgr.h"
#include "PgQuest.h"
#include "SkillEffectAbilSystem\PgSkillAbilHandleManager.h"
#include "PgMissionGround.h"
#include "AI/PgTargettingManager.h"
#include "PgAction_Pet.h"
#include "publicmap/PgBSGround.h"

extern void OnAttacked(CUnit* pkUnit, UNIT_PTR_ARRAY* pkUnitArray, int const iSkillNo, PgActionResultVector* pkResult, SActArg* pArg, DWORD const dwTimeStamp);
bool IsDetailAI(CUnit *pkUnit);

namespace PgGroundUtil
{
	bool SortAbs(float const& lhs, float const& rhs)
	{
		return NiAbs(lhs) < NiAbs(rhs);
	}

	float Point2DCross(POINT3 const& lhs, POINT3 const& rhs)
	{
		return (lhs.x * rhs.y) - (lhs.y * rhs.x);
	}

	bool IsIn2DTriangle(POINT3 const& kP1, POINT3 const& kP2, POINT3 const& kP3, POINT3 const& kPos)
	{
		typedef std::vector< float > ContCross;
		ContCross kVec(3);
		kVec[0] = Point2DCross(kP2 - kP1, kP1 - kPos);
		kVec[1] = Point2DCross(kP3 - kP2, kP2 - kPos);
		kVec[2] = Point2DCross(kP1 - kP3, kP3 - kPos);
		std::sort(kVec.begin(), kVec.end(), SortAbs);
		if( 0 <= kVec[0] && 0 < kVec[1] && 0 < kVec[2] )
		{
			return true;
		}
		if( 0 >= kVec[0] && 0 > kVec[1] && 0 > kVec[2] )
		{
			return true;
		}
		return false;
	}
}

int PgGround::GetEntity(BM::GUID const &kCaller, int const iClass, UNIT_PTR_ARRAY& rkUnitArray)
{
	BM::CAutoMutex kLock(m_kRscMutex);

	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr::GetFirstUnit(UT_ENTITY, kItor);
	CUnit* pkUnit = NULL;
	int iCount = 0;
	while ((pkUnit = PgObjectMgr::GetNextUnit(UT_ENTITY, kItor)) != NULL)
	{
		PgEntity* pkEntity = dynamic_cast<PgEntity*> (pkUnit);
		if( (kCaller.IsNull() || pkEntity->Caller() == kCaller)
		 && (iClass==0 || pkEntity->GetAbil(AT_CLASS) == iClass))
		{
			rkUnitArray.Add(pkUnit);
			++iCount;
		}
	}
	return iCount;
}

void PgGround::DeletePet( BM::GUID const &kPetID )
{
	BM::CAutoMutex kLock( m_kRscMutex );
	PgPet * pkPet = GetPet( kPetID );
	if ( pkPet )
	{
		PgPlayer * pkPlayer = GetUser( pkPet->Caller() );
		if (	pkPlayer 
			&&	(pkPlayer->CreatePetID() == pkPet->GetID()) 
		)
		{		
			PgActPet_RefreshPassiveSkill::DoAction_ReleaseTarget( pkPet, pkPlayer, this );
			ReleaseUnit(pkPet);
			pkPlayer->CreatePetID( BM::GUID::NullData() );
		}
		else
		{
			ReleaseUnit(pkPet);
		}
	}
}

PgPet* PgGround::CreatePet( PgPlayer * pkCaller, BM::GUID const &kPetID, CONT_PET_MAPMOVE_DATA::mapped_type &kPetData )
{
	BM::CAutoMutex kLock( m_kRscMutex );

	if ( ms_kOffPet_GroundAttr & this->GetAttr() )
	{
		return NULL;
	}

	PgBase_Item kPetItem;
	HRESULT const hRet = pkCaller->GetInven()->GetSelectedPetItem( kPetItem );

	{
		PgPet *pkOldPet = GetPet( pkCaller );
		if ( pkOldPet )
		{
			if ( pkOldPet->GetID() == kPetItem.Guid() )
			{
				// 시간이 갱신되었는지 확인
				__int64 const i64LimitTime = kPetItem.GetDelTime();
				if ( 0i64 < i64LimitTime )
				{
					if ( pkOldPet->GetPeriodEndSecTime() != i64LimitTime )
					{
						pkOldPet->SetPeriodEndSecTime( i64LimitTime );
					}
				}
				return pkOldPet;
			}

			PgActPet_RefreshPassiveSkill::DoAction_ReleaseTarget( pkOldPet, pkCaller, this );
			ReleaseUnit( pkOldPet );
			pkCaller->CreatePetID( BM::GUID::NullData() );//펫 초기화
		}
	}
	
	if ( S_OK == hRet )
	{// 인벤으로 부터 장착하려 하는 펫 아이템이 존재 하고
		if ( kPetID != kPetItem.Guid() )
		{
			return NULL;
		}

		if ( !kPetItem.IsUseTimeOut() )
		{// 펫이 기한이 다 하지 않았고
			PgItem_PetInfo *pkPetInfo = NULL;
			if ( true == kPetItem.GetExtInfo( pkPetInfo ) )
			{// 추가 아이템 정보가 존재한다면, UT_PET타입 유닛을 펫 아이템 GUID로 생성하고
				PgPet *pkPet = dynamic_cast<PgPet*>(g_kTotalObjMgr.CreateUnit(UT_PET, kPetItem.Guid() ) );
				if ( pkPet )
				{
					if ( SUCCEEDED(pkPet->Create( kPetItem, pkCaller, kPetData )) )
					{// LV, CLASS_NO, 이름, 스킬정보, 멘탈(지능?), 헬스(건강?), 인벤, 버프, State(US_IDLE), FrontDirection, OwnerType 등을 설정함
						pkPet->LastAreaIndex( PgSmallArea::NONE_AREA_INDEX );	// ?
						if ( true == AddUnit( pkPet, true ) )
						{
							pkCaller->CreatePetID( pkPet->GetID() );

							UNIT_PTR_ARRAY kAddUnitArray;
							kAddUnitArray.Add(pkPet);
							BM::Stream kAddPacket(PT_M_C_ADD_UNIT);
							kAddUnitArray.WriteToPacket( kAddPacket, WT_DEFAULT );
							pkCaller->Send( kAddPacket, E_SENDTYPE_SELF|E_SENDTYPE_MUSTSEND );

							if ( !pkCaller->IsMapLoading() )
							{
								pkPet->SetAddPetToOwner();
							}
							return pkPet;
						}
					}

					g_kTotalObjMgr.ReleaseUnit( dynamic_cast<CUnit*>(pkPet) );
				}
				else
				{
					VERIFY_INFO_LOG( false, BM::LOG_LV0, __FL__<<L"Cannot CreatePet Guid["<<kPetItem.Guid()<<L"]");
				}
			}// GetExtInfo
		}// IsTimeOut

		BM::Stream kCPacket( PT_M_C_NFY_PET_INVENTORY, kPetItem.Guid() );
		kPetData.kInventory.WriteToPacket( kCPacket, WT_DEFAULT );
		pkCaller->Send( kCPacket, E_SENDTYPE_SELF|E_SENDTYPE_MUSTSEND );//인벤정보를 보내주어야 한다.
	}

	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return NULL"));
	return NULL;
}

CUnit* PgGround::CreateEntity(CUnit* pkCaller, SCreateEntity* pkCreateInfo, LPCTSTR lpszName, bool bSyncUnit)
{
	BM::CAutoMutex kLock( m_kRscMutex );

	PgEntity *pkEntity = dynamic_cast<PgEntity*>(g_kTotalObjMgr.CreateUnit(UT_ENTITY, pkCreateInfo->kGuid));
	if (pkEntity == NULL)
	{
		INFO_LOG(BM::LOG_LV0, __FL__<<L"Cannot CreateEntity Guid["<<pkCreateInfo->kGuid<<L"]");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return NULL"));
		return NULL;
	}
	//VERIFY_INFO_LOG_RETURN(NULL, VPARAM(pkEntity != NULL, BM::LOG_LV2, _T("[%s] Cannot Create Entity ...Guid[%s]"),
	//	__FUNCTIONW__, kEntityGuid.str().c_str()));

	SEntityInfo kInfo(pkCreateInfo->kGuid, pkCreateInfo->kClassKey);
	kInfo.bSyncUnit = bSyncUnit;
	kInfo.bEternalLife = pkCreateInfo->bEternalLife;

	Direction eFrontDir = DIR_DOWN;
	if ( pkCaller )
	{
		kInfo.kCaller = pkCaller->GetID();
		kInfo.kCallerClassKey.iClass = pkCaller->GetAbil(AT_CLASS);
		kInfo.SetAbil(AT_TEAM, pkCaller->GetAbil(AT_TEAM));
		kInfo.SetAbil(AT_PHY_ATTACK_MIN, pkCaller->GetAbil(AT_PHY_ATTACK_MIN));
		kInfo.SetAbil(AT_PHY_ATTACK_MAX, pkCaller->GetAbil(AT_PHY_ATTACK_MAX));
		kInfo.SetAbil(AT_MAGIC_ATTACK_MIN, pkCaller->GetAbil(AT_MAGIC_ATTACK_MIN));
		kInfo.SetAbil(AT_MAGIC_ATTACK_MAX, pkCaller->GetAbil(AT_MAGIC_ATTACK_MAX));
		kInfo.SetAbil(AT_C_PHY_ATTACK_MIN, pkCaller->GetAbil(AT_C_PHY_ATTACK_MIN));
		kInfo.SetAbil(AT_C_PHY_ATTACK_MAX, pkCaller->GetAbil(AT_C_PHY_ATTACK_MAX));
		kInfo.SetAbil(AT_C_MAGIC_ATTACK_MIN, pkCaller->GetAbil(AT_C_MAGIC_ATTACK_MIN));
		kInfo.SetAbil(AT_C_MAGIC_ATTACK_MAX, pkCaller->GetAbil(AT_C_MAGIC_ATTACK_MAX));
		kInfo.SetAbil(AT_EQUIP_WEAPON_PHY_ATTACK_MIN, pkCaller->GetAbil(AT_EQUIP_WEAPON_PHY_ATTACK_MIN) );
		kInfo.SetAbil(AT_EQUIP_WEAPON_PHY_ATTACK_MAX, pkCaller->GetAbil(AT_EQUIP_WEAPON_PHY_ATTACK_MAX) );
		kInfo.SetAbil(AT_EQUIP_WEAPON_MAGIC_ATTACK_MIN, pkCaller->GetAbil(AT_EQUIP_WEAPON_MAGIC_ATTACK_MIN) );
		kInfo.SetAbil(AT_EQUIP_WEAPON_MAGIC_ATTACK_MAX, pkCaller->GetAbil(AT_EQUIP_WEAPON_MAGIC_ATTACK_MAX) );
		kInfo.SetAbil(AT_C_ABS_ADDED_DMG_PHY, pkCaller->GetAbil(AT_C_ABS_ADDED_DMG_PHY) );
		kInfo.SetAbil(AT_C_ABS_ADDED_DMG_MAGIC, pkCaller->GetAbil(AT_C_ABS_ADDED_DMG_MAGIC) );		
		kInfo.SetAbil(AT_HIT_SUCCESS_VALUE, pkCaller->GetAbil(AT_HIT_SUCCESS_VALUE));
		kInfo.SetAbil(AT_OWNER_TYPE, pkCaller->GetAbil(AT_OWNER_TYPE));
		kInfo.SetAbil(AT_CALLER_TYPE, pkCaller->UnitType());
		kInfo.SetAbil(AT_CALLER_LEVEL, pkCaller->GetAbil(AT_LEVEL));
		kInfo.SetAbil(AT_PHY_DMG_PER, pkCaller->GetAbil(AT_PHY_DMG_PER));
		kInfo.SetAbil(AT_MAGIC_DMG_PER, pkCaller->GetAbil(AT_MAGIC_DMG_PER));
		kInfo.SetAbil(AT_DUEL, pkCaller->GetAbil(AT_DUEL));
		
		{// 크리티컬 관계된 어빌들
			kInfo.SetAbil(AT_C_CRITICAL_SUCCESS_VALUE, pkCaller->GetAbil(AT_C_CRITICAL_SUCCESS_VALUE));
			kInfo.SetAbil(AT_CRITICAL_ONEHIT, pkCaller->GetAbil(AT_CRITICAL_ONEHIT));
			kInfo.SetAbil(AT_C_CRITICAL_POWER, pkCaller->GetAbil(AT_C_CRITICAL_POWER));
		}
		
		if(0 < ms_iEnableEntityCritialAttack)
		{
			kInfo.SetAbil(AT_C_CRITICAL_SUCCESS_VALUE, pkCaller->GetAbil(AT_C_CRITICAL_SUCCESS_VALUE));
			kInfo.SetAbil(AT_C_CRITICAL_POWER, pkCaller->GetAbil(AT_C_CRITICAL_POWER));
		}

		if(0 < ms_iEnableEntityHitRate)
		{
			kInfo.SetAbil(AT_C_HIT_SUCCESS_VALUE, pkCaller->GetAbil(AT_C_HIT_SUCCESS_VALUE));
			kInfo.SetAbil(AT_DEC_TARGETDODGE_ABS, pkCaller->GetAbil(AT_DEC_TARGETDODGE_ABS));
			kInfo.SetAbil(AT_DEC_TARGETDODGE_RATE, pkCaller->GetAbil(AT_DEC_TARGETDODGE_RATE));
		}

		if(0 < ms_iEnableEntityAttackExtInfo)
		{
			kInfo.SetAbil(AT_1ST_ATTACK_ADDED_RATE, pkCaller->GetAbil(AT_1ST_ATTACK_ADDED_RATE));
			kInfo.SetAbil(AT_1ST_ATTACK_ADDED_RATE_APPLY_NUM, pkCaller->GetAbil(AT_1ST_ATTACK_ADDED_RATE_APPLY_NUM));
			kInfo.SetAbil(AT_PHY_DEFENCE_IGNORE_RATE, pkCaller->GetAbil(AT_PHY_DEFENCE_IGNORE_RATE));
			kInfo.SetAbil(AT_MAGIC_DEFENCE_IGNORE_RATE, pkCaller->GetAbil(AT_MAGIC_DEFENCE_IGNORE_RATE));
			kInfo.SetAbil(AT_ABS_ADDED_DMG_PHY_2, pkCaller->GetAbil(AT_ABS_ADDED_DMG_PHY_2));
			kInfo.SetAbil(AT_ABS_ADDED_DMG_MAGIC_2, pkCaller->GetAbil(AT_ABS_ADDED_DMG_MAGIC_2));
			kInfo.SetAbil(AT_GRADE_NORMAL_DMG_ADD_RATE, pkCaller->GetAbil(AT_GRADE_NORMAL_DMG_ADD_RATE));
			kInfo.SetAbil(AT_GRADE_UPGRADED_DMG_ADD_RATE, pkCaller->GetAbil(AT_GRADE_UPGRADED_DMG_ADD_RATE));
			kInfo.SetAbil(AT_GRADE_ELITE_DMG_ADD_RATE, pkCaller->GetAbil(AT_GRADE_ELITE_DMG_ADD_RATE));
			kInfo.SetAbil(AT_GRADE_BOSS_DMG_ADD_RATE, pkCaller->GetAbil(AT_GRADE_BOSS_DMG_ADD_RATE));			
		}

		kInfo.SetAbil(AT_ENABLE_CHECK_ATTACK, pkCaller->GetAbil(AT_ENABLE_CHECK_ATTACK));
				
		//kInfo.SetAbil(AT_CRITICAL_ONEHIT, pkCaller->GetAbil(AT_CRITICAL_ONEHIT));

		if ( 0 < pkCaller->GetAbil(AT_USENOT_SMALLAREA) )
		{// Caller가 BigArea몬스터이면 소환물도 BigArea로 들어가야 한다.
			kInfo.SetAbil( AT_USENOT_SMALLAREA, 1 );
		}
		if( 0 < pkCaller->GetAbil(AT_MON_ENCHANT_LEVEL) )
		{
			kInfo.SetAbil(AT_MON_ENCHANT_LEVEL, pkCaller->GetAbil(AT_MON_ENCHANT_LEVEL));
		}
		kInfo.SetAbil(AT_OFFENCE_ENCHANT_LEVEL, pkCaller->GetAbil(AT_OFFENCE_ENCHANT_LEVEL));
		kInfo.SetAbil(AT_DEFENCE_ENCHANT_LEVEL, pkCaller->GetAbil(AT_DEFENCE_ENCHANT_LEVEL));

		eFrontDir = pkCaller->FrontDirection();

		//if(pkCaller)
		//{// 이곳에서 걸면 필요한 곳까지 이펙트가 걸려있는 상태로 전달되지 않음
		//	PgUnitEffectMgr& rkEffectMgr = pkCaller->GetEffectMgr();
		//	CEffect* pkEffect = NULL;
		//	ContEffectItor kItor;
		//	rkEffectMgr.GetFirstEffect(kItor);
		//	while ((pkEffect = rkEffectMgr.GetNextEffect(kItor)) != NULL)
		//	{
		//		if(pkEffect
		//			&& GlobalHelper::IsAdjustSkillEffect(pkEffect)
		//			)
		//		{// Caller에게 걸려있다면 똑같이 Entity에게도 적용해준다.
		//			SEffectCreateInfo kCreate;
		//			kCreate.eType = EFFECT_TYPE_NORMAL;
		//			kCreate.iEffectNum = pkEffect->GetEffectNo();
		//			kCreate.eOption = SEffectCreateInfo::ECreateOption_CallbyServer;
		//			pkEntity->AddEffect(kCreate);
		//		}
		//	}
		//}
	}
	else
	{
		kInfo.SetAbil(AT_OWNER_TYPE, UT_MONSTER);
		kInfo.SetAbil(AT_CALLER_TYPE, UT_MONSTER);
		kInfo.SetAbil(AT_CALLER_LEVEL, 0);
	}

	// pkCaller가 펫이라면 펫의 주인이 caller가 되어야 한다.
	// 이후 밑에 코드 부분
	if(pkCaller)
	{
		if(pkCaller->IsUnitType(UT_PET))
		{
			CUnit* pkCallerUnit = GetUnit(pkCaller->Caller());

			//실제 user를 얻어온다.
			if(pkCallerUnit)
			{
				//실제 유저를 Entity의 Caller로 설정해준다.
				pkCaller = pkCallerUnit;
				kInfo.kCaller = pkCaller->GetID();
			}
		}
	}
	
	if ( SUCCEEDED(pkEntity->Create( &kInfo )) )
	{
		if ( lpszName )
		{
			pkEntity->Name( lpszName );
		}
		if ( pkCreateInfo->iLifeTime )
		{
			pkEntity->LifeTime(pkCreateInfo->iLifeTime);
		}
		pkEntity->SetPos( pkCreateInfo->ptPos );
		pkEntity->SetState(US_IDLE);
		pkEntity->LastAreaIndex( PgSmallArea::NONE_AREA_INDEX );
		pkEntity->FrontDirection( eFrontDir );

		if ( !pkCaller || pkCaller->AddSummonUnit( pkEntity->GetID(), pkCreateInfo->kClassKey.iClass, PgGroundUtil::GetSummonOptionType(pkCreateInfo->bUniqueClass), GetMaxSummonUnitCount(pkCaller)) )
		{
			AddUnit(pkEntity, true);

			//스킬을 사용할때 자식 스킬의 영향을 받는 스킬을 사용해야하는 경우
			//Entity는 Entitny에 직접 세팅해 준다. 
			//Variant의 CS_GetSkillResultDefault 류의 함수 호출 시 Entity는 Caller의 포인터를 얻을 수 없기 때문에
			//Caller 가 영향을 받는 자식 스킬을 배웠는지 알 수가 없다. 
			//Entity에 직접 정보를 넣어서 세팅해야 한다.			
			
			if(pkEntity && pkCaller)
			{
				if(int const iSkillNo = pkEntity->GetAbil(AT_MON_SKILL_01))
				{
					if(0 < iSkillNo)
					{
						GET_DEF(CSkillDefMgr, kSkillDefMgr);
						CSkillDef const* pkSkill = kSkillDefMgr.GetDef(iSkillNo);
						if(pkSkill)
						{
							if(PgPlayer* pkPlayer = dynamic_cast<PgPlayer*>(pkCaller))
							{
								int iSkillindex = 0;
								while(CHILD_SKILL_MAX > iSkillindex)
								{
									//영향 받는 베이스 스킬
									int const iChildBaseSkillNo = pkSkill->GetAbil(AT_CHILD_SKILL_NUM_01 + iSkillindex);
									if(0 < iChildBaseSkillNo)
									{
										if(PgMySkill* pkPlayerSkill = pkPlayer->GetMySkill())
										{
											//해당 스킬의 실제 레벨에 해당되는 스킬을 얻어 온다.
											int const iLearnedChildSkillNo = pkPlayerSkill->GetLearnedSkill(iChildBaseSkillNo);
											if(0 < iLearnedChildSkillNo)
											{
												//실제 스킬 번호를 Entity에 세팅한다.
												//Variant의 CS_GetSkillResultDefault 류의 함수가 호출될때 Caller의 포인터를 직접 얻어 올 수 없다.
												pkEntity->SetAbil(AT_CHILD_SKILL_NUM_01 + iSkillindex, iLearnedChildSkillNo);												
											}
										}
									}
									else
									{
										break;
									}
									++iSkillindex;
								}
							}
						}
					}
				}
			}

			return pkEntity;
		}
	}

	g_kTotalObjMgr.ReleaseUnit( dynamic_cast<CUnit*>(pkEntity) );
	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return NULL"));
	return NULL;
}

/*
CUnit* PgGround::CreateEntity(CUnit* pkCaller, int iClass, short int iLevel, LPCTSTR lpszName, DWORD dwDistance)
{
	VERIFY_INFO_LOG_RETURN(NULL, VPARAM(pkCaller != NULL, BM::LOG_LV4, _T("[%s] Caller is NULL"), __FUNCTIONW__));
	BM::GUID kEntityGuid = BM::GUID::Create();
	PgEntity *pkEntity = dynamic_cast<PgEntity*>(g_kTotalObjMgr.CreateUnit(UT_ENTITY, kEntityGuid));
	VERIFY_INFO_LOG_RETURN(NULL, VPARAM(pkEntity != NULL, BM::LOG_LV2, _T("[%s] Cannot Create Entity ...Guid[%s]"),
		__FUNCTIONW__, kEntityGuid.str().c_str()));

	SEntityInfo kInfo;
	kInfo.kGuid = kEntityGuid;
	kInfo.kCaller = pkCaller->GetID();
	SClassKey kClassKey(iClass, iLevel);
	kInfo.ulLifeTime = g_ClassDef.GetAbil(kClassKey, AT_LIFETIME);
	kInfo.iClass = iClass;
	kInfo.sLevel = iLevel;
	kInfo.SetAbil(AT_TEAM, pkCaller->GetAbil(AT_TEAM));
	kInfo.SetAbil(AT_PHY_ATTACK_MIN, pkCaller->GetAbil(AT_PHY_ATTACK_MIN));
	kInfo.SetAbil(AT_PHY_ATTACK_MAX, pkCaller->GetAbil(AT_PHY_ATTACK_MAX));
	kInfo.SetAbil(AT_MAGIC_ATTACK_MIN, pkCaller->GetAbil(AT_MAGIC_ATTACK_MIN));
	kInfo.SetAbil(AT_MAGIC_ATTACK_MAX, pkCaller->GetAbil(AT_MAGIC_ATTACK_MAX));
	kInfo.SetAbil(AT_HIT_SUCCESS_VALUE, pkCaller->GetAbil(AT_HIT_SUCCESS_VALUE));
	
	pkEntity->Create( &kInfo );
	pkEntity->Name( lpszName );

	// YonMy 20070824 Party Skill.. Caller의 PartyGuid를 셋팅
	// Entity 위치 계산하기
	POINT3 ptEntityPos = pkCaller->GetPos();
	GetDistanceToPosition( GetPathRoot(), pkCaller->GetPos(), pkCaller->FrontDirection(), dwDistance, ptEntityPos );
	// 바닥에 밀착 시킨다
	NxRay kRay(NxVec3(ptEntityPos.x, ptEntityPos.y, ptEntityPos.z+20), NxVec3(0, 0, -1.0f));
	NxRaycastHit kHit;
	NxShape *pkHitShape = PhysXScene()->GetPhysXScene()->raycastClosestShape(kRay, NX_STATIC_SHAPES, kHit, -1, 200.0f, NX_RAYCAST_SHAPE|NX_RAYCAST_IMPACT);
	if(pkHitShape)
	{
		ptEntityPos.z = kHit.worldImpact.z;
	}

	pkEntity->SetPos( ptEntityPos );
	pkEntity->SetState(US_IDLE);

	AddUnit(pkEntity, true);
	return pkEntity;
}
*/


PgSubPlayer* PgGround::CreateSubPlayer( PgPlayer * pkCaller, BM::GUID const& rkSubPlayerID )
{
	BM::CAutoMutex kLock( m_kRscMutex );
	{// 쌍둥이 캐릭터
		int const iClass = pkCaller->GetAbil(AT_CLASS);
		if( IsClass_OwnSubPlayer(iClass) )
		{//이라면
			{
				PgSubPlayer* pkOldSubPlayer = GetSubPlayer(pkCaller);	// 현재 보조캐릭터를 얻어오고
				pkCaller->SubPlayerID( BM::GUID::NullData() );	// 본객체가 삭제되기전에 NULL GUID를 세팅해주고
				if(pkOldSubPlayer)
				{// 이미 있다면 삭제하고 다시 생성
					pkOldSubPlayer->SetCallerUnit(NULL);
					ReleaseUnit( pkOldSubPlayer );
				}
			}
			
			PgSubPlayer* pkSubPlayer = dynamic_cast<PgSubPlayer*>(g_kTotalObjMgr.CreateUnit(UT_SUB_PLAYER, rkSubPlayerID) );
			if(pkSubPlayer)
			{
				pkCaller->SubPlayerID(rkSubPlayerID);
				pkSubPlayer->LastAreaIndex( PgSmallArea::NONE_AREA_INDEX );	// ?
				pkSubPlayer->Create(pkCaller);

				AddUnit(pkSubPlayer);

				UNIT_PTR_ARRAY kAddUnitArray;
				kAddUnitArray.Add(pkSubPlayer);
				BM::Stream kAddPacket(PT_M_C_ADD_UNIT);
				kAddUnitArray.WriteToPacket( kAddPacket, WT_DEFAULT );
				pkCaller->Send( kAddPacket, E_SENDTYPE_BROADALL|E_SENDTYPE_MUSTSEND );

				if ( !pkCaller->IsMapLoading() )
				{
					//pkSubPlayer->SetAddPetToOwner(); // 아옭옭옭
				}
				return pkSubPlayer;
			}
		}
	}
	return NULL;
}

void PgGround::DeleteSubPlayer( BM::GUID const& rkSubPlayerID )
{
	BM::CAutoMutex kLock( m_kRscMutex );
	PgSubPlayer * pkSubPlayer = GetSubPlayer( rkSubPlayerID );
	if ( pkSubPlayer )
	{
		PgPlayer * pkPlayer = GetUser( pkSubPlayer->Caller() );
		pkSubPlayer->SetCallerUnit(NULL);
		if ( pkPlayer
			&&	(pkPlayer->SubPlayerID() == pkSubPlayer->GetID()) 
		)
		{
			pkPlayer->SubPlayerID( BM::GUID::NullData() );
		}
		ReleaseUnit(pkSubPlayer);
	}
}

bool PgGround::Locked_IsUnitInRange(ETeam const eTeam, POINT3 const& ptFind, int const iRange, EUnitType const eType)
{
	// Ground 전체에서 찾는다.
	BM::CAutoMutex kLock(m_kRscMutex);
	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr::GetFirstUnit(eType, kItor);
	CUnit* pkUnit = NULL;
	while ((pkUnit = PgObjectMgr::GetNextUnit(eType, kItor)) != NULL)
	{
		if( pkUnit->GetAbil(AT_TEAM)==eTeam &&
			IsUnitInRangeImp(pkUnit, ptFind, iRange, eType, iRange, false) )
		{
			return true;
		}
	}
	return false;
}

void PgGround::GetUnitInDistance( POINT3 const& ptPos, int const iRange, EUnitType const eType, UNIT_PTR_ARRAY& rkUnitArray, int const iZLimit)const
{
	// Ground 전체에서 찾는다.
	BM::CAutoMutex kLock(m_kRscMutex);
	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr::GetFirstUnit(eType, kItor);
	CUnit* pkUnit = NULL;
	while ((pkUnit = PgObjectMgr::GetNextUnit(eType, kItor)) != NULL)
	{
		float const fDistanceQ = GetDistanceQ(ptPos, pkUnit->GetPos());
		if (fDistanceQ <= (float)iRange * iRange)
		{
			if(iZLimit > 0)
			{
				POINT3 const ptDist = ptPos - pkUnit->GetPos();
				if (abs(ptDist.z) > iZLimit)
				{
					++kItor;
					continue;
				}
			}

			rkUnitArray.Add(pkUnit);
		}
		++kItor;
	}
}

void PgGround::GetUnitInRange( POINT3 const& ptFind, int iRange, EUnitType eType, UNIT_PTR_ARRAY& rkUnitArray, int iZLimit, bool const bFindFromGround)
{
	// Ground 전체에서 찾는다.
	BM::CAutoMutex kLock(m_kRscMutex);
	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr::GetFirstUnit(eType, kItor);
	CUnit* pkUnit = NULL;
	int iZ = (iZLimit == 0) ? iRange : iZLimit;

	while ((pkUnit = PgObjectMgr::GetNextUnit(eType, kItor)) != NULL)
	{
		CUnit* pRetUnit = IsUnitInRangeImp(pkUnit, ptFind, iRange, eType, iZ, bFindFromGround);
		if(NULL!=pRetUnit)
		{
			rkUnitArray.AddToUniqe(pRetUnit);
		}
	}
}

void PgGround::GetUnitInRange(EUnitType & eCheckUnitType, POINT3 const& FromPos, int const iRange, EUnitType const eUnitType, UNIT_PTR_ARRAY & rkUnitArray, int const iZLimit, bool const bFindFromGround)
{
	if(false == (eCheckUnitType&eUnitType))
	{
		GetUnitInRange(FromPos, iRange, eUnitType, rkUnitArray, iZLimit, bFindFromGround);
		eCheckUnitType = static_cast<EUnitType>(eCheckUnitType | eUnitType);
	}
}

CUnit * PgGround::IsUnitInRangeImp(CUnit *pUnit, POINT3 const& ptFind, int const iRange, EUnitType const eType, int const iZLimit, bool const bFindFromGround)
{
	if (NULL==pUnit)
	{
		return NULL;
	}
	int iApplyRange = iRange;
	if(UT_MONSTER == eType && pUnit->GetAbil(AT_GROWTH_SKILL_RANGE) )
	{
		iApplyRange = iRange + pUnit->GetAbil(AT_UNIT_SIZE_XY);
	}

	EInRangeRet eRet = ::IsInRange(GetUnitPos(pUnit), ptFind, iApplyRange, iZLimit, false);
	if(true == bFindFromGround && ERange_Z==eRet)	//Z값 때문에 못찾은 경우 옵션이 있으면 한번 더 찾아보자
	{
		eRet = ::IsInRange(GetUnitPos(pUnit, true), ptFind, iApplyRange, iZLimit, false);
	}
	if(ERange_OK==eRet)
	{
		return pUnit;
	}
	return NULL;
}

void PgGround::GetUnitInCube( POINT3 const &ptCubeMin, POINT3 const &ptCubeMax, POINT3 const &ptPos, EUnitType eType, UNIT_PTR_ARRAY& rkUnitArray )
{
	BM::CAutoMutex kLock(m_kRscMutex);
	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr::GetFirstUnit(eType, kItor);
	CUnit* pkUnit = NULL;
	while ((pkUnit = PgObjectMgr::GetNextUnit(eType, kItor)) != NULL)
	{
		POINT3 ptPos = GetUnitPos(pkUnit);
		if ( IsInCube( ptCubeMin, ptCubeMax, ptPos ) )
		{
			rkUnitArray.Add(pkUnit);
		}
	}
}

CUnit* PgGround::GetUnitByClassNo( int const iClassNo, EUnitType eType )
{
	BM::CAutoMutex kLock(m_kRscMutex);
	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr::GetFirstUnit(eType, kItor);
	CUnit* pkUnit = NULL;
	while ((pkUnit = PgObjectMgr::GetNextUnit(eType, kItor)) != NULL)
	{
		if( pkUnit->GetAbil(AT_CLASS) == iClassNo )
		{
			return pkUnit;
		}
	}

	return NULL;
}

int PgGround::GetUnitByClassNo( int const iClassNo, EUnitType eType, UNIT_PTR_ARRAY& rkUnitArray )
{
	BM::CAutoMutex kLock(m_kRscMutex);
	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr::GetFirstUnit(eType, kItor);
	CUnit* pkUnit = NULL;
	while ((pkUnit = PgObjectMgr::GetNextUnit(eType, kItor)) != NULL)
	{
		if( pkUnit->GetAbil(AT_CLASS) == iClassNo )
		{
			rkUnitArray.Add(pkUnit);
		}
	}
	return (static_cast<int>(rkUnitArray.size()));
}

CUnit* PgGround::GetUnitByType( EUnitType const eType )
{
	BM::CAutoMutex kLock(m_kRscMutex);
	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr::GetFirstUnit(eType, kItor);
	return PgObjectMgr::GetNextUnit(eType, kItor);
}

void PgGround::GetUnitInWidthFromLine(POINT3 const& ptStart, POINT3 const& ptEnd, int iWidth, EUnitType eType, UNIT_PTR_ARRAY& rkUnitArray)
{
	BM::CAutoMutex kLock( m_kRscMutex );
	
	// Unit Pos에서 ptEnd - ptStart Vector에 수선으로 내린 길이가 iWidth보다 작으면 Range안에 들어간 것이다.
	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr::GetFirstUnit(eType, kItor);
	CUnit* pkUnit = NULL;

	NiPoint3 kStart(ptStart.x, ptStart.y, ptStart.z);
	NiPoint3 kEnd(ptEnd.x, ptEnd.y, ptEnd.z);
	NiPoint3 kDirectionVec(kEnd - kStart);
	NiPoint3 kUnDirectionVec(kStart - kEnd);

	while ((pkUnit = PgObjectMgr::GetNextUnit(eType, kItor)) != NULL)
	{
		bool bInRange = false;
		POINT3 ptUnitPos = GetUnitPos(pkUnit);
		NiPoint3 kUnitPos(ptUnitPos.x, ptUnitPos.y, ptUnitPos.z);

		// ptPos에서 kCenterLineVec으로 수선을 내린 후, 그 길이가 iWidth보다 작으면 InRange!!
		NiPoint3 kProjection = (((kUnitPos - kStart).Dot(kDirectionVec)) / (kDirectionVec.Dot(kDirectionVec))) * kDirectionVec;
		float iLength = ((kUnitPos - kStart) - kProjection).Length();
		
		if(iWidth > iLength)
		{
			//선분 뒤쪽으로도 검사가 되는 현상 방지
			NiPoint3 kDif1 = kUnitPos-kStart;
			float kDot1 = kDirectionVec.Dot(kDif1);
			if(0.0f>kDot1)
			{
				continue;
			}

			NiPoint3 kDif2 = kUnitPos-kEnd;
			float kDot2 = kUnDirectionVec.Dot(kDif2);
			if(0.0f>kDot2)
			{
				continue;
			}

			rkUnitArray.Add(pkUnit);
		}
	}
}

void PgGround::GetUnitIn2DRectangle(POINT3 const& kP1, POINT3 const& kP2, POINT3 const& kP3, POINT3 const& kP4, EUnitType eType, UNIT_PTR_ARRAY& rkUnitArray)
{
	BM::CAutoMutex kLock( m_kRscMutex );
	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr::GetFirstUnit(eType, kItor);
	CUnit* pkUnit = NULL;

	bool bInArea = false;
	while( (pkUnit = PgObjectMgr::GetNextUnit(eType, kItor)) != NULL)
	{
		POINT3 kUnitPos = GetUnitPos(pkUnit);
		kUnitPos.z = 0;
		bInArea = PgGroundUtil::IsIn2DTriangle(kP1, kP2, kP3, kUnitPos);
		if( !bInArea )
		{
			bInArea = PgGroundUtil::IsIn2DTriangle(kP2, kP3, kP4, kUnitPos);
		}
		
		if( bInArea )
		{
			rkUnitArray.Add(pkUnit);
			bInArea = false;
		}
	}
}

POINT3 PgGround::GetUnitPos( CUnit* pkUnit, bool bCheckImpact, float const fRayRange )
{
	if (pkUnit->UnitType() == UT_PLAYER)
	{
		static int iValue = -1;
		if(0>iValue)
		{
			if(S_OK != g_kVariableContainer.Get(EVar_Kind_AI, UseRayCache, iValue) )
			{
				iValue = 1;
			}
		}
			
		PgPlayer* pkPlayer = dynamic_cast<PgPlayer*>(pkUnit);
		PLAYER_ACTION_INFO* pkAction = pkPlayer->GetPlayerActionInfo();
		DWORD const dwNow = BM::GetTime32();
		
		bool const bPosAtGroundTime = bCheckImpact && ((dwNow >= pkPlayer->PosAtGroundTime() + (MONSTER_AI_TICK_INTER-50)) || !iValue);
		if (dwNow >= pkAction->dwCalculateTime + MONSTER_AI_TICK_INTER || bPosAtGroundTime )
		{
			POINT3 ptNew = SimulateUnitPos2(pkPlayer, pkPlayer->GetPos(), pkAction->iActionID, dwNow-pkAction->dwLastTime, pkPlayer->Latency());
			pkAction->SetPos(dwNow+pkPlayer->Latency(), ptNew, true);
			if (POINT3::NullData() == pkPlayer->PosAtGround())
			{
				pkPlayer->PosAtGround(ptNew);
			}
			
			if (true==bCheckImpact)
			{
				if(ACTIONID_A_JUMP!=pkAction->iActionID)
				{
					bCheckImpact = false;
				}
				else
				{
					NxRay kRay(NxVec3(ptNew.x, ptNew.y, ptNew.z+20), NxVec3(0, 0, -1.0f));
					NxRaycastHit kHit;
					NxShape *pkHitShape = RayCast(kRay, kHit, fRayRange);

					pkPlayer->PosAtGroundTime(dwNow+pkPlayer->Latency());
					if(pkHitShape)
					{
						ptNew.z = kHit.worldImpact.z;
						pkPlayer->PosAtGround(ptNew);
						return ptNew;
					}
				}
			}
		}
		return bCheckImpact ? pkPlayer->PosAtGround() : pkAction->ptPos;
	}

	return pkUnit->GetPos();
}

bool PgGround::IsAttackable(EAbilType eType, CUnit* pkCaster, CUnit *pkTarget,int& iSkillNo)
{
	int iRand = BM::Rand_Index(100) ;
	if(pkCaster == NULL || pkTarget == NULL)
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}
	
	if(pkTarget->IsDead())
	{
		return false; 
	}
	
	if (pkTarget->GetAbil(AT_UNIT_HIDDEN) > 0 || ( 0!=pkTarget->GetAbil(AT_CANNOT_DAMAGE)) )
	{
		// Hidden 상태이거나 AT_CANNOT_DAMAGE 상태이면 때릴 수 없다.
		return false;
	}
	POINT3 const &ptM = GetUnitPos(pkCaster);
	POINT3 const &ptC = GetUnitPos(pkTarget);
	if (abs(ptM.z - ptC.z) > 30)
	{
		return false;
	}

	float fDistDouble = GetDistanceQ(ptM, ptC);

	int iBaseDist = pkCaster->GetAbil(eType) ;
	if ( pkCaster->IsUnitType(UT_MONSTER) && iSkillNo == 0 ) // 몬스터가 스킬이 없다면 여기서 스킬을 설정해야 한다.
	{
		iSkillNo = pkCaster->GetAbil(AT_NORMAL_SKILL_ID);
		
		GET_DEF(CSkillDefMgr, kSkillDefMgr);
		iBaseDist = kSkillDefMgr.GetDef(iSkillNo)->GetAbil(AT_ATTACK_RANGE) ;

		int iMaxSkill = pkCaster->GetAbil(AT_MAX_SKILL_NUM);
		for ( int i = 0 ; i < iMaxSkill ; i ++ )
		{
			int skillno = pkCaster->GetAbil(AT_MON_SKILL_01 + i) ;
			const CSkillDef* pkSkillDef = kSkillDefMgr.GetDef(skillno);
			if ( pkSkillDef )
			{
				int skilldist = pkSkillDef->GetAbil(AT_ATTACK_RANGE) ;
				if ( iBaseDist <= skilldist )
				{
					if ( iRand <= pkCaster->GetAbil(AT_MON_SKILL_RATE_01 + i) )
					{
						iBaseDist = skilldist ;
						iSkillNo = skillno ;
						break;
					}
				}
			}
		}


	}

	if(fDistDouble > iBaseDist*iBaseDist )
	{
		return false;
	}
#ifdef AI_DEBUG
	INFO_LOG(BM::LOG_LV9, __FL__<<L"Enabled Attack Distance["<<sqrt(fDistDouble)<<L"], BaseDist["<<iBaseDist<<L"]");
#endif

	return true;
}

//bool PgGround::SkillFire(int const iSkillNo, CUnit* pkCaster, CUnit* pkTarget, PgActionResultVector* pkResult, SActArg* pkAct, bool bSendPacket)
//{
//	if ( !pkCaster )
//	{
//		VERIFY_INFO_LOG(false, BM::LOG_LV0, __FL__<<L"pkCaster is NULL");
//		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
//		return false;
//	}
//
//	UNIT_PTR_ARRAY kTargetArray;
//	void* pkVoid = NULL;
//	pkAct->Get(ACTARG_GROUND, pkVoid);
//	PgGround* pkGround = (PgGround*)pkVoid;
//	if (NULL == pkTarget && pkGround != NULL)
//	{
//		pkGround->AI_GetSkillTargetList(pkCaster, iSkillNo, kTargetArray, true, pkAct);
//	}
//	else
//	{
//		kTargetArray.Add(pkTarget);
//	}
//
//	int iReturn = g_kSkillAbilHandleMgr.SkillFire(pkCaster, iSkillNo, pkAct, &kTargetArray, pkResult);
//
//	OnAttacked(pkCaster, &kTargetArray, iSkillNo, pkResult, pkAct);
//
//	if (bSendPacket && pkGround != NULL)
//	{
//		pkGround->SendNfyAIAction(pkCaster, US_ATTACK, pkResult);
//	}
//	return (iReturn > 0);
//}

bool NpcQuestEventFilter(const ContSimpleQuest::value_type& rkItem)
{
	switch(rkItem.cState)
	{
	case QS_Begin:
	case QS_End:
	case QS_Ing://대화 가능한 상태들
		{
			return false;//삭제 금지
		}break;
	}
	return true;//삭제
}

bool ScrollQuestFilter( const ContSimpleQuest::value_type& rkItem )
{
	PgQuestInfo const *pkQuestInfo = NULL;
	g_kQuestMan.GetQuest(rkItem.iQuestID, pkQuestInfo);
	
	if( !pkQuestInfo )
	{
		return false;
	}

	if( QT_Scroll == pkQuestInfo->Type() )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PgGround::ReqNpcTrigger(CUnit* pkUnit, BM::GUID const& kObjectGuid, int iActionType)
{
	CUnit *pkNpcUnit = GetNPC(kObjectGuid);
	if( !pkNpcUnit )
	{
		CAUTION_LOG(BM::LOG_LV1, __FL__<<L"Can't find NPC Unit, GUID: "<<kObjectGuid<<L" Ground: "<<GetGroundNo());
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("pkNpcUnit is NULL"));
		return;
	}

	PgNpc* pkNpc = dynamic_cast< PgNpc* >(pkNpcUnit);
	if( !pkNpc )
	{
		CAUTION_LOG(BM::LOG_LV1, __FL__<<L"isn't NPC Unit[UnitType: "<<pkNpcUnit->UnitType()<<L", GUID: "<<pkNpcUnit->GetID()<<L", Name: "<<pkNpcUnit->Name()<<L"] Ground: "<<GetGroundNo());
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("pkNpc is NULL"));
		return;
	}
	
	if( !PgGroundUtil::IsCanTalkableRange(pkUnit, kObjectGuid, pkNpc, GetGroundNo(), NMT_Quest, __FUNCTIONW__, __LINE__) )
	{
		return;
	}
	
	ContSimpleQuest kStateVec;
	PgCheckQuest kCheck(kStateVec);
	if( !kCheck.DoAction(pkUnit, pkNpc) )
	{
		return;
	}

	ContSimpleQuest::iterator new_iter = std::remove_if(kStateVec.begin(), kStateVec.end(), NpcQuestEventFilter);
	kStateVec.erase(new_iter, kStateVec.end());

	// 스크롤 퀘스트는 NPC에서 제거
	new_iter = std::remove_if(kStateVec.begin(), kStateVec.end(), ScrollQuestFilter);
	kStateVec.erase(new_iter, kStateVec.end());

	if( 1 == kStateVec.size() )
	{
		ContSimpleQuest::value_type const& rkElement = kStateVec.front();
		ReqIntroQuest(pkUnit, rkElement.iQuestID, kObjectGuid);
	}
	else if( !kStateVec.empty() )
	{
		//list는 이미 클라이언트가 알고 있으니 보내지 않는다.
		SendShowQuestDialog(pkUnit, kObjectGuid, QSDT_SelectDialog, 0, QRDID_Close);
	}
}

// Monster와의 충돌 데미지 ...
void PgGround::ReqMonsterTrigger(CUnit* pkUnit, BM::GUID const & kObjectGuid, int iActionType)
{
	CUnit* pkCaster = PgObjectMgr::GetUnit(kObjectGuid);
	if (pkCaster == NULL || (!pkCaster->IsUnitType(UT_MONSTER) && !pkCaster->IsUnitType(UT_ENTITY)))
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("pkCaster is NULL"));
		return;
	}

	PgAction_ReqCollisionDamage kAction(GroundKey(), this);
	kAction.DoAction(pkCaster, pkUnit);
}

// void PgGround::SendNoticeToAllUser(std::wstring wstrContent)
// {
// 	// 모든 유저에게 공지를 보낸다.
// 	BM::CAutoMutex Lock(m_kMutex);
// 
// 	PgPlayer* pkPlayer = NULL;
// 	CONT_OBJECT_MGR_UNIT::iterator kItor;
// 	PgObjectMgr::GetFirstUnit(UT_PLAYER, kItor);
// 	while ((pkPlayer = dynamic_cast<PgPlayer*> (PgObjectMgr::GetNextUnit(UT_PLAYER, kItor))) != NULL)
// 	{
// 		if (pkPlayer->UnitType() == UT_PLAYER)
// 		{
// 			// 유저에게 공지.
// 			BM::Stream kNoticePacket(PT_M_C_NFY_CHAT, (BYTE)CT_NOTICE);
// 			kNoticePacket.Push(wstrContent);
// 			pkPlayer->Send(kNoticePacket);
// 		}
// 	}
// }

EOpeningState PgGround::ActivateMonsterGenGroup( int const iGenGroup, bool const bReset, bool const bOnce, int const iCopy )
{
	BM::CAutoMutex kLock( m_kRscMutex );

	SGenGroupKey kGenGroupKey;
	GetGenGroupKey(kGenGroupKey);

	GET_DEF_CUSTOM( PgGenPointMgr, PgControlDefMgr::EDef_GenPointMgr, kGenPointMgr);
	if ( false==bReset && true==bOnce )
	{
		ContGenPoint_Monster kContGenPoint;
		if( SUCCEEDED(kGenPointMgr.GetGenPoint_Monster( kContGenPoint, kGenGroupKey, bReset, iGenGroup )) )
		{
//			INFO_LOG( BM::LOG_LV6, _T("[%s]One GenPoint MapNo[%d], MapLevel[%d], bReset[%d], GenGroup[%d], Count[%u]"), __FUNCTIONW__, kGenGroupKey.iMapNo, GetMapLevel(), (int)bReset, iGenGroup, kContGenPoint.size());
			EOpeningState const eRet = MonsterGenerate( kContGenPoint, iCopy, NULL );

			ContGenPoint_Monster::const_iterator c_it = kContGenPoint.begin();
			while(c_it != kContGenPoint.end())
			{
				std::pair<ContGenPoint_Monster::iterator, bool> kRet = m_kContGenPoint_Monster.insert(std::make_pair((*c_it).first, (*c_it).second));
				if(false==kRet.second)
				{
					OwnChildCont kContChild;
					(*c_it).second.GetChild(kContChild);
					OwnChildCont::const_iterator it = kContChild.begin();
					while(it != kContChild.end())
					{
						kRet.first->second.AddChild( (*it) );
						++it;
					}
				}
				++c_it;
			}
			return eRet;
		}
	}
	else if ( bOnce )
	{
		ContGenPoint_Monster kContGenPoint;
		if( SUCCEEDED(kGenPointMgr.GetGenPoint_Monster( kContGenPoint, kGenGroupKey, bReset, iGenGroup )) )
		{
//			INFO_LOG( BM::LOG_LV6, _T("[%s]One GenPoint MapNo[%d], MapLevel[%d], bReset[%d], GenGroup[%d], Count[%u]"), __FUNCTIONW__, kGenGroupKey.iMapNo, GetMapLevel(), (int)bReset, iGenGroup, kContGenPoint.size());
			return MonsterGenerate( kContGenPoint, iCopy, NULL );
		}
	}
	else
	{
		if( SUCCEEDED(kGenPointMgr.GetGenPoint_Monster( m_kContGenPoint_Monster, kGenGroupKey, bReset, iGenGroup )) )
		{
//			INFO_LOG( BM::LOG_LV6, _T("[%s]Loop GenPoint MapNo[%d], MapLevel[%d], bReset[%d], GenGroup[%d], Count[%u]"), __FUNCTIONW__, kGenGroupKey.iMapNo, GetMapLevel(), (int)bReset, iGenGroup, m_kContGenPoint_Monster.size());
			return MonsterGenerate( m_kContGenPoint_Monster, iCopy, NULL );
		}
	}
	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return E_OPENING_NONE"));
	return E_OPENING_NONE;
}

EOpeningState PgGround::ActivateObjectUnitGenGroup( int const iGenGroup, bool const bReset, bool const bOnce)
{
	GET_DEF_CUSTOM( PgGenPointMgr, PgControlDefMgr::EDef_GenPointMgr, kGenPointMgr);
	if ( bOnce )
	{
		ContGenPoint_Object kContGenPoint;
		if( SUCCEEDED(kGenPointMgr.GetGenPoint_Object( kContGenPoint, GetGroundNo(), bReset, iGenGroup )) )
		{
			return ObjectUnitGenerate( kContGenPoint, bReset);
		}
	}
	else
	{
		if( SUCCEEDED(kGenPointMgr.GetGenPoint_Object( m_kContGenPoint_Object, GetGroundNo(), bReset, iGenGroup )) )
		{
			return ObjectUnitGenerate(m_kContGenPoint_Object, bReset);
		}
	}
	
	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return E_OPENING_NONE"));
	return E_OPENING_NONE;
}

;
EOpeningState PgGround::ObjectUnitGenerate(PgGenPoint_Object& rkGenPoint)
{
	BM::CAutoMutex kLock(m_kRscMutex);
	// CanGen() 함수는 미리 검사 해야 한다 (아니면 강제 리젠이거나)

	PgGenPoint_Object::OwnGroupCont kCont;
	rkGenPoint.GetBaseInfo( kCont );
	return ObjectUnitGenerate(rkGenPoint, kCont);
}

EOpeningState PgGround::ObjectUnitGenerate(PgGenPoint_Object& rkGenPoint, PgGenPoint_Object::OwnGroupCont const& kCont)
{
	BM::CAutoMutex kLock(m_kRscMutex);
	// CanGen() 함수는 미리 검사 해야 한다 (아니면 강제 리젠이거나)

	BM::GUID kGuid;
	EOpeningState eState = E_OPENING_NONE;
	PgGenPoint_Object::OwnGroupCont::const_iterator info_itr = kCont.begin();
	for( ; info_itr!=kCont.end(); ++info_itr )
	{
		HRESULT hRet = InsertObjectUnit( rkGenPoint.Info(), (*info_itr), kGuid ); 
		eState = __max((EOpeningState)hRet,eState);
		if ( SUCCEEDED(hRet) )
		{
			rkGenPoint.AddChild( kGuid );
			PgWorldEventMgr::IncObjectGenPointCount(rkGenPoint.Info().kPosGuid);
			PgWorldEventMgr::IncObjectGenPointGroupCount(rkGenPoint.Info().iPointGroup);

			if( E_OPENING_NONE != eState )
			{
				PgWorldEventMgr::DoObjectRegenPoint(GetGroundNo(), rkGenPoint.Info().kPosGuid, rkGenPoint.Info().iPointGroup); // 월드 이벤트 검사
			}
		}
	}
	return eState;
}

EOpeningState PgGround::ObjectUnitGenerate(ContGenPoint_Object & kContGenPoint, bool const bReset)
{
	BM::CAutoMutex kLock(m_kRscMutex);

	EOpeningState eState = E_OPENING_NONE;
	if( PgGroundUtil::IsBSGround(GetAttr())
	&&	false == PgGroundUtil::IsHaveFreePVPAttr(DynamicGndAttr()) )
	{
		return eState; // 배틀 스퀘어 게임중이지 않다면 몬스터 리젠 없음
	}

	DWORD const dwCurTime = BM::GetTime32();
	BM::GUID kGuid;

	ContGenPoint_Object::iterator gen_point_itr = kContGenPoint.begin();
	for ( ; gen_point_itr!=kContGenPoint.end(); ++gen_point_itr )
	{
		PgGenPoint_Object &kGenPoint = gen_point_itr->second;
		if ( bReset )
		{
			kGenPoint.Reset();
		}

		if ( kGenPoint.CanGen(dwCurTime) )
		{
			EOpeningState const eTempState = ObjectUnitGenerate(kGenPoint);
			eState = __max(eTempState,eState);
		}
	}

	return eState;
}

void PgGround::ObjectUnitGenerate( bool const bReset, int const iGenGroup )
{
	BM::CAutoMutex kLock(m_kRscMutex);

	DWORD const dwCurTime = BM::GetTime32();
	BM::GUID kGuid;
	ContGenPoint_Object::iterator gen_point_itr;
	for ( gen_point_itr=m_kContGenPoint_Object.begin(); gen_point_itr!=m_kContGenPoint_Object.end(); ++gen_point_itr )
	{
		PgGenPoint_Object& kGenPoint = gen_point_itr->second;
		if ( bReset )
		{
			kGenPoint.Reset();
		}

		if ( (kGenPoint.Info().iPointGroup == iGenGroup) && kGenPoint.CanGen(dwCurTime) )
		{
			PgGenPoint_Object::OwnGroupCont kCont;
			kGenPoint.GetBaseInfo( kCont );

			ObjectUnitGenerate(kGenPoint, kCont);
		}
	}
}

EOpeningState PgGround::MonsterGenerate(PgGenPoint& rkGenPoint, int& iMonNo, BM::GUID& kMonGuid, CUnit* pkCaller)
{
	BM::CAutoMutex kLock(m_kRscMutex);
	// CanGen() 체크는 이미 하고 들어와야 한다. (또는 강제 리젠시 생략 한다.)
	EOpeningState eState = E_OPENING_NONE;
	if( S_OK == rkGenPoint.PopMonster(iMonNo) )
	{
		HRESULT hRet = InsertMonster( rkGenPoint.Info(), iMonNo, kMonGuid, pkCaller ); 
		eState = (EOpeningState)hRet;
		if( SUCCEEDED(hRet) )
		{
			rkGenPoint.AddChild(kMonGuid);
			PgWorldEventMgr::IncMonsterGenPointCount(rkGenPoint.Info().kPosGuid);
			PgWorldEventMgr::IncMonsterGenPointGroupCount(rkGenPoint.Info().iPointGroup);
			PgWorldEventMgr::DoMonsterRegenPoint(GetGroundNo(), rkGenPoint.Info().kPosGuid, rkGenPoint.Info().iPointGroup); // 월드 이벤트 검사
		}
	}
	else
	{
		rkGenPoint.AddChild(BM::GUID::NullData());
	}
	return eState;
}

EOpeningState PgGround::MonsterGenerate( ContGenPoint_Monster &kContGenPoint, int const iCopy, CUnit* pkCaller )
{
	BM::CAutoMutex kLock(m_kRscMutex);

	EOpeningState eState = E_OPENING_NONE;
	if( PgGroundUtil::IsBSGround(GetAttr())
	&&	false == PgGroundUtil::IsHaveFreePVPAttr(DynamicGndAttr()) )
	{
		return eState; // 배틀 스퀘어 게임중이지 않다면 몬스터 리젠 없음
	}

	int iMonNo;
	BM::GUID kMonGuid;
	ContGenPoint_Monster::iterator gen_point_itor;
	for ( gen_point_itor=kContGenPoint.begin(); gen_point_itor!=kContGenPoint.end(); ++gen_point_itor )
	{
		PgGenPoint &kGenPoint = gen_point_itor->second;
		if( kGenPoint.CanGen() )
		{
			int _iCopy = iCopy+1;
			while ( _iCopy-- )
			{
				EOpeningState const eTempState = MonsterGenerate(kGenPoint, iMonNo, kMonGuid, pkCaller);
				eState = __max(eTempState,eState);
			}
		}
	}
	return eState;
}

bool PgGround::IsTargetInRange(CUnit *pkUnit, int iZLimit, bool const bCheckFromGround)
{
	if(!pkUnit)
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	CUnit::DequeTarget& rkTargetList = pkUnit->GetTargetList();
	CUnit::DequeTarget::iterator itor = rkTargetList.begin();

	bool const bMonster = UT_MONSTER==pkUnit->UnitType();

	int iCount = 0;
	ESkillTargetType kType = pkUnit->GetSkill()->GetSkillDef() ? static_cast<ESkillTargetType>(pkUnit->GetSkill()->GetSkillDef()->GetTargetType()) : ESTARGET_ENEMY;
	//static const NxVec3 kDownRay(0.0f, 0.0f, -1.0f);

	while (itor != rkTargetList.end())
	{
		CUnit* pkTarget = GetUnit(itor->kGuid);
		if (pkTarget == NULL)
		{
			pkUnit->DeleteTarget(itor->kGuid);
			++itor;
			continue;
		}
		if (! pkUnit->IsTarget(pkTarget, true, kType))
		{
			pkUnit->DeleteTarget(itor->kGuid);
			++itor;
			continue;
		}

		PgPlayer* pkPlayer = dynamic_cast<PgPlayer*>(pkTarget);
		if(pkPlayer)
		{
			PLAYER_ACTION_INFO const* pkAction = pkPlayer->GetPlayerActionInfo();
			if(pkAction && ACTIONID_A_JUMP!=pkAction->iActionID)
			{
				iZLimit = 30;//이 값은 과연 어떻게 줘야 하나?
			}
		}

		int const iDetectRange = pkUnit->GetDetectRange();
		EInRangeRet eRet = ::IsInRange(pkUnit->GetPos(), GetUnitPos(pkTarget), iDetectRange, iZLimit, false);
		if (ERange_OK!=eRet)
		{
			if(true==bCheckFromGround && ERange_Z==eRet)	//z검사를 마지막에 한다는 가정
			{
				eRet = ::IsInRange(pkUnit->GetPos(), GetUnitPos(pkTarget, true, 300.0f), iDetectRange, iZLimit, false);	//바닥 체크해서 한번 더 검사해 보자
			}
			
			if(ERange_OK!=eRet)
			{
				pkUnit->DeleteTarget(itor->kGuid);
				++itor;
				continue;
			}
		}

		++itor;
		++iCount;
	}
	return (iCount > 0);
}

POINT3BY PgGround::GetMoveDirection(BM::GUID const & rkGuid)
{
	CUnit* pkUnit = GetUnit(rkGuid);
	if(!pkUnit)
	{
		return POINT3BY(0, 0, 0);
	}

	PgPlayer *pkPlayer = dynamic_cast<PgPlayer*>(pkUnit);
	if(!pkPlayer)
	{
		return POINT3BY(0, 0, 0);
	}

	return pkPlayer->MoveDirection();
}

POINT3BY PgGround::GetPathNormal(BM::GUID const & rkGuid)
{
	CUnit* pkUnit = GetUnit(rkGuid);
	if(!pkUnit)
	{
		return POINT3BY(0, 0, 0);
	}

	/*
	PgPlayer *pkPlayer = dynamic_cast<PgPlayer*>(pkUnit);
	if(!pkPlayer)
	{
		return POINT3BY(0, 0, 0);
	}

	return pkPlayer->PathNormal();
	*/
	return pkUnit->PathNormal();
}

POINT3 PgGround::GetUnitPos(BM::GUID const & rkGuid, bool bCheckImpact, float const fRayRange)
{
	CUnit* pkUnit = GetUnit(rkGuid);
	if (pkUnit == NULL)
	{
		return POINT3(0,0,0);
	}
	return GetUnitPos(pkUnit, bCheckImpact, fRayRange);
}

bool PgGround::CanAttackTarget(CUnit* pkAttacker)
{
	DWORD const dwServerTime = g_kEventView.GetServerElapsedTime();
	if ( (0 != pkAttacker->GetAbil(AT_CANNOT_ATTACK)) || !pkAttacker->GetSkill()->CheckCoolTime(SKILL_NO_GLOBAL_COOLTIME, dwServerTime))
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	if( pkAttacker->IsUnitType(UT_SUMMONED) && false==IsInBattleZone(pkAttacker) )
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	/*
	CUnit::ConTarget& rkList = pkAttacker->GetTargetList();
	CUnit::ConTarget::iterator itor = rkList.begin();
	UNIT_PTR_ARRAY kTargetArray;
	while (itor != rkList.end())
	{
		CUnit* pkTarget = GetUnit(*itor);
		if (pkTarget == NULL)
		{
			pkAttacker->DeleteTarget(*itor);
		}
		else
		{
			if (!pkAttacker->IsEnemy(pkTarget))
			{
				pkAttacker->DeleteTarget(*itor);
			}
			else
			{
				kTargetArray.Add(pkTarget);
			}
		}

		++itor;
	}
	*/

	UNIT_PTR_ARRAY kTargetArray;
	SActArg kActArg;
	PgGroundUtil::SetActArgGround(kActArg, this);
	//int iSkillNum = pkAttacker->GetSkill()->GetSkillNo();
	int iSkillNum = 0;
	//if (iSkillNum <= 0)
	{
		iSkillNum = g_kAISkillChooser.GetAvailableSkill(pkAttacker, kTargetArray, true, &kActArg);
	}
	if (iSkillNum > 0)
	{
		if(!kTargetArray.empty())
		{
			UNIT_PTR_ARRAY::iterator it = kTargetArray.begin();
			PgMonster* pkMonster = dynamic_cast<PgMonster*>(pkAttacker);
			if(pkMonster)
			{
				while(it!=kTargetArray.end())
				{
					CUnit const* pkTarget = (*it).pkUnit;
					if(pkTarget)
					{
						if(pkMonster->CheckIgnoreTarget(pkTarget, BM::GetTime32()))
						{
							break;	//한놈이라도 제대로 된 놈이 있다면
						}
						else
						{
							it = kTargetArray.erase(it);
							continue;
						}
					}
					++it;
				}
			}
		}
		pkAttacker->SetTargetList(kTargetArray);

#ifdef AI_DEBUG
		//INFO_LOG(BM::LOG_LV9, _T("[%s] AvailableSkill[%d]"), __FUNCTIONW__, iSkillNum);
#endif
		//ESkillCastType eCastType = (ESkillCastType) g_SkillDefMgr.GetAbil(iSkillNum, AT_CASTTYPE);
		return pkAttacker->GetSkill()->CheckCoolTime(iSkillNum, dwServerTime);
	}
	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
	return false;
}

bool PgGround::AI_SkillCasting(CUnit* pkCaster, SActArg* pkActArg, BM::Stream& rkTailPacket)
{
	//CUnit* pkTarget = GetUnit(pkCaster->GetTarget());
	//if (pkTarget == NULL)
	//{
	//	INFO_LOG(BM::LOG_LV5, _T("[%s] Unit cannot get Target Skill[%d]"), __FUNCTIONW__, pkTarget->GetSkill());
	//	return false;
	//}
	int const iSkillNo = pkCaster->GetSkill()->GetSkillNo();
	GET_DEF(CSkillDefMgr, kSkillDefMgr);
	const CSkillDef* pkSkillDef = kSkillDefMgr.GetDef(iSkillNo);
	if( !pkSkillDef )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV0, __FL__<<L"Cannot get SkillDef ["<<iSkillNo<<L"]");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	return (g_kSkillAbilHandleMgr.SkillBegin(pkCaster, iSkillNo, pkActArg, ESS_CASTTIME, &rkTailPacket) >= 0);
}

bool PgGround::AI_SkillFire(CUnit* pkCaster, SActArg* pkActArg, const ESkillStatus eSkillStatus)
{
	//CUnit* pkTarget = GetUnit(pkCaster->GetTarget());
	//if (pkTarget == NULL)
	//{
	//	return false;
	//}

	if ( (0 != pkCaster->GetAbil(AT_CANNOT_ATTACK)) )
	{
		//INFO_LOG(BM::LOG_LV5, _T("WARNING...[%s] Caster->GetAbil(AT_CANNOT_ATTACK)=[%d], Cannot Attack!!!!"), __FUNCTIONW__, pkCaster->GetAbil(AT_CANNOT_ATTACK));
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}
	
	int iSkillNo = pkCaster->GetSkill()->GetSkillNo();
	if (iSkillNo <= 0)
	{
		//INFO_LOG(BM::LOG_LV0, __FL__<<L"Unit cannot FireSkill because SkillNo is "<<iSkillNo);
		pkCaster->SetDelay(0);	// ERROR 발생하여 다른 Action으로 변경해야 함.
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}
	PgActionResultVector kResult;
	ESkillFireType eFireType = (ESkillFireType) pkCaster->GetSkill()->GetAbil(AT_FIRE_TYPE);
	if ((eSkillStatus != ESS_FIRE || (eFireType & EFireType_DontDmgWhenFire) == 0) && eSkillStatus!=ESS_TIMEWAITING)	//ESS_TIMEWAITING 은 공격하라는 신호만 보내자
	{
		// Target을 다시 잡아 보자
		UNIT_PTR_ARRAY kUnitArray;
		if ( !AI_GetSkillTargetList(pkCaster, iSkillNo, kUnitArray, true, pkActArg))
		{
			//if (eSkillStatus == ESS_TARGETLISTMODIFY)
			//{
				// Target이 없고 ESS_TARGETLISTMODIFY 상태이므로 그냥 리턴한다.
			//	return false;
			//}
			// Target이 없어도 Fire 액션을 보내줘야 클라이언트에서 연출이 된다.
			//return false;
		}
		//EActionResultCode eActionResult = pkCaster->GetSkill()->Fire(iSkillNo);

		CheckTargetList(kUnitArray);
		
		GET_DEF(CSkillDefMgr, kSkillDefMgr);
		CSkillDef const* pkSkillDef = kSkillDefMgr.GetDef(iSkillNo);
		if( !pkSkillDef )
		{
			VERIFY_INFO_LOG(false, BM::LOG_LV0, __FL__<<L"Cannot get SkillDef ["<<iSkillNo<<L"]");
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
			return false;
		}
		//if (CanAttackTarget(pkCaster))
		// Client Control Projectile 스킬일때에는 처음부터 서버가 Hit를 판정하지 않는다.
		// 나중에 Client 자신이 맞았음을 알려 온다.
		bool bClientCtrl = true;
		if (!pkSkillDef->IsSkillAtt(SAT_CLIENT_CTRL_PROJECTILE) || pkSkillDef->IsSkillAtt(static_cast<ESkillAttribute>(SAT_SERVER_FIRE)))
		{
			g_kTargettingManager.FindTarget(pkCaster, pkSkillDef, &kUnitArray, this);
			pkActArg->Set(ACTARG_EFFECT_CASTER_UNIT_TYPE, pkCaster->UnitType());	  // 캐스터 타입을 저장한다
			g_kSkillAbilHandleMgr.SkillFire(pkCaster, iSkillNo, pkActArg, &kUnitArray, &kResult);
			pkCaster->SetAbil(AT_AI_SKILL_USE_COUNT, pkCaster->GetAbil(AT_AI_SKILL_USE_COUNT)+1);
			pkCaster->SetAbil(AT_AI_SKILL_FIRE_TIME, BM::GetTime32());

			OnAttacked(pkCaster, &kUnitArray, iSkillNo, &kResult, pkActArg, g_kEventView.GetServerElapsedTime());
#ifdef AI_DEBUG
			INFO_LOG(BM::LOG_LV9, __FL__<<L"SkillFired Skill["<<iSkillNo<<L"] TIME["<<BM::GetTime32()<<L"] Target["<<kUnitArray.size()<<L"]");
#endif
			bClientCtrl = false;
		}

		GET_DEF(CEffectDefMgr, kEffectDefMgr);
		UNIT_PTR_ARRAY::const_iterator itor = kUnitArray.begin();
		while(itor != kUnitArray.end())
		{
			if(CUnit* pkTarget = itor->pkUnit)
			{
				if(PgActionResult* pkResult = kResult.GetResult(pkTarget->GetID(), bClientCtrl))
				{
					if(IsDecEquipDuration())
					{//내구도 까기.
						if(pkResult->GetValue())
						{//헛침이 아닐때만.
							PgAction_DecEquipDuration kDecDurAction(GroundKey(), false, pkResult->GetValue());
							kDecDurAction.DoAction(pkTarget, pkCaster);
						}
					}

					int const iDmgEffect = pkResult->GetEffect(0);
					if(pkTarget->IsAlive() && 0<iDmgEffect && pkResult->IsDamageAction())
					{
						CEffectDef const* pkDmgEffect = kEffectDefMgr.GetDef(iDmgEffect);
						if(pkDmgEffect && 0 < pkDmgEffect->GetAbil(AT_BLOW_VALUE) )	// AT_BLOW_VALUE값이 양수이면 DamageDelay가 있는 공격이다.
						{
							pkTarget->SetBlowAttacker(pkCaster->GetID());
							pkTarget->SetAbil(AT_DAMAGE_EFFECT_DURATION, pkDmgEffect->GetDurationTime());//데미지 액션 시간 저장
							pkTarget->SetDelay(__max(pkDmgEffect->GetDurationTime(), 3000));
						}
					}
				}
			}
			++itor;
		}
	}

	EActionResultCode eActionResult = pkCaster->GetSkill()->CheckSkillAction(iSkillNo, eSkillStatus, g_kEventView.GetServerElapsedTime(), pkCaster->GetAbil(AT_R_COOLTIME_RATE_SKILL), pkCaster->GetAbil(AT_CAST_TIME_RATE));
	if (eActionResult > EActionR_Success_Max)
	{
		INFO_LOG(BM::LOG_LV0, __FL__<<L"Unit cannot FireSkill EActionResultCode["<<static_cast<int>(eActionResult)<<L"]");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	// Sending Result
	// 간혹 자살폭탄공격의 경우에는 이미 US_DEAD 일수 있기 때문에
	// SendNfyAIAction에 GetState() 함수를 사용하지 않고 직접 US_ATTACK을 지정하여 호출한다.
	if (eSkillStatus == ESS_FIRE)
	{
		SendNfyAIAction(pkCaster, US_ATTACK, &kResult);
	}
	else
	{
		EUnitState const eState = pkCaster->GetState()==US_DEAD ? US_SKILL_FIRE : pkCaster->GetState();
		SendNfyAIAction(pkCaster, eState, &kResult);
	}

	return true;
}

void PgGround::ReleaseAllUnit()
{
	PgObjectMgr2::InitObjectMgr();
}

bool PgGround::GetTargetPos(CUnit* pkUnit, POINT3& rkTargetPos)
{
	CUnit* pkTarget = GetUnit(pkUnit->GetTarget());
	if (pkTarget == NULL)
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}
	rkTargetPos = pkTarget->GetPos();
	return true;
}

void PgGround::AI_CallHelp(CUnit* pkUnit, float fCallRange)
{
	EUnitType eUnitType = pkUnit->UnitType();
	POINT3 const kPos = pkUnit->GetPos();
	CUnit* pkFind = NULL;
	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr::GetFirstUnit(eUnitType, kItor);
	while((pkFind = PgObjectMgr::GetNextUnit(eUnitType, kItor)) != NULL)
	{
		if(ERange_OK==::IsInRange(kPos, pkFind->GetPos(), (int)fCallRange, 30))
		{
//#ifdef AI_DEBUG
			INFO_LOG(BM::LOG_LV0, __FL__<<L"Call Help UnitType["<<eUnitType<<L"], CalledUnit["<<pkFind->GetID()<<L"]");
//#endif
			pkFind->GetAI()->SetEvent(pkUnit->GetID(), EAI_EVENT_CALLED_HELP);
			pkUnit->SetAbil(AT_WAYPOINT_GROUP, -1);	// -1 이면 Patrol 상태에서 GoalPos로 이동하도록 한다.
			pkFind->GoalPos(kPos);
#ifdef AI_DEBUG
			INFO_LOG(BM::LOG_LV9, __FL__ << _T("GoalPos =") << pkFind->GoalPos());
#endif
		}
	}
	
}

int PgGround::GetReserveAISkill(CUnit* pkUnit)
{
	UNIT_PTR_ARRAY kTargetArray;
	GetTargetList(pkUnit, kTargetArray);
	if (kTargetArray.size() == 0)
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return 0"));
		return 0;
	}
	SActArg kActArg;
	PgGroundUtil::SetActArgGround(kActArg, this);
	return g_kAISkillChooser.GetReservableSkill(pkUnit, kTargetArray, true, &kActArg);
}

// SetValidGoalsPos()로 대체함.
//bool PgGround::CheckUnitGoalPos(CUnit* pkUnit)
//{
//	// Ray를 바닥으로 쏘아서 그쪽으로 가도 될것인가 판단하자.
//	DWORD const dwMoveTime = 200;
//	int iMoveSpeed = pkUnit->GetAbil(AT_C_MOVESPEED);
//	POINT3& ptCurrentPos = pkUnit->GetPos();
//	POINT3 const ptGoal = pkUnit->GoalPos();
//	NxVec3 kTargetVec = NxVec3(ptGoal.x, ptGoal.y, 0) - NxVec3(ptCurrentPos.x, ptCurrentPos.y, 0);
//	kTargetVec.normalize();
//	NxVec3 kResultVec = kTargetVec * NxReal(iMoveSpeed * dwMoveTime / 1000.0f) + NxVec3(ptCurrentPos.x, ptCurrentPos.y, ptCurrentPos.z);
//
//	// TODO : Z축 조정은 Client와 조율하여 없애도록 해야 한다.
//	NxRay kRay(NxVec3(kResultVec.x, kResultVec.y, ptCurrentPos.z+20), NxVec3(0, 0, -1.0f));
//	NxRaycastHit kHit;
//	NxShape *pkHitShape = PhysXScene()->GetPhysXScene()->raycastClosestShape(kRay, NX_STATIC_SHAPES, kHit, -1, 90.0f, NX_RAYCAST_SHAPE|NX_RAYCAST_IMPACT);
//	if(pkHitShape)
//	{
//		return true;
//	}
//	INFO_LOG(BM::LOG_LV9, _T("[%s] Check GoalPos failed GroundNo[%d]"), __FUNCTIONW__, GroundKey().GroundNo());
//	return false;
//}

CUnit* PgGround::GetPlayer(char const* pcCharacterName)
{
	std::wstring wCharacterName = UNI(pcCharacterName);
	return GetPlayer( wCharacterName );
}

CUnit* PgGround::GetPlayer( std::wstring const &wstrName )
{
	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr2::GetFirstUnit(UT_PLAYER, kItor);
	CUnit* pkPlayer = NULL;
	while ((pkPlayer = PgObjectMgr2::GetNextUnit(UT_PLAYER, kItor)) != NULL)
	{
		if ( wstrName == pkPlayer->Name() )
		{
			return pkPlayer;
		}
	}
	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return NULL"));
	return NULL;
}

// 각 스킬에 적합한 TargetList를 얻어 보자.
//	bDamageFire : Damage를 주기 위한 Target을 얻는 것인가?
// [NOTICE]
//	몇몇 스킬은 SkillFire를 하기 위한 Target을 잡는 방법과, 실제로 Damage를 줄 수 있는 Target잡는 방법이 다를 수 있다.
//	예를 들면, 돌격과 같은 스킬은 처음에 Range안에 들어오면 스킬을 발동하여 돌격 시작하지만,
//	실제로 충돌하여야만, 데미지를 주어야 하기 때문에, 범위값이 달라야 한다.
bool PgGround::AI_GetSkillTargetList(CUnit* pkCaster, int const iSkillNo, UNIT_PTR_ARRAY& rkTargetList, bool bDamageFire, SActArg const* pkActArg, POINT3 const* pkDir, SAddRange const& rkAddRange)
{
	if (pkCaster == NULL || iSkillNo < 0)
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}
	
	GET_DEF(CSkillDefMgr, kSkillDefMgr);
	CSkillDef const *pkSkillDef = kSkillDefMgr.GetDef(iSkillNo);
	if( !pkSkillDef )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV0, __FL__<<L"Cannot Get SkillDef["<<iSkillNo<<L"]");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}
	
	/*int const iMaxRange = PgAdjustSkillFunc::GetAttackRange(pkCaster, pkSkillDef);
	if (iMaxRange <= 0)
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}*/

	//int iMinRange = pkSkillDef->GetAbil(AT_SKILL_MIN_RANGE);
	POINT3 const ptCasterPos = GetUnitPos(pkCaster);
	int const iTargetType = pkSkillDef->GetTargetType();
	// 비교할 필요없는 UnitType은 빼 버리자
	//EUnitType const eUnitTypeArray[] = {UT_PLAYER, UT_MONSTER, UT_GROUNDBOX, UT_PET, UT_NPC, UT_BOSSMONSTER, UT_FIGURE, UT_ENTITY, UT_NONETYPE};
	static EUnitType const eUnitTypeArray[] = {UT_SUMMONED, UT_PLAYER, UT_MONSTER, UT_BOSSMONSTER, UT_OBJECT, UT_NONETYPE};	

	int iIndex = 0;
	EUnitType const eCasterUnitType = pkCaster->UnitType();
	rkTargetList.clear();
	while (eUnitTypeArray[iIndex] != UT_NONETYPE)
	{
		// Target이 될수 있는가 검사하고
		if (CUnit::IsTargetUnitType(eCasterUnitType, eUnitTypeArray[iIndex], iTargetType))
		{
			// 영역안에 타겟 Unit들을 가져온다.
			GetTargetInArea(pkCaster, pkSkillDef, eUnitTypeArray[iIndex], rkTargetList, bDamageFire, pkDir, rkAddRange);
		}
		++iIndex;
	}

	// 일단은 Caster를 중심으로 Range안에 있으면 모두 Target이 된다.
	/*
	int iMinRange = pkSkillDef->GetAbil(AT_SKILL_MIN_RANGE);
	EUnitType eUnitType = pkCaster->UnitType();
	POINT3 const ptCasterPos = GetUnitPos(pkCaster);
	int iFound = 0;
	switch(eUnitType)
	{
	case UT_PLAYER:
	case UT_ENTITY:
		iFound = GetTargetInArea(pkCaster, pkSkillDef, UT_PLAYER, rkTargetList, bDamageFire);
		iFound += GetTargetInArea(pkCaster, pkSkillDef, UT_MONSTER, rkTargetList, bDamageFire);
		break;
	case UT_MONSTER:
	case UT_BOSSMONSTER:
		iFound = GetTargetInArea(pkCaster, pkSkillDef, UT_PLAYER, rkTargetList, bDamageFire);
		break;
	default:
		VERIFY_INFO_LOG(false, BM::LOG_LV5, _T("[%s] NOT implemented UnitType[%d]"), __FUNCTIONW__, eUnitType);
		break;
	}
	*/

	if( rkTargetList.size()  > 0 )
	{
		return true;
	}
	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
	return false;
	//return (iFound > 0) ? true : false;
}

inline bool IsTarget(CUnit const& rkCaster, CUnit const& rkTarget, CSkillDef const& rkSkillDef, VEC_GUID const& rkPartyList)
{
	if(rkCaster.IsUnitType(UT_SUMMONED) && (ESTARGET_PARTY&rkSkillDef.GetTargetType()))
	{
		if(rkPartyList.end() != std::find(rkPartyList.begin(), rkPartyList.end(), rkTarget.GetID()))
		{
			return true;
		}
	}
	return false;
}

int PgGround::GetTargetInArea(CUnit* pkCaster, const CSkillDef* pkSkillDef, EUnitType const eUnitType, UNIT_PTR_ARRAY& rkTargetList, bool const bDamageFire, POINT3 const* pkDir, SAddRange const& rkAddRange)
{
	if(!pkCaster || !pkSkillDef)
	{ 
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return 0"));
		return 0;
	}

	bool const b2ndRange = (bDamageFire && pkSkillDef->GetAbil(AT_2ND_AREA_PARAM1) > 0);
	ESkillArea const eAreaType = (ESkillArea) pkSkillDef->GetAbil((b2ndRange) ? AT_2ND_AREA_TYPE : AT_1ST_AREA_TYPE);
	int const iRange = PgAdjustSkillFunc::CalcAttackRange(pkCaster, pkSkillDef->GetAbil((b2ndRange) ? AT_2ND_AREA_PARAM1 : AT_ATTACK_RANGE)) + std::get<0>(rkAddRange);
	int const iParam2 = pkSkillDef->GetAbil((b2ndRange) ? AT_2ND_AREA_PARAM2 : AT_1ST_AREA_PARAM2) + std::get<1>(rkAddRange);
	int const iParam3 = pkSkillDef->GetAbil((b2ndRange) ? AT_2ND_AREA_PARAM3 : AT_1ST_AREA_PARAM3) + std::get<2>(rkAddRange);
	int const iParam4 = pkSkillDef->GetAbil((b2ndRange) ? AT_2ND_AREA_PARAM4 : AT_1ST_AREA_PARAM4) + std::get<3>(rkAddRange);
	if (iRange <= 0)
	{
		INFO_LOG(BM::LOG_LV0, __FL__<<L"Skill["<<pkSkillDef->No()<<L"] has "<<iRange<<L" range");
	}

	if (iParam2 <= 0 && (eAreaType == ESArea_Cube || eAreaType == ESArea_Cone || eAreaType == ESArea_Front_Sphere))
	{
		INFO_LOG(BM::LOG_LV0, __FL__<<L"Skill["<<pkSkillDef->No()<<L"] has "<<eAreaType<<L" area type and "<<iParam2<<L" param2");
	}

	ESkillFireType const eFireType = (ESkillFireType) pkSkillDef->GetAbil(AT_FIRE_TYPE);
	POINT3 ptCaster = GetUnitPos(pkCaster);
	int iMinRange = pkSkillDef->GetAbil(AT_SKILL_MIN_RANGE);
	int iPCount = 0;
	std::vector<POINT3> vecCasterPos;
	if (bDamageFire)
	{
		if (eFireType & EFireType_Projectile) 
		{ 
			iPCount = pkSkillDef->GetAbil(AT_MON_PROJECTILE_NUM);
			if(0 == iPCount)
			{
				ptCaster = pkCaster->Projectile(0).ptCurrent;
			}
			else
			{
				for(int i=0; i<iPCount; ++i)
				{
					vecCasterPos.push_back(pkCaster->Projectile(i).ptCurrent);
				}
			}
			iMinRange = 0;	//프로젝틸이 공격할 때 MinRange가 있으면 안됨
		}	// 공격하는 개체가 Projectile 이다.
		else if (eFireType & EFireType_AttackToGoalPos) { ptCaster = pkCaster->GoalPos(); }	// GoalPos 위치로 공격하는 것이다.
	}
	int const iMaxTargetNum = std::max(1, pkSkillDef->GetAbil(AT_MAX_TARGETNUM));

#ifdef AI_DEBUG
	// Test를 위해 값을 강제 세팅
	//eAreaType = ESArea_Cube;
	//iParam2 = 10;
#endif

	NxVec3 kVisionDir;
	if(pkDir)
	{
		kVisionDir.setx(pkDir->x);
		kVisionDir.sety(pkDir->y);
		kVisionDir.setz(pkDir->z);
	}
	else
	{
		kVisionDir.zero();

		bool bUseTargetDir = true;
		if((eFireType & EFireType_KeepVisionVector) || pkCaster->GetAbil(AT_MON_ANGLE_FIX))
		{
			bUseTargetDir = !bDamageFire;
		}
		
		GetVisionDirection(pkCaster, kVisionDir, bUseTargetDir);
		if(!kVisionDir.isZero())
		{
			POINT3BY kOrientedVec;
			POINT3_2_POINT3BY(POINT3(kVisionDir.x, kVisionDir.y, kVisionDir.z), kOrientedVec);
			pkCaster->SetOrientedVector(kOrientedVec);
		}
		else	//제자리에 계속 서 있을땐 비전 벡터가 0일 수도 있다 그럴 땐 이전에 정상적으로 비전 벡더를 구해서 저장해 두었던 오리엔티드 벡터에서 복사해서 계산하자
		{
			POINT3BY kOrientedVec = pkCaster->GetOrientedVector();
			kVisionDir.set(kOrientedVec.x, kOrientedVec.y, kOrientedVec.z);
			kVisionDir.normalize();
		}
	}

	//
	VEC_GUID kPartyList;
	if(pkCaster->IsUnitType(UT_SUMMONED) && (ESTARGET_PARTY&pkSkillDef->GetTargetType()))
	{
		if(CUnit * pkOwnerUnit = GetUnit(pkCaster->Caller()))
		{
			BM::GUID const& kPartyGuid = pkOwnerUnit->GetPartyGuid();
			if(BM::GUID::IsNotNull(kPartyGuid))
			{
				GetPartyMember(kPartyGuid, kPartyList);
			}
		}
	}

	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr::GetFirstUnit(eUnitType, kItor);
	CUnit* pkEnemy = NULL;

    PgTargettingManager::E_TARGETTING_TYPE eSelectType = static_cast<PgTargettingManager::E_TARGETTING_TYPE>(pkSkillDef->GetAbil(AT_TARGET_SELECT_TYPE));
	if(PgTargettingManager::ETT_NONE==eSelectType)
	{
		eSelectType = static_cast<PgTargettingManager::E_TARGETTING_TYPE>(pkCaster->GetAbil(AT_TARGET_SELECT_TYPE));
	}

    if(PgTargettingManager::ETT_NONE==eSelectType)
    {
	    int iCount = rkTargetList.size();
	    while (iCount < iMaxTargetNum && (pkEnemy = PgObjectMgr::GetNextUnit(eUnitType, kItor)) != NULL)
	    {
		    if (!pkCaster->IsTarget(pkEnemy, true, pkSkillDef->GetTargetType(),pkSkillDef) && !IsTarget(*pkCaster, *pkEnemy, *pkSkillDef, kPartyList))
		    {
			    continue;
		    }
		    if(iPCount)
		    {
			    bool bInArea = false;
			    for(int i=0; i<iPCount; ++i)
			    {
				    if(PgSkillAreaChooser::InArea(pkEnemy, eAreaType, vecCasterPos.at(i), kVisionDir, GetUnitPos(pkEnemy, (!bDamageFire && IsDetailAI(pkCaster)), 300.0f), iRange, iParam2, iParam3, iParam4, iMinRange))
				    {
					    bInArea = true;
				    }
			    }
			    if(!bInArea)
			    {
				    continue;
			    }
		    }
		    else
		    {
			    if (!PgSkillAreaChooser::InArea(pkEnemy, eAreaType, ptCaster, kVisionDir, GetUnitPos(pkEnemy, (!bDamageFire && IsDetailAI(pkCaster)), 300.0f), iRange, iParam2, iParam3, iParam4, iMinRange))
			    {
				    continue;
			    }
		    }

		    // Debug Code...
		    //PgPlayer* pkPlayer = dynamic_cast<PgPlayer*>(pkEnemy);
		    //if(pkPlayer)
		    //{
		    //	INFO_LOG(BM::LOG_LV8, _T("[%s] GetUnitPos's Latency : %d"), __FUNCTIONW__, pkPlayer->Latency());
		    //}

		    rkTargetList.Add(pkEnemy);
		    ++iCount;
	    }
    }
    else
    {
	    while ((pkEnemy = PgObjectMgr::GetNextUnit(eUnitType, kItor)) != NULL)
	    {
		    if (!pkCaster->IsTarget(pkEnemy, true, pkSkillDef->GetTargetType(),pkSkillDef) && !IsTarget(*pkCaster, *pkEnemy, *pkSkillDef, kPartyList))
		    {
			    continue;
		    }
		    if(iPCount)
		    {
			    bool bInArea = false;
			    for(int i=0; i<iPCount; ++i)
			    {
				    if(PgSkillAreaChooser::InArea(pkEnemy, eAreaType, vecCasterPos.at(i), kVisionDir, GetUnitPos(pkEnemy, (!bDamageFire && IsDetailAI(pkCaster)), 300.0f), iRange, iParam2, iParam3, iParam4, iMinRange))
				    {
					    bInArea = true;
				    }
			    }
			    if(!bInArea)
			    {
				    continue;
			    }
		    }
		    else
		    {
			    if (!PgSkillAreaChooser::InArea(pkEnemy, eAreaType, ptCaster, kVisionDir, GetUnitPos(pkEnemy, (!bDamageFire && IsDetailAI(pkCaster)), 300.0f), iRange, iParam2, iParam3, iParam4, iMinRange))
			    {
				    continue;
			    }
		    }

		    // Debug Code...
		    //PgPlayer* pkPlayer = dynamic_cast<PgPlayer*>(pkEnemy);
		    //if(pkPlayer)
		    //{
		    //	INFO_LOG(BM::LOG_LV8, _T("[%s] GetUnitPos's Latency : %d"), __FUNCTIONW__, pkPlayer->Latency());
		    //}

		    rkTargetList.Add(pkEnemy);
	    }

        g_kTargettingManager.FindTarget(pkCaster, pkSkillDef, &rkTargetList, this, eSelectType, pkSkillDef->GetAbil(AT_TARGET_SELECT_VALUE));
        if(iMaxTargetNum < rkTargetList.size())
        {
            rkTargetList.resize(iMaxTargetNum);
        }
    }

	return rkTargetList.size();
}

bool PgGround::FireToggleSkill(CUnit* pkCaster, UNIT_PTR_ARRAY& rkTargetArray, const SActionInfo &rkAction, PgActionResultVector* pkActionResultVec)
{
	if(pkCaster == NULL)
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	if ( 0 != pkCaster->GetAbil(AT_CANNOT_ATTACK) 
		&& rkAction.byActionParam != ESS_TOGGLE_OFF
		)
	{
		//INFO_LOG(BM::LOG_LV0, _T("WARNING...[%s] Caster->GetAbil(AT_CANNOT_ATTACK)=[%d], Cannot Attack!!!!"), __FUNCTIONW__, pkCaster->GetAbil(AT_CANNOT_ATTACK));
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	// 숨어있다가 맞거나/때리면 Hidden 속성이 사라짐
	// 단 AT_LOCK_HIDDEN_ATTACK 이 있으면 풀리지 않는다.
	int iHiddenAbil = pkCaster->GetAbil(AT_UNIT_HIDDEN);
	if (iHiddenAbil > 0 && pkCaster->GetAbil(AT_LOCK_HIDDEN_ATTACK) <= 0)
	{
		pkCaster->SetAbil(AT_UNIT_HIDDEN, iHiddenAbil-1);
	}

	SActArg kArg;
	PgGroundUtil::SetActArgGround(kArg, this);
	kArg.Set(ACTARG_ACTIONINSTANCEID, rkAction.iActionInstanceID);	// Client한테 AddEffect 패킷 보낼때 필요하다.
	{
		int iLuaRet = g_kSkillAbilHandleMgr.SkillToggle(pkCaster, rkAction.iActionID, &kArg, (rkAction.byActionParam == ESS_TOGGLE_ON) ? true : false, 
			&rkTargetArray, pkActionResultVec);
		if (iLuaRet < 0)
		{
			GET_DEF(CSkillDefMgr, kSkillDefMgr);
			int iBasicSkill = kSkillDefMgr.GetCallSkillNum(rkAction.iActionID);
	
			INFO_LOG(BM::LOG_LV0, __FL__<<L"Skill_Toggle"<<iBasicSkill<<L" returnd ["<<iLuaRet<<L"]");
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
			return false;
		}
	}

	return true;
}

CUnit* PgGround::GetUnitControl(CUnit* pkUnit, CUnit* pkCalledUnit, unsigned short usPacketType, BM::Stream& rkPacket)
{
	CUnit* pkControlUnit = NULL;
	switch(usPacketType)
	{
// 	case PT_C_M_REQ_CREATE_ENTITY:
// 		{
// 			if (pkUnit->GetSummonUnitCount() >= pkUnit->GetMaxSummonUnitCount())
// 			{
// 				INFO_LOG(BM::LOG_LV0, _T("[%s] Cannot Create Entity anymore CurrentCount[%d]"), __FUNCTIONW__, pkUnit->GetSummonUnitCount());
// 				LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return NULL"));
// 				return NULL;
// 			}
// 			SCreateEntity sCreateInfo;
// 			rkPacket.Pop(sCreateInfo);
// 			pkControlUnit = CreateEntity(pkUnit, &sCreateInfo, _T("ClientMade"), false);
// 		}break;
// 	case PT_C_M_REQ_DELETE_ENTITY:
// 		{
// 			BM::GUID kEntityGuid;
// 			rkPacket.Pop(kEntityGuid);
// 			CUnit* pkDelete = GetUnit(kEntityGuid);
// 			if (pkDelete != NULL && pkDelete->IsUnitType(UT_ENTITY))
// 			{
// 				PgEntity* pkEntity = dynamic_cast<PgEntity*>(pkDelete);
// 				if (pkEntity != NULL && pkEntity->Caller() == pkUnit->GetID())
// 				{
// 					ReleaseUnit(pkEntity);
// 				}
// 			}
// 		}break;
	case PT_C_M_REQ_ACTION2:
		{
			if (pkCalledUnit != NULL || pkCalledUnit->Caller() == pkUnit->GetID())
			{
				pkControlUnit = pkCalledUnit;
			}
		}break;
	default:
		{
			INFO_LOG(BM::LOG_LV0, __FL__<<L"Unknown Packet Type ["<<usPacketType<<L"]");
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Invalid CaseType"));
		}break;
	}

	return pkControlUnit;
}

void PgGround::ReqProjectileAction(CUnit* pkSendUnit, BM::Stream * const pkPacket)
{	
	SProjectileAction kAction;
	float fLifeTime = 0;
	pkPacket->Pop(kAction);
	pkPacket->Pop(fLifeTime);
	CUnit* pkCaster = PgObjectMgr::GetUnit(kAction.kCasterGuid);
	if ( pkCaster == NULL )
	{
		INFO_LOG(BM::LOG_LV0, __FL__<<L"Caster is NULL Guid["<<kAction.kCasterGuid<<L"]");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("pkCaster is NULL"));
		return;
	}

	//INFO_LOG(BM::LOG_LV6, __FL__ << _T("Caster=") << kAction.kCasterGuid << _T(", iActionID=") << kAction.iActionID << _T(", InstanceID=")
	//	<< kAction.iActionInstanceID << _T(", ProjectileUID=") << kAction.uProjectileUID);

	// 보안검사를 어디까지 할 것인가 ? 흠흠~~~
	// 보안 1 : Monster가 공격할 경우 Target은 Player 자기자신만 있어야 한다.
	// 보안 2 : Player가 공격할 경우 Fire 된 스킬이 맞는가 검사.
	//	(이것은 Player가 발사체 Skill Fire 직후에는 다른 스킬을 사용할 수 없다는 가정이 필요하다.)
	//	(즉, 발사체가 날아가고 있는 도중에는 다른 공격 Skill Fire 할 수 없거나, 이미 발사된 발사체가 취소되어야 한다.)
	// 보안 3 : Skill이 Client가 조절하는 Projectile Skill이 맞는지 확인한다.
	if ( !::CheckUnitAction( pkCaster, kAction.iActionID, this, PT_C_M_REQ_PACTION ) )
	{
		return;
	}

	// Caster가 내가 아닌경우는 Target이 나여야 한다.
	BM::GUID const kCheckGuid = pkSendUnit->Caller();
	bool const bDamageAction = ( kCheckGuid != pkCaster->Caller() );
	
	BYTE byTargetNum;
	pkPacket->Pop(byTargetNum);
	// 보안 : Client가 Packet 길이를 결정하기 때문에 Max Limit를 만들어야 한다.

	bool bHackingUser = false;

	PgActionResultVector kActionResultVec;
	UNIT_PTR_ARRAY kTargetArray;
	byTargetNum = ((byTargetNum > MAX_SKILL_TARGETNUM) ? MAX_SKILL_TARGETNUM : byTargetNum);
	
	GET_DEF(CSkillDefMgr, kSkillDefMgr);
	CSkillDef const* pkSkillDef = (CSkillDef*) kSkillDefMgr.GetDef(kAction.iActionID);
	if(pkSkillDef)
	{
		int iMaxTarget = pkSkillDef->GetAbil(AT_MAX_TARGETNUM);

		//관통 어빌을 사용하는 스킬 이면 관통 수를 더 해준다.
		if(0 < pkSkillDef->GetAbil(AT_PENETRATION_USE_TYPE))
		{
			//무조건 넣으면 안되고 스킬에서 사용하는것만 넣어줘야한다.
			int iPenetrationCount = pkCaster->GetAbil(AT_PENETRATION_COUNT);
			if(0 != iPenetrationCount)
			{
				iMaxTarget += iPenetrationCount;
			}
		}
		else if (kAction.iActionID == 102100301)
		{
			iMaxTarget += 1;	//예외 (클라이언트 버그인듯..)
		}

		if(static_cast<int>(byTargetNum) > iMaxTarget)
		{
			if (PgGround::ms_kAntiHackCheckVariable.bUse_Projectile)
			{
				PgPlayer* pkPlayer = dynamic_cast<PgPlayer*>(pkSendUnit);
				if(pkPlayer)
				{
					// 이놈은 해킹이다.
					BM::vstring kLogMsg;
					kLogMsg << __FL__ << _T("[HACKING][Projectile MaxTarget] User[") << pkPlayer->Name() << _T("] GUID[") << pkPlayer->GetID() << _T("] MemberGUID[") << pkPlayer->GetMemberGUID() 
						<< _T("] GroundNo[") << GroundKey().GroundNo() << _T("] HackingType[ProjectileHacking] Action ID[") << kAction.iActionID << _T("] MaxTarget[") << iMaxTarget << _T("] ProjectileTarget[") << byTargetNum << _T("]");
					//VERIFY_INFO_LOG(false, BM::LOG_LV0, kLogMsg);
					HACKING_LOG(BM::LOG_LV0, kLogMsg);

					if (g_kProcessCfg.RunMode() & CProcessConfig::E_RunMode_Debug)
					{
						pkPlayer->SendWarnMessageStr(kLogMsg);
					}

					if (pkPlayer->SuspectHacking(EAHP_Projectile, PgGround::ms_kAntiHackCheckVariable.sProjectile_AddIndex))
					{
						// SpeedHack이 의심스러우니 강제접속 해제 시킨다.
						BM::Stream kDPacket( PT_A_S_NFY_USER_DISCONNECT, static_cast<BYTE>(CDC_Projectile_Hack) );
						kDPacket.Push( pkPlayer->GetMemberGUID() );
						SendToServer( pkPlayer->GetSwitchServer(), kDPacket );						
					}
					return;
				}
			}
		}
	}

	BM::GUID kTargetGuid;
	BYTE bySphereIndex = 0;
	CUnit* pkTarget = NULL;
	for (BYTE byI=0; byI<byTargetNum; ++byI)
	{
		pkPacket->Pop(kTargetGuid);
		pkPacket->Pop(bySphereIndex);
		pkTarget = PgObjectMgr::GetUnit(kTargetGuid);
		if (pkTarget != NULL)
		{
			if ( (true == bDamageAction) && (kCheckGuid != pkTarget->Caller()) )
			{
				if (PgGround::ms_kAntiHackCheckVariable.bUse_Projectile)
				{
					PgPlayer* pkPlayer = dynamic_cast<PgPlayer*>(pkSendUnit);
					if(pkPlayer)
					{
						bHackingUser = true;

						// 이거 해커다
						BM::vstring kLogMsg;
						kLogMsg << __FL__ << _T("[HACKING][Projectile] User[") << pkPlayer->Name() << _T("] GUID[") << pkPlayer->GetID() << _T("] MemberGUID[") << pkPlayer->GetMemberGUID() 
							<< _T("] GroundNo[") << GroundKey().GroundNo() << _T("] HackingType[ProjectileHacking] Action ID : ") << kAction.iActionID;
						//VERIFY_INFO_LOG(false, BM::LOG_LV0, kLogMsg);
						HACKING_LOG(BM::LOG_LV0, kLogMsg);
						if (g_kProcessCfg.RunMode() & CProcessConfig::E_RunMode_Debug)
						{
							pkPlayer->SendWarnMessageStr(kLogMsg);
						}

						if (pkPlayer->SuspectHacking(EAHP_Projectile, PgGround::ms_kAntiHackCheckVariable.sProjectile_AddIndex))
						{
							// SpeedHack이 의심스러우니 강제접속 해제 시킨다.
							BM::Stream kDPacket( PT_A_S_NFY_USER_DISCONNECT, static_cast<BYTE>(CDC_Projectile_Hack) );
							kDPacket.Push( pkPlayer->GetMemberGUID() );
							SendToServer( pkPlayer->GetSwitchServer(), kDPacket );
						}
					}
				}
				// 해킹해도 해킹한 새끼는 공격을 받아야 하니까 Loop를 다 돌아보자
			}
			else
			{
				if ((false == bDamageAction) && (pkCaster->IsUnitType(UT_SUMMONED)))
				{
					//소환체가 발사체를 발사한 경우 어떻게 할껀가?
					//PVP에서는 소환체가 유저를 공격할 수 있는데 해킹 처리를 어떻게 할것인지;;
				}
				else if ((false == bDamageAction) && (true == PgGround::ms_kAntiHackCheckVariable.bUse_Projectile))
				{
					// Player(or Entity) 가 다른 타겟을 공격한다.. Hacking 검사하자.
					HRESULT hResult = pkCaster->CheckClientProjectile(kAction.iActionID, kAction.iActionInstanceID, static_cast<BYTE>(kAction.uProjectileUID), pkTarget->GetPos(), pkTarget->GetAbil(AT_UNIT_SIZE_XY), (byI==0) ? true : false);

					if (S_OK != hResult)
					{
						if (hResult == E_ANTIHACK_DISTANCE)
						{
							// 거리 검사는 Network Lag 에 따라 발생할 수도 있는 문제 이므로.
							// 해킹으로 간주 하지 않고, 데미지만 주지 않도록 한다.
							return;
						}
						if (hResult == E_ANTIHACK_CANNOTFIND && kAction.iActionID == 102100101)
						{
							// Client 문제인듯, 점프후 내려오면서 궁수기본샷을 쏘면 액션패킷이 안온다.
							return;
						}
						PgPlayer* pkPlayer = dynamic_cast<PgPlayer*>(pkSendUnit);
						if (pkPlayer)
						{
							BM::vstring kLogMsg;
							kLogMsg << __FL__ << "[HACKING][Projectile] User[" << pkPlayer->Name() << "] GUID[" << pkPlayer->GetID() << "] MemberGUID[" << pkPlayer->GetMemberGUID() 
								<< "] GroundNo[" << GroundKey().GroundNo() << "] Cause=" << (hResult-E_FAIL) << ", ActionID=" << kAction.iActionID << ", InstanceID=" << kAction.iActionInstanceID
								<< ", ProjectileID=" << kAction.uProjectileUID;
							//VERIFY_INFO_LOG(false, BM::LOG_LV0, kLogMsg);
							HACKING_LOG(BM::LOG_LV0, kLogMsg);
							if (g_kProcessCfg.RunMode() & CProcessConfig::E_RunMode_Debug)
							{
								pkPlayer->SendWarnMessageStr(kLogMsg);
							}

							if (pkPlayer->SuspectHacking(EAHP_Projectile, PgGround::ms_kAntiHackCheckVariable.sProjectile_AddIndex))
							{
								BM::Stream kDPacket( PT_A_S_NFY_USER_DISCONNECT, static_cast<BYTE>(CDC_Projectile_Hack) );
								kDPacket.Push( pkPlayer->GetMemberGUID() );
								SendToServer( pkPlayer->GetSwitchServer(), kDPacket );
							}
						}
						return;
					}
				}
				kTargetArray.Add(pkTarget);
				// kActionResultVec.GetResult 는 NULL이 아님을 보장.
				PgActionResult* pkAResult = kActionResultVec.GetResult(kTargetGuid, true);
				if(pkAResult)
				{
					pkAResult->SetCollision(bySphereIndex);
				}
			}
		}
	}

	if(bHackingUser)
	{
		// 내가 보낸 패킷에 내가 아닌놈들이 들어있다면 해킹
		// 나를 타겟 리스트에서 제거 했을 경우도 있으니 나를 강제로 세팅해서 맞게 한다.			
		kTargetArray.Add(pkSendUnit);
		PgActionResult* pkAResult = kActionResultVec.GetResult(kCheckGuid, true);
		if(pkAResult)
		{
			pkAResult->SetCollision(0);
		}
	}

	if ( kTargetArray.empty() )
	{
		return;
	}
	
	
	pkCaster->UseRandomSeedType(false);

	// Skill : Target 에 적용시키기
	SActionInfo kActionInfo;
	kActionInfo.byActionParam = ESS_TARGETLISTMODIFY;
	kActionInfo.iActionID = kAction.iActionID;
	kActionInfo.iActionInstanceID = kAction.iActionInstanceID;
	if (FireSkill(pkCaster, kTargetArray, kActionInfo, &kActionResultVec))	// Success
	{
		// Send Broadcasting
		BYTE byResultNum = kActionResultVec.GetValidCount();

		BM::Stream kPPacket(PT_M_C_NFY_PACTION, kAction);
		kActionResultVec.WriteToPacket(kPPacket);
//		kPPacket.Push(pkCaster->LastRandomSeed());
//		kPPacket.Push(pkCaster->RandomSeedCallCounter());
		kPPacket.Push(fLifeTime);

		SendToArea(&kPPacket, pkCaster->LastAreaIndex(), BM::GUID::NullData(), SYNC_TYPE_RECV_ADD, E_SENDTYPE_NONE );
	}

	pkCaster->UseRandomSeedType(true);
}

void PgGround::SendNfyMapLoaded( PgPlayer* pkUser )
{
	BM::Stream kComplete(PT_M_C_NFY_MAPLOADED);//컴플리트
	g_kEventView.WriteToPacket(false, kComplete);

	kComplete.Push(static_cast<DWORD>(GetState()));
	m_kStoneCtrl.WriteToPacket(pkUser->GetID(), kComplete);//컴플리트에 Stone정보 포함
	m_kGroundOwnerInfo.WriteToPacket( kComplete );

	// BigArea의 유닛을 전부 보내 주어야 한다.
	UNIT_PTR_ARRAY kBigAreaUnitArray;
	if ( m_pkBigArea )
	{
		m_pkBigArea->GetUnitList( kBigAreaUnitArray, pkUser, UT_NONETYPE, SYNC_TYPE_SEND_ADD );
	}

	kBigAreaUnitArray.WriteToPacket( kComplete, WT_SIMPLE );

	PgWorldEventMgr::WorldEventWriteToPacket( kComplete );

	PgWEClientObjectServerMgr::WEClientObjectWriteToPacket( kComplete );
	kComplete.Push( static_cast< int >(DynamicGndAttr()) );
	{
		kComplete.Push( m_kContTrigger.size() );
		CONT_GTRIGGER::const_iterator triger_iter = m_kContTrigger.begin();
		while( m_kContTrigger.end() != triger_iter )
		{
			(*triger_iter).second->WriteToPacket(kComplete);
			++triger_iter;
		}
	}
	kComplete.Push( m_kWorldEnvironmentStatus.GetFlag() );
	PU::TWriteTable_AM(kComplete, m_kRealmQuestInfo);

	kComplete.Push( m_kContEmporiaPortal.size() );
	CONT_EMPORIA_PORTAL::const_iterator po_itr = m_kContEmporiaPortal.begin();
	for ( ; po_itr != m_kContEmporiaPortal.end() ; ++po_itr )
	{
		po_itr->second.WriteToPacket_ToClient( kComplete );
	}

	this->WriteToPacket_AddMapLoadComplete( kComplete );

	PgAlramMission &rkAlramMission = pkUser->GetAlramMission();
	if ( PgAlramMission::STATE_PACKET == rkAlramMission.GetState() )
	{
		if ( IsAlramMission() )
		{
			if ( S_OK == m_pkAlramMissionMgr->GetNewAction( pkUser->GetAbil(AT_CLASS), rkAlramMission ) )
			{
				rkAlramMission.WriteToPacket_Client( kComplete );
			}
		}
		else
		{
			rkAlramMission = PgAlramMission();//초기화
		}
	}
	
	pkUser->Send( kComplete, E_SENDTYPE_SELF|E_SENDTYPE_MUSTSEND ); // 전송

	PgSmallArea* pkArea = GetArea( pkUser->LastAreaIndex() );
	if( !pkArea )
	{
		POINT3 const& rkPos = pkUser->GetPos();
		INFO_LOG( BM::LOG_LV0, __FL__ << _T("Can't Find ") << pkUser->Name() << _T("'s SmallArea Index=") << pkUser->LastAreaIndex() << _T("Pos=") << rkPos.x << _T(",") << rkPos.y  << _T(",") << rkPos.z );
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("pkArea is NULL"));
	}

	SendAreaData(pkUser, pkArea, NULL);//지역 정보	

	// 펫의 초기화는 여기서 해주어야지 Owner가 정확히 패킷을 받을 수 있다!!!
	PgPet * pkPet = GetPet( pkUser );
	if ( pkPet )
	{
		if ( !pkPet->CanNfyAddEffect() )
		{
			pkPet->DoEffect();
			pkPet->SetAddPetToOwner();
		}
		
		// Passive skill setting						
		PgActPet_RefreshPassiveSkill kRefreshPassiveSkillAction( this );
		kRefreshPassiveSkillAction.DoAction( pkPet );
	}

	//소환체
	PgSummoned * pkSummoned = NULL;
	VEC_SUMMONUNIT const kContSummonUnit = pkUser->GetSummonUnit();
	for(VEC_SUMMONUNIT::const_iterator c_it=kContSummonUnit.begin(); c_it!=kContSummonUnit.end(); ++c_it)
	{
		pkSummoned = dynamic_cast<PgSummoned*>(GetUnit((*c_it).kGuid));
		if(pkSummoned && !pkSummoned->CanNfyAddEffect() )
		{
			pkSummoned->DoEffect();
			pkSummoned->SetAddSummonedToOwner();
		}

		//소환체 소환사에게 패시브 적용
		PgAction_MapLoaded::RefreshPassiveSkill(pkSummoned, this, dynamic_cast<PgPlayer*>(pkUser));
	}

	BM::Stream kJobSkillPacket;
	JobSkillLocationMgr().WriteToPacketLocation(kJobSkillPacket);
	pkUser->Send( kJobSkillPacket, E_SENDTYPE_SELF|E_SENDTYPE_MUSTSEND );

	pkUser->SetAbil(AT_EVENT_SCRIPT, 0); // 초기화
	pkUser->SetAbil(AT_EVENT_SCRIPT_TIME, 0); // 초기화
	BM::Stream LockPacket(PT_M_C_REQ_UNLOCK_INPUT_EVENT_SCRIPT);
	pkUser->Send(LockPacket, E_SENDTYPE_SELF);
}

BM::GUID const & PgGround::GetFollowingHead(CUnit* pkTail, bool const bGotoEnd, short int sCallDepth)
{
	BM::CAutoMutex kLock(m_kRscMutex);

	if (pkTail == NULL)
	{
		return BM::GUID::NullData();
	}
	PgPlayer* pkPlayer = dynamic_cast<PgPlayer*>(pkTail);
	BM::GUID const & rkHead = pkPlayer->FollowingHeadGuid();
	if (rkHead == BM::GUID::NullData())
	{
		return (sCallDepth == 0) ? BM::GUID::NullData() : pkPlayer->GetID();
	}
	PgPlayer* pkHeadPlayer = dynamic_cast<PgPlayer*>(PgObjectMgr::GetUnit(UT_PLAYER, rkHead));
	if (pkHeadPlayer == NULL)
	{
		pkPlayer->FollowingHeadGuid(BM::GUID::NullData());
		return (sCallDepth == 0) ? BM::GUID::NullData() : pkPlayer->GetID();
	}
	if (bGotoEnd)
	{
		if (sCallDepth < MAX_FOLLOWING_MODE_LENGTH)
		{
			return GetFollowingHead(pkHeadPlayer, bGotoEnd, sCallDepth+1);
		}
		INFO_LOG(BM::LOG_LV0, __FL__<<L"Folling Length to long CurrentLength["<<sCallDepth<<L"]");
	}
	return (sCallDepth == 0) ? BM::GUID::NullData() : pkPlayer->GetID();
}

int PgGround::GetUnitAbil(BM::GUID const & rkGuid, WORD const wType)
{
	BM::CAutoMutex kLock( m_kRscMutex );

	CUnit const* pkUnit = PgObjectMgr::GetUnit(UT_PLAYER, rkGuid);
	if (pkUnit != NULL)
	{
		return pkUnit->GetAbil(wType);
	}
	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return 0"));
	return 0;
}

void PgGround::OrderSyncGameTime(BM::Stream* const pkSendPacket)
{
	BM::CAutoMutex Lock(m_kRscMutex);

	CONT_OBJECT_MGR_UNIT::iterator unit_itr;
	PgObjectMgr::GetFirstUnit(UT_PLAYER, unit_itr);
	CUnit* pkUnit = NULL;
	while ( (pkUnit = PgObjectMgr::GetNextUnit(UT_PLAYER, unit_itr)) != NULL )
	{
		// 모든 유저의 NotifyTime을 초기화 하고 패킷을 다시 보낸다.
		PgPlayer* pkPlayer = dynamic_cast<PgPlayer*>(pkUnit);
		if (pkPlayer != NULL)
		{
			pkPlayer->NotifyTime(0);
			pkPlayer->Send(*pkSendPacket);
		}
	}
}

void PgGround::DequeTargetToUNIT_PTR_ARRAY(CUnit::DequeTarget const &rkDeque, UNIT_PTR_ARRAY& rkArr)
{
	BM::CAutoMutex kLock( m_kRscMutex );
	CUnit::DequeTarget::const_iterator deq_it = rkDeque.begin();
	while(deq_it!=rkDeque.end())
	{
		CUnit* pkFind = GetUnit((*deq_it).kGuid);
		if(pkFind)
		{
			rkArr.Add(pkFind);
		}
		++deq_it;
	}
}

NxShape* PgGround::RayCast(NxRay& rkWorldRay, NxRaycastHit& rkHit, NxReal maxDist, NxU32 hintFlags) const
{ 
	if(fabsf(rkWorldRay.dir.magnitudeSquared()-1)>=1e-4)	//벡터의 길이가 1보타 크면
	{
		rkWorldRay.dir.normalize();
	}
	else
	{
		if ( rkWorldRay.dir.isZero() )
		{
			INFO_LOG(BM::LOG_LV6, __FL__<<" rkWorldRay.dir is Zero!! MapNo : "<<GroundKey().GroundNo()<<" origin X : "<<rkWorldRay.orig.x<<" origin Y : "<<rkWorldRay.orig.y<<" origin Z : "<<rkWorldRay.orig.z);
			return NULL;
		}
	}
		
	return PhysXScene()->GetPhysXScene()->raycastClosestShape(rkWorldRay, NX_STATIC_SHAPES, rkHit, -1, maxDist, hintFlags);;
}

bool PgGround::CheckPathNormal(CUnit* pkUnit, CSkillDef const* pkSkillDef, SActionInfo const& rkAction, float const fErrorDelta)
{
	if(GetUnlockBidirection() & pkUnit->UnitType())
	{
		return true;
	}

	if(pkSkillDef && ESArea_Sphere==pkSkillDef->GetAbil(AT_1ST_AREA_TYPE))	//타겟팅 타입이 구형일 경우 패스노말 체크가 소용없음
	{
		return true;
	}
	NiPoint3 kDir(rkAction.ptDirection.x, rkAction.ptDirection.y, rkAction.ptDirection.z);
	kDir.Unitize();
	NiPoint3 kPathNormal(rkAction.ptPathNormal.x, rkAction.ptPathNormal.y, 0);
	kPathNormal.Unitize();
	float const fAngle = fabs(kDir.Dot(kPathNormal))*90.0f;
	if(fErrorDelta < fAngle)//공격방향과 패스노말이 수직이 아님
	{
		INFO_LOG(BM::LOG_LV5, __FL__<<" Dir and PathNormal is Not Cross. Name : "<<pkUnit->Name()<<" Angle : "<<fAngle);
		return false;
	}

	NiPick kPick;
	kPick.SetTarget(GetPathRoot());
	kPick.SetReturnNormal( true );
	NiPoint3 kOpPathNormal(kPathNormal.x * -1, kPathNormal.y * -1, 0);//클라에서 보내준 패스방향의 역방향으로 쏴보자

	kPick.PickObjects( NiPoint3(rkAction.ptPos.x, rkAction.ptPos.y, rkAction.ptPos.z+25.0f), kOpPathNormal, true );	//클라에서는 25높기때문에
	if ( kPick.GetSize() )
	{
		NiPoint3 const kNiNormal = kPick.GetResults().GetAt(0)->GetNormal();
		if( fErrorDelta>=fabs(90.0f - kNiNormal.Dot(kPathNormal)*90.0f))
		{
			return true;//두 방향이 일치해야 함
		}
		else
		{
			INFO_LOG(BM::LOG_LV5, __FL__<<" Server PathNormal and Client PathNormal is Not SameDir. Name : "<<pkUnit->Name());
		}
	}

	INFO_LOG(BM::LOG_LV5, __FL__<<" Cannot Find PathNormal. Name : "<<pkUnit->Name());
	return false;
}

void PgGround::SetAntiHackVariable()
{
	// ms_kAntiHackCheckActionCount
	PgGround::ms_kAntiHackCheckActionCount.m_bUseAntiHackCheckActionCount = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_ActionCount);

	int iValue = 0;
	float fValue = 0;
	if (S_OK == g_kAntiHackMgr.Locked_GetPolicy_GetValue(EAHP_ActionCount, EHack_CVar_ActionCount_ForcedResultView, iValue))
	{
		PgGround::ms_kAntiHackCheckActionCount.m_bForcedResultView = (0 == iValue) ? false : true;
	}
	else
	{
		PgGround::ms_kAntiHackCheckActionCount.m_bForcedResultView = false;
	}
	if (S_OK == g_kAntiHackMgr.Locked_GetPolicy_GetValue(EAHP_ActionCount, EHack_CVar_ActionCount_ResultToPlayer, iValue))
	{
		PgGround::ms_kAntiHackCheckActionCount.m_bResultToPlayer = (0 == iValue) ? false : true;
	}
	else
	{
		PgGround::ms_kAntiHackCheckActionCount.m_bResultToPlayer = false;
	}
	if (S_OK == g_kAntiHackMgr.Locked_GetPolicy_GetValue(EAHP_ActionCount, EHack_CVar_ActionCount_Use_HackingPoint,iValue))
	{
		PgGround::ms_kAntiHackCheckActionCount.m_bHackingIndex = (0 == iValue) ? false : true;
	}
	else
	{
		PgGround::ms_kAntiHackCheckActionCount.m_bHackingIndex = false;
	}
	g_kAntiHackMgr.Locked_GetPolicy_GetValue(EAHP_ActionCount, EHack_CVar_ActionCount_CheckTime,			PgGround::ms_kAntiHackCheckActionCount.m_iActionCount_CheckTime);
	g_kAntiHackMgr.Locked_GetPolicy_GetValue(EAHP_ActionCount, EHack_CVar_ActionCount_ActionCount,			PgGround::ms_kAntiHackCheckActionCount.m_iCheckCountSum);
	PgGround::ms_kAntiHackCheckActionCount.m_iActionCount_CheckTime_Mutiflier = static_cast<int>(g_kAntiHackMgr.Locked_GetPolicy_IndexMutiflier(EAHP_ActionCount));
	PgGround::ms_kAntiHackCheckActionCount.m_iAddHackingPoint = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_ActionCount);

	// PgPlayer::m_sMaxHackIndex
	PgPlayer::m_sMaxHackIndex.resize(EAHP_POLICY_MAX+1);
	for (int i = 1; i <= EAHP_POLICY_MAX; ++i)
	{
		PgPlayer::m_sMaxHackIndex[i] = g_kAntiHackMgr.Locked_GetPolicy_MaxHackIndex(static_cast<EAntiHack_Policy>(i));
	}

	// ms_kAntiHackCheckVariable
	PgGround::ms_kAntiHackCheckVariable.bUse_GameTimeOver = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_CheckGameTimeOver);
	PgGround::ms_kAntiHackCheckVariable.sGameTimeOver_AddIndex = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_CheckGameTimeOver);

	PgGround::ms_kAntiHackCheckVariable.bUse_GameTimeUnder = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_CheckGameTimeUnder);
	PgGround::ms_kAntiHackCheckVariable.sGameTimeUnder_AddIndex = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_CheckGameTimeUnder);

	PgGround::ms_kAntiHackCheckVariable.bUse_MaxTarget = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_MaxTarget);
	PgGround::ms_kAntiHackCheckVariable.sMaxTarget_AddIndex = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_MaxTarget);

	PgGround::ms_kAntiHackCheckVariable.bUse_SkillRange = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_SkillRange);
	PgGround::ms_kAntiHackCheckVariable.sSkillRange_AddIndex = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_SkillRange);

	PgGround::ms_kAntiHackCheckVariable.bUse_MoveSpeed = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_MoveSpeed);
	PgGround::ms_kAntiHackCheckVariable.sMoveSpeed_AddIndex = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_MoveSpeed);
	g_kAntiHackMgr.Locked_GetPolicy_GetValue(EAHP_MoveSpeed, EHack_CVar_MoveSpeed_BoundRate, PgGround::ms_kAntiHackCheckVariable.fMoveSpeed_BoundRate);
	g_kAntiHackMgr.Locked_GetPolicy_GetValue(EAHP_MoveSpeed, EHack_CVar_MoveSpeed_HackingCounter, PgGround::ms_kAntiHackCheckVariable.sMoveSpeed_HackingCount);

	PgGround::ms_kAntiHackCheckVariable.bUse_Projectile = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_Projectile);
	PgGround::ms_kAntiHackCheckVariable.sProjectile_AddIndex = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_Projectile);

	PgGround::ms_kAntiHackCheckVariable.bUse_OpenMarket = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_OpenMarket);
	PgGround::ms_kAntiHackCheckVariable.sOpenMarket_AddIndex = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_OpenMarket);

	PgGround::ms_kAntiHackCheckVariable.bUse_CashShop = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_CashShop);
	PgGround::ms_kAntiHackCheckVariable.sCashShop_AddIndex = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_CashShop);

	PgGround::ms_kAntiHackCheckVariable.bUse_NPCRange = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_NPCRange);
	PgGround::ms_kAntiHackCheckVariable.sNPCRange_AddIndex = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_NPCRange);

	PgGround::ms_kAntiHackCheckVariable.bUse_ClientNotify = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_ClientNotify);
	PgGround::ms_kAntiHackCheckVariable.sClientNotify_AddIndex = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_ClientNotify);

	PgGround::ms_kAntiHackCheckVariable.bUse_AntiMacro = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_AntiMacro);
	PgGround::ms_kAntiHackCheckVariable.sAntiMacro_AddIndex = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_AntiMacro);

	PgGround::ms_kAntiHackCheckVariable.bUse_HyperMove = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_HyperMove);
	PgGround::ms_kAntiHackCheckVariable.sHyperMove_WrongGuid_AddIndex = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_HyperMove);
	g_kAntiHackMgr.Locked_GetPolicy_GetValue(EAHP_HyperMove, EHack_CVar_HyperMove_WrongDistance_HackIndex_Add, PgGround::ms_kAntiHackCheckVariable.sHyperMove_WrongDistance_AddIndex);

	PgGround::ms_kAntiHackCheckVariable.bUse_Blowup = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_Blowup);
	PgGround::ms_kAntiHackCheckVariable.sBlowup_AddIndex = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_Blowup);

	PgGround::ms_kAntiHackCheckVariable.bUse_RandomSeedCallCounter = g_kAntiHackMgr.Locked_GetPolicy_Enabled(EAHP_RandomSeedCallCounter);
	PgGround::ms_kAntiHackCheckVariable.sRandomSeedCallCounter_AddHackIndex = g_kAntiHackMgr.Locked_GetPolicy_IndexAdd(EAHP_RandomSeedCallCounter);
	g_kAntiHackMgr.Locked_GetPolicy_GetValue(EAHP_RandomSeedCallCounter, EHack_CVar_RandomSeedCallCounter_CheckValue, PgGround::ms_kAntiHackCheckVariable.iRandomSeedCallCounter_CheckValue);

}

void PgGround::GetClinetProjectileInfo(CUnit* const pkCaster, SActionInfo const & rkAction, CSkillDef const* pkSkillDef, SClientProjectile & kInfo) const
{
	kInfo.ptFirePos = pkCaster->GetPos();
	kInfo.ptDirection = rkAction.ptDirection;
	kInfo.iActionID = rkAction.iActionID;
	switch (rkAction.iActionID)
	{
	case 104301101:	// a_Gimmlet (예외코드), 클라이언트 수정후 이부분 삭제
	case 104301102:
	case 104301103:
	case 104301104:
	case 104301105:
		{
			kInfo.byMaxTargetPerProjectile = 20;
			kInfo.fDmgRangeQ *= 1.7f;
		}break;
	default:
		{
			kInfo.byMaxTargetPerProjectile = 1;
		}break;
	}

	// 여기부터는 스킬마다 설정해 주어야 할 값
	kInfo.dwExpireTime = BM::GetTime32() + 15000;	// 하드코딩...최대값...
	kInfo.byMaxProjectile = std::max(1, pkSkillDef->GetAbil(AT_PROJECTILE_NUM));
	// Range값은 외부에서 세팅한다.
	//kInfo.fDmgRangeQ = pow(iSkillRange, 2) * 1.5;
	PgPlayer* pkPlayer = dynamic_cast<PgPlayer*>(pkCaster);
	if (pkPlayer)
	{
		int iAddedTarget = 0;
		int iSkillindex = 0;
		PgMySkill* const pkPlayerSkill = pkPlayer->GetMySkill();
		GET_DEF(CSkillDefMgr, kSkillDefMgr);
		while(CHILD_SKILL_MAX > iSkillindex)
		{
			//영향 받는 베이스 스킬
			int const iChildBaseSkillNo = pkSkillDef->GetAbil(AT_CHILD_SKILL_NUM_01 + iSkillindex);
			if(0 < iChildBaseSkillNo)
			{
				if(pkPlayerSkill)
				{
					//해당 스킬의 실제 레벨에 해당되는 스킬을 얻어 온다.
					int const iLearnedChildSkillNo = pkPlayerSkill->GetLearnedSkill(iChildBaseSkillNo);
					if(0 < iLearnedChildSkillNo)
					{
						CSkillDef const* pkLearnedSkillDef = kSkillDefMgr.GetDef(iLearnedChildSkillNo);
						if (pkLearnedSkillDef)
						{
							iAddedTarget += pkLearnedSkillDef->GetAbil(AT_PROJECTILE_NUM);						
						}
					}
				}
			}
			else
			{
				break;
			}
			++iSkillindex;
		}
		if (iAddedTarget > 0)
		{
			kInfo.byMaxProjectile = iAddedTarget;
		}
	}
	if (0 < pkSkillDef->GetAbil(AT_PENETRATION_USE_TYPE))	// 관통 사용하는가?
	{
		kInfo.byMaxTargetPerProjectile += pkCaster->GetAbil(AT_PENETRATION_COUNT);
		kInfo.fDmgRangeQ *= 3.0f;	// 관통관련 거리 버그 있다..(클라이언트 수정 필요)
	}

	switch (rkAction.iActionID)
	{
	case 110003001:	// a_HE Granade
	case 110003002:
	case 110003003:
	case 110003004:
	case 110003005:
		{
			kInfo.fDmgRangeQ *= 6.0f;
		}break;
	default:
		{
		}break;
	}
}

void PgGround::SetChangeGroundOwnerInfo( SGroundOwnerInfo const &kInfo, bool const bBroadCast )
{
	if ( kInfo != m_kGroundOwnerInfo )
	{
		m_kGroundOwnerInfo = kInfo;
		if ( true == bBroadCast )
		{
			BM::Stream kPacket( PT_M_C_NFY_GROUNDOWNER_INFO );
			m_kGroundOwnerInfo.WriteToPacket( kPacket );
			Broadcast( kPacket );
		}

		// 권한을 체크하여 쫒아내야 한다.
		std::list< PgPlayer * >	kOutPlayerList;

		{
			PgPlayer* pkPlayer = NULL;
			CONT_OBJECT_MGR_UNIT::iterator kItor;
			PgObjectMgr::GetFirstUnit(UT_PLAYER, kItor);
			pkPlayer = dynamic_cast<PgPlayer*> (PgObjectMgr::GetNextUnit(UT_PLAYER, kItor));
			while ( pkPlayer )
			{
				if ( !this->IsAccess(pkPlayer) )
				{
					kOutPlayerList.push_back( pkPlayer );
				}

				pkPlayer = dynamic_cast<PgPlayer*>(PgObjectMgr::GetNextUnit(UT_PLAYER, kItor));
			}
		}

		std::list< PgPlayer * >::iterator player_itr = kOutPlayerList.begin();
		for ( ; player_itr != kOutPlayerList.end() ; ++player_itr )
		{
			this->RecvRecentMapMove( *player_itr );
		}
	}
}

void PgGround::CheckEffectUser(CUnit* pkUnit)
{
	if( this->GetAttr() & GATTR_MARRY )
	{
		// Center로 가서 내가 결혼 하는지 체크를 해서 복장 교체를 시도해 보자.
		BM::Stream kPacket(PT_C_M_REQ_MARRY_COMMAND, static_cast<BYTE>(MC_EffectCheck));
		kPacket.Push(pkUnit->GetID());
		kPacket.Push(GroundKey());
		SendToCenter(kPacket);
	}
	/*else
	{
		int iEffectNo = 0;
		if( GWL_MALE == pkUnit->GetAbil(AT_GENDER) )
		{
			iEffectNo = m_kMarryMgr.GetEffectMALE();
		}
		else
		{
			iEffectNo = m_kMarryMgr.GetEffectFEMALE();
		}
		CEffect const* pkEffect = pkUnit->GetEffect(iEffectNo, true);
		if(NULL != pkEffect)
		{
			if( 0 < iEffectNo )
			{
				pkUnit->DeleteEffect(iEffectNo);
			}
		}
	}*/
}

void PgGround::HiddenMapCheck(CUnit* pkUnit)
{
	if( this->GetAttr() & GATTR_HIDDEN_F )
	{
		PgPlayer *pkPlayer = dynamic_cast<PgPlayer*>(pkUnit);
		if( pkPlayer )
		{
			int const iGroundNo = GetGroundNo();

			if( 0 != iGroundNo )
			{
				const CONT_DEFMAP* pkContDefMap = NULL;
				g_kTblDataMgr.GetContDef(pkContDefMap);

				if(!pkContDefMap)
				{
					INFO_LOG(BM::LOG_LV0, __FL__ << L"Cannot find ContDefMap");
					return;
				}

				CONT_DEFMAP::const_iterator itor = pkContDefMap->find(iGroundNo);
				if (itor == pkContDefMap->end())
				{
					INFO_LOG(BM::LOG_LV0, __FL__ << L"Cannot find DefMap MapNo[" << iGroundNo << "]" );
					return;
				}

				const TBL_DEF_MAP& rkDefMap = itor->second;
				if( false == pkPlayer->GetHiddenOpen()->IsComplete(rkDefMap.sHiddenIndex) )
				{
					CONT_PLAYER_MODIFY_ORDER kCont;

					kCont.push_back(SPMO(IMET_COMPLETE_HIDDEN_OPEN, pkPlayer->GetID(), SPMOD_Complete_HiddenOpen(rkDefMap.sHiddenIndex, 1)));

					PgAction_ReqModifyItem kItemModifyAction(CAE_HiddenOpen, GroundKey(), kCont,BM::Stream(),true);

					if( !pkUnit )
					{
						return;
					}

					kItemModifyAction.DoAction(pkUnit, NULL);
				}
			}
		}
	}
}

bool PgGround::PickUpGroundBox(CUnit* pkUnit, BM::GUID const& rkGuid, CUnit* pkLooter)
{
	CUnit *pkTargetUnit = PgObjectMgr::GetUnit(UT_GROUNDBOX, rkGuid);
	if( pkTargetUnit )
	{
		PgAction_PickUpItem kPickUpAction( this, this->m_kLocalPartyMgr, pkLooter );
		bool const bPickItem = kPickUpAction.DoAction( pkUnit, pkTargetUnit);
		if( true == bPickItem )
		{
			this->ReleaseUnit( pkTargetUnit, false, false );//지워
			return true;
		}
	}

	return false;
}

void PgGround::GetStatisticsPlayTime(__int64 i64Now, SMapPlayTime& rkOut)
{
	BM::CAutoMutex kLock( m_kRscMutex );

	// 현재 접속중인 유저의 Playtime 을 합산
	CUnit *pkUnit = NULL;
	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr::GetFirstUnit(UT_PLAYER, kItor);
	while((pkUnit = PgObjectMgr::GetNextUnit(UT_PLAYER, kItor)) != NULL)
	{
		PgPlayer const* pkPlayer = dynamic_cast<PgPlayer*>(pkUnit);
		if (pkPlayer != NULL)
		{
			__int64 i64Enter = i64Now - std::max<__int64>(pkPlayer->GroundEnterTimeSec(), LastPlayTimeCalculateTime());
			m_kPlayTime.iPlayTime += i64Enter;
		}
	}

	rkOut = PlayTime();

	LastPlayTimeCalculateTime(i64Now);
	m_kPlayTime.Clear();
}

void PgGround::AddEffectToAllPlayer(int const iEffectNo)
{
	BM::CAutoMutex kLock( m_kRscMutex );

	SEffectCreateInfo kCreate;
	kCreate.eType = EFFECT_TYPE_NORMAL;
	kCreate.iEffectNum = iEffectNo;
	PgGroundUtil::SetActArgGround(kCreate.kActArg, this);
	kCreate.eOption = SEffectCreateInfo::ECreateOption_CallbyServer;

	CUnit *pkUnit = NULL;
	CONT_OBJECT_MGR_UNIT::iterator kItor;
	PgObjectMgr::GetFirstUnit(UT_PLAYER, kItor);
	while((pkUnit = PgObjectMgr::GetNextUnit(UT_PLAYER, kItor)) != NULL)
	{
		PgPlayer* pkPlayer = dynamic_cast< PgPlayer* >(pkUnit);
		if( pkPlayer != NULL )
		{
			pkPlayer->AddEffect(kCreate);
		}
	}
}

int PgGround::GetMapAbil(WORD const wType)
{
	// lock 없음
	// 만약 외부 개체가 호출하려 한다면(=public 함수) lock 을 해주어야 한다.
	CONT_MAPABIL::const_iterator itor_abil = m_kContMapAbil.find(wType);
	if (itor_abil != m_kContMapAbil.end())
	{
		return (*itor_abil).second;
	}

	GET_DEF(PgDefMapMgr, kDefMap);
	int iValue = kDefMap.GetAbil(GroundKey().GroundNo(), wType);
	m_kContMapAbil.insert(std::make_pair(wType, iValue));
	return iValue;
}

void PgGround::SetEventQuest(PgEventQuest const & rkNewEventQuest)
{
	BM::CAutoMutex kLock( m_kRscMutex );
	m_kEventQuest = rkNewEventQuest;
}

void PgGround::OnPT_T_C_NFY_MARRY(EMarryState const eCommandType, BM::Stream *const pkPacket)
{
	BM::CAutoMutex kLock(m_kRscMutex);
	
	
	switch( eCommandType )
	{
	case EM_MONSTER:
		{
			int iMonsterNo = 0;
			int iMonsterCount = 0;
			BM::GUID kCasterGuid;
			SGroundKey kGndKey;

			pkPacket->Pop( iMonsterNo );
			pkPacket->Pop( iMonsterCount );
			pkPacket->Pop( kCasterGuid );
			pkPacket->Pop( kGndKey );

			if(iMonsterCount < 1 )
			{
				LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
				break;
			}					

			POINT3 kCurPos1(-50, 161, 1540);
			POINT3 kCurPos2(435, 182, 1540);

			BM::GUID kMonsterGuid;
			for( int i=0; i<iMonsterCount; ++i)
			{
				int const iSpreadRange = 200;
				int m_iLength = __max(2, iSpreadRange);
				int x = BM::Rand_Range(0, m_iLength);
				int y = BM::Rand_Range(0, m_iLength);
				int const iRandScaleX = (BM::Rand_Index(2) == 0) ? x : x*-1;
				int const iRandScaleY = (BM::Rand_Index(2) == 0) ? y : y*-1;

				POINT3 kRegenPos;
				kRegenPos = (BM::Rand_Index(2) == 0) ? kCurPos1 : kCurPos2;
				kRegenPos.x = kRegenPos.x + iRandScaleX;
				kRegenPos.y = kRegenPos.y + iRandScaleY;
				TBL_DEF_MAP_REGEN_POINT kRegenInfo;
				kRegenInfo.iMapNo = GetGroundNo();
				kRegenInfo.pt3Pos = kRegenPos;

				if (E_FAIL == InsertMonster( kRegenInfo, iMonsterNo, kMonsterGuid ))
				{
					LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
					break;
				}
			}
		}break;
	case EM_NPCTALK:
	case EM_MARRY_ACTION:
	case EM_ACTION:
		{
			if ( pkPacket )
			{
				BM::Stream kCenterPacket;
				kCenterPacket.Push( *pkPacket );
				SendToCenter(kCenterPacket);
			}
		}break;
	case EM_NOTICE:
		{
			VERIFY_INFO_LOG(false, BM::LOG_LV3, __FL__ << _T("[EM_NOTICE] Cannot handle this type command"));
		}break;
	case EM_MARRY:
		{
			BM::GUID kGuid;
			BM::GUID kCoupleGuid;
			SGroundKey kGndKey;

			pkPacket->Pop( kGuid );
			pkPacket->Pop( kCoupleGuid );
			pkPacket->Pop( kGndKey );

			CUnit * pkUnit = GetUnit(kGuid);;
			if(NULL == pkUnit)
			{
				break;
			}

			if( kCoupleGuid == pkUnit->GetCoupleGuid() )
			{
				CUnit * pkCoupleUnit = GetUnit(kCoupleGuid);;
				if(NULL == pkCoupleUnit)
				{
					break;
				}

				BM::GUID kMineGuid = kGuid;
				bool bSayYes = true;
				int const iQuestID = 588;
				int const iSkillNo = 90000002;

				BM::Stream kPacket(PT_C_N_REQ_COUPLE_COMMAND, pkUnit->GetID());
				kPacket.Push( (BYTE)CC_Ans_SweetHeart_Complete );
				kPacket.Push( kCoupleGuid );
				kPacket.Push( bSayYes );
				kPacket.Push( iQuestID );
				kPacket.Push( iSkillNo );
				SendToCoupleMgr(kPacket);
			}
		}break;
	default:
		{
			VERIFY_INFO_LOG(false, BM::LOG_LV5, __FL__ << _T("unhandled Marry Commandtype =") << eCommandType);
		}break;
	}

}

CUnit* PgGround::CreateGuardianEntity(CUnit* pkCaller, SCreateEntity* pkCreateInfo, LPCTSTR lpszName, bool bSyncUnit, int const iStartActionID)
{
	BM::CAutoMutex kLock( m_kRscMutex );

    if(!pkCreateInfo)
    {
        VERIFY_INFO_LOG(false, BM::LOG_LV0, __FL__<<L"CreateEntity NULL Data");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
        return NULL;
    }

	PgEntity *pkEntity = dynamic_cast<PgEntity*>(g_kTotalObjMgr.CreateUnit(UT_ENTITY, pkCreateInfo->kGuid));
	if (pkEntity == NULL)
	{
		INFO_LOG(BM::LOG_LV0, __FL__<<L"Cannot CreateGuardianEntity Guid["<<pkCreateInfo->kGuid<<L"]");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return NULL"));
		return NULL;
	}

	SEntityInfo kInfo(pkCreateInfo->kGuid, pkCreateInfo->kClassKey);
	kInfo.bSyncUnit = bSyncUnit;
	kInfo.bEternalLife = pkCreateInfo->bEternalLife;
    kInfo.iTunningNo = pkCreateInfo->iTunningNo;
    kInfo.iTunningLevel = pkCreateInfo->iTunningLevel;

	Direction eFrontDir = DIR_DOWN;
	if ( pkCaller )
	{
		kInfo.kCaller = pkCaller->GetID();
		kInfo.kCallerClassKey.iClass = pkCaller->GetAbil(AT_CLASS);
		kInfo.SetAbil(AT_TEAM, pkCaller->GetAbil(AT_TEAM));
		kInfo.SetAbil(AT_OWNER_TYPE, pkCaller->GetAbil(AT_OWNER_TYPE));
		kInfo.SetAbil(AT_CALLER_TYPE, pkCaller->UnitType());
		kInfo.SetAbil(AT_CALLER_LEVEL, pkCaller->GetAbil(AT_LEVEL));
		kInfo.SetAbil(AT_ENABLE_CHECK_ATTACK, pkCaller->GetAbil(AT_ENABLE_CHECK_ATTACK));
		kInfo.SetAbil(AT_ENTITY_TYPE, ENTITY_GUARDIAN);
				
		if ( 0 < pkCaller->GetAbil(AT_USENOT_SMALLAREA) )
		{// Caller가 BigArea몬스터이면 소환물도 BigArea로 들어가야 한다.
			kInfo.SetAbil( AT_USENOT_SMALLAREA, 1 );
		}
		if( 0 < pkCaller->GetAbil(AT_MON_ENCHANT_LEVEL) )
		{
			kInfo.SetAbil(AT_MON_ENCHANT_LEVEL, pkCaller->GetAbil(AT_MON_ENCHANT_LEVEL));
		}
		kInfo.SetAbil(AT_OFFENCE_ENCHANT_LEVEL, pkCaller->GetAbil(AT_OFFENCE_ENCHANT_LEVEL));
		kInfo.SetAbil(AT_DEFENCE_ENCHANT_LEVEL, pkCaller->GetAbil(AT_DEFENCE_ENCHANT_LEVEL));

		eFrontDir = pkCaller->FrontDirection();
	}
	else
	{
		kInfo.SetAbil(AT_OWNER_TYPE, UT_MONSTER);
		kInfo.SetAbil(AT_CALLER_TYPE, UT_MONSTER);
		kInfo.SetAbil(AT_CALLER_LEVEL, 0);
		kInfo.SetAbil(AT_ENTITY_TYPE, ENTITY_GUARDIAN);
	}
	
	if ( SUCCEEDED(pkEntity->Create( &kInfo )) )
	{
		if ( lpszName )
		{
			pkEntity->Name( lpszName );
		}
		pkEntity->SetPos( pkCreateInfo->ptPos );
		pkEntity->SetState(US_IDLE);
		pkEntity->LastAreaIndex( PgSmallArea::NONE_AREA_INDEX );
		pkEntity->FrontDirection( eFrontDir );
        pkEntity->LifeTime( pkCreateInfo->iLifeTime );
		if(iStartActionID)
		{
			pkEntity->ActionID(iStartActionID);
		}

		if ( !pkCaller || pkCaller->AddSummonUnit( pkEntity->GetID(), pkCreateInfo->kClassKey.iClass, PgGroundUtil::GetSummonOptionType(pkCreateInfo->bUniqueClass), GetMaxSummonUnitCount(pkCaller)) )
		{
			if ( GetAttr() & GATTR_MISSION )
			{
				if(PgMissionGround * pkMissionGround = dynamic_cast<PgMissionGround*>(this) )
				{
					//전략모드에서 전체 가디언 공격력 상승 스킬을 배운 경우

					CONT_DEFENCE_SKILL kCont;
					pkMissionGround->GetContDefenceMissionSkill(kCont);

					CONT_DEFENCE_SKILL::const_iterator team_it = kCont.find(pkCaller->GetAbil(AT_TEAM));
					if(kCont.end() != team_it)
					{
						GET_DEF(CSkillDefMgr, kSkillDefMgr);
						GET_DEF(CEffectDefMgr, kEffectDefMgr);

						typedef std::map<int, int> CONT_INT;
						CONT_INT kContData;
						int iApplyEffect = 0;
						CONT_SET_DATA::const_iterator learn_it = team_it->second.begin();
						while (learn_it!=team_it->second.end())
						{
							if(CSkillDef const* pkSkill = kSkillDefMgr.GetDef((*learn_it))) /*No Block*/
							if(CEffectDef const* pkEffectDef = kEffectDefMgr.GetDef(pkSkill->GetEffectNo())) /*No Block*/
							if(DS_ADD_PC_ATTACK == pkEffectDef->GetAbil(AT_USE_ITEM_CUSTOM_TYPE)) /*No Block*/
							if(int const iGuardianEffect = pkSkill->GetAbil(AT_EFFECTNUM1))
							{
								int const iBasic = GET_BASICSKILL_NUM(iGuardianEffect);
								std::pair<CONT_INT::iterator, bool> kRet = kContData.insert(std::make_pair(iBasic,iGuardianEffect));
								if(false==kRet.second)
								{
									if(kRet.first->second<iGuardianEffect)
									{
										kRet.first->second = iGuardianEffect;
									}
								}
							}
							++learn_it;
						}

						for(CONT_INT::const_iterator c_it=kContData.begin(); c_it!=kContData.end(); ++c_it)
						{
							PgGroundUtil::InsertEffectAbil(pkEntity, (*c_it).second);
						}
					}
				}
			}

			AddUnit(pkEntity, true);

			//스킬을 사용할때 자식 스킬의 영향을 받는 스킬을 사용해야하는 경우
			//Entity는 Entitny에 직접 세팅해 준다. 
			//Variant의 CS_GetSkillResultDefault 류의 함수 호출 시 Entity는 Caller의 포인터를 얻을 수 없기 때문에
			//Caller 가 영향을 받는 자식 스킬을 배웠는지 알 수가 없다. 
			//Entity에 직접 정보를 넣어서 세팅해야 한다.			
			
			if(pkEntity && pkCaller)
			{
				if(int const iSkillNo = pkEntity->GetAbil(AT_MON_SKILL_01))
				{
					if(0 < iSkillNo)
					{
						GET_DEF(CSkillDefMgr, kSkillDefMgr);
						CSkillDef const* pkSkill = kSkillDefMgr.GetDef(iSkillNo);
						if(pkSkill)
						{
							if(PgPlayer* pkPlayer = dynamic_cast<PgPlayer*>(pkCaller))
							{
								int iSkillindex = 0;
								while(CHILD_SKILL_MAX > iSkillindex)
								{
									//영향 받는 베이스 스킬
									int const iChildBaseSkillNo = pkSkill->GetAbil(AT_CHILD_SKILL_NUM_01 + iSkillindex);
									if(0 < iChildBaseSkillNo)
									{
										if(PgMySkill* pkPlayerSkill = pkPlayer->GetMySkill())
										{
											//해당 스킬의 실제 레벨에 해당되는 스킬을 얻어 온다.
											int const iLearnedChildSkillNo = pkPlayerSkill->GetLearnedSkill(iChildBaseSkillNo);
											if(0 < iLearnedChildSkillNo)
											{
												//실제 스킬 번호를 Entity에 세팅한다.
												//Variant의 CS_GetSkillResultDefault 류의 함수가 호출될때 Caller의 포인터를 직접 얻어 올 수 없다.
												pkEntity->SetAbil(AT_CHILD_SKILL_NUM_01 + iSkillindex, iLearnedChildSkillNo);												
											}
										}
									}
									else
									{
										break;
									}
									++iSkillindex;
								}
							}
						}
					}
				}
			}

			return pkEntity;
		}
	}

	g_kTotalObjMgr.ReleaseUnit( dynamic_cast<CUnit*>(pkEntity) );
	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return NULL"));
	return NULL;
}

// 인스턴스 아이템 젠그룹 활성화.
// GenGroup - 10000 : 중립 ( 아무팀이나 먹을 수 있음 ).
// GenGroup - 10001 : 레드팀 ( 레드팀이 먹었을 때만 이펙트 활성화 ).
// GenGroup - 10002 : 블루팀 ( 블루팀이 먹엇을 때만 이펙트 활성화 ).
EOpeningState PgGround::ActivateInstanceItemGenGroup( int const GenGroup, bool const bReset, bool const bOnce, int const Copy)
{
	BM::CAutoMutex Lock( m_kRscMutex );

	SGenGroupKey GenGroupKey;
	GetGenGroupKey(GenGroupKey);

	GET_DEF_CUSTOM(PgGenPointMgr, PgControlDefMgr::EDef_GenPointMgr, GenPointMgr);
	if( false == bReset && true == bOnce )
	{
		ContGenPoint_InstanceItem ContGenPoint;
		if( SUCCEEDED(GenPointMgr.GetGenPoint_Monster( ContGenPoint, GenGroupKey, bReset, GenGroup )) )
		{
			EOpeningState const eRet = InstanceItemGenerate( ContGenPoint, Copy, NULL );

			int Team = GenGroup % 10;
			ContGenPoint_InstanceItem * pContItem = NULL;
			switch( Team )
			{
			case TEAM_NONE:
				{
					pContItem = &m_ContGenPoint_InstanceItem_AnyTeam;
				}break;
			case TEAM_RED:
				{
					pContItem = &m_ContGenPoint_InstanceItem_RedTeam;
				}break;
			case TEAM_BLUE:
				{
					pContItem = &m_ContGenPoint_InstanceItem_BlueTeam;
				}break;
			}

			if(NULL == pContItem)
			{
				VERIFY_INFO_LOG(false, BM::LOG_LV5, __FL__<<L"MapNo["<<GenGroupKey.iMapNo<<L"] Balance["<<GenGroupKey.iBalance<<L"] GenGroup["<<GenGroup<<L"]");
				return E_OPENING_NONE;
			}

			ContGenPoint_InstanceItem::const_iterator c_itor = ContGenPoint.begin();
			while( c_itor != ContGenPoint.end() )
			{
				std::pair<ContGenPoint_InstanceItem::iterator, bool> Ret = (*pContItem).insert( std::make_pair( (*c_itor).first, (*c_itor).second ) );
				if( false == Ret.second )
				{
					OwnChildCont ContChild;
					(*c_itor).second.GetChild(ContChild);
					OwnChildCont::const_iterator it = ContChild.begin();
					while( it != ContChild.end() )
					{
						Ret.first->second.AddChild( (*it) );
						++it;
					}
				}
				++c_itor;
			}
			return eRet;
		}
	}
	else if( bOnce )
	{
		ContGenPoint_InstanceItem ContGenPoint;
		if( SUCCEEDED( GenPointMgr.GetGenPoint_Monster( ContGenPoint, GenGroupKey, bReset, GenGroup ) ) )
		{
			return InstanceItemGenerate(ContGenPoint, Copy, NULL);
		}
	}
	else
	{
		int Team = GenGroup % 10;
		switch( Team )
		{
		case TEAM_NONE:
			{
				if( SUCCEEDED(GenPointMgr.GetGenPoint_Monster( m_ContGenPoint_InstanceItem_AnyTeam, GenGroupKey, bReset, GenGroup )) )
				{
					return InstanceItemGenerate(m_ContGenPoint_InstanceItem_AnyTeam, Copy, NULL);
				}
			}break;
		case TEAM_RED:
			{
				if( SUCCEEDED(GenPointMgr.GetGenPoint_Monster( m_ContGenPoint_InstanceItem_RedTeam, GenGroupKey, bReset, GenGroup )) )
				{
					return InstanceItemGenerate(m_ContGenPoint_InstanceItem_RedTeam, Copy, NULL);
				}
			}break;
		case TEAM_BLUE:
			{
				if( SUCCEEDED(GenPointMgr.GetGenPoint_Monster( m_ContGenPoint_InstanceItem_BlueTeam, GenGroupKey, bReset, GenGroup )) )
				{
					return InstanceItemGenerate(m_ContGenPoint_InstanceItem_BlueTeam, Copy, NULL);
				}
			}break;
		}			
	}
	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return E_OPENING_NONE"));
	return E_OPENING_NONE;
}

EOpeningState PgGround::InstanceItemGenerate(ContGenPoint_InstanceItem & ContGenPoint, int const iCopy, CUnit* pCaller)
{
	BM::CAutoMutex Lock(m_kRscMutex);

	EOpeningState eState = E_OPENING_NONE;
	if( PgGroundUtil::IsBSGround(GetAttr())
		&& false == PgGroundUtil::IsHaveFreePVPAttr(DynamicGndAttr()) )
	{
		return eState;
	}

	int ItemNo;
	BM::GUID ItemGuid;
	ContGenPoint_InstanceItem::iterator gen_point_itor;
	for( gen_point_itor = ContGenPoint.begin() ; gen_point_itor != ContGenPoint.end() ; ++gen_point_itor )
	{
		PgGenPoint & GenPoint = gen_point_itor->second;
		if( GenPoint.CanGen() )
		{
			int _iCopy = iCopy + 1;
			while( _iCopy-- )
			{
				EOpeningState const eTempState = InstanceItemGenerate(GenPoint, ItemNo, ItemGuid, pCaller);
				eState = __max(eTempState, eState);
			}
		}
	}
	return eState;
}

EOpeningState PgGround::InstanceItemGenerate(PgGenPoint & GenPoint, int & ItemNo, BM::GUID & ItemGuid, CUnit * pCaller)
{
	BM::CAutoMutex Lock(m_kRscMutex);

	EOpeningState eState = E_OPENING_NONE;
	if( S_OK == GenPoint.PopMonster( ItemNo ) )
	{
		PgBase_Item InstanceItem;
		if( SUCCEEDED(::CreateSItem(ItemNo, 1, GIOT_FIELD, InstanceItem)) )
		{
			POINT3 GenPos = GenPoint.Info().pt3Pos;

			VEC_GUID OwnerVec;
			PgLogCont LogCont;
			BM::GUID InsertBoxGuid;
			InsertItemBox( GenPoint.Info(), OwnerVec, NULL, InstanceItem, 0i64, LogCont, InsertBoxGuid );
			GenPoint.AddChild( InsertBoxGuid );
			return E_OPENING_READY;
		}
	}
	return E_OPENING_NONE;
}

void PgGround::RemoveInstanceItem(TBL_DEF_MAP_REGEN_POINT const & GenInfo, BM::GUID const & ItemGuid)
{
	BM::CAutoMutex Lock(m_kRscMutex);

	int const Team = GenInfo.iPointGroup % 10;
	ContGenPoint_InstanceItem * pContItem = NULL;
	switch( Team )
	{
	case TEAM_NONE:
		{
			pContItem = &m_ContGenPoint_InstanceItem_AnyTeam;
		}break;
	case TEAM_RED:
		{
			pContItem = &m_ContGenPoint_InstanceItem_RedTeam;
		}break;
	case TEAM_BLUE:
		{
			pContItem = &m_ContGenPoint_InstanceItem_BlueTeam;
		}break;
	}

	if(NULL == pContItem)
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV5, __FL__<<L"MapNo["<<GenInfo.iMapNo<<L"BagControlNo["<<GenInfo.iBagControlNo<<L"] PointGroup["<<GenInfo.iPointGroup<<L"] Team["<<Team<<L"]");
		return;
	}

	ContGenPoint_InstanceItem::iterator gen_point_itor = (*pContItem).find(GenInfo.kPosGuid);
	if( gen_point_itor != (*pContItem).end() )
	{
		PgGenPoint & GenPoint = gen_point_itor->second;
		GenPoint.RemoveChild(ItemGuid);
	}
}

void PgGround::ReserveDeleteInsItem(BM::GUID const & CharGuid, TBL_DEF_MAP_REGEN_POINT const & GenInfo, BM::GUID const & ItemGuid)
{
	BM::CAutoMutex Lock(m_kRscMutex);

	SDeleteReserveInsItemInfo DelInfo;
	DelInfo.GenInfo = GenInfo;
	DelInfo.DelItemGuid = ItemGuid;

	m_ContDeleteReserveInsItem.insert( std::make_pair(CharGuid, DelInfo) );
}

void PgGround::RemoveReserveDeleteInsItem(BM::GUID const & CharGuid)
{
	BM::CAutoMutex Lock(m_kRscMutex);

	CONT_DELETERESERVERINSITEM::iterator iter = m_ContDeleteReserveInsItem.find(CharGuid);
	if( iter != m_ContDeleteReserveInsItem.end() )
	{
		CONT_DELETERESERVERINSITEM::mapped_type const & Element = (*iter).second;

		RemoveInstanceItem(Element.GenInfo, Element.DelItemGuid);

		m_ContDeleteReserveInsItem.erase(iter);
	}
}

void PgGround::UpdateDeleInsItemOwner(BM::GUID const & Looter, BM::GUID const & Droper)
{	// 이전에 아이템을 획득했던 플레이어의 GUID를 새로 아이템을 획득하는 플레이어의 GUID로 교체한다.
	BM::CAutoMutex Lock(m_kRscMutex);

	CONT_DELETERESERVERINSITEM::iterator iter = m_ContDeleteReserveInsItem.find(Droper);
	if( iter != m_ContDeleteReserveInsItem.end() )
	{
		CONT_DELETERESERVERINSITEM::mapped_type const & Element = (*iter).second;

		m_ContDeleteReserveInsItem.erase(iter);

		m_ContDeleteReserveInsItem.insert( std::make_pair(Looter, Element) );
	}
}