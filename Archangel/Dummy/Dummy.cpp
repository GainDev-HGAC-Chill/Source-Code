#include "stdafx.h"
#include "KeyEvent.h"
#include "BM/LocalMgr.h"


const CONT_DEF_ABIL_TYPE* g_pAbilType = NULL;
const CONT_DEFSKILL	*g_pDefSkill = NULL;
const CONT_DEFUPGRADECLASS	*g_pDefUpgradeClass = NULL;

#include "variant/MonsterDefMgr.h"
#include "variant/PgClassDefMgr.h"
#include "variant/PgItemOptionMgr.h"

#include "ai_Action.h"
#include "PgClientMng.h"
#include "Network.h"
#include "DummyClientMgr.h"

#include "Lohengrin/VariableContainer.h"

bool LoadTBData(const std::wstring &strFolder)
{
	const bool bRet = g_kTblDataMgr.LoadDump(strFolder);

	if( bRet )
	{
		TB_REF_COUNT tbRef;

		const CONT_DEF_ABIL_TYPE* pContAbilType = NULL;
		const CONT_DEFMONSTER* pContDefMonster = NULL;
		const CONT_DEFMONSTERABIL* pContDefMonsterAbil = NULL;
		const CONT_DEFSKILL* pContDefSkill = NULL;
		const CONT_DEFSTRINGS* pContDefStrings = NULL;

		//const CONT_DEFCLASS2* pkDefClass2 = NULL;
		//const CONT_DEFCLASS2ABIL* pkDefClass2Abil = NULL;
		const CONT_DEFITEMENCHANT* pContDefItemEnchant = NULL;

		const CONT_DEFUPGRADECLASS	*pContDefUpgradeClass = NULL;
		const CONT_DEFITEMRARE* pContDefRare = NULL;
		const CONT_DEFEFFECT* pContEffect = NULL;
		const CONT_DEFEFFECTABIL* pContEffectAbil = NULL;
		const CONT_DEFSKILLABIL* pContDefSkillAbil = NULL;

		const CONT_DEFITEM* pContDefItem = NULL;
		const CONT_DEFITEMABIL* pContDefItemAbil = NULL;
		const CONT_DEFRES* pContDefRes = NULL;

		const CONT_DEF_ITEM_BAG* pkItemBag = NULL;
		const CONT_DEF_ITEM_BAG_ELEMENTS* pkBagElements = NULL;
		const CONT_DEF_COUNT_CONTROL* pkCountControl = NULL;
		const CONT_DEF_DROP_MONEY_CONTROL* pkMoneyControl = NULL;
		const CONT_DEF_SUCCESS_RATE_CONTROL* pkSuccessRateControl = NULL;

		const CONT_TBL_DEF_ITEM_OPTION *pkItemOption = NULL;
		const CONT_TBL_DEF_ITEM_OPTION_ABIL *pkItemOptionAbil = NULL;

		const CONT_DEF_MAP_REGEN_POINT *pkMapRegenPoint = NULL;
		const CONT_DEF_MONSTER_BAG_CONTROL *pkMonsterBagControl = NULL;
		const CONT_DEF_MONSTER_BAG *pkMonsterBag = NULL;
		const CONT_DEF_MONSTER_BAG_ELEMENTS *pkMonsterBagElements = NULL;
		const CONT_DEF_PVP_GROUNDMODE *pkPvPGroundMode = NULL;

		const CONT_DEFITEMMAKING *pkDefItemMaking = NULL;
		const CONT_DEFRESULT_CONTROL *pkDefResultControl = NULL;
		const CONT_DEF_MISSION_ROOT *pkDefMissionRoot = NULL;
		const CONT_DEF_MISSION_CANDIDATE *pkDefMissionCandidate = NULL;

		g_kTblDataMgr.GetContDef(tbRef,pContAbilType);
		g_kTblDataMgr.GetContDef(tbRef,pContDefMonster);
		g_kTblDataMgr.GetContDef(tbRef,pContDefMonsterAbil);
		g_kTblDataMgr.GetContDef(tbRef,pContDefSkill);
		g_kTblDataMgr.GetContDef(tbRef,pContDefSkillAbil);

		g_kTblDataMgr.GetContDef(tbRef,pContDefItem);
		g_kTblDataMgr.GetContDef(tbRef,pContDefItemAbil);
		g_kTblDataMgr.GetContDef(tbRef,pContDefRes);
		g_kTblDataMgr.GetContDef(tbRef,pContDefStrings);
		
		//g_kTblDataMgr.GetContDef(tbRef,pkDefClass2);
		//g_kTblDataMgr.GetContDef(tbRef,pkDefClass2Abil);
		g_kTblDataMgr.GetContDef(tbRef,pContDefItemEnchant);
		g_kTblDataMgr.GetContDef(tbRef,pContDefUpgradeClass);

		g_kTblDataMgr.GetContDef(tbRef,pContDefRare);
		g_kTblDataMgr.GetContDef(tbRef,pContEffect);
		g_kTblDataMgr.GetContDef(tbRef,pContEffectAbil);

		g_kTblDataMgr.GetContDef(tbRef, pkItemBag);
		g_kTblDataMgr.GetContDef(tbRef, pkBagElements);
		g_kTblDataMgr.GetContDef(tbRef, pkCountControl);
		g_kTblDataMgr.GetContDef(tbRef, pkMoneyControl);
		g_kTblDataMgr.GetContDef(tbRef, pkSuccessRateControl);

		g_kTblDataMgr.GetContDef(tbRef, pkItemOption);
		g_kTblDataMgr.GetContDef(tbRef, pkItemOptionAbil);
//		g_kTblDataMgr.GetContDef(tbRef, pkItemOptionCandidate);
//		g_kTblDataMgr.GetContDef(tbRef, pkItemOptionSelector);

		g_kTblDataMgr.GetContDef(tbRef, pkItemOptionAbil);

		g_kTblDataMgr.GetContDef(tbRef, pkMapRegenPoint);
		g_kTblDataMgr.GetContDef(tbRef, pkMonsterBagControl);
		g_kTblDataMgr.GetContDef(tbRef, pkMonsterBag);
		g_kTblDataMgr.GetContDef(tbRef, pkMonsterBagElements);
		g_kTblDataMgr.GetContDef(tbRef, pkPvPGroundMode);

		g_kTblDataMgr.GetContDef(tbRef, pkDefItemMaking);
		g_kTblDataMgr.GetContDef(tbRef, pkDefResultControl);
		g_kTblDataMgr.GetContDef(tbRef, pkDefMissionRoot);
		g_kTblDataMgr.GetContDef(tbRef, pkDefMissionCandidate);

		g_pAbilType = pContAbilType;
		g_pDefSkill = pContDefSkill;
		g_pDefUpgradeClass = pContDefUpgradeClass;

//		g_MonsterDef.Build(*pContDefMonster, *pContDefMonsterAbil);//빌드
//		g_kItemDefMgr.Build(*pContDefItem, *pContDefItemAbil);//빌드
//		g_SkillDefMgr.Build(*pContDefSkill, *pContDefSkillAbil);//빌드
//		g_ClassDef.Build(pkDefClass2, pkDefClass2Abil);
//		g_PetDef.Build(pkDefPet, pkDefPetAbil);
//		g_RareDefMgr.Build( *pContDefRare, *pContDefItemAbil );

//		g_ItemEnchantDefMgr.Build( *pContDefItemEnchant, *pContDefItemAbil );
//		g_kEffectDefMgr.Build(*pContEffect, *pContEffectAbil);

//		g_kItemOptMgr.Build(pkItemOption, pkItemOptionAbil, pkItemOptionCandidate, pkItemOptionSelector, pkSuccessRateControl);

//		g_MonsterBag.Build(pkMapRegenPoint, pkMonsterBagControl, pkMonsterBag, pkMonsterBagElements);
//		lwPvP::Build(pkPvPGroundMode);

//		g_ItemMakingDefMgr.Build(pkDefItemMaking, pkDefResultControl);// ItemMaking Build
//		g_kItemBagMgr.Build(*pkItemBag, *pkBagElements, *pkSuccessRateControl, *pkCountControl, *pkMoneyControl, NULL );

// 		CONT_DEFRES::const_iterator res_itr = pContDefRes->begin();
// 		float fTime = NiGetCurrentTimeInSec();
// 		while(res_itr != pContDefRes->end())
// 		{
// 			SUVInfo kUVInfo( (*res_itr).second.U, (*res_itr).second.V, (*res_itr).second.UVIndex);
// 			g_kUIScene.AddIconRsc( (*res_itr).second.ResNo, (*res_itr).second.strIconPath, kUVInfo);
// 			PgXmlLoader::PrepareXmlDocument(MB((*res_itr).second.strXmlPath));
// 			++res_itr;
// 		}
// 		fTime = NiGetCurrentTimeInSec() - fTime;
// 		NILOG(PGLOG_STAT, "AddIconRsc %f time \n", fTime);


	int iDefLoad = 
		PgControlDefMgr::EDef_MonsterDefMgr
		|	PgControlDefMgr::EDef_SkillDefMgr
		|	PgControlDefMgr::EDef_ItemDefMgr
		|	PgControlDefMgr::EDef_RareDefMgr
		|	PgControlDefMgr::EDef_ItemEnchantDefMgr
		|	PgControlDefMgr::EDef_ClassDefMgr
		|	PgControlDefMgr::EDef_ItemBagMgr
		|	PgControlDefMgr::EDef_StoreMgr
		|	PgControlDefMgr::EDef_ItemOptionMgr
		|	PgControlDefMgr::EDef_ItemSetDefMgr
		|	PgControlDefMgr::EDef_PropertyMgr
		|	PgControlDefMgr::EDef_GroundEffect
		|	PgControlDefMgr::EDef_RecommendationItem;

	SReloadDef sReloadDef;
	g_kTblDataMgr.GetReloadDef(tbRef, sReloadDef, iDefLoad);
	g_kControlDefMgr.Update( sReloadDef, iDefLoad );

	}

	return bRet;
}

int _tmain(int argc, _TCHAR* argv[])
{
	g_kCoreCenter;//인스턴스 생성.
	g_kLogWorker.StartSvc(1);

	g_kProcessCfg.Locked_SetConfigDirectory();
	if( !g_kLocal.LoadFromINI() )
	{
		std::cout << "Load From \"local.ini\" Error!!" << std::endl;
		system("pause");
		return 0;
	}

#ifndef _DEBUG
	SET_GLOBAL_EXCEPTION_FILTER();
	//CMiniDump2::Install(CMiniDump2::DUMP_LEVEL_HEAVY);
#endif

	TCHAR chLog[MAX_PATH] = {0,};
	_stprintf_s(chLog, _countof(chLog), _T("DUMMY%04d"), g_kProcessCfg.ServerNo());

	std::wstring kLogFolder;
	InitLog(kLogFolder, chLog, BM::LOG_LV9);
	
	const bool bRet =LoadTBData(_T("./Table/"));
	if(!bRet)
	{
		assert(NULL);
		return 0;
	}

	g_kNetwork.ParseArg(argc, argv);
	const TEST_INFO* pkInfo = g_kNetwork.GetTestInfo();
	if (_tcslen(pkInfo->chID) == 0)
	{
		// ini 못 읽었으면 기본 INI 읽기
		const std::wstring kIniFile = _T("./Dummy.ini");
		g_kDummyMgr.IniFile(kIniFile);
		g_kNetwork.ReadConfigFile(kIniFile.c_str());
	}
	g_kAiActionMgr.Build();
	g_kDummyMgr.Build();
	g_kNetwork.Init();


	if( !RegistKeyEvent() ){ return 0; }

	std::cout<< "시작" << std::endl;
	g_kConsoleCommander.MainLoof();

	g_ClientMng.WriteStatistic();
	g_kLogWorker.VDeactivate();
	g_kCoreCenter.Close();
//! 	::CoUninitialize();
	return 0;
}

