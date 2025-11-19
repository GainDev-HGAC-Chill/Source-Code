#include "stdafx.h"
#include "BM/PgTask.h"
#include "Lohengrin/VariableContainer.h"
#include "Variant/PgQuestInfo.h"
#include "Variant/PgMissionInfo.h"
#include "Variant/PgParty.h"
#include "Variant/PgPartyMgr.h"
#include "Variant/PgMCtrl.h"
#include "PgKeyEvent.h"
#include "PgTimer.h"
#include "PgRecvFromCenter.h"
#include "PgRecvFromSwitch.h"
#include "PgRecvFromUser.h"
#include "PgQuest.h"
#include "PgMissionMan.h"
// #include "Lohengrin/PacketType.h"
#include "PgTask_MapServer.h"
#include "PgPartyItemRule.h"
#include "PgLocalPartyMgr.h"
#include "PgRecvFromLog.h"
#include "PgGroundMgr.h"
#include "PgMonKillCountReward.h"
#include "PgAction.h"
#include "PgDBProcess.h"
#include "PublicMap/PgWarMode.h"

bool GlobalInit( bool const bKey );
void GlobalRelease();
void ReleaseGsa();

//LOCAL_MGR::CLocal g_kLocal;

void CALLBACK OnRegist( CEL::SRegistResult const &rkArg )
{
	if( rkArg.iRet != CEL::CRV_SUCCESS)
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__<<L"OnRegist Failed Type["<<rkArg.eType<<L"] Ret["<<rkArg.iRet<<L"]" );
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("OnRegist Failed!"));
		return;
	}

	if( CEL::RT_CONNECTOR == rkArg.eType )
	{
		switch(rkArg.iIdentityValue)
		{
		case CEL::ST_LOG:
			{
				g_kProcessCfg.LogConnector(rkArg.guidObj);
			}break;
		case CEL::ST_CENTER:
			{
				g_kProcessCfg.CenterConnector(rkArg.guidObj);
				g_kProcessCfg.Locked_ConnectCenter();
			}break;
		case CEL::ST_SWITCH:
			{
				g_kProcessCfg.SwitchConnector(rkArg.guidObj);
			}break;
		case CEL::ST_IMMIGRATION:
			{
				g_kProcessCfg.ImmigrationConnector(rkArg.guidObj);
				g_kProcessCfg.Locked_ConnectImmigration();
			}break;
		default:
			{
				VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("============ Connector!!!! ======================"));
			}break;
		}
	}

	if( CEL::RT_FINAL_SIGNAL == rkArg.eType )
	{
		switch(rkArg.iIdentityValue)
		{
		case 0:
			{
				if(g_kCoreCenter.SvcStart())
				{
					INFO_LOG(BM::LOG_LV6, _T("=================================================="));
					INFO_LOG(BM::LOG_LV6, _T("============ CoreCenter Run ======================"));
					INFO_LOG(BM::LOG_LV6, _T("=================================================="));

					LoadDB();
				}
				else
				{
					VERIFY_INFO_LOG(false, BM::LOG_LV0, _T("============ CoreCenter Cannot Run!!!! ======================"));
				}
			}break;
		}
	}
}
void PgOutputDebugStringFromGameBryo(const char* pcOut)
{
	if(!pcOut)
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("pkOut is NULL"));
		return;
	}

	std::wstring kMessage(_T("[GameBryo]"));
	kMessage += UNI(pcOut);

	INFO_LOG(BM::LOG_LV6, kMessage);
}

int CALLBACK ExceptionTerminate(void)
{
	g_kLogWorker.VDeactivate();
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	g_kCoreCenter;//인스턴스 생성.

#ifndef _DEBUG
	PgExceptionFilter::Install( PgExceptionFilter::DUMP_LEVEL_HEAVY, PgExceptionFilter::DUMP_OP_Exit_Program|PgExceptionFilter::DUMP_OP_UseTimeInDumpFile, ExceptionTerminate );
#endif

	g_kProcessCfg.Locked_SetConfigDirectory();
	if(!g_kLocal.LoadFromINI(g_kProcessCfg.ConfigDir() + L"Local.ini"))
	{
		std::cout << "Load From \"local.ini\" Error!!" << std::endl;
		system("pause");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return 0"));
		return 0;
	}
	//! 들어온 인자를 파싱해서.
	g_kProcessCfg.Locked_SetServerType(CEL::ST_MAP);
	if( !g_kProcessCfg.Locked_ParseArg(argc, argv) )
	{
		BM::vstring arg;
		for ( int i = 1; i< argc ; ++i )
		{
			arg += argv[i];
			arg += _T(" ");
		}
		CAUTION_LOG( BM::LOG_LV0, _T("Argment Error! ") << arg );
		system("pause");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return 0"));
		return 0;
	}

	std::wstring kLogFolder;
	CONT_DB_INIT_DESC kContDBInit;

	{
		TCHAR chLog[MAX_PATH] = {0,};
		_stprintf_s(chLog, _countof(chLog), _T("R%dC%d_MAP%04d"), g_kProcessCfg.RealmNo(), g_kProcessCfg.ChannelNo(), g_kProcessCfg.ServerNo());
		InitLog( kLogFolder, chLog, BM::OUTPUT_ALL );

#ifndef _DEBUG
		if ( !(g_kProcessCfg.RunMode() & CProcessConfig::E_RunMode_Debug) )
		{
			INFO_LOG_LEVEL(BM::LOG_LV9);
		}
#endif
#ifdef AI_DEBUG
		INFO_LOG_LEVEL(BM::LOG_LV9);
#endif
	}

	if (g_kProcessCfg.RunMode() == CProcessConfig::E_RunMode_ReadIni)
	{
		if (!ReadDBConfig(EConfigType_Ini, g_kProcessCfg.ConfigDir(), g_kProcessCfg.ServerIdentity(), kContDBInit)) { return 0; }
	}
	else
	{
		if (!ReadDBConfig(EConfigType_Inb, g_kProcessCfg.ConfigDir(), g_kProcessCfg.ServerIdentity(), kContDBInit)) { return 0; }
	}

	if( !GlobalInit(false) )
	{
		ExceptionTerminate();
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return 0"));
		return 0;
	}

	TCHAR chProductVersion[80], chFileVersion[80];
	g_kProcessCfg.Locked_GetVersion(80, chFileVersion, 80, chProductVersion);
	INFO_LOG(BM::LOG_LV6, _T("==================== Server Initialize Start ===================="));
	INFO_LOG(BM::LOG_LV6, _T("Product Version : ")<<chProductVersion);
	INFO_LOG(BM::LOG_LV6, _T("File Version : ")<<chFileVersion);
	INFO_LOG( BM::LOG_LV6, _T("Packet Version S : ") << PACKET_VERSION_S );

	// 게임브리오 기반 시스템을 초기화한다
	NiInit();

	// Set the callback function printing the debug messages coming from GameBryo to the console window.
	NiSetOutputDebugStringCallback(PgOutputDebugStringFromGameBryo);

    NiPhysXManager* pkManager = NiPhysXManager::GetPhysXManager();
	if( !pkManager )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__<<L"failed to initializing physX engine");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return 0"));
		return 0;
	}
	if(	!pkManager->Initialize() )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__<<L"failed to initializing physX engine");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return 0"));
        return 0;
	}
	
	if( !g_kPatternMng.Init() )			
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV4, __FL__<<L"PatternMng Init failed");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("PatternMng Init Failed!"));
		return 0;
	}

	CEL::INIT_CENTER_DESC kCenterInit;
	kCenterInit.eOT = BM::OUTPUT_ALL;
	kCenterInit.pOnRegist = OnRegist;
	kCenterInit.dwProactorThreadCount = __min(kCenterInit.dwProactorThreadCount, 6);//스위치 3개, 센터 1개,
	kCenterInit.m_kCelLogFolder = kLogFolder;

	g_kCoreCenter.Init(kCenterInit);

	INFO_LOG( BM::LOG_LV6, __FL__<<L"Regist Log Timer 100ms");
	CEL::REGIST_TIMER_DESC kInit100ms;
	kInit100ms.pFunc = Timer100ms;	// TickTimer
	kInit100ms.dwInterval = 100;	// 10 frames/sec
	g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &kInit100ms);
	g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &kInit100ms);
	g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &kInit100ms);
	g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &kInit100ms);

	INFO_LOG( BM::LOG_LV6, __FL__<<L"Regist Log Timer 30S");
	CEL::REGIST_TIMER_DESC kInit30s;
	kInit30s.pFunc = Timer30s;	// Save Character
	kInit30s.dwInterval = 10000;	// 2 frames / min
	g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &kInit30s);

	INFO_LOG( BM::LOG_LV6, __FL__<<L"Regist Log Timer 1S");
	CEL::REGIST_TIMER_DESC kInit1s;
	kInit1s.pFunc = Timer1s;	// Instant dungeon timer
	kInit1s.dwInterval = 500;	// 1 frame / sec	
	g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &kInit1s);
	g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &kInit1s);
	g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &kInit1s);

	INFO_LOG( BM::LOG_LV6, __FL__<<L"Regist Log Timer 5S");
	CEL::REGIST_TIMER_DESC kInit5s;
	kInit5s.pFunc = Timer5s;	// 
	kInit5s.dwInterval = 2500;	// 5 frame / sec	
	g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &kInit5s);

	INFO_LOG( BM::LOG_LV6, __FL__<<L"Regist Log Timer 1M");
	CEL::REGIST_TIMER_DESC Init1m;
	Init1m.pFunc		= Timer1m;
	Init1m.dwInterval	= 60000;
	g_kCoreCenter.Regist(CEL::RT_TIMER_FUNC, &Init1m);

	INFO_LOG( BM::LOG_LV6, __FL__<<L"Regist Log Connector Switch");

	CEL::INIT_CORE_DESC kSwitchConnectorInit;
	kSwitchConnectorInit.OnSessionOpen	= OnConnectToSwitch;
	kSwitchConnectorInit.OnDisconnect = OnDisConnectToSwitch;
	kSwitchConnectorInit.OnRecv = OnRecvFromSwitch;
	kSwitchConnectorInit.IdentityValue(CEL::ST_SWITCH);
	kSwitchConnectorInit.ServiceHandlerType(CEL::SHT_SERVER);

	INFO_LOG( BM::LOG_LV6, __FL__<<L"Regist Log Connector Center");
	CEL::INIT_CORE_DESC kCenterConnectorInit;
	kCenterConnectorInit.OnSessionOpen	= OnConnectToCenter;
	kCenterConnectorInit.OnDisconnect = OnDisConnectToCenter;
	kCenterConnectorInit.OnRecv = OnRecvFromCenter;
	kCenterConnectorInit.IdentityValue(CEL::ST_CENTER);
	kCenterConnectorInit.ServiceHandlerType(CEL::SHT_SERVER);

	INFO_LOG( BM::LOG_LV6, __FL__<<L"Regist Log Connector Log");
	CEL::INIT_CORE_DESC kLogConnectorInit;
	kLogConnectorInit.OnSessionOpen	= OnConnectToLog;
	kLogConnectorInit.OnDisconnect = OnDisConnectToLog;
	kLogConnectorInit.OnRecv = OnRecvFromLog;
	kLogConnectorInit.IdentityValue(CEL::ST_LOG);
	kLogConnectorInit.ServiceHandlerType(CEL::SHT_SERVER);

	g_kCoreCenter.Regist(CEL::RT_CONNECTOR, &kSwitchConnectorInit);
	g_kCoreCenter.Regist(CEL::RT_CONNECTOR, &kCenterConnectorInit);
	g_kCoreCenter.Regist(CEL::RT_CONNECTOR, &kLogConnectorInit);

	SYSTEM_INFO kSystemInfo;
	::GetSystemInfo(&kSystemInfo);

	CONT_DB_INIT_DESC::iterator dbinit_itor = kContDBInit.begin();
	while (dbinit_itor != kContDBInit.end())
	{
		CEL::INIT_DB_DESC &kDBInit = (*dbinit_itor);

		kDBInit.dwWorkerCount = (kSystemInfo.dwNumberOfProcessors * 2 + 1);//로그 서버만.
		kDBInit.bUseConsoleLog = true;
		kDBInit.OnDBExecute = OnDB_EXECUTE;
		kDBInit.OnDBExecuteTran = OnDB_EXECUTE_TRAN;
		kDBInit.m_kLogFolder = kLogFolder;

		g_kCoreCenter.Regist(CEL::RT_DB_WORKER, &kDBInit);
		++dbinit_itor;
	}

	PgWarMode::ParseXml("./XML/Setting/PvP.xml");

	//INFO_LOG(BM::LOG_LV7, _T("Start pre-loading quest ..."));
	//if( !g_kQuestMan.Create() )
	//{
	//	return 0;
	//}

	CEL::INIT_FINAL_SIGNAL kFinalInit;
	kFinalInit.kIdentity = 0;
	g_kCoreCenter.Regist(CEL::RT_FINAL_SIGNAL, &kFinalInit);

	INFO_LOG( BM::LOG_LV6, _T("==================== Service Start Now ====================") );

	g_kTask.StartSvc();

	if( !RegistKeyEvent() )
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return 0"));
		return 0; 
	}

	g_kGndMgr.Init( g_kProcessCfg.IsPublicChannel() );

	g_kProcessCfg.Locked_SetConsoleTitle();

	g_kConsoleCommander.MainLoof();

	g_kLogWorker.VDeactivate();
	g_kCoreCenter.Close();

	ReleaseGsa();
	NiPhysXManager::GetPhysXManager()->Shutdown();
	NiShutdown();

	GlobalRelease();
	
	return 0;
}


bool GlobalInit(bool const bKey)
{
	if ( !bKey )
	{
#ifdef _MEMORY_TRACKING
		g_pkMemoryTrack = new PgMemoryTrack();
		g_pkMemoryTrack->Init(BM::OUTPUT_FILE_AND_CONSOLE, _T("./MemoryTrack"), _T("MemoryTrack.txt"));
#endif

		g_kTerminateFunc = OnTerminateServer;//Init MCtrl
		g_kGetNowUserFunc = GetConnectionUserCount;
	}

	std::wstring const wstrInIPath = g_kProcessCfg.ConfigDir() + _T("Map_constant.ini");
	if ( !g_kVariableContainer.LoadIni(wstrInIPath) )
	{
		VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << L"Load Failed PATH=" << wstrInIPath );
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	if( S_OK != g_kVariableContainer.Get(EVar_Kind_Hunting, EVar_MonsterExp_CanMinDiffLevel, iCanAddExpMinLevel) )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__<<L"Can't Find 'MonsterKill_SystemEnable'");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	if( S_OK != g_kVariableContainer.Get(EVar_Kind_Hunting, EVar_MonsterExp_CanMaxDiffLevel, iCanAddExpMaxLevel) )
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__<<L"Can't Find 'MonsterKill_SystemEnable'");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	if (S_OK != g_kVariableContainer.Get(EVar_Kind_MyHome, EVar_MyHome_AuctionLimitGold, g_iMyHomeAuctionLimitGold))
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__<<L"Can't Find 'MyHome_AuctionLimitGold'");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
	}

	if (S_OK != g_kVariableContainer.Get(EVar_Kind_EntityExtInfo, EVar_EntityExtInfo_EnableCriticalAttack, PgGround::ms_iEnableEntityCritialAttack))
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__<<L"Can't Find 'EVar_EntityExtInfo_EnableCriticalAttack'");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
	}

	if (S_OK != g_kVariableContainer.Get(EVar_Kind_EntityExtInfo, EVar_EntityExtInfo_EnableHitRate, PgGround::ms_iEnableEntityHitRate))
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__<<L"Can't Find 'EVar_EntityExtInfo_EnableHitRate'");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
	}

	if (S_OK != g_kVariableContainer.Get(EVar_Kind_EntityExtInfo, EVar_EntityExtInfo_EnableAttackExtInfo, PgGround::ms_iEnableEntityAttackExtInfo))
	{
		VERIFY_INFO_LOG(false, BM::LOG_LV1, __FL__<<L"Can't Find 'EVar_EntityExtInfo_EnableAttackExtInfo'");
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
	}

	g_kVariableContainer.Get(EVar_Kind_Player, EVar_Player_AutoHeal_Multiplier_NotInVillage, PgGround::ms_fAutoHealMultiplier_NotInViliage);

	int iDebugMode = 0;
	if (S_OK == g_kVariableContainer.Get(EVar_Kind_System, EVar_System_RunDebugMode, iDebugMode))
	{
		if (iDebugMode == 1)
		{
			g_kProcessCfg.RunMode(g_kProcessCfg.RunMode() | CProcessConfig::E_RunMode_Debug);
		}
	}

	if( !PgAction_PickUpItem::InitStaticValue() )
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	if( !GuildUtil::InitConstantValue() )
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	{
		int iGndAttr = 0;
		if ( SUCCEEDED( g_kVariableContainer.Get( EVar_Kind_Pet, EVar_Pet_OffGroundAttr, iGndAttr ) ) )
		{
			PgGround::ms_kOffPet_GroundAttr = static_cast<T_GNDATTR>(iGndAttr);
		}
	}

	{
		int iTakePCExpRate = 0;
		if ( SUCCEEDED( g_kVariableContainer.Get( EVar_Kind_Pet, EVar_Pet_TakePCExpRate, iTakePCExpRate ) ) )
		{
			PgAction_AddExp::ms_i64TakePCExpRate = static_cast<__int64>(iTakePCExpRate);
		}
	}

	if( S_OK != g_kVariableContainer.Get(EVar_Kind_Hidden, EVar_Hidden_Stone_Item, PgGround::ms_iHiddenRewordItemNo) )
	{
		VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("Can't Find EVar_Kind_Hidden 'EVar_Hidden_Stone_Item' Value") );
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
	}
	
	{// 몬스터 킬당 얻는 각성치의 보정값 얻어오기
		if( S_OK != g_kVariableContainer.Get(EVar_Kind_EachClassAwakeValueReviser, eVar_Knight_Reviser, PgGround::ms_KnightAwakeReviserByKill) )
		{// 기사류
			VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("Can't Find EVar_Kind_EachClassAwakeValueReviser 'eVar_Knight_Reviser' Value") );
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		}
		if( S_OK != g_kVariableContainer.Get(EVar_Kind_EachClassAwakeValueReviser, eVar_Warrior_Reviser, PgGround::ms_WarriorAwakeReviserByKill) )
		{// 워리어류
			VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("Can't Find EVar_Kind_EachClassAwakeValueReviser 'eVar_Warrior_Reviser' Value") );
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		}
		if( S_OK != g_kVariableContainer.Get(EVar_Kind_EachClassAwakeValueReviser, eVar_Mage_Reviser, PgGround::ms_MageAwakeReviserByKill) )
		{// 메이지류
			VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("Can't Find EVar_Kind_EachClassAwakeValueReviser 'eVar_Mage_Reviser' Value") );
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		}
		if( S_OK != g_kVariableContainer.Get(EVar_Kind_EachClassAwakeValueReviser, eVar_BattleMage_Reviser, PgGround::ms_BattleMageAwakeReviserByKill) )
		{// 배틀메이지류
			VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("Can't Find EVar_Kind_EachClassAwakeValueReviser 'eVar_BattleMage_Reviser' Value") );
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		}
		if( S_OK != g_kVariableContainer.Get(EVar_Kind_EachClassAwakeValueReviser, eVar_Hunter_Reviser, PgGround::ms_HunterAwakeReviserByKill) )
		{// 헌터류
			VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("Can't Find EVar_Kind_EachClassAwakeValueReviser 'eVar_Hunter_Reviser' Value") );
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		}
		if( S_OK != g_kVariableContainer.Get(EVar_Kind_EachClassAwakeValueReviser, eVar_Ranger_Reviser, PgGround::ms_RangerAwakeReviserByKill) )
		{// 레인저류
			VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("Can't Find EVar_Kind_EachClassAwakeValueReviser 'eVar_Ranger_Reviser' Value") );
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		}
		if( S_OK != g_kVariableContainer.Get(EVar_Kind_EachClassAwakeValueReviser, eVar_Clown_Reviser, PgGround::ms_ClownAwakeReviserByKill) )
		{// 광대류
			VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("Can't Find EVar_Kind_EachClassAwakeValueReviser 'eVar_Clown_Reviser' Value") );
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		}
		if( S_OK != g_kVariableContainer.Get(EVar_Kind_EachClassAwakeValueReviser, eVar_Assassin_Reviser, PgGround::ms_AssassinAwakeReviserByKill) )
		{// 암살자류
			VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("Can't Find EVar_Kind_EachClassAwakeValueReviser 'eVar_Assassin_Reviser' Value") );
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		}
		if( S_OK != g_kVariableContainer.Get(EVar_Kind_EachClassAwakeValueReviser, eVar_Shaman_Reviser, PgGround::ms_ShamanAwakeReviserByKill) )
		{// 소환사류
			VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("Can't Find EVar_Kind_EachClassAwakeValueReviser 'eVar_Shaman_Reviser' Value") );
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		}
		if( S_OK != g_kVariableContainer.Get(EVar_Kind_EachClassAwakeValueReviser, eVar_DoubleFighter_Reviser, PgGround::ms_DoubleFighterAwakeReviserByKill) )
		{// 쌍둥이 격투가류 
			VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("Can't Find EVar_Kind_EachClassAwakeValueReviser 'eVar_DoubleFighter_Reviser' Value") );
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		}
	}
	{// 기준 숙련도와 차이에 따른 숙련도 획득량
		bool bRet = true;
		int const iConfigCount = 4;
		for( int iCur = 0; iConfigCount > iCur; ++iCur )
		{
			EVar_JobSkillPenalty const eVal = static_cast< EVar_JobSkillPenalty >(JobPenalty_BaseExp_Diff_1 + iCur);
			if( S_OK != g_kVariableContainer.Get(EVar_Kind_JobSkillPenalty, eVal, PgGround::ms_JobSkillBaseExpDiff[iCur]) )
			{
				VERIFY_INFO_LOG( false, BM::LOG_LV1, __FL__ << _T("Can't Find EVar_Kind_JobSkillPenalty 'JobPenalty_BaseExp_Diff_") << iCur+1 << _T("' Value") );
				bRet = false;
			}
		}
		if( !bRet )
		{
			return false;
		}
	}

	{// Log
		int iValue_OutPut = BM::OUTPUT_ALL;
		int iValue_Level = static_cast<int>(BM::LOG_LV9);

		g_kVariableContainer.Get(EVar_Kind_Log, EVar_LogOutputType, iValue_OutPut);
		g_kVariableContainer.Get(EVar_Kind_Log, EVar_LogLevelLimit, iValue_Level);

		iValue_OutPut &= BM::OUTPUT_ALL;

		SetLogOutPutType(static_cast<BM::E_OUPUT_TYPE>(iValue_OutPut));
		SetLogLeveLimit(static_cast<BM::E_LOG_LEVEL>(iValue_Level));

		INFO_LOG(BM::LOG_LV0, __FL__ << _T("Load EVar_LogOutputType = ") << iValue_OutPut);
		INFO_LOG(BM::LOG_LV0, __FL__ << _T("Load EVar_LogLevelLimit = ") << iValue_Level);
	}

	if( !TaskUtil::Init() )
	{
		return false;
	}

	return true;
}


void GlobalRelease()
{
#ifdef _MEMORY_TRACKING
	PgMemoryTrack* pkTrack = g_pkMemoryTrack;
	g_pkMemoryTrack = NULL;
	delete pkTrack;
#endif

	//g_kTask.IsStop(true);
	g_kTask.Close();
}

void ReleaseGsa()
{
	g_kGndMgr.Clear();
}