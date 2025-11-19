#pragma once

#include "lohengrin/PgRealmManager.h"

typedef enum eDBQueryType_Immgration
{
	DQT_LOAD_SITE_CONFIG			= 1,
	DQT_LOAD_REALM_CONFIG			= 2,

//	DQT_TRY_AUTH					= 5,

	DQT_LOAD_MAP_CONFIG_STATIC		= 6,
	DQT_LOAD_MAP_CONFIG_MISSION		= 7,
	DQT_LOAD_MAP_CONFIG_PUBLIC		= 8,
	DQT_PATCH_VERSION_EDIT			= 9,

}EDBQueryType_Immgration;

class PgSiteMgr
{
public:
	PgSiteMgr(void);
	virtual ~PgSiteMgr(void);

public:
	void LoadFromDB();

	void GetRealmCandi(CONT_REALM_CANDIDATE &kOutCont)const;

	HRESULT Q_DQT_LOAD_REALM_CONFIG(CEL::DB_RESULT &rkResult);
	HRESULT Q_DQT_LOAD_SITE_CONFIG(CEL::DB_RESULT &rkResult);

	HRESULT Q_DQT_LOAD_MAP_CONFIG_STATIC(CEL::DB_RESULT &rkResult);
	HRESULT Q_DQT_LOAD_MAP_CONFIG_MISSION(CEL::DB_RESULT &rkResult);
	HRESULT Q_DQT_LOAD_MAP_CONFIG_PUBLIC(CEL::DB_RESULT &rkResult);

	HRESULT Q_DQT_PATCH_VERSION_EDIT(CEL::DB_RESULT &rkResult);

protected:
	CONT_REALM_CANDIDATE m_kRealmCandi;
	mutable Loki::Mutex m_kMutex;
};

#define g_kSiteMgr SINGLETON_STATIC(PgSiteMgr)