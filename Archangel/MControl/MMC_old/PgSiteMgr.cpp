#include "StdAfx.h"
#include "PgSiteMgr.h"

PgSiteMgr::PgSiteMgr(void)
{
}

PgSiteMgr::~PgSiteMgr(void)
{
}

void PgSiteMgr::LoadFromDB()
{
{
	TCHAR szTemp[100] = _T("TB_SiteConfig");
	::GetPrivateProfileString(_T("ETC"),_T("SERVER_TBNAME"),szTemp,szTemp,100,_T("./DB_Config.ini"));

	CEL::DB_QUERY kQuery( DT_SITE_CONFIG, DQT_LOAD_SITE_CONFIG, _T("EXEC [dbo].[UP_LoadSiteConfig]"));
	kQuery.PushStrParam((std::wstring)szTemp);
	g_kCoreCenter.PushQuery(kQuery, true);
}
{
	CONT_REALM_CANDIDATE::const_iterator realm_candi_itor =  m_kRealmCandi.begin();
	while(m_kRealmCandi.end() != realm_candi_itor)
	{
		CEL::DB_QUERY kQuery(DT_SITE_CONFIG, DQT_LOAD_REALM_CONFIG, _T("EXEC [dbo].UP_LoadRealmConfig"));

		kQuery.PushStrParam((*realm_candi_itor).second.RealmTblName());
		kQuery.PushStrParam((*realm_candi_itor).second.RealmNo());
		kQuery.PushStrParam((*realm_candi_itor).second.RealmName());

		g_kCoreCenter.PushQuery(kQuery, true);
		++realm_candi_itor;
	}
}
{
	TCHAR szTemp[100] = _T("TB_MapCfg_Static");
	::GetPrivateProfileString(_T("ETC"),_T("MAPCFG_TBNAME_STATIC"),szTemp,szTemp,100,_T("./DB_Config.ini"));
	CEL::DB_QUERY kQuery( DT_SITE_CONFIG, DQT_LOAD_MAP_CONFIG_STATIC, _T("EXEC [dbo].[UP_Load_MapCfg_Static]"));
	kQuery.PushStrParam(std::wstring(szTemp));
	g_kCoreCenter.PushQuery(kQuery, true);
}
{
	TCHAR szTemp[100] = _T("TB_MapCfg_Mission");
	::GetPrivateProfileString(_T("ETC"),_T("MAPCFG_TBNAME_MISSION"),szTemp,szTemp,100,_T("./DB_Config.ini"));
	CEL::DB_QUERY kQuery( DT_SITE_CONFIG, DQT_LOAD_MAP_CONFIG_MISSION, _T("EXEC [dbo].[UP_Load_MapCfg_Mission]"));
	kQuery.PushStrParam(std::wstring(szTemp));
	g_kCoreCenter.PushQuery(kQuery, true);
}
{
	TCHAR szTemp[100] = _T("TB_MapCfg_Public");
	::GetPrivateProfileString(_T("ETC"),_T("MAPCFG_TBNAME_PUBLIC"),szTemp,szTemp,100,_T("./DB_Config.ini"));
	CEL::DB_QUERY kQuery( DT_SITE_CONFIG, DQT_LOAD_MAP_CONFIG_PUBLIC, _T("EXEC [dbo].[UP_Load_MapCfg_Public]"));
	kQuery.PushStrParam(std::wstring(szTemp));
	g_kCoreCenter.PushQuery(kQuery, true);
}
}

void PgSiteMgr::GetRealmCandi(CONT_REALM_CANDIDATE &kOutCont)const
{
	BM::CAutoMutex kLock(m_kMutex);

	kOutCont = m_kRealmCandi;
}

HRESULT PgSiteMgr::Q_DQT_LOAD_SITE_CONFIG(CEL::DB_RESULT &rkResult)
{
	BM::CAutoMutex kLock(m_kMutex);

	if(CEL::DR_SUCCESS == rkResult.eRet 
	|| CEL::DR_NO_RESULT == rkResult.eRet)
	{
		CEL::DB_DATA_ARRAY::const_iterator kIter = rkResult.vecArray.begin();		
		while(rkResult.vecArray.end() != kIter)
		{
			short nRealmNo;
			std::wstring  strRealmName;
			std::wstring  strRealmTblName;
			
			kIter->Pop(nRealmNo); ++kIter;
			kIter->Pop(strRealmName); ++kIter;
			kIter->Pop(strRealmTblName); ++kIter;

			m_kRealmCandi.insert(std::make_pair(nRealmNo, tagRealmElement(nRealmNo, strRealmName, strRealmTblName)));
		}

		return S_OK;
	}

	VERIFY_INFO_LOG( false, BM::LOG_LV0, __FL__ << _T("None Data") );
	return E_FAIL;
}

HRESULT PgSiteMgr::Q_DQT_LOAD_REALM_CONFIG(CEL::DB_RESULT &rkResult)
{
	BM::CAutoMutex kLock(m_kMutex);

	if(CEL::DR_SUCCESS == rkResult.eRet)
	{
		short nRealm = 0;
		std::wstring kRealmName = _T("");

		CEL::DB_DATA_ARRAY::const_iterator itor = rkResult.vecArray.begin();
		if( rkResult.vecArray.end() != itor )
		{
			(*itor).Pop( nRealm );	++itor;
			(*itor).Pop( kRealmName );	++itor;
		}

		if( rkResult.vecArray.end() == itor )
		{//렐름 테이블 명을 잘못 기입.
			VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__ << _T("Wrong TblName<") << kRealmName << _T("> in Realm<") << nRealm << _T(">") );
//			VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] TblNameWrong"), __FUNCTIONW__, __LINE__);
			return E_FAIL;
		}

		while( rkResult.vecArray.end() != itor )
		{
			CONT_SERVER_HASH::mapped_type element;

			std::wstring kName = _T("");
			std::wstring kMachineIP = _T("");
			std::wstring kBindIP = _T("");
			std::wstring kNATIP = _T("");
			unsigned short usBindPort = 0;
			unsigned short usNatPort = 0;
			
			element.nRealm = nRealm;
			(*itor).Pop( element.nChannel );	++itor;
			(*itor).Pop( element.nServerNo );	++itor;
			(*itor).Pop( element.nServerType );		++itor;
			(*itor).Pop( kMachineIP );			++itor;
			(*itor).Pop( kName );				++itor;
			
			(*itor).Pop( kBindIP );				++itor;
			(*itor).Pop( usBindPort );			++itor;
			(*itor).Pop( kNATIP );				++itor;
			(*itor).Pop( usNatPort );			++itor;

			element.strMachinIP = kMachineIP;
			element.addrServerBind.Set(kBindIP, usBindPort);
			element.addrServerNat.Set(kNATIP, usNatPort);

			kBindIP = _T("");
			kNATIP = _T("");
			usBindPort = 0;
			usNatPort = 0;

			(*itor).Pop( kBindIP );			++itor;
			(*itor).Pop( usBindPort );			++itor;
			(*itor).Pop( kNATIP );			++itor;
			(*itor).Pop( usNatPort );			++itor;

			element.addrUserBind.Set(kBindIP, usBindPort);
			element.addrUserNat.Set(kNATIP, usNatPort);
			element.strName = kName;
			element.Build();

			bool bIsSuccess = g_kProcessCfg.Locked_AddServerInfo(element);
			if(!bIsSuccess)
			{
				VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__ << _T("Already Use ServerIdentity Realm<") << element.nRealm << _T("> Channel<") << element.nChannel << _T("> ServerNo<") << element.nServerNo << _T("> ServerType<") << element.nServerType << _T(">") );
			}
		}
		return S_OK;
	}

	VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__ << _T("TABLE [Tbl_ServerList] is row count 0") );
//	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] TABLE [Tbl_ServerList] is row count 0"), __FUNCTIONW__, __LINE__);
	return E_FAIL;
}

HRESULT PgSiteMgr::Q_DQT_LOAD_MAP_CONFIG_STATIC( CEL::DB_RESULT &rkResult )
{
	BM::CAutoMutex kLock(m_kMutex);

	if(CEL::DR_SUCCESS == rkResult.eRet)
	{
		CEL::DB_DATA_ARRAY::const_iterator itor = rkResult.vecArray.begin();
		while( rkResult.vecArray.end() != itor )
		{
			CONT_MAP_CONFIG::key_type element;

			(*itor).Pop( element.nRealmNo );	++itor;
			(*itor).Pop( element.nChannelNo );	++itor;
			(*itor).Pop( element.nServerNo );	++itor;
			(*itor).Pop( element.iGroundNo );	++itor;
			
			if( (0==element.nChannelNo) || FAILED(g_kProcessCfg.Locked_AddMapCfg(element)) )
			{
				VERIFY_INFO_LOG(false, BM::LOG_LV1, __FUNCTIONW__ << _T(" Insert Failed Realm[") << element.nRealmNo
					<< _T("] Channel[") << element.nChannelNo << _T("] Server[") 
					<< element.nServerNo << _T("] Ground[") << element.iGroundNo << _T("]") );
				//VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s] Insert Failed Realm[%d] Channel[%d] Server[%d] Ground[%d]"), __FUNCTIONW__, element.nRealmNo, element.nChannelNo, element.nServerNo, element.iGroundNo);
			}
		}
		return S_OK;
	}

	VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__ << _T("TABLE row count 0") );
//	VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s]-[%d] TABLE row count 0"), __FUNCTIONW__, __LINE__);
	return E_FAIL;
}

HRESULT PgSiteMgr::Q_DQT_LOAD_MAP_CONFIG_MISSION( CEL::DB_RESULT &rkResult )
{
	BM::CAutoMutex kLock(m_kMutex);

	if(CEL::DR_SUCCESS == rkResult.eRet)
	{
		CEL::DB_DATA_ARRAY::const_iterator itor = rkResult.vecArray.begin();
		while( rkResult.vecArray.end() != itor )
		{
			CONT_MAP_CONFIG::key_type element;

			(*itor).Pop( element.nRealmNo );	++itor;
			(*itor).Pop( element.nChannelNo );	++itor;
			(*itor).Pop( element.nServerNo );	++itor;
			(*itor).Pop( element.iGroundNo );	++itor;

			if( (0==element.nChannelNo) || FAILED(g_kProcessCfg.Locked_AddMapCfg_Mission(element)) )
			{
				VERIFY_INFO_LOG(false, BM::LOG_LV0, __FL__ << _T(" Insert Failed Realm[") << element.nRealmNo 
					<< _T("] Channel[") << element.nChannelNo << _T("] Server[") << element.nServerNo
					<< _T("] MissionNo[") << element.iGroundNo <<_T("]") );
//				VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("[%s] Insert Failed Realm[%d] Channel[%d] Server[%d] MissionNo[%d]"), __FUNCTIONW__, element.nRealmNo, element.nChannelNo, element.nServerNo, element.iGroundNo);
			}
		}
		return S_OK;
	}

	//INFO_LOG(BM::LOG_LV0, _T("[%s]-[%d] TABLE row count 0"), __FUNCTIONW__, __LINE__);
	return E_FAIL;
}

HRESULT PgSiteMgr::Q_DQT_LOAD_MAP_CONFIG_PUBLIC(CEL::DB_RESULT &rkResult)
{
	BM::CAutoMutex kLock(m_kMutex);

	if(CEL::DR_SUCCESS == rkResult.eRet)
	{
		CEL::DB_DATA_ARRAY::const_iterator itor = rkResult.vecArray.begin();
		while( rkResult.vecArray.end() != itor )
		{
			CONT_MAP_CONFIG::key_type element;

			(*itor).Pop( element.nRealmNo );	++itor;
//			(*itor).Pop( element.nChannelNo );	++itor;
			element.nChannelNo = 0;// 채널번호는 0으로 강제.
			(*itor).Pop( element.nServerNo );	++itor;
			(*itor).Pop( element.iGroundNo );	++itor;

			if( FAILED(g_kProcessCfg.Locked_AddMapCfg(element) ) )
			{
				VERIFY_INFO_LOG(false, BM::LOG_LV0, __FL__ << _T(" Insert Failed Realm[") << element.nRealmNo 
					<< _T("] Channel[") << element.nChannelNo << _T("] Server[") << element.nServerNo
					<< _T("] MissionNo[") << element.iGroundNo <<_T("]") );
//				VERIFY_INFO_LOG(false, BM::LOG_LV1, _T("[%s] Insert Failed Realm[%d] Channel[%d] Server[%d] Ground[%d]"), __FUNCTIONW__, element.nRealmNo, element.nChannelNo, element.nServerNo, element.iGroundNo);
			}
		}
		return S_OK;
	}

	return E_FAIL;
}

HRESULT PgSiteMgr::Q_DQT_PATCH_VERSION_EDIT(CEL::DB_RESULT &rkResult)
{
	if(CEL::DR_SUCCESS == rkResult.eRet)
	{
		CEL::DB_DATA_ARRAY::const_iterator itor = rkResult.vecArray.begin();
		if( rkResult.vecArray.end() != itor )
		{
		}
		return S_OK;
	}
	return E_FAIL;
}
