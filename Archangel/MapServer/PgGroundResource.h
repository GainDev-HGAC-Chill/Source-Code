#ifndef MAP_MAPSERVER_MAP_GROUND_PGGROUNDRESOURCE_H
#define MAP_MAPSERVER_MAP_GROUND_PGGROUNDRESOURCE_H

#include "BM/ObjectPool.h"
#include "Variant/PgObjectMgr2.h"
#include "Variant/PgSmallAreaInfo.h"
#include "Variant/PgWorldEvent.h"
#include "Variant/PgWorldEventObject.h"
#include "PgGroundTrigger.h"
#include "PgPortal_Emporia.h"
#include "PublicMap/PgPvPModeStruct.h"
#include "PgStoneMgr.h"

#define LOADGSA_USE_SHARE
#define LOADGSA_FIND_MINMAX

// Available Entity 를 사용할지 여부.
#define LOADGSA_USE_AVAILABLE_ENTITY

HRESULT const GA_FORCE_MOVE_TO_SPAWN = 10;
typedef std::set<int> SET_INT;

class PgAlramMissionMgr_Warpper;

class PgGroundResource : public PgWorldEventMgr, public PgWEClientObjectServerMgr//리소스는. 락 필요 없음.
{

public:
	PgGroundResource();
	PgGroundResource( const PgGroundResource& rhs );
	virtual ~PgGroundResource();

public:
	PgGroundResource& operator=( const PgGroundResource& rhs );

	void CloneResource( const PgGroundResource* prhs );
	void Clear();

	HRESULT LoadGsa(char const *pcGsaPath);
	HRESULT LoadNif(char const *pcNifPath);
	HRESULT BuildAbil();
	int GetRscAbil(WORD const wType);

	bool FindMinMaxInLoadGsa(NiPhysXScene *pkScene, NiPoint3 kTranslation, char const *pcGsaPath);
	void FindMinMax(NiNode *pkNode, NxVec3 &kMin, NxVec3 &kMax);

	void SetScaleToPhysXObject(NiPhysXSceneDesc *pkDesc, float fScale);
	HRESULT GetAvailEntity(const NiEntityInterface *pkEntity) const;

	POINT3 GetNodePosition(char const *pcNodeName) const ;

	const NiAVObject* GetObjectByName_FromScene(std::string &rkName)const;
	NiPhysXScenePtr PhysXScene()const	{	return m_spPhysXScene;				}
	NiNode* GetSceneRoot()const			{	return (NiNode*)m_spSceneRoot;			}
	NiPhysXScene* GetPhysXScene()const	{	return (NiPhysXScene*)m_spPhysXScene;	}
	NiNode* GetPhysxObject()const		{	return m_pkPhysxObject;					}
	NiNode* GetPhysxNode()const			{	return m_pkPhysxNode;					}
	NiNode* GetPathRoot()const			{	return (NiNode*)m_spPathRoot;			}
	NiNode* GetSpawnRoot()const			{	return (NiNode*)m_spSpawnRoot;			}
	NiNode* GetPermissionRoot()const	{	return (NiNode*)m_spPermissionRoot;		}
	NiNodePtr GetTriggerNode()const		{	return m_spTriggerRoot;					}
	NiNode* GetTriggerRoot()const		{	return (NiNode*)m_spTriggerRoot;		}
	NiNode* GetpLadderRoot()const		{	return (NiNode*)m_spLadderRoot;			}
	CONT_GTRIGGER const& GetContTrigger()const{return m_kContTrigger;}
	
	NxVec3 const& GetMapMin()const		{return m_kMin;}
	NxVec3 const& GetMapMax()const		{return m_kMax;}

	bool GetLoadedByNif()const			{	return m_bLoadedByNif;	}
	bool GetFoundMinMax()const			{	return m_bFoundMinMax;	}
//	char const *GetDecoratorPath()const {	return m_kDecoratorPath.c_str();		}

	static int SearchNode( NiNode* pkTargetNode, const NiFixedString &kName, bool bRecursive = false );

	bool AddNPC( TiXmlAttribute const *pkAttribute );
	PgNpc* AddNPC(char const* pcName, char const* pcActor, char const* pcScript, char const* pcLocation, BM::GUID const &rkGuid, int iID, int GiveEffectNo, ENpcType const kNpcType=E_NPC_TYPE_FIXED );
	
	void AddStone( TiXmlAttribute const *pkAttribute );
	void AddStoneRegenPoint(SStoneRegenPoint const &kStoneRegenPoint);

	bool AddGTrigger( TiXmlElement const *pkElement );

	bool AddEventScriptStopAI(TiXmlElement const *pkElement);
	bool IsCheckEventScriptStopAI(int const iEventScriptNo)const;

	bool AddEventScriptNoLock(TiXmlElement const *pkElement);
	bool IsCheckEventScriptNoLock(int const iEventScriptNo)const;

	bool FindCorrectPos( POINT3 &rkPos, float const fZBuffer = 50.0f )const;
	bool IsCorrectPos(POINT3 const &rkPos)const;
	void RebuildQuest();
	typedef std::map< std::string, NiStream* > CONT_NiStream;

	CUnit* GetNPC(BM::GUID const &rkGuid)const;
	
	void SetResultSpawnLoc( POINT3 const &pt3Pos );
	void SetAlramMissionMgr( PgAlramMissionMgr_Warpper const * pkAlramMissionMgr ){m_pkAlramMissionMgr = pkAlramMissionMgr;}

// PvP
	bool LoadHill( size_t const iHillNo, char const *szValue );
	CONT_PVPHILL const &GetContPvPHill()const{return m_kContPvPHill;}

	void SetAttr( const T_GNDATTR kAttr )	{	m_kAttribute = kAttr;	}
	virtual T_GNDATTR GetAttr()const	{	return m_kAttribute;	}
	void AddAttr( const T_GNDATTR kAddAttr )	{	m_kAttribute |= kAddAttr;	}
	void RemoveAttr( const T_GNDATTR kRemoveAttr )	{	m_kAttribute &= (~kRemoveAttr);	} 
	bool IsPartyBreakIn()const	{ return m_bPartyBreakIn; }
	
	int GetRandomSpawn(int& iTeam)const;

	CLASS_DECLARATION_S(SGroundKey, GroundKey);
	CLASS_DECLARATION(bool, m_bOpeningMovie, OpeningMovie);
	CLASS_DECLARATION_S(int, MaxMonsterCount);	//그라운드에서 소환가능한 최대 몬스터 수(AT_IGNORE_GROUND_MONSTER_COUNT을 통해서 무시가능)

	CLASS_DECLARATION_S(int, MaxSpawnLocationCount);	// 맵에 있는 스폰 지역의 개수.
	CLASS_DECLARATION_S(int, SpawnCountPerLocation);	// m_nMaxSpawnLocationCount에 속한 스폰 위치 개수.

	PgStoneControl		m_kStoneCtrl;

	EUnitType GetUnlockBidirection() { return m_eUnlockBidirection; }
	void AddUnlockBidirection(EUnitType const eType) { m_eUnlockBidirection = static_cast<EUnitType>(m_eUnlockBidirection|eType); }
#ifdef LOADGSA_USE_SHARE
	static CONT_NiStream m_skShareStream;
#endif

	void CopyContGTrigger( CONT_GTRIGGER const& rkFrom );
	void UpdateGTrigger();

	PgEventAbil const * const GetEventAbil(void)const{return m_pkEventAbil;}

protected:
	NiNodePtr			m_spSceneRoot;					//! 맵 데이터의 루트
	NiPhysXScenePtr		m_spPhysXScene;					//! 맵의 물리데이터 씬
	NiNodePtr			m_pkPhysxObject;				// Physx 오브젝트
	NiNodePtr			m_pkPhysxNode;					// Node 오브젝트

	// 빠른 엑세스를 위한 노드들의 루트
	NiNodePtr			m_spPathRoot;					//! Path-wall의 루트 노드
	NiNodePtr			m_spSpawnRoot;					//! 스폰 더미들의 루트 노드
	NiNodePtr			m_spPermissionRoot;				//! 제한구역의 루트 노드
	NiNodePtr			m_spTriggerRoot;				//! 트리거 쉐이프들의 루트 노드
	NiNodePtr			m_spLadderRoot;					//! 사다리 쉐이프들의 루트 노드

	// m_bLoadedByNif 가 false 일 경우는 GSA 로딩.
	bool				m_bLoadedByNif;
	bool				m_bFoundMinMax;

	// 전체 맵의 Min Max
	NxVec3				m_kMin;
	NxVec3				m_kMax;

	CONT_OBJECT_MGR_UNIT	m_kNpcCont;

	// PvP에서 쓰는거
	CONT_PVPHILL		m_kContPvPHill;		// Hill List
	int					m_iSpawnCount[2];	// MultiSpawn Count

	// Ground Trigger
	CONT_GTRIGGER		m_kContTrigger;
	CONT_ORDER_CHECKPOINT	m_kContCheckPointOrder; //달리기 이벤트 전용 트리거 컨테이너 (체크포인트)

	// SmallArea Build Info
	PgSmallAreaInfo		m_kSmallAreaInfo;

	//8방향 풀지 말지
	EUnitType			m_eUnlockBidirection;

	CONT_EMPORIA_PORTAL	m_kContEmporiaPortal;

	// Evnet Abil
	PgEventAbil *		m_pkEventAbil;

	// Alram Mission Mgr
	PgAlramMissionMgr_Warpper const *	m_pkAlramMissionMgr;
	
	typedef std::map< WORD, int> DYN_ABIL;
	DYN_ABIL			m_kResourceAbil;

	POINT3*				m_pkPT3ResultSpawnLoc;

private:
	T_GNDATTR			m_kAttribute;
	SET_INT				m_kContEventScriptStopAI;	//이벤트 스크립트 작동중에 AI 작동하지 않을 목록
	SET_INT				m_kContEventScriptNoLock;	//이벤트 스크립트 락을 걸지 않을 목록
	bool				m_bPartyBreakIn;	//파티난입 가능유무
};

inline const NiAVObject* PgGroundResource::GetObjectByName_FromScene(std::string &rkName)const
{
	if(!m_spSceneRoot)
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__<<L"m_spSceneRoot == NULL");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return NULL"));
		return NULL;
	}
	return m_spSceneRoot->GetObjectByName(rkName.c_str());
}

inline int PgGroundResource::GetRandomSpawn(int& iTeam)const
{
	if ( (TEAM_MAX <= iTeam) || (TEAM_NONE == iTeam) )
	{
		iTeam = BM::Rand_Range( TEAM_RED, TEAM_BLUE );
	}
	
	if ( m_iSpawnCount[ iTeam - 1] > 0 )
	{
		return BM::Rand_Range( 1, m_iSpawnCount[ iTeam - 1 ] );
	}
	return 1;
}

#endif // MAP_MAPSERVER_MAP_GROUND_PGGROUNDRESOURCE_H