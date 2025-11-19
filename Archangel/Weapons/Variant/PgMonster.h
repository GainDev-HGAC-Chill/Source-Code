#ifndef WEAPON_VARIANT_UNIT_PGMONSTER_H
#define WEAPON_VARIANT_UNIT_PGMONSTER_H

#include "unit.h"

typedef enum
{
	EMONTYPE_NORMAL		= 0,	// 보통몬스터
	EMONTYPE_FLYING		= 1,	// 공중형 몬스터
} EMonsterType;

typedef enum
{
	EPS_NONE		= 0,
	EPS_NORMAL		= 1,
	EPS_FRENZY		= 2,
	EPS_GROGGY		= 3,
	EPS_INIT		= 100,
} EElitePattenStateType;

#pragma pack(1)

typedef struct tagMonsterCreate
{
	tagMonsterCreate()
		:	kGuid()
		,	iMonNo(0)
		,	iControlID(0)
		,	iWeight(0)
		,	iTunningLevel(0)
		,	iEnchantGradeNo(0)
		,	wstrName()
		,	kTable()
	{}

	BM::GUID kGuid;//몬스터의 GUID
	int iMonNo;
	int iControlID;
	int iWeight;	// 가중치(유저의 수에따른)
	int iTunningLevel;
	int iEnchantGradeNo;
	std::wstring wstrName;
	TBL_DEF_MAP_REGEN_POINT kTable;
}SMonsterCreate;
#pragma pack()

typedef struct tagIgnoreTarget
{
	tagIgnoreTarget() : kTime(0)
	{}

	tagIgnoreTarget(BM::GUID const& rkGuid, POINT3 const& rkPos, DWORD const kNow) : 
	kGuid(rkGuid), kTargetPos(rkPos), kTime(kNow)
	{}

	bool IsMoved(POINT3 const& rkPos, float const fDist = 10.0) const	//이전 위치에서 움직였느냐
	{
		return fDist < POINT3::Distance(kTargetPos, rkPos);
	}
	BM::GUID	kGuid;		//타겟의 GUID
	POINT3		kTargetPos;	//타겟 위치
	DWORD		kTime;		//타겟 무시 시작 시작
	
}SIgnoreTarget;

class PgMonster 
	:	public CUnit
{
public:
	PgMonster(void);
	virtual ~PgMonster(void);

	typedef std::set<int> FAILED_SKILL_LIST;
	typedef std::map<BM::GUID, SIgnoreTarget> IGNORE_TARGET_LIST;

public:
	virtual HRESULT Create(void const* pkInfo);
	virtual EUnitType UnitType()const{ return UT_MONSTER; }
	virtual int GetAbil(WORD const Type) const;
	virtual __int64 GetAbil64(WORD const eAT)const;
	virtual bool SetAbil(WORD const Type, int const iValue, bool const bIsSend = false, bool const bBroadcast = false);
	virtual void WriteToPacket(BM::Stream &rkPacket, EWRITETYPE const kWriteType=WT_DEFAULT)const;
	virtual EWRITETYPE ReadFromPacket(BM::Stream &rkPacket);
// 	virtual void WriteToPacket(BM::Stream &rkPacket, bool const bIsSimple, bool const bIsForSave)const;
// 	virtual void ReadFromPacket(BM::Stream &rkPacket, bool &bIsSimple, bool &bIsForSave);
	virtual void Invalidate();
	virtual bool IsCheckZoneTime(DWORD dwElapsed);
	virtual int CallAction(WORD wActCode, SActArg *pActArg) { return 0; }
	virtual bool SetState(const EUnitState eState);

	virtual int GetMaxSummonUnitCount()						{ return 20; }

	virtual void Init();

	//bool IsAIType(const EMonsterAIType eMonAIType)const;

	CLASS_DECLARATION_S(TBL_DEF_MAP_REGEN_POINT, GenInfo);

	void SetGenPos(POINT3 const kPos){m_pt3Gen = kPos;}
	POINT3 const GetGenPos(){return m_pt3Gen;}

	void SetLastActionTime(DWORD dwTime);
	DWORD GetLastActionTime();
	void AddFailedSkill(int iSkillNo)	{ m_kFailSkill.insert(iSkillNo); }
	bool const IsFailedSkill(int const iSkillNo) const { return m_kFailSkill.end() != m_kFailSkill.find(iSkillNo); } 
	void AddIgnoreTarget(CUnit const* pkUnit, DWORD const dwNow);
	bool IsIgnoreTarget(BM::GUID const& rkGuid) const { return m_kIgnoreTargetList.end() != m_kIgnoreTargetList.find(rkGuid); }
	void ClearIgnoreTarget() { m_kIgnoreTargetList.clear(); }
	bool CheckIgnoreTarget(CUnit const* pkUnit, DWORD const dwNow);

	CLASS_DECLARATION_S_NO_SET(SAggro, Aggro);							//몬스터 개인 AI에서 쓰는 통계의 일부분
	virtual bool IsTarget(CUnit* pkTarget, bool bCheckTargetValid = true, int iSkillTargetType = ESTARGET_ENEMY, CSkillDef const* pkSkillDef = NULL, int iDmgCheckTime = -1);
protected:
	void SetBasicAbil( int const iControlID=0, int const iWeight=1, int const iTunningNo=0, int const iGrade=0, int const iTunningLv=0 );
	void SetCommonAbil();
	void TunningAbil();
	void TunningAbil(int const iNo, int const iLv, int const iGrade);
	void SetEnchantGrade(int const iEnchantGradeNo);
	void ApplyEnchantAbil(int const iMonAbilNo, bool const bSet, CONT_DEFMONSTERABIL const* pkDefMonAbil);

	virtual void VOnDie(){CUnit::VOnDie();}

private:
	void InitEliteAbil();
	void SetEliteTunningAbil(int const iLv);

protected:
	DWORD m_dwLastActionTime;
	POINT3 m_pt3Gen;		// Gen 되는 좌표값

	//CLASS_DECLARATION_S(int, WayPointIndex);
private:
	FAILED_SKILL_LIST	m_kFailSkill;
	IGNORE_TARGET_LIST	m_kIgnoreTargetList;
};

#endif // WEAPON_VARIANT_UNIT_PGMONSTER_H