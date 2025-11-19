#ifndef MAP_MAPSERVER_MAP_GROUND_PGGROUND_H
#define MAP_MAPSERVER_MAP_GROUND_PGGROUND_H

#include "BM/Observer.h"
#include "Lohengrin/GMCommand.h"
#include "Variant/Global.h"
#include "variant/gm_const.h"
#include "Variant/PgAggroMeter.h"
#include "Variant/PgAggroMeterMgr.h"
#include "Variant/PgComboCounter.h"
#include "Variant/PgComboCounterMgr.h"
#include "Variant/PgEventQuestBase.h"
#include "Variant/AlramMissionChecker.h"
#include "Collins/Log.h"
#include "constant.h"
#include "AI/PgAIManager.h"
#include "PgSmallArea.h"
#include "PgGroundResource.h"
#include "PgReqMapMove.h"
#include "PgGenPointMgr.h"
#include "PgLocalPartyMgr.h"
#include "PgLocalVendorMgr.h"
#include "PgUserQuestSessionMgr.h"
#include "PgMarryMgr.h"
#include "PgWorldEnvironmentStatus.h"
#include "Variant/PgHiddenRewordItemMgr.h"
#include "PgEventItemSet.h"
#include "PgDefencePartyMgr.h"
#include "PgJobSkillMgr.h"
#include "Variant/PgJobSkillLocationItem.h"
#include "PgDuelSystem.h"
#include "Variant/PgConstellation.h"

typedef enum eFAKE_REMOVE_TYPE
{
	FRT_NONE = 0,
	FRT_ONLY_HIDE,
	FRT_HIDE_AND_NO_MSG,
	FRT_HIDE_AND_NO_MSG_BUT_MAPMOVE,
}EFAKE_REMOVE_TYPE;

typedef enum eCREATE_HP_TYPE
{
	ECHT_NONE				= 0,
	ECHT_CALLER_HP_RATE		= 1,
	ECHT_ELGA_BONE_MON		= 2,
	ECHT_ELGA_EYE_MON		= 3,
} ECREATE_HP_TYPE;

typedef enum eINSTANCE_ITEM_GEN_GROUP
{
	EIGG_ANY		= 10000,
	EIGG_RED		= 10001,
	EIGG_BULE		= 10002,
	EIGG_END		= 19999,
} EINSTANCEITEM_GEN_GROUP;

namespace PgGroundUtil
{
	inline bool IsVillageGround(T_GNDATTR const& rAttr);
	bool IsCanTalkableRange(CUnit* pkPC, BM::GUID const& rkNpcGuid, CUnit* pkNPC, int const iCurGround, ENpcMenuType const eMenuType, TCHAR const* szFucn, size_t const iLine);
	bool IsCanTalkableRange(CUnit* pkPC, POINT3 const& rkPos, BM::GUID const& rkNpcGuid, CUnit* pkNPC, int const iCurGround, ENpcMenuType const eMenuType, TCHAR const* szFunc, size_t const iLine);

	bool IsNeedNpcTestChangeItemEvent(SItemPos const& rkPos);
	bool IsCallSafe(CUnit * pkUnit,SItemPos const & kSourcePos,SItemPos const & kTargetPos);
	bool IsCanTalkableRange(CUnit* pkPC, BM::GUID const& rkNpcGuid, CUnit* pkNPC, int const iCurGround, ENpcMenuType const eMenuType, TCHAR const* szFunc, size_t const iLine);
	bool IsMyHomeHasFuctionItem(CUnit * pkPlayerUnit,CUnit * pkNpcUnit,EUseItemCustomType const kType);

	enum ESpecialUnitStatusType
	{
		SUST_None					= 0,
		SUST_CashShop				= 1,
		SUST_OpenMarket				= 2,
		SUST_PvPModeSelectting		= 3,
		SUST_HardCoreDungeonVote	= 4,
		SUST_Vendor					= 5,
	};
	typedef std::map< BM::GUID, ESpecialUnitStatusType > ContUnitSpecialStatus;
	typedef std::map<int, size_t> ContAbilValue;

	
	class PgUnitSepcailStatusHandler // 상태값은 양립 못한다. (양립 하려면 컨테이너로 second를 적당히 수정 하시오)
	{
	protected:
		PgUnitSepcailStatusHandler();
		virtual ~PgUnitSepcailStatusHandler();

		ESpecialUnitStatusType EnterSpecStatus(BM::GUID const& rkGuid, ESpecialUnitStatusType const eEnterType, bool const bChange = false );
		bool ChangeSpecStatus( BM::GUID const &rkGuid, ESpecialUnitStatusType const eCheckType, ESpecialUnitStatusType const eChangeType );
		bool LeaveSpecStatus(BM::GUID const& rkGuid, ESpecialUnitStatusType const eLeaveType);
		ESpecialUnitStatusType GetSpecStatus(BM::GUID const& rkGuid) const;
		void ClearSpecStatus(BM::GUID const& rkGuid);

	private:
		mutable Loki::Mutex m_kUnitSpecialStatusMutex;
		ContUnitSpecialStatus m_kContSpecStatus;
	};

	void DeleteInvenCoupleItem(CUnit* pkUnit, WORD const wItemHaveAbilType, CItemDefMgr const& rkItemDefMgr, SGroundKey const& rkGndKey);

	bool IsMyHomeHasFuctionItem(CUnit * pkPlayerUnit,CUnit * pkNpcUnit,EUseItemCustomType);
	bool IsMyHomeHasSideJob(CUnit * pkPlayerUnit,CUnit * pkNpcUnit,eMyHomeSideJob const kSideJob);
	bool IsSaveHPMP(EGndAttr const eGndAttr);

	template<typename T_CONT>
	void InitGenPointChild(T_CONT& rkCont)
	{
		T_CONT::iterator itor_cont = rkCont.begin();
		while (rkCont.end() != itor_cont)
		{
			T_CONT::mapped_type& rkGenInfo = (*itor_cont).second;
			rkGenInfo.RemoveAll();

			++itor_cont;
		}
	}

	SummonOptionType GetSummonOptionType(bool const bUniqueClass);

	void SafeImportAlwaysDropItemCont(ContAbilValue& rkOut, int iItemNo, size_t iItemCount = 1);
	void GetAlwaysDropItem(CUnit& rkMonster, ContAbilValue &rkOut);
	bool InsertAlwaysDropItem(CUnit * pkUnit, int const iItemNo, size_t iItemCount = 1);
	bool InsertEffectAbil(CUnit * pkUnit, int const iEffectNo);
	void DeleteEffect(CUnit* pkUnit, WORD const wEffetHaveAbilType);
	void DeleteInvenItem(CUnit* pkUnit, EInvType const eFromInvType, WORD const wItemHaveAbilType, CItemDefMgr const& rkItemDefMgr, SGroundKey const& rkGndKey);
	void DeleteInvenCoupleItem(CUnit* pkUnit, WORD const wItemHaveAbilType, CItemDefMgr const& rkItemDefMgr, SGroundKey const& rkGndKey);

	void SendAddSimpleUnit(CUnit * pkUnit, UNIT_PTR_ARRAY const& kUnitArray, DWORD const dwSendFlag);
	void SendPartyMgr_Refuse(BM::GUID const& rkCharGuid, EPartyRefuse const eType, bool const bRefuse);

	void SetActArgGround(SActArg & kArg, PgGround const* pkGround);
};

class PgPlayer;
class PgActionResultVector;
class PgLocalPartyMgr;
class PgLocalMarketMgr;

//#define MAX_SEND_BROADCASTING_DISTANCE 800
//#define MAX_SEND_BC_AREA_DISTANCE	MAX_SEND_BROADCASTING_DISTANCE * 1.5

int const MONSTER_AI_TICK_INTER = 300;	//몬스터 AI틱 간격
int const MONSTER_AI_TICK_INTER_ERROR = 30;	//몬스터 틱의 허용오차. 기준의 1/10

int const MISSION_LEVEL5 = 4;
int const MISSION_LEVEL6 = 5;

#define AI_MONSTER_MAX_MOVETIME 10000	// Monster maximum move time
#define AI_MONSTER_MIN_MOVETIME	1500	// Monster minimum move time

enum eIndunState
{
	INDUN_STATE_NONE		= 0x00,
	INDUN_STATE_OPEN		= 0x01,	// 인던이 오픈되었다.
	INDUN_STATE_WAIT		= 0x02,	// 인던이 유저를 기다리는 중이다.
	INDUN_STATE_READY		= 0x04,	// 인던이 준비가 되었다.
	INDUN_STATE_PLAY		= 0x08,	// 인던의 유저들이 놀고 있는 중이다.
	INDUN_STATE_RESULT_WAIT	= 0x10,	// 인던의 플레이 결과를 보여주어야 한다.
	INDUN_STATE_RESULT		= 0x20,	//
	INDUN_STATE_CLOSE		= 0x40,	// 인던이 닫혀야 한다.
	INDUN_STATE_FAIL		= 0x80, // 인던 도전 실패. 결과창을 패스하고 PLAY -> FAIL -> CLOSE 순으로 상태를 변경한다.
	INDUN_STATE_REGIST_RESULT_MGR = INDUN_STATE_OPEN | INDUN_STATE_WAIT | INDUN_STATE_READY | INDUN_STATE_PLAY,
};
typedef DWORD	EIndunState;

// 오프닝여부
typedef enum eOpeningState
{
	E_OPENING_NONE			= S_OK,
	E_OPENING_READY			= S_FALSE,//인던 Ready상태에서 오프닝을 해야함
	E_OPENING_PLAY			= E_OPENING_READY+1,
	E_OPENING_ERROR			= E_FAIL,
}EOpeningState;

typedef enum
{
	E_SPAWN_DEFAULT			= 0,
	E_SPAWN_RED				= TEAM_RED,
	E_SPAWN_BLUE			= TEAM_BLUE,
	E_SPAWN_WIN				= 3,
	E_SPAWN_LOSE			= 4,
	E_SPAWN_BATTLEAREA_ATK	= 5,
	E_SPAWN_BATTLEAREA_DEF	= 6,
	E_SPAWN_DEFENCE7_RED	= 7,
	E_SPAWN_DEFENCE7_BLUE	= 8,
	E_SPAWN_EVENT_GROUND	= 9,
}ESpawnType;

// 이벤트 그라운드 상태.
// 상태에 따라 다른 로직 수행하기 위해( 인던처럼 ).
typedef enum eEventGroundState
{
	EGS_NONE			= 0x00,
	EGS_IDLE			= 0x01,		// 이벤트 진행 중이 아님( 유저도 없고 이벤트가 시작할 수 있는지 시간만 검사하는 상태)
	EGS_START_WAIT		= 0x02,		// 유저 입장 대기.
	EGS_READY			= 0x04,		// 이벤트 시작 전. 유저들이 이벤트 맵으로 이동하는 중.
	EGS_PLAY			= 0x08,		// 이벤트가 진행 중. 보스 리젠 순서에 따라 몬스터가 생성 된다.
	EGS_WAIT_SHORTTIME	= 0x10,		// 잠깐 대기하는 상태.
	EGS_END_WAIT		= 0x20,		// 이벤트가 끝남(시간이 다되거나 마지막 보스 몬스터가 사망). 잠시 대기 후 다음 상태로 변경.
	EGS_END				= 0x40,		// 이벤트가 종료되어 맵에 남아 있는 모든 유저를 원래 맵으로 돌려보냄.
}EEventGroundState;

// 현재 이벤트 맵에 진입한 유저 수를 관리하는 컨테이너.
// key : EventNo, value : user count
typedef std::map<int, int> CONT_CURRENT_EVENT_MAP_USER_COUNT_LIST;

// 현재 이벤트 맵에 진입할 수 있는지 관리하는 컨테이너.
// key : EventNo, value : 이벤트맵에 진입할 수 있는지?
typedef std::map<int, bool> CONT_EVENT_MAP_ENTERABLE_ENTER_LIST;

typedef struct tagJoinPartyMember
{
	BM::GUID CharGuid;
	BM::GUID PartyGuid;
	bool bMaster;

	tagJoinPartyMember()
	{
		CharGuid.Clear();
		PartyGuid.Clear();
		bMaster = false;
	}

}SJoinPartyMember;
typedef std::map<BM::GUID, SJoinPartyMember> CONT_JOIN_PARTY_MEMBER_LIST;

#pragma pack(1)

/*
class CCheckSmallArea
	: public TVisitor< PgSmallArea* >
{
public:
	CCheckSmallArea(POINT3 const &rkPos)
		: m_kPoint(rkPos)
	{
	}

	virtual bool VIsCorrect(PgSmallArea* &pArea)
	{
		return pArea->IsAdjacentArea(m_kPoint);
	}
	POINT3 const m_kPoint;
};
*/

typedef struct tagSMonsterGen
{
	tagSMonsterGen()
	{
		iMonNo = 0;
		i64GenTime = 0;
	}

	tagSMonsterGen(int const _iMonNo,__int64 const i64CurTime)
	{
		iMonNo = _iMonNo;
		i64GenTime = i64CurTime;
	}

	tagSMonsterGen(tagSMonsterGen const& rkInfo)
	{
		iMonNo = rkInfo.iMonNo;
		i64GenTime = rkInfo.i64GenTime;
	}

	int		iMonNo;
	__int64	i64GenTime;
} SMonsterGen;

typedef struct tagEventMonsterGen
{
	tagEventMonsterGen()
	{
		MonNo = 0;
		GenTime = 0;
		DelTime = 0;
		DelayTime = 0;
		RegenPeriod = 0;
		GenPos = POINT3(0, 0, 0);
		RewardItemGroupNo = 0;
		RewardCount = 0;
		GenerateMessage.clear();
		IsInsertMonster = false;
	}

	tagEventMonsterGen(tagEventMonsterGen const & Info)
	{
		MonNo = Info.MonNo;
		GenTime = Info.GenTime;
		DelTime = Info.DelTime;
		DelayTime = Info.DelayTime;
		RegenPeriod = Info.RegenPeriod;
		GenPos = Info.GenPos;
		RewardItemGroupNo = Info.RewardItemGroupNo;
		RewardCount = Info.RewardCount;
		GenerateMessage = Info.GenerateMessage;
		IsInsertMonster = Info.IsInsertMonster;
	}

	int MonNo;
	__int64 GenTime;
	__int64 DelTime;
	int DelayTime;
	int RegenPeriod;
	POINT3 GenPos;
	int RewardItemGroupNo;
	int RewardCount;
	std::wstring GenerateMessage;
	bool IsInsertMonster;
} SEventMonsterGen;

typedef struct tagDeleteReserveInsItemInfo
{
	tagDeleteReserveInsItemInfo()
	{
		GenInfo.Clear();
		DelItemGuid.Clear();
	}

	tagDeleteReserveInsItemInfo( tagDeleteReserveInsItemInfo const & rhs )
	{
		GenInfo = rhs.GenInfo;
		DelItemGuid = rhs.DelItemGuid;
	}

	TBL_DEF_MAP_REGEN_POINT GenInfo;
	BM::GUID DelItemGuid;

} SDeleteReserveInsItemInfo;

typedef struct tagEventDropAnyMonster
{
	tagEventDropAnyMonster()
	{
		StartTime.Clear();
		EndTime.Clear();
		RewardItemGroupNo = 0;
		RewardCount = 0;
		bIsEventTime = false;
	}

	tagEventDropAnyMonster(tagEventDropAnyMonster const & param)
	{
		StartTime = param.StartTime;
		EndTime = param.EndTime;
		RewardItemGroupNo = param.RewardItemGroupNo;
		RewardCount = param.RewardCount;
		bIsEventTime = param.bIsEventTime;
	}

	BM::DBTIMESTAMP_EX StartTime;
	BM::DBTIMESTAMP_EX EndTime;
	int RewardItemGroupNo;
	int RewardCount;
	bool bIsEventTime;
}SEventDropAnyMonster;

#pragma pack()

typedef std::map<int,SMonsterGen>	CONT_MONSTER_GEN;
typedef std::set<int>		CONT_GENERATED_MONSTER;

typedef std::vector<SEventMonsterGen> VEC_EVENTMONSTERGEN;
typedef std::map<int, SEventMonsterGen> CONT_EVENT_MONSTER_GEN;

typedef std::vector<SEventDropAnyMonster> VEC_EVENTDROPANYMONSTER;

typedef std::map<BM::GUID, SDeleteReserveInsItemInfo> CONT_DELETERESERVERINSITEM;
typedef std::map<BM::GUID, BM::GUID> CONT_PARTY_MASTER;	//first:PartyGuid, second:MasterGuid

typedef std::tuple<int, int, int, int> SAddRange;

class PgGroundManager;
class PgUserQuestSessionMgr;
//Unit은 SmallArea 를 전혀 모른다. 단지 그라운드가 관리하기 쉽게 하려고 하는것이다. Objserver로도 등록 말것
class PgGround
	:	public BM::CObserver< BM::Stream* >
	,	public PgGroundResource
	,	public PgAggroMeterMgr
	,	public PgComboCounterMgr
	,	protected PgObjectMgr2
	,	protected PgGroundUtil::PgUnitSepcailStatusHandler
{
	// 상수들
public:
	typedef std::vector<CUnit const*>	ConUnit;

	//typedef std::map< POINT3, PgSmallArea* > ContArea;
	typedef std::vector<PgSmallArea*> ContArea;

	typedef std::map< BM::GUID, SPartyUserInfo > ContPartyMember;
	typedef std::vector<SPartyUserInfo> VEC_UserInfo;
	typedef std::map< int, int > ContClassLevel;

public :
	static AntiHackCheckActionCount ms_kAntiHackCheckActionCount;
	static AntiHackCheckVariable ms_kAntiHackCheckVariable;
	static void SetAntiHackVariable();

	static float		ms_fAutoHealMultiplier_NotInViliage;

	static int			ms_iEnableEntityCritialAttack;	// Entity 생성시 Player의 Critial 확률및 공격력 적용
	static int			ms_iEnableEntityHitRate;		// Entity 생성시 Player의 명중률 적용
	static int			ms_iEnableEntityAttackExtInfo;	// Entity 생성시 Player의 추가 공격정보 적용

	static int			ms_iHiddenRewordItemNo;
	static T_GNDATTR	ms_kOffPet_GroundAttr;			// 펫이 나오지 않는 그라운드 속성

	static float		ms_KnightAwakeReviserByKill;	//몬스터를 죽였을때 차는 각성치 보정값
	static float		ms_WarriorAwakeReviserByKill;
	static float		ms_MageAwakeReviserByKill;
	static float		ms_BattleMageAwakeReviserByKill;
	static float		ms_HunterAwakeReviserByKill;
	static float		ms_RangerAwakeReviserByKill;
	static float		ms_ClownAwakeReviserByKill;
	static float		ms_AssassinAwakeReviserByKill;
	static float		ms_ShamanAwakeReviserByKill;
	static float		ms_DoubleFighterAwakeReviserByKill;

	static int			ms_JobSkillBaseExpDiff[4]; // 1~4

public:
	PgGround();
	virtual ~PgGround();

public: //AI 예외 public 
	void AI_CallHelp(CUnit* pkUnit, float fCallRange);
	bool AI_SkillFire( CUnit* pkCaster, SActArg* pkActArg, const ESkillStatus eUnitState = ESS_FIRE);
	bool AI_SkillCasting( CUnit* pkCaster, SActArg* pkActArg, BM::Stream& rkTailPacket);
	bool AI_GetSkillTargetList(CUnit* pkCaster, int const iSkillNo, UNIT_PTR_ARRAY& rkTargetList, bool bDamageFire, SActArg const* pkActArg, POINT3 const* pkDir = NULL, SAddRange const& rkAddRange = SAddRange(0,0,0,0));
	bool FindEnemy(CUnit* pkFrom, int const iMaxTarget = 5);
	bool CanAttackTarget(CUnit* pkAttacker);
	void SendNfyAIAction(CUnit* pkUnit, EUnitState eState = US_IDLE, PgActionResultVector* pkActionResultVec=NULL, BM::Stream* pkTailPacket = NULL, int const iSkillNo = 0);
	bool IsTargetInRange(CUnit* pkUnit, int const iZLimit = AI_Z_LIMIT, bool const bCheckFromGround = false);
	int GetReserveAISkill(CUnit* pkUnit);
	POINT3 GetUnitPos( BM::GUID const & rkGuid, bool bCheckImpact = false, float const fRayRange = 300.0f );
	void SendNftChaseEnemy(CUnit* pkUnit);
	float GetAdditionalAttackProb(CUnit *pkUnit);	
	bool GetAroundVector(CUnit *pkUnit, BM::GUID const &rkTargetGuid, float const fRange, bool bNear, POINT3 &rkOut);
	POINT3BY GetPathNormal(BM::GUID const & rkGuid);
	bool GetTargetPos(CUnit* pkUnit, POINT3& rkTargetPos);

protected:

	void ProcessTimeOutedItem(PgPlayer * const pkPlayer);
	void ProcessTimeOutedMonsterCard(PgPlayer * const pkPlayer);
	void ProcessUnbindItem(PgPlayer * const pkPlayer);
	void ProcessCheckMacroUse(PgPlayer * const pkPlayer);
	void ProcessRecommendPointRefresh(PgPlayer * const pkPlayer);

//////////////////////////

	void OnReqItemAction( PgPlayer *pkPlayer, BM::Stream * pkNfy, PgPet * pkPet=NULL);

	void CheckPetAliveAchievement(PgPlayer * pkPlayer);

    virtual int GetMaxSummonUnitCount(CUnit * pkUnit)const;
	virtual void SendMonsterCount();


	bool	m_bUpdateMonsterCount;	//몬스터 카운트가 수정되었는지 유무

public:
	virtual EOpeningState Init( int const iMonsterControlID=0, bool const bMonsterGen=true );
	virtual void Clear();
	virtual bool Clone( PgGround* pkGround );

	// Ground Manager의 OnTimer에서 호출(리턴값이 true이면 그라운드가 삭제된다.)
	virtual bool IsDeleteTime()const{return false;}
	virtual void OnTick100ms();
	virtual void OnTick1s();
	virtual void OnTick5s();
	virtual void OnTick30s();
	virtual void OnTick1m();
	inline bool CheckTickAvailable(ETickInterval const eInterval, DWORD const dwNow, DWORD& rdwElapsedTime, bool bUpdateLastTime = false);

	virtual EGroundKind GetKind()const{	return GKIND_DEFAULT;	}
	virtual EIndunState GetState()const{return INDUN_STATE_NONE;}
	virtual int GetGroundNo()const { return GroundKey().GroundNo();}; //현재 그라운드 번호
	virtual int GetGroundItemRarityNo()const { return GIOT_FIELD; }
	virtual void CheckEnchantControl(PgBase_Item& rkItem)const {};

	virtual int GetMapItemBagGroundNo() const { return GetGroundNo(); };

	virtual void GetGenGroupKey(SGenGroupKey& rkkGenGrpKey)const;
	virtual SRecentInfo const& GetRecentInfo()const;

protected:
	DWORD GetTimeStamp();

	//	Zone
	HRESULT BuildZone();
#ifdef ZONE_OPTIMIZE_20090624
	HRESULT MakeZone(NiNode *pkRootNode);
#endif
	void ReleaseZone();

	bool RemoveGenGroupMonster(int const iGenGroupNo, bool const bKill);	//! gen group 몬스터를 제거한다. 
	bool RemoveGenGroupObject(int const iGenGroupNo);						//! 젠 그룹의 오브젝트를 제거한다. 

	HRESULT GetArea(POINT3 const &rkPos, POINT3 &rkOut, PgSmallArea* &pRetArea, bool const bIsMoveToSpawn = true, bool bCheckPos = true);
	PgSmallArea* GetArea( int const iAreaIndex )const;

	void ProcessMonsterGenNfy(int const iGenGroupNo,E_MONSTER_GEN_MODE const kMode);
	float GetAutoHealMultiplier()const;
	void OnActivateEventMonsterGroup();
	bool CheckPathNormal(CUnit* pkUnit, CSkillDef const* pkSkillDef, SActionInfo const& rkAction, float const fErrorDelta = 10.0f);//클라에서 보내준 패스노말과 공격방향 검사. 오차한계 10도
//	+-------------------------------------------------------+
//	|	Unit Control Method									|
//	+-------------------------------------------------------+
public:
	void OnRecvMonsterGenNfy(int const iGenGroupNo,E_MONSTER_GEN_MODE const kMode);
	size_t GetUnitCount( const eUnitType eType )const;
	bool UnitEventNfy(BM::GUID const &rkGuid, BM::Stream* pkPacket);

	CUnit* GetUnit( BM::GUID const &rkGuid )const;
	PgPlayer* GetUser( BM::GUID const &rkCharGuid ) const;
	PgPet* GetPet( PgPlayer * pkPlayer )const;
	PgPet* GetPet( BM::GUID const &kPetID )const;
	
	PgSubPlayer* GetSubPlayer( PgPlayer * pkPlayer )const;
	PgSubPlayer* GetSubPlayer( BM::GUID const &rkSubPlayerGuid )const;

	bool CheckUnit( BM::GUID const &rkGuid )const;//Unit이 있는가?
	BM::GUID const & GetFollowingHead(CUnit* pktail, bool const bGotoEnd, short int sCallDepth = 0);

	int GetUnitAbil(BM::GUID const & rkGuid, WORD const wType);

	virtual HRESULT InsertMonster(TBL_DEF_MAP_REGEN_POINT const &rkGenInfo, int const iMonNo, BM::GUID &rkOutGuid, CUnit* pkCaller=NULL, bool bDropAllItem = false, int iEnchantGradeNo = 0, ECREATE_HP_TYPE const eCreate_HP_Type = ECHT_NONE);

	void DeletePet( BM::GUID const &kPetID );
	PgPet* CreatePet( PgPlayer * pkCaller, BM::GUID const &kPetID, CONT_PET_MAPMOVE_DATA::mapped_type &kPetData );
	CUnit* CreateEntity(CUnit* pkCaller, SCreateEntity* pkCreateInfo, LPCTSTR lpszName, bool bSyncUnit = true);
	int GetEntity( BM::GUID const &kCaller, int const iClass, UNIT_PTR_ARRAY& rkUnitArray);
	CUnit* CreateGuardianEntity(CUnit* pkCaller, SCreateEntity* pkCreateInfo, LPCTSTR lpszName, bool bSyncUnit = true, int const iStartActionID=0);	
	CUnit* CreateSummoned(CUnit* pCaller, SCreateSummoned* pCreateInfo, LPCTSTR lpszName, SSummonedMapMoveData const& kMapMoveData, POINT3 kCreatePos = POINT3::NullData());
	CUnit* CreateCustomUnit(int iClassNo, POINT3 const& ptPos, Direction const& rkDirFront);
	void RefreshSummonEffect(PgPlayer* pkPlayer) const;
	PgSubPlayer* CreateSubPlayer( PgPlayer * pkCaller, BM::GUID const& rkSubPlayerID );
	void DeleteSubPlayer( BM::GUID const& rkSubPlayerID );

	int GetTotalSummonedSupply(CUnit* pkCaller)const;

	virtual bool ReleaseUnit( CUnit *pkUnit, bool bRecursiveCall=false, bool const bSendArea=true );
	void OnPT_T_C_NFY_MARRY(EMarryState const eCommandType, BM::Stream *const pkPacket);

protected:
	bool FakeRemoveUnit( CUnit * pkCaller, int const iHideMode );
	bool FakeAddUnit(CUnit * pkCaller);
	
	void SetUnitAbil( BM::GUID const & kCharGuid, WORD const Type, int const iValue, bool const blsSend = false, bool const bBroadcast = false );
	
	//void AddNPC(char const* pcName, char const* pcActor, char const* pcScript, char const* pcLocation, BM::GUID const &rkGuid, int iID);
	
	POINT3BY GetMoveDirection(BM::GUID const & rkGuid);

	void AutoHealAndCheckDieSkill(CUnit * pkUnit, DWORD const dwkElapsed, float const fAutoHealMultiplier = 1.0f);

public:
	void LogOut( SERVER_IDENTITY const &kSI );
	virtual bool LogOut(BM::GUID const &rkCharGuid);

public:
	PgMonster* GetFirstMonster(int const iMonID);
	PgBoss* GetBossMonster(int const iMonID);

protected:
	CUnit* GetUnitControl(CUnit* pkUnit, CUnit* pkCalledUnit, unsigned short usPacketType, BM::Stream& rkPacket);

	virtual bool SaveUnit( CUnit *pkUnit, SReqSwitchReserveMember const *pRSRM = NULL, BM::Stream * const pPacket = NULL );
	bool AddUnit( CUnit *pkUnit, bool const bIsSendAreaData = true );	//상속금지

	virtual void PreReleaseUnit( CUnit const *pkUnit );
	void ReleaseUnit( UNIT_PTR_ARRAY& rkUnitArray, bool bRecursiveCall=false );
	void ReleaseAllUnit();
	bool RemoveAllMonster(bool const bKill=false, CUnit *pUnit = NULL, int iVoluntarilyDie = 0);
	bool RemoveAllObject();

	CUnit* GetTarget( CUnit *pkUnit )const;
	void GetTargetList(CUnit* pkUnit, UNIT_PTR_ARRAY& rkUnitArray, int const iInNum);
	void GetSummonUnitArray( CUnit *pkUnit, UNIT_PTR_ARRAY& rkUnitArray );
	
//	void GetFirstUnit( EUnitType const eUnitType, CONT_OBJECT_MGR_UNIT::iterator& rkItor );
//	CUnit* GetNextUnit( EUnitType const eUnitType, CONT_OBJECT_MGR_UNIT::iterator& rkItor );
	
	CUnit* GetPlayer(char const *pcCharacterName);
	CUnit* GetPlayer( std::wstring const &wstrName );

	int GetTargetInArea(CUnit* pkCaster, CSkillDef const *pkSkillDef, EUnitType const eUnitType, UNIT_PTR_ARRAY& rkTargetList, bool const bDamageFire, POINT3 const* pkDIr = NULL, SAddRange const& rkAddRange = SAddRange(0,0,0,0));

	POINT3 GetUnitPos( CUnit* pkUnit, bool bCheckImpact = false, float const fRayRange = 300.0f );
	
	void SetUserLife( PgPlayer *pkUser, int const iHP, int const iMP, DWORD const dwFlag=E_SENDTYPE_SELF );
	
	HRESULT InsertObjectUnit( TBL_DEF_MAP_REGEN_POINT const &rkGenInfo, SObjUnitBaseInfo const &kInfo, BM::GUID &rkOutGuid, CUnit* pkCaller=NULL );

	void UpdateAbilGuild(PgPlayer const *pkPC, const WORD eAbil);
	void UpdatePartyUnitAbil(PgPlayer const *pkPC, BYTE const cAbil);//파티 맴버의 컨텐츠로 HP갱신
	void SendNfyMapLoaded( PgPlayer* pkUser );// 상속금지
	virtual void WriteToPacket_AddMapLoadComplete( BM::Stream &rkPacket )const{}

	bool IsInTriggerUnit( GTRIGGER_ID const& rkTriggerID, CUnit const* pkUnit);
	bool SetTriggerEnable(GTRIGGER_ID const& rkTriggerID, bool const bNewEnable);
	bool RecvTriggerAction( CUnit *pkUnit, BM::Stream * const pkPacket );
	bool RecvTriggerActionScript(std::string const& rkID);

public:
	void InsertItemBox(POINT3 const &kptPos, VEC_GUID const &kOwners, CUnit* pkCaller, PgBase_Item const &kItem, __int64 const iMoney, PgLogCont &kLogCont, ETeam Team = TEAM_NONE, BM::GUID & OutGuid = BM::GUID::Create(), WORD wCollectRemainTime = 0 );//아이템을 여러개쥔건 떨어지지 않는다.
	void InsertItemBox(TBL_DEF_MAP_REGEN_POINT const & GenInfo, VEC_GUID const & Owners, CUnit * pCaller, PgBase_Item const & Item, __int64 const iMoney, PgLogCont & LogCont, BM::GUID & OutGuid = BM::GUID::Create(), WORD wCollectRemainTime = 0 );//인스턴스 아이템 전용.

	//	+-------------------------------------------------------+
	//	|	Map Move / Spawn Method								|
	//	+-------------------------------------------------------+
	bool SendToSpawnLoc(CUnit *pkUnit, int iPotalNo, bool bRandomize = true, int iSpawnType=E_SPAWN_DEFAULT);// 스폰지역으로 유저를 보냄
	bool SendToSpawnLoc(BM::GUID const &rkCharGuid, int iPotalNo, bool bRandomize = true, int iSpawnType=E_SPAWN_DEFAULT);	// 스폰지역으로 유저를 보냄

	HRESULT FindTriggerLoc( char const* szName, POINT3 &rkTriggerLoc_out, bool const bFindSpawn=false )const;
	HRESULT FindSpawnLoc( int iPotalNo, POINT3 &rkSpawnLoc_out, bool bRandomize = true, int iSpawnType=E_SPAWN_DEFAULT) const;
	bool SendToPosLoc( CUnit *pkUnit, POINT3 const &pt3Pos, BYTE const byType=MMET_Normal );
	bool MissionItemOrderCheck(PgPlayer *pkPlayer, PgReqMapMove& kMapMove, int const iMissionNo, int const iCount,int const iMissionLevel = 0);
	bool MissionItemOrderCheck(PgPlayer *pkPlayer, CONT_PLAYER_MODIFY_ORDER & kOrder, int const iMissionNo, int const iCount, int const iMissionLevel = 0);
	bool MissionChaosItemOrderCheck(PgPlayer *pkPlayer, PgReqMapMove& kMapMove, int const iMissionNo, int const iCount);
	bool MissionChaosItemOrderCheck(PgPlayer *pkPlayer, CONT_PLAYER_MODIFY_ORDER & kOrder, int const iMissionNo, int const iCount);
	
	void ReqMapMoveCome( SReqMapMove_CM const &kRMMC, VEC_GUID const &kUserList );
	bool AddPartyMember( PgPlayer *pkMaster, PgReqMapMove &kMapMoveAction );
	bool AddExpeditionMember( PgPlayer * pMaster, PgReqMapMove & MapMoveAction );
	void GetStatisticsPlayTime(__int64 i64Now, SMapPlayTime& rkOut);
	void SetEventQuest(PgEventQuest const & rkNewEventQuest);
	bool AddAnyPartyMember( PgPlayer *pkMember, PgReqMapMove &kMapMoveAction );
	bool AddAnyExpeditionMember( PgPlayer *pMember, PgReqMapMove & MapMoveAction );
	bool AddPartyAllMember( PgPlayer *pkMaster, PgReqMapMove &kMapMoveAction );

	virtual void ProcessGateWayUnLock(HRESULT const hRet, CUnit * pkCaster, BM::Stream & rkAddonPacket);

protected:
	virtual bool RecvMapMove( UNIT_PTR_ARRAY &rkUnitArray, SReqMapMove_MT& rkRMM, CONT_PET_MAPMOVE_DATA &kContPetMapMoveData, CONT_UNIT_SUMMONED_MAPMOVE_DATA &kContUnitSummonedMapMoveData, CONT_PLAYER_MODIFY_ORDER const &kModifyOrder );
	bool RecvMapMoveCome( SReqMapMove_CM const &kRMMC, BM::GUID const &kComeCharGuid );
	virtual bool RecvMapMoveTarget( BM::GUID const &kTargetCharGuid, BM::GUID const &kReqCharGuid, bool const bGMCommand );
	virtual void RecvMapMoveComeFailed( BM::GUID const &kCharGuid );

	virtual bool IsAccess( PgPlayer * ){return true;}
	void ProcessMapMoveResult( UNIT_PTR_ARRAY& rkUnitArray, SAnsMapMove_MT const &rkAMM );
	virtual bool RecvRecentMapMove( PgPlayer *pkUser );	// 리센트맵 위치로 돌려 보내라!
	virtual bool AdjustArea( CUnit *pkUnit, bool const bIsSendAreaData, bool const bIsCheckPos );
	void ChangeArea( CUnit *pkUnit, PgSmallArea *pkNewArea, PgSmallArea *pkLastArea, bool const bSendAreaData );
	virtual void SendMapLoadComplete( PgPlayer *pkUser );

	void PartyBreakIn_CousumeKeyItem(PgPlayer * pPlayer); // 파티난입 시 키아이템 소모
public:

	void DisplayAreaState();
	//NiPick* GetPhysxPick(){return m_pkPhysxPick;}
	//int GetWayPointGroupCount();
	//int GetWayPointIndexCount(int const iGroup);

//	+-------------------------------------------------------+
//	|	AI Method											|
//	+-------------------------------------------------------+
public:
	bool FindEnemy( CUnit* pkFrom, UNIT_PTR_ARRAY& rkUnitArray, int const iMaxTarget = 5, int const iUnitType=UT_PLAYER|UT_MONSTER, bool const bFindFromGround = false, bool const bCallTimeCheck = true);	//땅으로 레이 쏴서 확인
	bool Locked_IsUnitInRange(ETeam const eTeam, POINT3 const& ptFind, int const iRange, EUnitType const eType);
	void GetTriggerInRange( GTRIGGER_ID const& rkTriggerID, EUnitType const eUnitType, UNIT_PTR_ARRAY & rkUnitArray)const;
	void GetUnitInDistance( POINT3 const& ptPos, int const iRange, EUnitType const eType, UNIT_PTR_ARRAY& rkUnitArray, int const iZLimit = 0)const;
	void GetUnitInRange( POINT3 const& ptPos, int iRange, EUnitType eType, UNIT_PTR_ARRAY& rkUnitArray, int iZLimit = 0, bool const bFindFromGround = false);
	void GetUnitInRange( EUnitType & eCheckUnitType, POINT3 const& FromPos, int const iRange, EUnitType const eUnitType, UNIT_PTR_ARRAY & rkUnitArray, int const iZLimit = 0, bool const bFindFromGround = false);
	void GetUnitInCube( POINT3 const &ptCubeMin, POINT3 const &ptCubeMax, POINT3 const &ptPos, EUnitType eType, UNIT_PTR_ARRAY& rkUnitArray );
	CUnit* GetUnitByClassNo( int const iClassNo, EUnitType eType );
	int GetUnitByClassNo( int const iClassNo, EUnitType eType, UNIT_PTR_ARRAY& rkUnitArray );
    CUnit* GetUnitByType( EUnitType const eType );
	bool GetVisionDirection(CUnit* pkUnit, NxVec3& rkDirectionOut, bool bUseTargetPos = true);
	void GetUnitInWidthFromLine(POINT3 const& ptStart, POINT3 const& ptEnd, int iWidth, EUnitType eType, UNIT_PTR_ARRAY& rkUnitArray);
	void GetUnitIn2DRectangle(POINT3 const& kP1, POINT3 const& kP2, POINT3 const& kP3, POINT3 const& kP4, EUnitType eType, UNIT_PTR_ARRAY& rkUnitArray); // Only use x,y
	void DequeTargetToUNIT_PTR_ARRAY(CUnit::DequeTarget const &rkDeque, UNIT_PTR_ARRAY& rkArr);
	NxShape* RayCast(NxRay& rkWorldRay, NxRaycastHit& rkHit, NxReal maxDist = 200.0f, NxU32 hintFlags = NX_STATIC_SHAPES) const;

	//GetTargetList와 함수명 겹치지 않도록
	//pkUnit 에 따라서 타겟을 잡아 리스트에 넣어준다.
	void GetUnitTargetList(CUnit* pkUnit, UNIT_PTR_ARRAY& rkUnitArray, int const iTargetType, int iRange = 0, int const iZLimit = AI_Z_LIMIT);

	EOpeningState ActivateMonsterGenGroup( int const iGenGroup=0, bool const bReset=true, bool const bOnce=false, int const iCopy=0 );

	bool IsInReturnZone(CUnit * pkUnit)const;
	bool IsInWalkingZone(CUnit * pkUnit)const;
	bool IsInRunningZone(CUnit * pkUnit)const;
	bool IsInBattleZone(CUnit * pkUnit)const;

protected:
	void FindUnit_WhenJoinedTeam(CUnit* pkUnit, UNIT_PTR_ARRAY& rkUnitArray, int const iTargetType, int const iRange, int const iZLimit, int const iTeam, bool const bIfNoneRangeThenAddUnit = false );
	void FindUnit_WhenNoneJoinedTeam(CUnit* pkUnit, UNIT_PTR_ARRAY& rkUnitArray, int const iTargetType, int const iRange, int const iZLimit);
	void FindUnit_DuelTarget(CUnit* pkUnit, UNIT_PTR_ARRAY& rkUnitArray, int const iTargetType, int const iRange, int const iZLimit);
	void FindUnit_DuelTarget(EUnitType const eUnitType, CUnit* pkUnit, UNIT_PTR_ARRAY& rkUnitArray, int const iTargetType, int const iRange, int const iZLimit);
	void RemoveNoneHiddenUnit(CUnit* pkUnit, UNIT_PTR_ARRAY& rkUnitArray, int const iRange, int const iZLimit);
	void RemoveAliveUnit(CUnit* pkUnit, UNIT_PTR_ARRAY& rkUnitArray, int const iRange, int const iZLimit);

	bool FindNearestUnt(const EUnitType eUT, POINT3 const& rkPos, float const fRange, int const iFindType, bool const bOnlyAlive, float* pfDist,
		BM::GUID& pkFindUnit, NxVec3& kNormalVector);
	CUnit* FindRandomUnit(POINT3 const &rkPos,float const fRange,const EUnitType eUnitType);
	
	HRESULT CheckMonsterDie(PgMonster* pkUnit);
	HRESULT CheckObjectUnitDie(PgObjectUnit* pkUnit);
	virtual HRESULT SetUnitDropItem(CUnit *pkOwner, CUnit *pkDroper, PgLogCont &kLogCont );
	HRESULT SetUnitDropItemImp(CUnit *pkOwner, CUnit *pkDroper, POINT3 const& kDropPos, PgCreateSpreadPos& kCreatePosAction, int iItemDropRate, float fMoneyDropRate, VEC_GUID const& kOwnerVec, TBL_DQT_DEF_MAP_ITEM_BAG const& kDefMapItemBag, PgLogCont &kLogCont);
	size_t GetAddDropItemCount(CUnit* pkOwner);
	void GetItemOwner(CUnit const* pkUnit, VEC_GUID & rkOwnerVec)const;

	bool InitRareMonsterGen();
	bool RareMonsterGenerate();
	bool GetRareMonster(int const iMonBagNo,int & iMonNo) const;
	bool RemoveRareMonster(int const iMonNo,PgMonster * pkMonster);
	bool GetRandomMonsterGenPoint(int const iGenGroup,PgGenPoint & kGenPoint);	// 몬스터 젠 그룹중 랜덤으로 젠포인트 하나를 가져 온다.

public:

	void GetEventMonsterGenInfo(int MonsterNo, SEventMonsterGen & OutInfo) const;
	void DropAnyMonsterCheck(CONT_MONSTER_DROP_ITEM & DropItems) const;

protected:

	bool InitEventMonsterGen();
	void InitEventMonsterGen_sub(SEventGroup const& rkElement, VEC_EVENTMONSTERINFO const& rkMonsterInfo, bool const bInsertMonster, BM::PgPackedTime const& rkNowTime, __int64 const& rkCurTime);
	bool EventMonsterGenerate();
	void RemoveEventMonster(int MonsterNo);
	bool DropAnyMonsterTimeCheck();
	
	EOpeningState MonsterGenerate( ContGenPoint_Monster& kContGenPoint, int const iCopy=0, CUnit* pkCaller=NULL);
	EOpeningState InstanceItemGenerate(ContGenPoint_InstanceItem & ContGenPoint, int const iCopy = 0, CUnit* pCaller = NULL);

	EOpeningState ActivateObjectUnitGenGroup( int const iGenGroup, bool const bReset, bool const bOnce);
	EOpeningState ActivateInstanceItemGenGroup( int const GenGroup, bool const bReset, bool const bOnce, int const Copy);

	bool ObjectUnitGenerateGroundCheck(PgGenPoint_Object& kGenPoint, BM::GUID& kGuid);	
	EOpeningState ObjectUnitGenerate(ContGenPoint_Object & kContGenPoint, bool const bReset = false);
	void ObjectUnitGenerate( bool const bReset=false, int const iGenGroup=0 );

	int TickAI( CUnit* pkUnit, DWORD dwkElapsed );
	virtual HRESULT PlayerTick(DWORD const dwElapsed);
	virtual HRESULT PetTick(DWORD const dwElapsed);

	HRESULT MonsterTick(DWORD const dwElapsed,VEC_UNIT& rkDelUnitVec);
	HRESULT ObjectUnitTick( DWORD const dwElapsed, UNIT_PTR_ARRAY& rkDelUnitArray );
	virtual void EntityTick(CUnit * pkUnit, DWORD const dwkElapsed, float const fAutoHealMultiplier);
	virtual bool IsMonsterTickOK() const {	return PgObjectMgr::GetUnitCount(UT_PLAYER) > 0;}
	int MonsterTickAI( CUnit* pkUnit, DWORD dwkElapsed );

	bool IsAttackable(EAbilType eType, CUnit* pkCaster, CUnit *pkTarget,int& iSkillNo);
	//bool SkillFire(int const iSkillNo, CUnit* pkCaster, CUnit* pkTarget, PgActionResultVector* pkResult, SActArg* pkAct, bool bSendPacket = false);

	//void PlayerQuestTick(CUnit* pkUnit);

private:
	EOpeningState MonsterGenerate(PgGenPoint& rkGenPoint, int& iMonNo, BM::GUID& kMonGuid, CUnit* pkCaller = NULL);
	EOpeningState InstanceItemGenerate(PgGenPoint & GenPoint, int & ItemNo, BM::GUID & ItemGuid, CUnit * pCaller = NULL);
	EOpeningState ObjectUnitGenerate(PgGenPoint_Object& rkGenPoint, PgGenPoint_Object::OwnGroupCont const& kCont);
	EOpeningState ObjectUnitGenerate(PgGenPoint_Object& rkGenPoint);

//	+-------------------------------------------------------+
//	|	Network Method										|
//	+-------------------------------------------------------+
public:
	virtual void VUpdate( BM::CSubject< BM::Stream* > * const pChangedSubject, BM::Stream* iNotifyCause );
//	void SendNoticeToAllUser( std::wstring wstrContent );

	//bool SendToUser_ByGuid( BM::GUID& rkGuid, BM::Stream &rkPacket, DWORD const dwSendType = E_SENDTYPE_SELF );
	//bool SendToUser_ByGuidVec( VEC_GUID const &rkVec, BM::Stream const &rkPacket, BM::GUID const &rkPartyGuid, DWORD const dwSendType = E_SENDTYPE_SELF);//GroundMng이외에서 호출 하지 마세요
	bool SendToUser_ByGuidVec( VEC_GUID const &rkVec, BM::Stream const &rkPacket, DWORD const dwSendType = E_SENDTYPE_SELF);
	void SendToParty(BM::GUID const& rkPartyGuid, BM::Stream & Packet);

	void RecvGndWrapped( BM::Stream* const pkPacket );
	void RecvChatInputState(CUnit *pkUnit, BM::Stream *pkPacket);
	void OrderSyncGameTime(BM::Stream* const pkSendPacket);

	void Broadcast( BM::Stream const& rkPacket, BM::GUID const &kCallerCharGuid, DWORD const dwSendFlag=E_SENDTYPE_NONE);
	void Broadcast(BM::Stream const& rkPacket, CUnit const *pkCaller=NULL, DWORD const dwSendFlag=E_SENDTYPE_NONE);

protected:
	void Broadcast( BM::Stream const& rkPacket, VEC_GUID& rkVecUnit, DWORD const dwSendFlag=E_SENDTYPE_NONE);

	virtual bool VUpdate( CUnit* pkUnit, WORD const wType, BM::Stream* pkNfy );
	virtual bool RecvGndWrapped( unsigned short usType, BM::Stream* const pkPacket );
	virtual bool RecvGndWrapped_ItemPacket(unsigned short usType, BM::Stream* const pkPacket );
	virtual bool Recv_PT_C_M_REQ_PET_ACTION( PgPlayer *pkOwner, BM::Stream * pkNfy );
	void SendContentsToDirect( CUnit* pkUnit, WORD const wType, BM::Stream* pkNfy );			// 그냥 콘텐츠 서버로 바로 보내는 패킷
	
	void SendToArea(BM::Stream *pkPacket, int const iAreaIndex, BM::GUID const &rkIgnoreGuid, BYTE const bySyncTypeCheck, DWORD const dwSendFlag );
	void SendToArea(BM::Stream *pkPacket, PgSmallArea const &rkSmallArea, BM::GUID const &rkIgnoreGuid, BYTE const bySyncTypeCheck, DWORD const dwSendFlag );
	void SendAreaData( CUnit *pkUnit, PgSmallArea const* pkTo, PgSmallArea const* pkFrom,  BYTE const bySyncType=SYNC_TYPE_DEFAULT );
	void SendAddUnitAreaData( PgNetModule<> const &kNetModule, PgSmallArea const* pkTo, PgSmallArea const* pkFrom, BM::GUID const &kIgnoreCharGuid );
	void EffectTick(CUnit* pkUnit, DWORD dwElapsed);

	void ProcNotifyMsg( CUnit* pkUnit, WORD const wType, BM::Stream* pkNfy);

	bool GMCommand( PgPlayer *pkPlayer, EGMCmdType const iCmdType, BM::Stream * const pkNfy );
	bool GMCommandToContents( PgPlayer *pkPlayer, EGMCmdType const iCmdType, BM::Stream * const pkNfy );
	virtual void GMCommand_RecvGamePoint( PgPlayer *pkPlayer, int const iPoint ){}

	void RecvChat( PgPlayer *pkUnit, BM::Stream *pkPacket );

//	+-------------------------------------------------------+
//	|	 파티 / 퀘스트 관련									|
//	+-------------------------------------------------------+
public:
	PgPlayer const* GetPartyMaster(PgPlayer const* pkPlayer)const;
	bool GetPartyMember(BM::GUID const & rkPartyGuid, VEC_GUID& rkOut)const;
	bool GetPartyMaster(CONT_PARTY_MASTER & rkOut)const;
	bool GetPartyMasterGuid(BM::GUID const & rkPartyGuid, BM::GUID& rkOutGuid)const;
	bool GetPartyMemberGround(BM::GUID const & rkPartyGuid, SGroundKey const& rkGndKey, VEC_GUID& rkOutVec, BM::GUID const & rkIgnore = BM::GUID::NullData())const;
	bool GetPartyMemberGround(PgPlayer const* pkPlayer, SGroundKey const& rkGndKey, VEC_GUID& rkOutVec, BM::GUID const & rkIgnore = BM::GUID::NullData())const;
	size_t GetPartyMemberCount(BM::GUID const & rkPartyGuid)const;
	//void SendToGroundPartyPacket(SGroundKey const& rkGndKey, BM::GUID const & rkPartyGuid, VEC_GUID const& rkRecvGuidVec, BM::Stream const& rkPacket, DWORD const dwSendType = E_SENDTYPE_SELF) const;
	bool GetPartyOption(BM::GUID const & rkPartyGuid, SPartyOption& rkOut);
	bool GetPartyShareItem_NextOwner(BM::GUID const & rkPartyGuid, SGroundKey const& rkGndKey, BM::GUID& rkNextOwner);
	int GetPartyMemberFriend(BM::GUID const & rkPartyGuid, BM::GUID const & rkCharGuid);
	bool CheckEffectFromPartyMember( BM::GUID const & PartyGuid, int const EffectNo ); // 파티원에게 해당 이펙트가 모두 걸려있는지 검사
	void GetIndunPartyGuid(CONT_INDUN_PARTY & rkCont);
protected:
	bool SetPartyGuid( CUnit* pkUnit, BM::GUID const& rkNewGuid, EPartySystemType const kCause );
	void SetPartyGuid(BM::GUID const& rkCharGuid, BM::GUID const& rkNewGuid, EPartySystemType const kCause );
	void SetPartyGuid(VEC_GUID const& rkVecGuid, BM::GUID const& rkNewGuid, EPartySystemType const kCause );
    virtual bool CheckApplyUnitOwner(CUnit* pkOwner, BM::GUID& rkOutApplyOwner);
    virtual int GetGiveLevel(CUnit * pkMonster, CUnit * pkOwner);
	virtual void GiveExp(CUnit* pkMonster, CUnit* pkOwner);
	virtual void CheckMonsterDieQuest(CUnit* pkCaster, CUnit* pkMonster);
	bool CheckUnitOwner(CUnit* pkUnit, BM::GUID& rkOut, BM::GUID * pkOutApplyOwner=NULL);
	void PartyBuffAction(int& iMasterGroundNo, BM::GUID& rkPartyGuid, BM::GUID& kCharGuid, CUnit* pkUnit, bool bBuff, BM::Stream* pkPacket);

	void SendShowQuestDialog(CUnit* pkUnit, BM::GUID const &rkNpcGUID, EQuestShowDialogType const eQuestShowDialogType, int const iQuestID, int const iDialogID);
	void GiveAwakeValue(CUnit* pkMurderee, CUnit* pkMurderer);

//	+-------------------------------------------------------+
//	|	 원정대 관련										|
//	+-------------------------------------------------------+
public:

	bool GetExpeditionMember(BM::GUID const & ExpeditionGuid, VEC_GUID & Out);
	bool GetExpeditionMasterGuid(BM::GUID const & rkPartyGuid, BM::GUID& rkOutGuid)const;
	bool GetExpeditionMemberGround(BM::GUID const & ExpeditionGuid, SGroundKey const& GndKey, VEC_GUID & OutVec, BM::GUID const & Ignore = BM::GUID::NullData()) const;
	bool AccumulatePlayerHeal(CUnit * pHealCaster, int HealValue);	// 힐을 사용 했을 때(원정대 던전에서만 사용).
	bool CheckEffectFromExpeditionMember( BM::GUID const & ExpeditionGuid, int const EffectNo ); // 원정대원에게 해당 이펙트가 모두 걸려있는지 검사
protected:

	typedef std::vector<SExpeditionInviteUserInfo> ContExpeditionInviteUserInfo;

	bool SetExpeditionGuid( CUnit* pUnit, BM::GUID const & NewGuid, EPartySystemType const Cause );
	void SetExpeditionGuid(BM::GUID const & CharGuid, BM::GUID const & NewGuid, EPartySystemType const Cause);
	void SetExpeditionGuid(VEC_GUID const& VecGuid, BM::GUID const& NewGuid, EPartySystemType const Cause);

//	+-------------------------------------------------------+
//	|	 NetWork Method										|
//	+-------------------------------------------------------+
	void Recv_PT_C_M_REQ_JOIN_LOBBY( CUnit *pkUnit, BM::Stream &rkPacket );
	void Recv_PT_T_M_ANS_REGIST_HARDCORE_VOTE( BM::Stream &rkPacket );
	void Recv_PT_C_M_REQ_RET_HARDCORE_VOTE( CUnit *pkUnit, BM::Stream &rkPacket );
	void Recv_PT_T_M_ANS_RET_HARDCORE_VOTE_CANCEL( BM::Stream &rkPacket );
	void Recv_PT_T_M_REQ_JOIN_HARDCORE( BM::Stream &rkPacket );

//	+-------------------------------------------------------+
//	|	 피로도 관련										|
//	+-------------------------------------------------------+

public:

	void Recv_PT_T_M_NFY_RECOVERY_STRATEGY_FATIGUABILITY(int RecoveryValue);

protected:

//	+-------------------------------------------------------+
//	|	 AI 관련										    |
//	+-------------------------------------------------------+
    void StartAI() { m_bRunAI = true; }
    void StopAI() { m_bRunAI = false; }
    bool IsRunAI() const { return m_bRunAI; }

public:
	void SyncPlayerPlayTime(BM::GUID const kCharGuid, int const iAccConSec, int const iAccDisSec, __int64 const i64SelectSec);

//	+-------------------------------------------------------+
//	|	상속받은 클래스가 필요에 따라 추가하는 함수			|
//	+-------------------------------------------------------+
public:
//	PgPvPGround Method

public://영역 및 AI Protected 로 할것.
	//void SendNftMonsterGoal(CUnit* pkUnit,CUnit* pkTarget,POINT3& kPos);
	//void ProcessMonsterAttack(CUnit* pkMonster, CUnit* pkTarget, NxVec3& kNormal, int iSkill);
	//bool FindWayPos(CUnit* pkUnit);
	//bool FindBeforeWayPoint(int const& iGroup, int const& iIndex,POINT3& pt3NextPos);
	//bool FindNearWayPoint(POINT3 const& pt3Pos,int& iGroup , int& iIndex);
	//bool FindNextWayPoint(int const& iGroup, int const& iIndex,POINT3& pt3NextPos);
	//PgWayPoint2* GetWayPoint(int iGroup, int iIndex);

	bool GroundWeight(int const iWeight);
	void TunningLevel(int const iLevel);
	bool GetHaveAbilUnitArray(UNIT_PTR_ARRAY &rkUnitArray, WORD const kAbilType, EUnitType const eUnitType );
	int GroundTunningNo()const;

// 컨텐츠
protected:
	bool ReqJoinHardCoreDungeon( PgPlayer * pkUser, SGroundKey const *pkDungeonGndKey );
	
	void AddUnitArray( UNIT_PTR_ARRAY &kUnitArray, EUnitType const kUnitType );

	void ReqProjectileAction(CUnit* pkSendUnit, BM::Stream * const pkPacket);
	void RecvReqAction2(CUnit* pkUnit, SActionInfo& rkAction, BM::Stream * const pkPacket);
	virtual bool VCheckUsableSkill(CUnit* pkUnit, const SActionInfo& rkAction) { return true; } //그라운드 마다 스킬 사용 유무를 체크하기 위한 함수

	EActionResultCode CheckAction2(CUnit* pkUnit, const SActionInfo& rkAction);
	bool CheckAction2_SubFunc_CheckPlayerAction(PgPlayer* pkPlayer, CSkillDef* pkSkillDef, SActionInfo const& rkAction, EActionResultCode& rkOut);

	bool FireSkill(CUnit* pkCaster, UNIT_PTR_ARRAY& rkTargetArray, const SActionInfo &rkAction, PgActionResultVector* pkActionResultVec);
	bool FireToggleSkill(CUnit* pkCaster, UNIT_PTR_ARRAY& rkTargetArray, const SActionInfo &rkAction, PgActionResultVector* pkActionResultVec);
	void FireSkillFailed(CUnit* pkCaster, UNIT_PTR_ARRAY& rkTargetArray, const SActionInfo &rkAction, PgActionResultVector* pkActionResultVec);	
	void RecvReqTrigger(CUnit* pkUnit, int const iType, BM::Stream *pkNfy);
	void RecvReqRegQuickSlot(CUnit* pkUnit, size_t const slot_idx, SQuickInvInfo const& kQuickInvInfo);
	void RecvReqRegQuickSlotViewPage(CUnit* pkUnit, char const cViewPage);
	void RecvReqCastBegin(CUnit* pkUnit, int const iSkillNo, DWORD const dwCurrentTime);
	void ReqMonsterTrigger(CUnit* pkUnit, BM::GUID const & kObjectGuid, int iActionType);

	void CheckTargetList(UNIT_PTR_ARRAY& rkTargetArray); // 대신 맞는 타겟이 있는지 검사하여 리스트를 갱신한다.
	bool CheckHackingAction(CUnit* pkUnit, SActionInfo& rkAction); // 액션이 해킹된 것인지 체크 한다.
	void GetClinetProjectileInfo(CUnit* const pkCaster, SActionInfo const & rkAction, CSkillDef const* pkSkillDef, SClientProjectile & kInfo) const;
	void CheckEffectUser(CUnit* pkUnit);
	void HiddenMapCheck(CUnit* pkUnit);
	void HiddenMapTimeLimit(CUnit* pkUnit);
	void GetHiddenMapTime(DWORD &m_dwTotalTimeLimit);

	//>>Quest
	void SendAllQuestInfo(PgPlayer* pkPlayer);
	void ReqIntroQuest(CUnit *pkUnit, int const iQuestID, BM::GUID const& rkObjectGuid);
	void ReqRemoteCompleteQuest(CUnit *pkUnit, int const iQuestID);
	//<<Quest
	void ReqNpcTrigger(CUnit* pkUnit, BM::GUID const& kObjectGuid, int iActionType);

	//>>WorldEvent
	virtual void DoWorldEventAction(int const iGroundNo, SWorldEventAction const& rkAction, PgWorldEvent const& rkWorldEvent);
	virtual void DoWorldEventCondition(int const iGroundNo, SWorldEventCondition const& rkCondition, PgWorldEvent const& rkWorldEvent, CUnit const* pkCaster = NULL);
	virtual void NfyWorldEventToGroundUser(PgWorldEventState const& rkState);
	//<<WorldEvent
	//>>
	virtual void NfyWEClientOjbectToGroundUser(PgWEClientObjectState const& rkState);
	//<<

	virtual void DynamicGndAttr(EDynamicGroundAttr const eNewDGAttr);
	void CheckTickMarry();
	void CheckTickHidden();
	void CheckTickCouple();

	virtual void RecvUnitDie(CUnit *pkUnit);
	virtual bool PushBSInvenItem(CUnit* pkUnit, PgBase_Item const& rkItem)		{ return false; }

	virtual bool PushMissionDefenceInvenItem(CUnit* pkUnit, PgBase_Item const& rkItem)		{ return false; }

	virtual void Defence7ItemUse(CUnit* pkUnit, BM::Stream * const pkPacket);
    int GetGuardianTunningNo(int const iGuardian)const;
	void SetGuardianAbil(CUnit* pkUnit, SMISSION_DEFENCE7_GUARDIAN const& kValue)const;
	void SetGuardianAbilUpdate(CUnit* pkUnit, int const iMonAbilNo)const;
//---------------------------------------------------------------------
// Alram Mission
	virtual void OnTick_AlramMission( PgPlayer *pkPlayer, DWORD const dwCurTime );
	virtual bool IsAlramMission(void)const{return ( NULL != m_pkAlramMissionMgr );}

public:
	virtual void CallAlramReward( PgPlayer * pkPlayer );
// Alram Mission
//======================================================================
//---------------------------------------------------------------------
// SimpleMarket 노점
public:
	bool RecvReqVendorCreate(CUnit* pkUnit, BM::GUID const& rkVendorGuid, std::wstring const& VendorTitle);
	bool RecvReqVendorRename(CUnit* pkUnit, BM::GUID const& rkVendorGuid, std::wstring const& VendorTitle);
	bool RecvReqVendorDelete(CUnit* pkUnit, BM::GUID const& rkVendorGuid);
	bool RecvReqReadToPacketVendorName(CUnit* pkUnit, BM::GUID const& rkVendorGuid, BM::Stream &rkPacket);
	void RecvVendorClose(CUnit* pkUnit);
//======================================================================
	CLASS_DECLARATION_S(DWORD, LastGenCheckTime);
	CLASS_DECLARATION_S_NO_SET(BM::GUID, GroundMute);
	//CLASS_DECLARATION_S(DWORD, LastTickTime);
#ifdef DEF_ESTIMATE_TICK_DELAY
	CLASS_DECLARATION_S(DWORD, Tick100msDelayAverage);
#endif
	CLASS_DECLARATION_S_NO_SET(EDynamicGroundAttr, DynamicGndAttr);
	CLASS_DECLARATION_S_NO_SET(PgEventQuest, EventQuest);
	CLASS_DECLARATION_S(SMapPlayTime, PlayTime);
	CLASS_DECLARATION_S(__int64, LastPlayTimeCalculateTime);	// CGameTime::GetLocalTimeSec()
	typedef std::vector< DWORD > LASTTICKTIME_VEC;
	LASTTICKTIME_VEC m_kContLastTickTime;
	CLASS_DECLARATION_S_NO_SET(PgWorldEnvironmentStatus, WorldEnvironmentStatus);
	CLASS_DECLARATION_S(DWORD, LastAddExpInVillageTickTime);
	CLASS_DECLARATION_S(DWORD, DefendModeTickTime);
	CLASS_DECLARATION_S(bool, HiddenMapOut);
	CLASS_DECLARATION_S(bool, IndunPartyDie);

public:
	int GetMapLevel()const{return m_iMapLevel;}
	void SetMapLevel( int const iMapLevel );

	HRESULT SetEvent( TBL_EVENT const &kTblEvent );

	virtual bool IsBSItem(int const iItemNo) const				{ return false; }
	void UpdateWorldEnvironmentStatus(SWorldEnvironmentStatus const& rkNewEnvStatus);

	void SetRealmQuestStatus(SRealmQuestInfo const& rkRealmQuestInfo);

    virtual void SetTeam(BM::GUID const& kGuid, int const iTeam);
    virtual int GetTeam(BM::GUID const& kGuid)const;
	virtual bool IsDefenceItemList(int const iItemNo) const		{ return false; }
	bool GetDefenceModeMatchParty(BM::GUID const& kMyPartyGuid, BM::GUID& rkPartyGuid);
	int DefenceIsJoinParty(BM::GUID const& kPartyGuid);
	bool DefenceAddWaitParty(BM::GUID const& kPartyGuid, int eType);
	bool DefenceModifyWaitParty(BM::GUID const& kPartyGuid, int eType);
	bool DefenceDelWaitParty(BM::GUID const& kPartyGuid);
	void SendDefencePartyAllList(CUnit* pkUnit);

	PgJobSkillLocationMgr& JobSkillLocationMgr()		{ return m_kJobSkillLocationMgr; }
	void JobSkillLocationItemInit();
	void CheckTickJobSkillLocationItem();
    bool IsEventScriptPlayer()const { return !m_kContEventScriptPlayer.empty(); }

	void RemoveInstanceItem(TBL_DEF_MAP_REGEN_POINT const & GenInfo, BM::GUID const & ItemGuid);
	void RemoveReserveDeleteInsItem(BM::GUID const & CharGuid);
	void ReserveDeleteInsItem(BM::GUID const & CharGuid, TBL_DEF_MAP_REGEN_POINT const & GenInfo, BM::GUID const & ItemGuid);
	void UpdateDeleInsItemOwner(BM::GUID const & Looter, BM::GUID const & Droper);
	bool RemoveGenGroupInsItem(int const iGenGroupNo);

///////////////////////////////////////////////////////////////////////
///////////////////////// 커뮤니티 이벤트 //////////////////////////////////
////////////////////////////////////////////////////////////////////////////
public:

	EErrorEventMapMove Recv_PT_C_M_REQ_MOVE_EVENT_GROUND(CUnit * pUnit, BM::Stream & Packet);
	void MoveToEventGround(int EventNo, PgPlayer * pPlayer, int GroundNo, bool bMaster = false, bool bSendCenter = false);
	void Recv_PT_T_M_NFY_COMMUNITY_EVENT_GROUND_STATE_CHANGE(int EventNo, bool EventMapState);
	void Recv_PT_T_M_NFY_EVENT_GROUND_USER_COUNT_MODIFY(int EventNo, int UserCount);

protected:

	virtual void AddJoinPartyMemberList(BM::Stream & Packet);
	void DelJoinPartyMemberList(BM::GUID & CharGuid);
	void CheckJoinPartyMemberList(CUnit * pUnit);

////////////////////////////////////////////////////////////////////////////

protected:
	
	int					m_iMapLevel;
	ContArea			m_kAreaCont;	//Small Area
	PgSmallArea*		m_pkBigArea;
	int					m_iGroundWeight;
	int					m_iTunningLevel;
	int					m_iGroundTunningNo;
    SET_GUID            m_kContEventScriptPlayer; //실행중인 EventScript UserGuid
	bool				m_bIsBossRoom;
	int					m_iMapMoveResultStartTimeSec;

	int m_iMonsterControlID;	//이름 짓기 정말 힘들다..
	DWORD m_dwTimeStamp;

	ContGenPoint_Monster		m_kContGenPoint_Monster;//몬스터 리젠포인트
	ContGenPoint_Object			m_kContGenPoint_Object;// ObjectUnit 리젠 포인트
	ContGenPoint_InstanceItem	m_ContGenPoint_InstanceItem_AnyTeam;// InstanceItem 리젠 포인트
	ContGenPoint_InstanceItem	m_ContGenPoint_InstanceItem_RedTeam;// InstanceItem 리젠 포인트
	ContGenPoint_InstanceItem	m_ContGenPoint_InstanceItem_BlueTeam;// InstanceItem 리젠 포인트
	ContGenPoint_Object			m_kContGenPoint_SummonNPC;// SummonedNPC 리젠 포인트

	PgAIManager m_kAIMng;	// 일단 Ground에 소속되도록 해 놓았지만, Global로 빼 놓을 만도 하다.(Lock문제만 해결 된다면 가능)

	CONT_MONSTER_GEN		m_kContRareMonsterGen;// 희귀 몬스터 젠 테이블
	CONT_GENERATED_MONSTER	m_kContGeneratedMonster;//이미 젠된 몬스터 테이블 같은 희귀 몬스터가 다시 젠 될수 없다.

	CONT_EVENT_MONSTER_GEN	m_ContEventMonsterGen; // 이벤트 몬스터 젠 테이블.
	CONT_GENERATED_MONSTER	m_ContGeneratedEventMonster; //이미 젠된 몬스터 테이블 같은 이벤트 몬스터가 다시 젠 될수 없다.

	VEC_EVENTDROPANYMONSTER m_ContEventDropAnyMonster; // 이벤트 중 특정 이벤트는 모든 몬스터에게서 동일한 아이템이 드랍되도록 한다.

	CONT_DELETERESERVERINSITEM m_ContDeleteReserveInsItem;	// 리젠 주기가 0으로 설정된 인스턴스 아이템은 원하는 시점에 리젠시키길 원하는 아이템.

	CONT_EVENT_MAP_ENTERABLE_ENTER_LIST	m_EventMapEnterableList;

	CONT_CURRENT_EVENT_MAP_USER_COUNT_LIST m_CurrentEventMapUserCountList;

	// 미리 만들어둔 파티에 가입할 캐릭터들의 리스트. 접속시에 만들어둔 파티에 넣어준다.
	CONT_JOIN_PARTY_MEMBER_LIST m_JoinPartyMemberList;

	// 그라운드의 소유자(현재는 엠포리아만 사용한다. 나중에 MyHome에서도 사용 할 수 있다.
	SGroundOwnerInfo		m_kGroundOwnerInfo;

	CONT_REALM_QUEST_INFO	m_kRealmQuestInfo;

public:
	bool PickUpGroundBox(CUnit* pkUnit, BM::GUID const& rkGuid, CUnit* pkLooter = NULL);
	void AddEffectToAllPlayer(int const iEffectNo);
	void HiddenMapRewordItem(CUnit* pkUnit);

public:
	// 특정옵션
	virtual bool IsGroundEffect()const{return true;}// 그라운으 이펙트 사용 여부
	virtual bool IsUseItem()const{return true;}// 소비 아이템을 사용 여부
	virtual bool IsDecEquipDuration()const{return true;}// 죽었을때 아이템 내구도 까기
	virtual bool IsDeathPenalty()const{return true;}// 죽었을때 패널티 주기

protected:
	static void SendUnitPosChange( CUnit *pkUnit, BYTE const eType, DWORD const dwSendFlag );

	virtual bool IsMacroCheckGround() const;
	void SetChangeGroundOwnerInfo( SGroundOwnerInfo const &kInfo, bool const bBroadCast=true );

	// Observer Mode Packet
	HRESULT SetOBMode_Start( PgPlayer *pkCasterPlayer, CUnit *pkTarget );
	HRESULT SetOBMode_Start( PgNetModule<> const &kNetModule, BM::GUID const &kCharID, CUnit *pkTarget, bool const bOnlyModule );
	HRESULT SetOBMode_End( BM::GUID const &kCharID );

	bool ProcessObserverPacket( BM::GUID const &kCharGuid, PgNetModule<> const &kNetModule, PgPlayer *pkPlayer, BM::Stream::DEF_STREAM_TYPE const kType, BM::Stream &rkPacket );
	int GetMapAbil(WORD const wType);	// public 함수 아님..(Lock 안했음)

	mutable Loki::Mutex m_kRscMutex;

	DWORD m_dwOnTick1s_Check2s;	//2초마다 유저의 스피드해킹 카운트를 초기화 시켜 줄려고.
	typedef std::map<int, int> CONT_MAPABIL;
	CONT_MAPABIL	m_kContMapAbil;


protected:
	PgLocalPartyMgr		m_kLocalPartyMgr;
	PgUserQuestSessionMgr m_kQuestTalkSession;
	PgLocalVendorMgr	m_kLocalVendorMgr;

	//
	PgMarryMgr				m_kMarryMgr;
	PgHiddenRewordItemMgr	m_kHiddenRewordItemMgr;
	PgEventItemSetMgr		m_kEventItemSetMgr;
	PgDefencePartyMgr		m_kDefencePartyMgr;
	PgJobSkillLocationMgr	m_kJobSkillLocationMgr;
	PgDuelMgr				m_kDuelMgr;

private:

	bool Recv_PT_I_M_MYHOME_MOVE_TO_HOMETOWN(BM::Stream* const pkPacket );
    
    bool m_bRunAI;
	__int64 m_i64EventViewOldTime;

	CUnit* IsUnitInRangeImp(CUnit *pUnit, POINT3 const& ptFind, int const iRange, EUnitType const eType, int const iZLimit, bool const bFindFromGround);
	CUnit* GetReservedUnitByEffect(CUnit *pUnit);

public: 
	void SetEventScript_LockPartyMember(CUnit const *pkUnit, int const iEventScriptID);
	void SetEventScript_UnLockPartyMember(CUnit const *pkUnit);
	
	void Set_LockPlayerInGround();
private:
	void SetEventScript_PartyLock( CUnit const *pkUnit, int const iEventScriptID, BM::Stream::DEF_STREAM_TYPE const kPacketType );

/////////////////////////// 별자리 던전 ////////////////////////////////////
public:
	DWORD const Constellation_CheckCondition(PgPlayer *pPlayer, Constellation::ConstellationKey const& Key, bool const UseCashItem, int & NeedItemNo, int & NeedItemCount);
	Constellation::ECE_RESULT Constellation_MoveDungeon(PgPlayer *pPlayer, Constellation::ConstellationKey const& Key, int & NeedItemNo, int & NeedItemCount);
	Constellation::ECE_RESULT Constellation_MoveDungeon_Boss(PgPlayer *pPlayer, Constellation::SConstellationKey const& Key);
	void Constellation_NotifyResult(PgPlayer *pPlayer, DWORD const dwRet, int const worldNo, Constellation::ConstellationKey const& Key);

	void SetConstellationKey(Constellation::SConstellationKey const& constellationKey) { m_ConstellationKey = constellationKey; }
	Constellation::SConstellationKey const& GetConstellationKey()const { return m_ConstellationKey; }

	void Constellation_GetMapNo(VEC_INT & ContMapNo);
private:
	Constellation::SConstellationKey m_ConstellationKey;

	bool Constellation_CheckCondition_CashItem(PgPlayer *pPlayer, int & NeedItemNo, int & NeedItemCount);
	DWORD Constellation_CheckCondition_DayofWeek(Constellation::CONT_CONSTELLATION_ENTER::mapped_type const& MissionInfo);
	DWORD Constellation_CheckCondition_Level(PgPlayer *pPlayer, Constellation::CONT_CONSTELLATION_ENTER::mapped_type const& MissionInfo);
	DWORD Constellation_CheckCondition_Item(PgPlayer *pPlayer, Constellation::CONT_CONSTELLATION_ENTER::mapped_type const& MissionInfo, int & NeedItemNo, int & NeedItemCount);
	DWORD Constellation_CheckCondition_Quest(PgPlayer *pPlayer, Constellation::CONT_CONSTELLATION_ENTER::mapped_type const& MissionInfo);

	bool Constellation_Consume_Item(PgPlayer *pPlayer, Constellation::CONT_CONSTELLATION_ENTER::mapped_type const& MissionInfo
									, PgReqMapMove & MapMove, int const& NeedItemNo, int const& NeedItemCount); // 입장 아이템 소비
////////////////////////////////////////////////////////////////////////////
};

#include "PgGround.inl"

float const COUPLE_PASSIVE_HPMP_INCREASE_EFFECT_ABLE_DIST = 600.f;	//꿩먹고 알먹고 이펙트 가능 거리
float const DEFAULT_CLASS_AWAKE_VALUE_REVISER = 2.4f;
#endif // MAP_MAPSERVER_MAP_GROUND_PGGROUND_H