#pragma once

#include "PgGround.h"

class PgGuildHouse
	:	public PgGround
{
public:
	PgGuildHouse();
	virtual ~PgGuildHouse();

	virtual void Clear();
	bool Clone( PgGuildHouse *pkGround );
	virtual bool Clone( PgGround *pkGround );

	virtual EOpeningState Init( int const iMonsterControlID=0, bool const bMonsterGen=true );
	virtual EGroundKind GetKind(){return GKIND_EMPORIA;}

	virtual void OnTick30s();

public:
	virtual bool VUpdate( CUnit* pkUnit, WORD const wType, CEL::CPacket* pkNfy );
	virtual bool RecvGndWrapped( unsigned short usType, CEL::CPacket* const pkPacket );

protected:
	virtual void FilterGateWay( UNIT_PTR_ARRAY& rkAddUnitArray, UNIT_PTR_ARRAY& kFailedUnitArray, SReqMapMove_MT &rkRMM );

public:
// 전용함수
//	CONT_MEMBER_GUILDHOUSE::key_type GetKey()const{return CONT_MEMBER_GUILDHOUSE::key_type(GetGroundNo());}
	bool IsHoldSiegeWar()const{return BM::GUID::IsNotNull(m_kHoldSiegeWarID);}
	bool IsIngSiegeWar()const{return m_kWarGroundKey.GroundNo()>0;}
	bool IsCreateSiwgeWarGround()const{return BM::GUID::IsNotNull(m_kWarGroundKey.Guid());}
	bool IsEmptyMaster()const{return BM::GUID::IsNull(m_kGuildGuid);}
	
	bool BeginWar();
	bool ReadyWar( SGroundKey const &rkGndKey );
	bool StartWar();
	void FailedWar();
	bool EndWar( BM::GUID const &kWinGuild );

protected:

	HRESULT RecvDeclareSiegeWar( CEL::CPacket &kPacket, short const nChannelNo );
//	void SetGuildMaster( SGuildHouseInfo const &kGuildInfo, BYTE const kDBType=PgGuildHouseMgr::SW_UPDATE_ERROR );
//	void GetBaseSiegeWarinfo( CONT_SIEGEWAR_LIST::mapped_type &kElement );

	void SetNextTime();
private:

	BM::GUID				m_kGuildGuid;// Guild GUID
	std::wstring			m_kGuildName;//	Guild Name
	std::wstring			m_kMasterName;// Master Name
	int						m_iDefStringName;

	BM::GUID				m_kHoldSiegeWarID;
	__int64					m_i64NextSiegeWarTime;
	bool					m_bNotice;
	SGroundKey				m_kWarGroundKey;
};
