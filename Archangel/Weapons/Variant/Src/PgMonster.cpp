#include "StdAfx.h"
#include "Global.h"
#include "PgMonster.h"
#include "lohengrin/dbtables.h"
//#include "MonsterDefMgr.h"
#include "TableDataManager.h"
#include "PgControlDefMgr.h"
#include "PgDefControl.h"

namespace PgMonsterUtil
{
	struct STunningKeyFind
	{
		STunningKeyFind(SMonsterTunningKey const & key)
			:	Key(key)
		{}

		bool operator() (CONT_DEFMONSTERTUNNINGABIL::value_type const &rhs)const
		{
			if( (Key.iNo == rhs.first.iNo)
			&& (Key.iGrade == rhs.first.iGrade)
			&& (Key.iLevel >= rhs.first.iLevel) )
			{
				return true;
			}

			return false;
		}

		SMonsterTunningKey const & Key;
	};
}

PgMonster::PgMonster(void)
{
	m_bSendSyncPacket = false;
	m_kGenInfo.Clear();
//	m_kItemBagCont.clear();
}

PgMonster::~PgMonster(void)
{
}

HRESULT PgMonster::Create(const void* pkInfo)
{
	if(pkInfo == NULL)
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return E_FAIL"));
		return E_FAIL;
	}
	Init();

	SMonsterCreate const *pkCreateInfo = (SMonsterCreate const *)pkInfo;
	TBL_DEF_MAP_REGEN_POINT const *pkMInfo = &(pkCreateInfo->kTable);

	SetID(pkCreateInfo->kGuid);
	SetAbil(AT_CLASS, pkCreateInfo->iMonNo);
	
	GenInfo(*pkMInfo);
	SetPos( m_kGenInfo.pt3Pos );
	SetGenPos(GetPos());
	
	//m_bMoveDir = false;
	m_dwElapsedTimeCheckZone = 0;
	m_dwLastActionTime = 0;

	int const iTunningNo = pkMInfo->iTunningNo;
	int const iGrade = GetAbil(AT_GRADE);
	int const iTunningLv = pkCreateInfo->iTunningLevel;

	SetAbil( AT_MOVE_RANGE, m_kGenInfo.iMoveRange );
	SetCommonAbil();
	SetBasicAbil(pkCreateInfo->iControlID,pkCreateInfo->iWeight, iTunningNo,iGrade,iTunningLv);
	
	SetAbil(AT_MONSTER_TUNNING_NO,iTunningNo);
	SetAbil(AT_MONSTER_TUNNING_GRADE,iGrade);
	SetAbil(AT_MONSTER_TUNNING_USER_LV,iTunningLv);
	SetAbil(AT_MONSTER_TUNNING_WEIGHT, pkCreateInfo->iWeight);
	TunningAbil(iTunningNo, iGrade, iTunningLv);
	SetEliteTunningAbil(pkCreateInfo->iWeight);
	InitEliteAbil();

	SetEnchantGrade(pkCreateInfo->iEnchantGradeNo);

	SetAbil(AT_HP, GetAbil(AT_C_MAX_HP));
//	SetAbil(AT_DP, GetAbil(AT_C_MAX_DP));
	
	GoalPos(POINT3(0, 0, 0));
	//SetWayPoint(0,0);
    SetAbil(AT_WAYPOINT_GROUP,0);
	SetAbil(AT_WAYPOINT_INDEX,0);

	HRESULT hRet = S_OK;
	int iActionID = GetAbil(AT_MANUAL_OPENING);
	int iOpeningDelay = GetAbil(AT_MON_OPENING_TIME);//3000;
	if( 0==iOpeningDelay )
	{
		iOpeningDelay = 3000;
	}
	GET_DEF(CSkillDefMgr, kSkillDefMgr);
	if ( iActionID > 0 )
	{
		const CSkillDef* pkSkillDef = kSkillDefMgr.GetDef(iActionID);
		if ( pkSkillDef )
		{
			iOpeningDelay = __max(pkSkillDef->GetAbil(AT_ANIMATION_TIME),iOpeningDelay);
		}
		hRet = S_MANUAL_OPENING;
		//SetSync(true); AddUnit에서 싱크를 맞추기 때문에 또 보낼 필요가 없음
	}
	else
	{
		GET_DEF(CSkillDefMgr, kSkillDefMgr);
		iActionID = kSkillDefMgr.GetSkillNum(_T("a_opening"));
	}

	SetState(US_OPENING);
	SetDelay(iOpeningDelay);
	ActionID(iActionID);

	m_kName = pkCreateInfo->wstrName;

//	m_iActionNo = 100001 ; // SJY_DEBUG : TODO : UnitState랑 연계해서 자동으로 설정되도록 차후 구현

	// Set Default AI Information
	//	나중에 Monster에 대한 AI정보가 입력되면 입력된 값으로 설정되도록 한다.
	int iValue = GetAbil(AT_AI_TYPE);
	// 라발론 임시

#ifdef LAVALON_AI_DISABLE
	if ( iValue == 4096 )
	{
		iValue = 2;
		SetAbil(AT_AI_TYPE,iValue);
	}
#endif

	m_kAI.SetPattern((iValue>0) ? iValue : 1);
	m_kAI.SetCurrentAction(EAI_ACTION_OPENING);
	for (int i=1; i<EAI_ACTION_MAX; i++)
	{
		iValue = GetAbil(AT_AI_ACTIONTYPE_MIN + i);
		if (iValue != 0)
		{
			m_kAI.AddActionType((EAIActionType)i, iValue);
		}
	}
	return hRet;
}

CONT_DEFMONSTERTUNNINGABIL::mapped_type const * GetContTunningAbilDef(int const iNo, int const iGrade, int const iLv)
{
	if(iNo < 1 || iLv < 1)
	{
		return NULL;
	}

	CONT_DEFMONSTERTUNNINGABIL const * pkCont = NULL;
	g_kTblDataMgr.GetContDef(pkCont);
	if(!pkCont)
	{
		return NULL;
	}

	SMonsterTunningKey kKey(iNo,iGrade,iLv);
	CONT_DEFMONSTERTUNNINGABIL::const_iterator c_iter =
		std::find_if((*pkCont).begin(), (*pkCont).end(), PgMonsterUtil::STunningKeyFind(kKey));
	if((*pkCont).end() == c_iter)
	{
		return NULL;
	}

	return &((*c_iter).second);
}

void PgMonster::SetBasicAbil( int const iControlID, int const iWeight, int const iTunningNo, int const iGrade, int const iTunningLv )
{
	CONT_DEFMONSTERTUNNINGABIL::mapped_type const * pMonsterTunning = GetContTunningAbilDef(iTunningNo,iGrade,iTunningLv);
	CMonsterTunningDefMgr kTunningMgr(pMonsterTunning);

	GET_DEF(CMonsterDefMgr, kMonsterDefMgr)
	CMonsterDef const * pkDef = kMonsterDefMgr.GetDef(GetAbil(AT_CLASS));
	if(NULL == pkDef)
	{
		return;
	}
	PgDefControl<CMonsterDef,PgMonster,CMonsterTunningDefMgr> kDef( iControlID, pkDef, this, iWeight, &kTunningMgr );

	m_kBasic.iMaxHP = kDef.GetAbil(AT_MAX_HP);		// Basic Max HP (DB value)
	m_kBasic.iHPRecoveryInterval = kDef.GetAbil(AT_HP_RECOVERY_INTERVAL);	// Basic HP Recovery Speed
	m_kBasic.sHPRecovery = kDef.GetAbil(AT_HP_RECOVERY);
	m_kBasic.iMaxMP = kDef.GetAbil(AT_MAX_MP);		// Basic Max MP
	m_kBasic.iMPRecoveryInterval = kDef.GetAbil(AT_MP_RECOVERY_INTERVAL);	// Basic MP Recovery Speed
	m_kBasic.sMPRecovery = kDef.GetAbil(AT_MP_RECOVERY);
// 	SetAbil(AT_MAX_DP,kDef.GetAbil(AT_MAX_DP));
// 	SetAbil(AT_DP_RECOVERY_INTERVAL,kDef.GetAbil(AT_DP_RECOVERY_INTERVAL));
// 	SetAbil(AT_DP_RECOVERY,kDef.GetAbil(AT_DP_RECOVERY));
	m_kBasic.sInitStr = kDef.GetAbil(AT_STR);			// Basic Strength
	m_kBasic.sInitInt = kDef.GetAbil(AT_INT);			// Basic Intelligence
	m_kBasic.sInitCon = kDef.GetAbil(AT_CON);			// Basic Constitution
	m_kBasic.sInitDex = kDef.GetAbil(AT_DEX);			// Basic Dexterity
	m_kBasic.sMoveSpeed = kDef.GetAbil(AT_MOVESPEED);		// Basic Move speed
	m_kBasic.sPhysicsDefence = kDef.GetAbil(AT_PHY_DEFENCE);	// Basic Physics Defence
	m_kBasic.sMagicDefence = kDef.GetAbil(AT_MAGIC_DEFENCE);	// Basic Magic Defence
	m_kBasic.sAttackSpeed = kDef.GetAbil(AT_ATTACK_SPEED);		// Basic Attack speed
	m_kBasic.sBlockRate = kDef.GetAbil(AT_BLOCK_SUCCESS_VALUE);		// Basic Block-attack rate
	m_kBasic.sDodgeRate = kDef.GetAbil(AT_DODGE_SUCCESS_VALUE);		// Basic Dodge-attack rate
	m_kBasic.sCriticalRate = kDef.GetAbil(AT_CRITICAL_SUCCESS_VALUE);	// AT_CRITICAL_SUCCESS_VALUE : Basic Critical Rate
	m_kBasic.sCriticalPower = kDef.GetAbil(AT_CRITICAL_POWER);	// AT_CRITICAL_POWER : Basic Critical Power
	m_kBasic.sHitRate = kDef.GetAbil(AT_HIT_SUCCESS_VALUE);
	m_kBasic.iAIType = kDef.GetAbil(AT_AI_TYPE);	// AT_AI_TYPE : AI Type
	SetAbil(AT_HP_GAUGE_TYPE, kDef.GetAbil(AT_HP_GAUGE_TYPE));
	SetAbil(AT_PHY_ATTACK_MAX, kDef.GetAbil(AT_PHY_ATTACK_MAX));	//공격력
	SetAbil(AT_PHY_ATTACK_MIN, kDef.GetAbil(AT_PHY_ATTACK_MIN));
	SetAbil(AT_MAGIC_ATTACK_MAX, kDef.GetAbil(AT_MAGIC_ATTACK_MAX));
	SetAbil(AT_MAGIC_ATTACK_MIN, kDef.GetAbil(AT_MAGIC_ATTACK_MIN));
//	m_kBasic.sInvenSize = kDef.GetAbil(AT_INVEN_SIZE);		// AT_INVEN_SIZE
//	m_kBasic.sEquipsSize = kDef.GetAbil(AT_EQUIPS_SIZE);		// AT_EQUIPS_SIZE
}

void PgMonster::SetCommonAbil()
{
	int const iMonNo = GetAbil(AT_CLASS);
	GET_DEF(CMonsterDefMgr, kMonsterDefMgr)
	const CMonsterDef *pDef = kMonsterDefMgr.GetDef(iMonNo);

	if(pDef)
	{
		m_kCommon.sLevel = pDef->GetAbil(AT_LEVEL);
		m_kCommon.byGender = 0;
		m_kCommon.iRace = pDef->GetAbil(AT_RACE);
	}
	else
	{
		VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T(" pDef is Null") );
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Get MonsterDef Failed!"));
	}
}

void PgMonster::TunningAbil(int const iNo, int const iGrade, int const iLv)
{
	CONT_DEFMONSTERTUNNINGABIL::mapped_type const * pMonsterTunning = GetContTunningAbilDef(iNo,iGrade,iLv);
	if(!pMonsterTunning)
	{
		return;
	}

	CONT_DEFMONSTERABIL const * pkContAbil = NULL;
	g_kTblDataMgr.GetContDef(pkContAbil);
	if(!pkContAbil)
	{
		return;
	}

	for(int i=0; i<MAX_MONSTER_ABIL_ARRAY; ++i)
	{
		CONT_DEFMONSTERABIL::const_iterator c_abil = (*pkContAbil).find(pMonsterTunning->iAbil[i]);
		if((*pkContAbil).end()==c_abil)
		{
			continue;
		}

		for(int j=0; j<MAX_MONSTER_ABIL_ARRAY; ++j)
		{
			CONT_DEFMONSTERABIL::mapped_type const &kAbil = (*c_abil).second;
			int const iType = kAbil.aType[j];
			int const iValue = kAbil.aValue[j];
			switch(iType)
			{
			case AT_EXPERIENCE:
			case AT_MONEY:
			case AT_DIE_EXP:
			case AT_CLASSLIMIT:
				{
					SetAbil64(iType,iValue);
				}break;
			default:
				{
					SetAbil(iType,iValue);
				}break;
			}
		}
	}
}

float GetEliteProbability_FrenzyFire(int const iWeight)
{
	if(iWeight>=3)		return 0.8;

	switch(iWeight)
	{
	case 0: return 2.0f;
	case 1: return 1.4f;
	case 2: return 1.0f;
	}
	return 1.0f;
}

float GetEliteProbability_GroggyMax(int const iWeight)
{
	if(iWeight>=3)		return 1.3f;

	switch(iWeight)
	{
	case 0: return 0.6f;
	case 1: return 0.8f;
	case 2: return 1.0f;
	}
	return 1.0f;
}

float GetEliteProbability_FrenzyRecovery(int const iWeight)
{
	if(iWeight>=3)		return 1.5f;

	switch(iWeight)
	{
	case 0: return 0.5f;
	case 1: return 0.8f;
	case 2: return 1.0f;
	}
	return 1.0f;
}

float GetEliteProbability_GroggyRecovery(int const iWeight)
{
	if(iWeight>=3)		return 1.2f;

	switch(iWeight)
	{
	case 0: return 0.4f;
	case 1: return 0.7f;
	case 2: return 1.0f;
	}
	return 1.0f;
}

void PgMonster::SetEliteTunningAbil(int const iWeight)
{
	int const iMaxGroggy = GetAbil(AT_GROGGY_MAX);
	if( iMaxGroggy )
	{
		SetAbil(AT_FRENZY_R_FIRE,		GetAbil(AT_FRENZY_R_FIRE) * GetEliteProbability_FrenzyFire(iWeight));
		SetAbil(AT_FRENZY_RECOVERY,		GetAbil(AT_FRENZY_RECOVERY) * GetEliteProbability_FrenzyRecovery(iWeight));
		SetAbil(AT_GROGGY_MAX,			GetAbil(AT_GROGGY_MAX) * GetEliteProbability_GroggyMax(iWeight));
		SetAbil(AT_GROGGY_RECOVERY,		GetAbil(AT_GROGGY_RECOVERY) * GetEliteProbability_GroggyRecovery(iWeight));

		int const iMaxHP = GetAbil(AT_C_MAX_HP);
		float const fMaxFrenzy = GetAbil(AT_FRENZY_R_FIRE)/ABILITY_RATE_VALUE_FLOAT;

		if( 0==GetAbil(AT_GROGGY_RECOVERY_INTERVAL) )
		{
			SetAbil(AT_GROGGY_RECOVERY_INTERVAL, 300);
		}
		SetAbil(AT_FRENZY_MAX_FIRE, static_cast<int>(iMaxHP*fMaxFrenzy));
	}
}

void PgMonster::InitEliteAbil()
{
	int const iMaxGroggy = GetAbil(AT_GROGGY_MAX);
	if( iMaxGroggy )
	{
		SetAbil(AT_ELITEPATTEN_STATE, EPS_INIT);
	}
}

void PgMonster::SetEnchantGrade(int const iEnchantGradeNo)
{
	if( iEnchantGradeNo )
	{
		CONT_DEF_MONSTER_ENCHANT_GRADE const* pkDefMonEnchantGrade = NULL;
		CONT_DEFMONSTERABIL const* pkDefMonAbil = NULL;
		g_kTblDataMgr.GetContDef(pkDefMonEnchantGrade);
		g_kTblDataMgr.GetContDef(pkDefMonAbil);

		CONT_DEF_MONSTER_ENCHANT_GRADE::const_iterator find_iter = pkDefMonEnchantGrade->find(iEnchantGradeNo);
		if( pkDefMonEnchantGrade->end() != find_iter )
		{
			CONT_DEF_MONSTER_ENCHANT_GRADE::mapped_type const& rkMonEnchantGrade = (*find_iter).second;
			SetAbil(AT_MON_ENCHANT_GRADE_NO, iEnchantGradeNo);
			SetAbil(AT_MON_ENCHANT_LEVEL, rkMonEnchantGrade.iEnchantLevel);
			for( int iCur = 0; MAX_MONSTER_ENCHANT_ADD_ABIL_COUNT > iCur; ++iCur )
			{
				ApplyEnchantAbil(rkMonEnchantGrade.aiAddAbilNo[iCur], false, pkDefMonAbil);
			}
			for( int iCur = 0; MAX_MONSTER_ENCHANT_SET_ABIL_COUNT > iCur; ++iCur )
			{
				ApplyEnchantAbil(rkMonEnchantGrade.aiSetAbilNo[iCur], true, pkDefMonAbil);
			}
		}
	}
}
void PgMonster::ApplyEnchantAbil(int const iMonAbilNo, bool const bSet, CONT_DEFMONSTERABIL const* pkDefMonAbil)
{
	int const iMonNo = CUnit::GetAbil(AT_CLASS);
	GET_DEF(CMonsterDefMgr, kMonsterDefMgr)
	const CMonsterDef *pkDef = kMonsterDefMgr.GetDef(iMonNo);
	if(!pkDef)
	{
		return;
	}

	CONT_DEFMONSTERABIL::const_iterator abil_iter = pkDefMonAbil->find(iMonAbilNo);
	if( pkDefMonAbil->end() != abil_iter )
	{
		CONT_DEFMONSTERABIL::mapped_type const& rkMonAbil = (*abil_iter).second;
		for( int iAbilCur = 0; MAX_MONSTER_ABIL_ARRAY > iAbilCur; ++iAbilCur )
		{
			WORD const wAbilType = static_cast< WORD >(rkMonAbil.aType[iAbilCur]);
			int const iAbilValue = rkMonAbil.aValue[iAbilCur];
			if( 0 != wAbilType
			&&	0 != iAbilValue )
			{
				if( bSet )
				{
					SetAbil(wAbilType, iAbilValue);
				}
				else
				{
					if( false == CAbilObject::HasAbil(wAbilType)
					&&	0 != pkDef->GetAbil(wAbilType) )
					{
						SetAbil(wAbilType, pkDef->GetAbil(wAbilType)); // Def에만 정의된 어빌은 미리 더해서 셋팅한다
					}
					AddAbil(wAbilType, iAbilValue);
				}
			}
		}
	}
}

int PgMonster::GetAbil(WORD const Type) const
{
	int iValue = 0;
	switch(Type)
	{
	case AT_OWNER_TYPE:
	case AT_CALLER_TYPE:
		{
			return UT_MONSTER;
		}break;
	case AT_MOVE_RANGE:		{ iValue = m_kGenInfo.iMoveRange; }break;
	//case AT_WAYPOINT_INDEX:	{ iValue = m_iWayPointIndex; }break;
	//case AT_WAYPOINT_GROUP:	{ iValue = m_iWayPointGroup; }break;
	case AT_OFFENCE_ENCHANT_LEVEL:
	case AT_DEFENCE_ENCHANT_LEVEL:
		{
			iValue = CUnit::GetAbil(AT_MON_ENCHANT_LEVEL);
		}break;
// 아래는 64bit 어빌
	case AT_EXPERIENCE:
	case AT_MONEY:
	//case AT_DIE_EXP:
	case AT_CLASSLIMIT:
		{
			VERIFY_INFO_LOG( false, BM::LOG_LV0, __FL__ << _T(" Plz Use GetAbil64") );
		}break;
	default:
		{
			iValue = CUnit::GetAbil(Type);
			if (iValue == 0 && !CAbilObject::HasAbil(Type))	// 진짜로 Value==0일때와, 아직 값을 안 읽어서 0 일때를 구별해 주어야 한다.
			{
				int const iMonNo = CUnit::GetAbil(AT_CLASS);
				GET_DEF(CMonsterDefMgr, kMonsterDefMgr)
				const CMonsterDef *pDef = kMonsterDefMgr.GetDef(iMonNo);
				if(pDef)
				{
					// MonsterDef의 경우에는 BasicAbil (ex:AT_MAX_HP) 와 같은 Abil만 들어가 있으므로
					// CalculatedAbil(ex:AT_C_MAX_HP)를 요청하면 BasicAbil로 값을 얻어와야 한다.
					WORD wTemp = Type;
					if (IsCalculatedAbil(Type))
					{
						wTemp = GetBasicAbil(Type);
					}
					iValue = pDef->GetAbil(wTemp);
					// 성능향상을 위해 Caching
					// 코드가 좀 맘에 안되는데 좋은 방법이 없을까?
					// 사실 아래 한줄을 주석 달아도 기능에는 문제가 없다...
					//((CUnit*)this)->SetAbil(Type, iValue);
				}
				else
				{
					VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T(" pDef Is Null") );
					LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Get MonsterDef Failed!"));
				}
			}
		}break;
	}
	return iValue;
}


bool PgMonster::SetAbil(WORD const Type, int const iValue, bool const bIsSend, bool const bBroadcast)
{
	bool bIntercept = true;
	switch(Type)
	{
	case AT_MOVE_RANGE:		{ m_kGenInfo.iMoveRange = iValue; }break;
	//case AT_WAYPOINT_INDEX:
	//	{
	//		m_iWayPointIndex = iValue;
	//	}break;
	//case AT_WAYPOINT_GROUP:
	//	{
	//		m_iWayPointGroup = iValue;
	//	}break;
	case AT_DIE_EXP:
	case AT_CLASSLIMIT:
	case AT_EXPERIENCE:
	case AT_MONEY:
		{
			VERIFY_INFO_LOG( false, BM::LOG_LV0, __FL__ << _T(" int64 can't put on SetAbil(use SetAbil64)") );
		}break;
//	case AT_MAX_DP:
	case AT_C_MAX_HP:
		{
			if ( iValue > 0 )
			{
				SetAbil(AT_ENABLE_AUTOHEAL,AUTOHEAL_MONSTER);
			}
		}// break; // Nothing
	default:
		{
			bIntercept = false;
			CUnit::SetAbil(Type, iValue, bIsSend, bBroadcast);
		}break;
	}

	if(bIntercept)
	{
		DWORD dwSendFlag = 0;
	
		if(bIsSend){dwSendFlag |= E_SENDTYPE_SELF;}
		if(bBroadcast){dwSendFlag |= E_SENDTYPE_BROADCAST;}

		if(dwSendFlag)
		{
			SendAbil((EAbilType)Type, dwSendFlag);
		}

		OnSetAbil(Type, iValue);
	}
	return true;
}

void PgMonster::WriteToPacket(BM::Stream &rkPacket, EWRITETYPE const kWriteType)const
{
	CUnit::WriteToPacket(rkPacket,kWriteType);//몬스터는 무조건 디테일?

	DEFAULT_MONSTER_INFO kDefMonsterInfo;

	kDefMonsterInfo.iMonNo = GetAbil(AT_CLASS);//GUID ID(엑터 -> 모델 GUID)
	kDefMonsterInfo.kGuid = GetID();//자체 고유키.
	kDefMonsterInfo.ptPos = GetPos();//현재 
	kDefMonsterInfo.iState = GetState();
	kDefMonsterInfo.bDir = 0;	// m_bMoveDir값이 없어졌다? / 동기화에 문제 생길까?
	kDefMonsterInfo.sLevel = m_kCommon.sLevel;
	kDefMonsterInfo.iMaxHP = GetAbil(AT_C_MAX_HP);
	kDefMonsterInfo.iHP = GetAbil(AT_HP);
	kDefMonsterInfo.iMaxMP = GetAbil(AT_C_MAX_MP);
	kDefMonsterInfo.iMP = GetAbil(AT_MP);
// 	kDefMonsterInfo.iMaxDP = GetAbil(AT_MAX_DP);
// 	kDefMonsterInfo.iDP = GetAbil(AT_DP);
	kDefMonsterInfo.cDirection = GetAbil(AT_MON_DEFAULT_ANGLE);
	kDefMonsterInfo.iTunningNo = GetAbil(AT_MONSTER_TUNNING_NO);
	kDefMonsterInfo.iTunningGrade = GetAbil(AT_MONSTER_TUNNING_GRADE);
	kDefMonsterInfo.iTunningUserLv = GetAbil(AT_MONSTER_TUNNING_USER_LV);
	kDefMonsterInfo.iEnchantGradeNo = GetAbil(AT_MON_ENCHANT_GRADE_NO);

	rkPacket.Push(kDefMonsterInfo);
	//rkPacket.Push(m_kName);

	rkPacket.Push(ActionID());
	rkPacket.Push(GoalPos());
	rkPacket.Push((BYTE)GetAbil(AT_TEAM));//팀
	rkPacket.Push(GetAbil(AT_DAMAGEACTION_TYPE));
	if( GetAbil(AT_GROGGY_MAX) )
	{
		rkPacket.Push(GetAbil(AT_ELITEPATTEN_STATE));
		rkPacket.Push(GetAbil(AT_MONSTER_TUNNING_WEIGHT));
	}
}

EWRITETYPE PgMonster::ReadFromPacket(BM::Stream &rkPacket)
{
	EWRITETYPE kWriteType = CUnit::ReadFromPacket(rkPacket);
	
	EffectNftChangeAbil();

	DEFAULT_MONSTER_INFO kDefMonsterInfo;
	BYTE byTeam = 0;
	int iDamageActionType = 0;
	int iElitePattenState = 0;
	int iTunningWeight = 0;

	rkPacket.Pop(kDefMonsterInfo);
	//rkPacket.Pop(m_kName);
	rkPacket.Pop(m_kActionID);
	rkPacket.Pop(m_kGoalPos);
	rkPacket.Pop(byTeam);//팀
	rkPacket.Pop(iDamageActionType);
	if( GetAbil(AT_GROGGY_MAX) )
	{
		rkPacket.Pop(iElitePattenState);
		rkPacket.Pop(iTunningWeight);
	}

	SetAbil(AT_CLASS, kDefMonsterInfo.iMonNo);
	SetID(kDefMonsterInfo.kGuid);
	SetPos(kDefMonsterInfo.ptPos);
	SetState((EUnitState)kDefMonsterInfo.iState);
	//m_bMoveDir = kDefMonsterInfo.bDir;
	m_kCommon.sLevel = kDefMonsterInfo.sLevel;
	SetAbil(AT_C_MAX_HP, kDefMonsterInfo.iMaxHP);
	SetAbil(AT_HP, kDefMonsterInfo.iHP);
	SetAbil(AT_C_MAX_MP, kDefMonsterInfo.iMaxMP);
	SetAbil(AT_MP, kDefMonsterInfo.iMP);
// 	SetAbil(AT_C_MAX_DP, kDefMonsterInfo.iMaxDP);
// 	SetAbil(AT_DP, kDefMonsterInfo.iDP);
	SetAbil(AT_MON_DEFAULT_ANGLE, kDefMonsterInfo.cDirection);

	SetBasicAbil();
	SetCommonAbil();

	SetAbil(AT_MONSTER_TUNNING_NO,kDefMonsterInfo.iTunningNo);
	SetAbil(AT_MONSTER_TUNNING_GRADE,kDefMonsterInfo.iTunningGrade);
	SetAbil(AT_MONSTER_TUNNING_USER_LV,kDefMonsterInfo.iTunningUserLv);
	TunningAbil(kDefMonsterInfo.iTunningNo, kDefMonsterInfo.iTunningGrade, kDefMonsterInfo.iTunningUserLv);
	SetEliteTunningAbil(iTunningWeight);
	SetEnchantGrade(kDefMonsterInfo.iEnchantGradeNo);

	SetAbil(AT_TEAM,(int)byTeam);
	SetAbil(AT_DAMAGEACTION_TYPE,iDamageActionType);
	SetAbil(AT_ELITEPATTEN_STATE,iElitePattenState);

	// 클라이언트는 Name을 서버로 받지 말고, 스스로 읽어 오도록 하자.
	GET_DEF(CMonsterDefMgr, kMonsterDefMgr)
	const CMonsterDef *pkDef = kMonsterDefMgr.GetDef(GetAbil(AT_CLASS));
	if (pkDef != NULL)
	{
		std::wstring wName;
		if (g_kTblDataMgr.GetStringName(pkDef->NameNo(), wName))
		{
			Name(wName);
		}
	}
	else
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Get MonsterDef Failed!"));
	}

	if (Name().length() == 0)
	{
		VERIFY_INFO_LOG( false, BM::LOG_LV5, __FL__ << _T(" Monster Name is NULL MonsterID[") << GetAbil(AT_CLASS) << _T("]") );
	}
	return kWriteType;
}

void PgMonster::Invalidate()
{//xxx todo invali 하더라도 nonetype으로 바꾸진 말자
	CUnit::Invalidate();
	m_kGenInfo.Clear();
}

bool PgMonster::IsCheckZoneTime(DWORD dwElapsed)
{
	if ( m_dwElapsedTimeCheckZone > 1000 )
	{
		m_dwElapsedTimeCheckZone = 0;
		return true;
	}
	else
	{
		m_dwElapsedTimeCheckZone += dwElapsed;
	}
	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
	return false;
}

void PgMonster::Init()
{
	CUnit::Init();

	SetTarget(BM::GUID::NullData());
	m_pt3Gen.Clear();
	GoalPos(POINT3(0, 0, 0));
	m_bSendSyncPacket = false;

	m_kGenInfo.Clear();

	m_kAggro.Clear();
//	m_kItemBagCont.clear();
	//m_iWayPointIndex = m_iWayPointGroup = 0;
//	m_kItemBagCont.clear();
	//WayPointIndex(0);
}


// CUnit 으로 이전됨
//bool PgMonster::GetSync()
//{
//	bool bOld = m_bSendSyncPacket;
//	m_bSendSyncPacket = false;
//	return bOld;
//}

/*
bool PgMonster::IsAIType(const EMonsterAIType eMonAIType)const
{
	int iAI = GetAbil(AT_AI_TYPE);

	if(iAI&eMonAIType )
	{
		return true ;
	}
	return false;
}
*/

bool PgMonster::SetState(const EUnitState eState)
{
	EUnitState eOld = GetState();

	switch(eOld)
	{
	case US_DEAD:// Monster 는 한번 죽으면 STATE 값 변경이 불가하다.
		{
			if (0==GetAbil(AT_SKILL_ON_DIE))	//자폭 스킬이 있을 경우 죽고나서도 스킬을 써야 하기 때문에 STATE값을 변경해야 한다. 않좋다;;
			{
				LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
				return false;
			}
		}break;
	case US_DAMAGEDELAY:
	case US_DAMAGEDELAY_NOCHANGE:
		{
			if (eState != US_DEAD && eState != US_NONE)
			{
				LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
				return false;
			}
		}break;
	}
	// Race Condition 문제로 DamageDelay 상태일때 US_ATTACK 같은 상태로 변경되려고 할 수도 있다.
	// 해결방안 1. TickAI 에서 Unit에 대해서 Lock을 건다. <-- Performance 를 생각하면 비추천
	// 해결방안 2. 아주 완벽하지는 않더라도, 상태변환에 대한 우선순위를 두고
	//		이 함수 안에서 우선순위를 검사하여 변경한다.
	if (eState == US_IDLE)
	{
		MoveDir(DIR_NONE);
	}

	if (eState!=eOld)
	{
		m_kFailSkill.clear();
	}
	return CUnit::SetState(eState);
}

__int64 PgMonster::GetAbil64(WORD const eAT)const
{
	__int64 i64Value = CUnit::GetAbil64(eAT);
	if ( 0i64 == i64Value )
	{
		int const iMonNo = m_kCommon.iClass;
		GET_DEF(CMonsterDefMgr, kMonsterDefMgr)
		CMonsterDef const *pDef = kMonsterDefMgr.GetDef(iMonNo);
		if(pDef)
		{
			i64Value = pDef->GetAbil64(eAT);
		}
		else
		{
			VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T(" PgMonster::GetAbil pDef Is Null") );
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Get MonsterDef Failed!"));
		}
	}
	return i64Value;
}

void PgMonster::TunningAbil()
{
}

DWORD PgMonster::GetLastActionTime()
{
	return m_dwLastActionTime;
}

void PgMonster::SetLastActionTime(DWORD dwTime)
{
	m_dwLastActionTime = dwTime;
}

void PgMonster::AddIgnoreTarget(CUnit const* pkUnit, DWORD const dwNow)
{
	if(!pkUnit)
	{
		INFO_LOG(BM::LOG_LV9, __FUNCTION__<<"pkUnit Is Null. Monster Name Is : "<<this->Name());
		return;
	}

	if(!IsIgnoreTarget(pkUnit->GetID()))
	{
		m_kIgnoreTargetList.insert(std::make_pair(pkUnit->GetID(), SIgnoreTarget(pkUnit->GetID(), pkUnit->GetPos(), dwNow)));
	}
}

bool PgMonster::CheckIgnoreTarget(CUnit const* pkUnit, DWORD const dwNow)
{
	IGNORE_TARGET_LIST::iterator target_it = m_kIgnoreTargetList.find(pkUnit->GetID());
	if(target_it == m_kIgnoreTargetList.end())
	{
		return true; //야예 없으니까 true
	}

	SIgnoreTarget const& rkTarget = (*target_it).second;
	if(rkTarget.IsMoved(pkUnit->GetPos())) //1초 동안은 무시
	{
		if(rkTarget.kTime + 3000 < dwNow)
		{
			m_kIgnoreTargetList.erase(target_it);
			return true;
		}
	}
	
	return false;
}

bool PgMonster::IsTarget(CUnit* pkTarget, bool bCheckTargetValid, int iSkillTargetType, CSkillDef const* pkSkillDef, int iDmgCheckTime)
{
	if(pkSkillDef)
	{
		int const iMonNo = pkSkillDef->GetAbil(AT_MON_SKILL_MONSTER_NO);
		if(iMonNo && pkTarget->GetAbil(AT_CLASS) != iMonNo)
		{
			return false;
		}
	}

	if(CUnit::IsTarget(pkTarget, bCheckTargetValid, iSkillTargetType, pkSkillDef ,iDmgCheckTime))
	{
		return !IsIgnoreTarget(pkTarget->GetID());	//무시하는 놈이냐?
	}
	return false;
}
