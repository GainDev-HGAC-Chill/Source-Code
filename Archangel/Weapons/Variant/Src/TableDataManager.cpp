#include "StdAfx.h"
#include "TableDataManager.h"
#include "PgControlDefMgr.h"

#include "BM/FileSupport.h"

#include "Lohengrin/LogGroup.h"
#include "BM/HSEL.h"

char const* const XML_ELEMENT_STRING_TABLE_LOCAL = "STRING_TABLE_LOCAL";
char const* const XML_ELEMENT_TEXT = "TEXT";
char const* const XML_ATTRIBUTE_ID = "ID";
char const* const XML_ATTRIBUTE_TEXT = "Text";

typedef std::vector< BM::Stream > PACKET_CONT;

CTableDataManager::CTableDataManager(void) : m_bUTF8(false)
{
	IsInit(false);
}

CTableDataManager::~CTableDataManager(void)
{
}

void CTableDataManager::DataToPacket(BM::Stream &rkPacket)
{//이건 2메가.
//	/*
	rkPacket.Data().reserve(1024*1024*15);//10메가로 리저브

	DWORD const dwBeginTime = BM::GetTime32();
	INFO_LOG(BM::LOG_LV9, __FL__<<L"Begin ----");

	//BM::CAutoMutex Lock(GetLock()->kObjectLock);//내 테이블을 외부에서 쓸때 데드락 걸려버림 무조건 위에서.
	BM::CAutoMutex lock(m_kMutex);

	PU::TWriteTable_MM(rkPacket, m_DefClass);
	PU::TWriteTable_MM(rkPacket, m_DefClassAbil);
	PU::TWriteTable_MM(rkPacket, m_DefClassPet);
	PU::TWriteTable_AM(rkPacket, m_DefClassPetLevel);
	PU::TWriteTableArray_AMM(rkPacket, m_DefClassPetSkill);
	PU::TWriteTable_AM(rkPacket, m_DefClassPetItemOption);
	PU::TWriteTable_MM(rkPacket, m_DefClassPetAbil);
	PU::TWriteTable_AM(rkPacket, m_DefItemBag);
	PU::TWriteTable_MM(rkPacket, m_DefAbilType);
	PU::TWriteTable_MM(rkPacket, m_DefBaseCharacter);
	PU::TWriteTable_MM(rkPacket, m_DefItem);
	PU::TWriteTable_MM(rkPacket, m_DefItemAbil);
	PU::TWriteTable_MM(rkPacket, m_DefItemRare);
	PU::TWriteTable_MM(rkPacket, m_DefItemRareGroup);
	PU::TWriteTable_MM(rkPacket, m_DefItemResConvert);
	PU::TWriteTable_MM(rkPacket, m_DefMap);
	PU::TWriteTable_MM(rkPacket, m_DefMapAbil);
	PU::TWriteTable_MM(rkPacket, m_DefMapItem);
	PU::TWriteTable_MM(rkPacket, m_DefMapRegenPoint);
	PU::TWriteTable_MM(rkPacket, m_DefMonster);
	PU::TWriteTable_MM(rkPacket, m_DefMonsterAbil);
	PU::TWriteTable_MM(rkPacket, m_DefMonsterTunningAbil);
	PU::TWriteTable_MM(rkPacket, m_DefNPC);
	PU::TWriteTable_MM(rkPacket, m_DefNPCAbil);
	PU::TWriteTable_MM(rkPacket, m_DefSkill);
	PU::TWriteTable_MM(rkPacket, m_DefSkillAbil);
	PU::TWriteTable_MM(rkPacket, m_DefSkillSet);
	PU::TWriteTable_MM(rkPacket, m_DefRes);
	PU::TWriteTable_AM(rkPacket, m_DefChannelEffect);
	PU::TWriteTable_MM(rkPacket, m_DefStrings);
	PU::TWriteTable_MM(rkPacket, m_DefEffect);
	PU::TWriteTable_MM(rkPacket, m_DefEffectAbil);
	PU::TWriteTable_MM(rkPacket, m_DefUpgradeClass);
	PU::TWriteTable_MM(rkPacket, m_DefItemEnchant);
	PU::TWriteTable_MM(rkPacket, m_DefCharacterBaseWear);
	PU::TWriteTable_MM(rkPacket, m_DefItemPlusUpgrade);
	PU::TWriteTable_MM(rkPacket, m_DefItemRarityUpgrade);
	PU::TWriteTable_MM(rkPacket, m_DefItemRarityControl);
	PU::TWriteTable_MM(rkPacket, m_DefItemPlusUpControl);
	PU::TWriteTable_MM(rkPacket, m_DefItemEnchantShift);
	PU::TWriteTable_MM(rkPacket, m_DefItemDisassemble);
	PU::TWriteTable_MM(rkPacket, m_DefSuccessRateControl);
	PU::TWriteTable_MM(rkPacket, m_DefMonsterBag);
	PU::TWriteTable_MM(rkPacket, m_kDefGmCmd);
	PU::TWriteTable_MM(rkPacket, m_DefCountControl);
	PU::TWriteTable_MM(rkPacket, m_DefItemBagElements);
	PU::TWriteTable_MM(rkPacket, m_DefMonsterBagElements);
	PU::TWriteTable_MM(rkPacket, m_DefMonsterBagControl);
	PU::TWriteTable_MM(rkPacket, m_DefItemContainer);
	PU::TWriteTable_MM(rkPacket, m_DefObject);
	PU::TWriteTable_MM(rkPacket, m_DefObjectAbil);
	PU::TWriteTable_MM(rkPacket, m_DefObjcetBag);
	PU::TWriteTable_MM(rkPacket, m_DefObjcetBagElements);
	PU::TWriteTable_MM(rkPacket, m_DefItemBagGroup);
	PU::TWriteTable_MM(rkPacket, m_DefMapItemBag);
	PU::TWriteTable_MM(rkPacket, m_DefMissionResult);
	PU::TWriteTable_MM(rkPacket, m_DefMissionRoot);
	PU::TWriteTable_MM(rkPacket, m_DefMissionCandidate);
	PU::TWriteTable_MM(rkPacket, m_DefDefenceAddMonster);
    PU::TWriteTable_MM(rkPacket, m_DefShopInEmporia);
	PU::TWriteTable_MM(rkPacket, m_DefShopInGame);
	PU::TWriteTable_MM(rkPacket, m_DefShopInStock);
	PU::TWriteArray_M(rkPacket, m_DefItemOption);
	PU::TWriteTable_MM(rkPacket, m_DefItemOptionAbil);
	PU::TWriteTable_MM(rkPacket, m_DefDropMoneyControl);
	PU::TWriteTable_AM(rkPacket, m_DefPvPGroundGroup);
	PU::TWriteTable_MM(rkPacket, m_DefPvPGroundMode);
	PU::TWriteArray_M(rkPacket, m_kDefPvPReward);
	PU::TWriteTable_AM(rkPacket, m_kDefPvPRewardItem);
	PU::TWriteTable_AA(rkPacket, m_kDefPvPPlayTimeInfo);
	PU::TWriteTable_MM(rkPacket, m_DefItemMaking);
	PU::TWriteTable_MM(rkPacket, m_DefCooking);
	PU::TWriteTable_MM(rkPacket, m_DefResultControl);
	PU::TWriteTable_MM(rkPacket, m_DefQuestReward);
	PU::TWriteArray_M(rkPacket, m_DefQuestResetSchedule);
	PU::TWriteArray_M(rkPacket, m_DefQuestRandom);
	PU::TWriteTable_MM(rkPacket, m_DefQuestRandomExp);
	PU::TWriteTable_MM(rkPacket, m_DefQuestRandomTacticsExp);
	PU::TWriteTable_MM(rkPacket, m_DefQuestWanted);
	PU::TWriteTable_MM(rkPacket, m_DefDynamicAbilRate);
	PU::TWriteTable_MM(rkPacket, m_DefDynamicAbilRateBag);
	PU::TWriteTable_MM(rkPacket, m_DefItemSet);
	PU::TWriteTable_MM(rkPacket, m_DefSpendMoney);
	PU::TWriteTable_MM(rkPacket, m_DefGuildLevel);
	PU::TWriteTable_MM(rkPacket, m_DefGuildSkill);
	PU::TWriteArray_M(rkPacket, m_DefFilterUnicode);
	PU::TWriteTable_MM(rkPacket, m_kDefProperty);
	PU::TWriteArray_M(rkPacket, m_DefMapEffect);
	PU::TWriteArray_M(rkPacket, m_DefMapEntity);
	PU::TWriteTable_MM(rkPacket, m_DefFiveElementInfo);
	PU::TWriteTable_MM(rkPacket, m_DefMapStoneControl);
	PU::TWriteTable_MM(rkPacket, m_DefItemRarityUpgradeCostRate);
	PU::TWriteTable_MM(rkPacket, m_DefTacticsLevel);
	PU::TWriteTable_MM(rkPacket, m_DefTacticsQuestPseudo);
	PU::TWriteTable_MM(rkPacket, m_DefMonKillCountReward);
	PU::TWriteTable_AA(rkPacket, m_DefTransTower);
	PU::TWriteTable_AA(rkPacket, m_DefParty_Info);	
	PU::TWriteTable_MM(rkPacket, m_DefCashShop);
	PU::TWriteTable_AM(rkPacket, m_kDefEmporia);
	PU::TWriteTable_MM(rkPacket, m_DefCashShopArticle);
	PU::TWriteTable_MM(rkPacket, m_DefCashShopLimitSell);
	PU::TWriteTable_MM(rkPacket, m_kDefContAchievements);
	PU::TWriteTable_MM(rkPacket, m_kDefAchievements);
	PU::TWriteTable_MM(rkPacket, m_kDefAchievements_SaveIdx);
	PU::TWriteTable_MM(rkPacket, m_kDefRecommendationItem);
	PU::TWriteTable_MM(rkPacket, m_DefItem2Achievement);
	PU::TWriteTable_MM(rkPacket, m_kDefGroundRareMonster);
	PU::TWriteTable_MM(rkPacket, m_kDefRareMonsterSpeech);
	PU::TWriteTable_MM(rkPacket, m_kCardLocal);
	PU::TWriteTable_MM(rkPacket, m_kDefCardKeyString);
	PU::TWriteTable_MM(rkPacket, m_kCardAbil);
	PU::TWriteTable_AM(rkPacket, m_kGemStore);
	PU::TWriteTable_AM(rkPacket, m_kDefGemStore);	
	PU::TWriteTable_AM(rkPacket, m_kDefAntique);
	PU::TWriteTable_MM(rkPacket, m_kOXQuizInfo);
	PU::TWriteTable_MM(rkPacket, m_kOXQuizReward);
	PU::TWriteTable_MM(rkPacket, m_kOXQuizEventInfo);
	PU::TWriteTable_AA(rkPacket, m_kDefMonsterCard);
	PU::TWriteTable_AA(rkPacket, m_kDefMarryText);
	PU::TWriteTable_AA(rkPacket, m_kDefHiddenRewordItem);	
	PU::TWriteTable_AA(rkPacket, m_kDefHiddenRewordBag);
	PU::TWriteTable_AM(rkPacket, m_kDefMissionClassReward);
	PU::TWriteTable_AM(rkPacket, m_kDefMissionRankReward);	
	PU::TWriteTable_AM(rkPacket, m_kMissionDefenceStage);		
	PU::TWriteTable_AM(rkPacket, m_kMissionDefenceWave);		

	PU::TWriteTable_AM(rkPacket, m_kMissionDefence7Mission);
	PU::TWriteTable_AM(rkPacket, m_kMissionDefence7Stage);
	PU::TWriteTable_AM(rkPacket, m_kMissionDefence7Wave);
	PU::TWriteTable_AM(rkPacket, m_kMissionDefence7guardian);

	PU::TWriteTable_MM(rkPacket, m_kMissionBonusMap);	

	PU::TWriteTable_AA(rkPacket, m_kDefEmotion);
	PU::TWriteTable_AA(rkPacket, m_kDefEmotionGroup);
	PU::TWriteArray_A(rkPacket, m_kDefCashItemAbilFilter);
	PU::TWriteTable_AA(rkPacket, m_kDefGamble);
	PU::TWriteTable_AA(rkPacket, m_kContLimitedItem);
	PU::TWriteTable_AA(rkPacket, m_kContLimitedItemCtrl);
	PU::TWriteTable_AA(rkPacket, m_kPCRoom);
	PU::TWriteTable_AA(rkPacket, m_kPCCafe);
	PU::TWriteTable_AA(rkPacket, m_kPCCafeAbil);
	PU::TWriteTable_AA(rkPacket, m_kDefConvertItem);
	PU::TWriteTable_AA(rkPacket, m_kDefGambleShoutItem);
	PU::TWriteTable_AM(rkPacket, m_kDefPetHatch);
	PU::TWriteTable_AM(rkPacket, m_kDefPetBonusStatus);
	PU::TWriteTable_AM(rkPacket, m_kCCERewardTable);
	PU::TWriteTable_AM(rkPacket, m_kRealtyDealer);
	PU::TWriteTable_AA(rkPacket, m_kRareOptSkill);
	PU::TWriteTable_AA(rkPacket, m_kRareOptMagic);
	PU::TWriteTable_AA(rkPacket, m_kIdx2SkillNo);
	PU::TWriteTable_AA(rkPacket, m_kMixupItem);
	PU::TWriteTable_AA(rkPacket, m_kTown2Ground);
	PU::TWriteTable_AA(rkPacket, m_kMyHomeDefaultItem);
	PU::TWriteTable_AA(rkPacket, m_kMyhomeTex);
	PU::TWriteTable_AA(rkPacket, m_kHometownToMapCost);
	PU::TWriteTable_AA(rkPacket, m_DefShopNpcGuid);
	PU::TWriteTable_MM(rkPacket, m_kLuckyStarInfo);
	PU::TWriteTable_MM(rkPacket, m_kLuckyStarReward);
	PU::TWriteTable_MM(rkPacket, m_kLuckyStarRewardStep);	
	PU::TWriteTable_MM(rkPacket, m_kLuckyStarEventJoinReward);	
	PU::TWriteTable_AA(rkPacket, m_kDefItemEnchantAbilWeight);
	PU::TWriteTable_AM(rkPacket, m_kContEventItemReward);
	PU::TWriteTable_AM(rkPacket, m_kContTreasureChest);
	PU::TWriteTable_AM(rkPacket, m_DefItemByLevel);
	PU::TWriteTable_AM(rkPacket, m_kContDefCharCardEffect);
	PU::TWriteTable_AM(rkPacket, m_kContDefAlramMission);
	PU::TWriteTable_AA(rkPacket, m_kDefSideJobRate);
	PU::TWriteArray_M(rkPacket, m_kDefPartyEventItemSet);
	PU::TWriteTable_AA(rkPacket, m_kContDefRediceOptionCost);
	PU::TWriteTable_AA(rkPacket, m_kContDefMyHomeSidejobTime);
	PU::TWriteTable_MM(rkPacket, m_kContDefMonsterEnchantGrade);
	PU::TWriteTable_MM(rkPacket, m_kContDefMonsterGradeProbabilityGroup);
	PU::TWriteTable_MM(rkPacket, m_kContDefSuperGroundGroup);
	PU::TWriteTable_AA(rkPacket, m_kContDefMyhomeBuildings);
	PU::TWriteTable_AM(rkPacket, m_kContDefGroundBuildings);
	PU::TWriteTable_AA(rkPacket, m_kContDefBasicOptionAmp);
	PU::TWriteTable_AM(rkPacket, m_kContDefItemAmpSpecific);
	PU::TWriteTable_AA(rkPacket, m_kContDefDeathPenalty);
	PU::TWriteTable_AM(rkPacket, m_kContDefSkillExtendItem);
	PU::TWriteTable_AA(rkPacket, m_kContDefNpcTalkMapMove);
	PU::TWriteTable_AA(rkPacket, m_kContDefSpecificReward);
	PU::TWriteTable_AA(rkPacket, m_ContDefSpecificReward);
	PU::TWriteArray_M(rkPacket, m_kContDefPvPLeagueTime);
	PU::TWriteTable_AA(rkPacket, m_kContDefPvPLeagueSession);
	PU::TWriteTable_AA(rkPacket, m_kContDefPvPLeagueReward);
	PU::TWriteTable_AM(rkPacket, m_kContDefJobSkillProbabilityBag);
	PU::TWriteTable_AM(rkPacket, m_kContDefJobSkillItemUpgrade);
	PU::TWriteTable_AM(rkPacket, m_kContDefJobSkillSaveIdx);

	PU::TWriteTable_MM(rkPacket, m_kContDefJobSkillLocationItem);
	PU::TWriteTable_MM(rkPacket, m_kContDefJobSkillSkill);
	PU::TWriteArray_M(rkPacket, m_kContDefJobSkillExpertness);
	PU::TWriteTable_MM(rkPacket, m_kContDefJobSkillTool);
	PU::TWriteTable_AM(rkPacket, m_kContDefJobSkillShop);
	PU::TWriteTable_AM(rkPacket, m_kContDefSocketItem);	
	PU::TWriteTable_AM(rkPacket, m_kContDefJobSkillRecipe);	
	PU::TWriteTable_AM(rkPacket, m_kContDefJobSkillProbabilityBag);
	PU::TWriteArray_M(rkPacket, m_kContDefJobSkillSoulExtract);
	PU::TWriteArray_M(rkPacket, m_kContDefJobSkillSoulTrasition);
	PU::TWriteTable_AM(rkPacket, m_kContDefExpeditionNpc);

	PU::TWriteTable_AA(rkPacket, m_kContDefBSGenGround);

	PU::TWriteTable_AM(rkPacket, m_ContDefEventGroup);
	{
		rkPacket.Push(m_ContDefEventMonsterGroup.size());
		CONT_DEF_EVENT_MONSTER_GROUP::iterator iter = m_ContDefEventMonsterGroup.begin();
		for( ; iter != m_ContDefEventMonsterGroup.end() ; ++iter )
		{
			rkPacket.Push((*iter).first);

			PU::TWriteTable_AM(rkPacket, (*iter).second);
		}
	}
	PU::TWriteTable_AA(rkPacket, m_ContDefEventRewardItemGroup);
	
	PU::TWriteTable_AM(rkPacket, m_kContDefPremium);
	PU::TWriteTable_AA(rkPacket, m_kContDefPremiumType);


	PU::TWriteTable_AM(rkPacket, m_ContEventSchedule);
	PU::TWriteTable_AM(rkPacket, m_ContEvent_BossBattle);
	PU::TWriteTable_AM(rkPacket, m_ContEvent_Race);

	PU::TWriteTable_AM(rkPacket, m_kContDefQuestLevelReward);
	PU::TWriteArray_M(rkPacket, m_kContJobSkillEventLocation);

	DWORD const dwEndTime = BM::GetTime32();
	INFO_LOG(BM::LOG_LV9, __FL__<<L"End Elapsed["<<dwEndTime - dwBeginTime<<L"]");
//*/
}

void CTableDataManager::PacketToData(BM::Stream &rkPacket, bool bReload)
{//이게 3메가?
//	/*	
	//BM::CAutoMutex Lock(GetLock()->kObjectLock);
	BM::CAutoMutex lock(m_kMutex, true);
	Clear(bReload);

	PU::TLoadTable_MM(rkPacket, m_DefClass);
	PU::TLoadTable_MM(rkPacket, m_DefClassAbil);
	PU::TLoadTable_MM(rkPacket, m_DefClassPet);
	PU::TLoadTable_AM(rkPacket, m_DefClassPetLevel);
	PU::TLoadTableArray_AMM(rkPacket, m_DefClassPetSkill);
	PU::TLoadTable_AM(rkPacket, m_DefClassPetItemOption);
	PU::TLoadTable_MM(rkPacket, m_DefClassPetAbil);
	PU::TLoadTable_AM(rkPacket, m_DefItemBag);
	PU::TLoadTable_MM(rkPacket, m_DefAbilType);
	PU::TLoadTable_MM(rkPacket, m_DefBaseCharacter);
	PU::TLoadTable_MM(rkPacket, m_DefItem);
	PU::TLoadTable_MM(rkPacket, m_DefItemAbil);
	PU::TLoadTable_MM(rkPacket, m_DefItemRare);
	PU::TLoadTable_MM(rkPacket, m_DefItemRareGroup);
	PU::TLoadTable_MM(rkPacket, m_DefItemResConvert);
	PU::TLoadTable_MM(rkPacket, m_DefMap);
	PU::TLoadTable_MM(rkPacket, m_DefMapAbil);
	PU::TLoadTable_MM(rkPacket, m_DefMapItem);
	PU::TLoadTable_MM(rkPacket, m_DefMapRegenPoint);
	PU::TLoadTable_MM(rkPacket, m_DefMonster);
	PU::TLoadTable_MM(rkPacket, m_DefMonsterAbil);
	PU::TLoadTable_MM(rkPacket, m_DefMonsterTunningAbil);
	PU::TLoadTable_MM(rkPacket, m_DefNPC);
	PU::TLoadTable_MM(rkPacket, m_DefNPCAbil);
	PU::TLoadTable_MM(rkPacket, m_DefSkill);
	PU::TLoadTable_MM(rkPacket, m_DefSkillAbil);
	PU::TLoadTable_MM(rkPacket, m_DefSkillSet);
	PU::TLoadTable_MM(rkPacket, m_DefRes);
	PU::TLoadTable_AM(rkPacket, m_DefChannelEffect);
	PU::TLoadTable_MM(rkPacket, m_DefStrings);
	PU::TLoadTable_MM(rkPacket, m_DefEffect);
	PU::TLoadTable_MM(rkPacket, m_DefEffectAbil);
	PU::TLoadTable_MM(rkPacket, m_DefUpgradeClass);
	PU::TLoadTable_MM(rkPacket, m_DefItemEnchant);
	PU::TLoadTable_MM(rkPacket, m_DefCharacterBaseWear);
	PU::TLoadTable_MM(rkPacket, m_DefItemPlusUpgrade);
	PU::TLoadTable_MM(rkPacket, m_DefItemRarityUpgrade);
	PU::TLoadTable_MM(rkPacket, m_DefItemRarityControl);
	PU::TLoadTable_MM(rkPacket, m_DefItemPlusUpControl);
	PU::TLoadTable_MM(rkPacket, m_DefItemEnchantShift);
	PU::TLoadTable_MM(rkPacket, m_DefItemDisassemble);
	PU::TLoadTable_MM(rkPacket, m_DefSuccessRateControl);
	PU::TLoadTable_MM(rkPacket, m_DefMonsterBag);
	PU::TLoadTable_MM(rkPacket, m_kDefGmCmd);
	PU::TLoadTable_MM(rkPacket, m_DefCountControl);
	PU::TLoadTable_MM(rkPacket, m_DefItemBagElements);
	PU::TLoadTable_MM(rkPacket, m_DefMonsterBagElements);
	PU::TLoadTable_MM(rkPacket, m_DefMonsterBagControl);
	PU::TLoadTable_MM(rkPacket, m_DefItemContainer);
	PU::TLoadTable_MM(rkPacket, m_DefObject);
	PU::TLoadTable_MM(rkPacket, m_DefObjectAbil);
	PU::TLoadTable_MM(rkPacket, m_DefObjcetBag);
	PU::TLoadTable_MM(rkPacket, m_DefObjcetBagElements);
	PU::TLoadTable_MM(rkPacket, m_DefItemBagGroup);
	PU::TLoadTable_MM(rkPacket, m_DefMapItemBag);
	PU::TLoadTable_MM(rkPacket, m_DefMissionResult);
	PU::TLoadTable_MM(rkPacket, m_DefMissionRoot);
	PU::TLoadTable_MM(rkPacket, m_DefMissionCandidate);
	PU::TLoadTable_MM(rkPacket, m_DefDefenceAddMonster);
    PU::TLoadTable_MM(rkPacket, m_DefShopInEmporia);
	PU::TLoadTable_MM(rkPacket, m_DefShopInGame);
	PU::TLoadTable_MM(rkPacket, m_DefShopInStock);
	PU::TLoadArray_M(rkPacket, m_DefItemOption);
	PU::TLoadTable_MM(rkPacket, m_DefItemOptionAbil);
	PU::TLoadTable_MM(rkPacket, m_DefDropMoneyControl);
	PU::TLoadTable_AM(rkPacket, m_DefPvPGroundGroup);
	PU::TLoadTable_MM(rkPacket, m_DefPvPGroundMode);
	PU::TLoadArray_M(rkPacket, m_kDefPvPReward);
	PU::TLoadTable_AM(rkPacket, m_kDefPvPRewardItem);
	PU::TLoadTable_AA(rkPacket, m_kDefPvPPlayTimeInfo);
	PU::TLoadTable_MM(rkPacket, m_DefItemMaking);
	PU::TLoadTable_MM(rkPacket, m_DefCooking);
	PU::TLoadTable_MM(rkPacket, m_DefResultControl);
	PU::TLoadTable_MM(rkPacket, m_DefQuestReward);
	PU::TLoadArray_M(rkPacket, m_DefQuestResetSchedule);
	PU::TLoadArray_M(rkPacket, m_DefQuestRandom);
	PU::TLoadTable_MM(rkPacket, m_DefQuestRandomExp);
	PU::TLoadTable_MM(rkPacket, m_DefQuestRandomTacticsExp);
	PU::TLoadTable_MM(rkPacket, m_DefQuestWanted);
	PU::TLoadTable_MM(rkPacket, m_DefDynamicAbilRate);
	PU::TLoadTable_MM(rkPacket, m_DefDynamicAbilRateBag);
	PU::TLoadTable_MM(rkPacket, m_DefItemSet);
	PU::TLoadTable_MM(rkPacket, m_DefSpendMoney);
	PU::TLoadTable_MM(rkPacket, m_DefGuildLevel);
	PU::TLoadTable_MM(rkPacket, m_DefGuildSkill);
	PU::TLoadArray_M(rkPacket, m_DefFilterUnicode);
	PU::TLoadTable_MM(rkPacket, m_kDefProperty);
	PU::TLoadArray_M(rkPacket, m_DefMapEffect);
	PU::TLoadArray_M(rkPacket, m_DefMapEntity);
	PU::TLoadTable_MM(rkPacket, m_DefFiveElementInfo);
	PU::TLoadTable_MM(rkPacket, m_DefMapStoneControl);
	PU::TLoadTable_MM(rkPacket, m_DefItemRarityUpgradeCostRate);
	PU::TLoadTable_MM(rkPacket, m_DefTacticsLevel);
	PU::TLoadTable_MM(rkPacket, m_DefTacticsQuestPseudo);
	PU::TLoadTable_MM(rkPacket, m_DefMonKillCountReward);
	PU::TLoadTable_AA(rkPacket, m_DefTransTower);
	PU::TLoadTable_AA(rkPacket, m_DefParty_Info);	
	PU::TLoadTable_MM(rkPacket, m_DefCashShop);
	PU::TLoadTable_AM(rkPacket, m_kDefEmporia);
	PU::TLoadTable_MM(rkPacket, m_DefCashShopArticle);
	PU::TLoadTable_MM(rkPacket, m_DefCashShopLimitSell);	
	PU::TLoadTable_MM(rkPacket, m_kDefContAchievements);
	PU::TLoadTable_MM(rkPacket, m_kDefAchievements);
	PU::TLoadTable_MM(rkPacket, m_kDefAchievements_SaveIdx);
	PU::TLoadTable_MM(rkPacket, m_kDefRecommendationItem);
	PU::TLoadTable_MM(rkPacket, m_DefItem2Achievement);
	PU::TLoadTable_MM(rkPacket, m_kDefGroundRareMonster);
	PU::TLoadTable_MM(rkPacket, m_kDefRareMonsterSpeech);
	PU::TLoadTable_MM(rkPacket, m_kCardLocal);
	PU::TLoadTable_MM(rkPacket, m_kDefCardKeyString);
	PU::TLoadTable_MM(rkPacket, m_kCardAbil);
	PU::TLoadTable_AM(rkPacket, m_kGemStore);
	PU::TLoadTable_AM(rkPacket, m_kDefGemStore);	
	PU::TLoadTable_AM(rkPacket, m_kDefAntique);
	PU::TLoadTable_MM(rkPacket, m_kOXQuizInfo);
	PU::TLoadTable_MM(rkPacket, m_kOXQuizReward);
	PU::TLoadTable_MM(rkPacket, m_kOXQuizEventInfo);
	PU::TLoadTable_AA(rkPacket, m_kDefMonsterCard);
	PU::TLoadTable_AA(rkPacket, m_kDefMarryText);
	PU::TLoadTable_AA(rkPacket, m_kDefHiddenRewordItem);	
	PU::TLoadTable_AA(rkPacket, m_kDefHiddenRewordBag);		
	PU::TLoadTable_AM(rkPacket, m_kDefMissionClassReward);
	PU::TLoadTable_AM(rkPacket, m_kDefMissionRankReward);
	PU::TLoadTable_AM(rkPacket, m_kMissionDefenceStage);	
	PU::TLoadTable_AM(rkPacket, m_kMissionDefenceWave);	

	PU::TLoadTable_AM(rkPacket, m_kMissionDefence7Mission);
	PU::TLoadTable_AM(rkPacket, m_kMissionDefence7Stage);
	PU::TLoadTable_AM(rkPacket, m_kMissionDefence7Wave);
	PU::TLoadTable_AM(rkPacket, m_kMissionDefence7guardian);

	PU::TLoadTable_MM(rkPacket, m_kMissionBonusMap);

	PU::TLoadTable_AA(rkPacket, m_kDefEmotion);
	PU::TLoadTable_AA(rkPacket, m_kDefEmotionGroup);
	PU::TLoadArray_A(rkPacket, m_kDefCashItemAbilFilter);
	PU::TLoadTable_AA(rkPacket, m_kDefGamble);
	PU::TLoadTable_AA(rkPacket, m_kContLimitedItem);
	PU::TLoadTable_AA(rkPacket, m_kContLimitedItemCtrl);
	PU::TLoadTable_AA(rkPacket, m_kPCRoom);
	PU::TLoadTable_AA(rkPacket, m_kPCCafe);
	PU::TLoadTable_AA(rkPacket, m_kPCCafeAbil);
	PU::TLoadTable_AA(rkPacket, m_kDefConvertItem);
	PU::TLoadTable_AA(rkPacket, m_kDefGambleShoutItem);
	PU::TLoadTable_AM(rkPacket, m_kDefPetHatch);
	PU::TLoadTable_AM(rkPacket, m_kDefPetBonusStatus);
	PU::TLoadTable_AM(rkPacket, m_kCCERewardTable);
	PU::TLoadTable_AM(rkPacket, m_kRealtyDealer);
	PU::TLoadTable_AA(rkPacket, m_kRareOptSkill);
	PU::TLoadTable_AA(rkPacket, m_kRareOptMagic);
	PU::TLoadTable_AA(rkPacket, m_kIdx2SkillNo);
	PU::TLoadTable_AA(rkPacket, m_kMixupItem);
	PU::TLoadTable_AA(rkPacket, m_kTown2Ground);
	PU::TLoadTable_AA(rkPacket, m_kMyHomeDefaultItem);
	PU::TLoadTable_AA(rkPacket, m_kMyhomeTex);
	PU::TLoadTable_AA(rkPacket, m_kHometownToMapCost);
	PU::TLoadTable_AA(rkPacket, m_DefShopNpcGuid);
	PU::TLoadTable_MM(rkPacket, m_kLuckyStarInfo);
	PU::TLoadTable_MM(rkPacket, m_kLuckyStarReward);
	PU::TLoadTable_MM(rkPacket, m_kLuckyStarRewardStep);
	PU::TLoadTable_MM(rkPacket, m_kLuckyStarEventJoinReward);
	PU::TLoadTable_AA(rkPacket, m_kDefItemEnchantAbilWeight);
	PU::TLoadTable_AM(rkPacket, m_kContEventItemReward);
	PU::TLoadTable_AM(rkPacket, m_kContTreasureChest);
	PU::TLoadTable_AM(rkPacket, m_DefItemByLevel);
	PU::TLoadTable_AM(rkPacket, m_kContDefCharCardEffect);
	PU::TLoadTable_AM(rkPacket, m_kContDefAlramMission);
	PU::TLoadTable_AA(rkPacket, m_kDefSideJobRate);
	PU::TLoadArray_M(rkPacket, m_kDefPartyEventItemSet);
	PU::TLoadTable_AA(rkPacket, m_kContDefRediceOptionCost);
	PU::TLoadTable_AA(rkPacket, m_kContDefMyHomeSidejobTime);
	PU::TLoadTable_MM(rkPacket, m_kContDefMonsterEnchantGrade);
	PU::TLoadTable_MM(rkPacket, m_kContDefMonsterGradeProbabilityGroup);
	PU::TLoadTable_MM(rkPacket, m_kContDefSuperGroundGroup);
	PU::TLoadTable_AA(rkPacket, m_kContDefMyhomeBuildings);
	PU::TLoadTable_AM(rkPacket, m_kContDefGroundBuildings);
	PU::TLoadTable_AA(rkPacket, m_kContDefBasicOptionAmp);
	PU::TLoadTable_AM(rkPacket, m_kContDefItemAmpSpecific);
	PU::TLoadTable_AA(rkPacket, m_kContDefDeathPenalty);
	PU::TLoadTable_AM(rkPacket, m_kContDefSkillExtendItem);
	PU::TLoadTable_AA(rkPacket, m_kContDefNpcTalkMapMove);
	PU::TLoadTable_AA(rkPacket, m_kContDefSpecificReward);
	PU::TLoadTable_AA(rkPacket, m_ContDefSpecificReward);
	PU::TLoadArray_M(rkPacket, m_kContDefPvPLeagueTime);
	PU::TLoadTable_AA(rkPacket, m_kContDefPvPLeagueSession);
	PU::TLoadTable_AA(rkPacket, m_kContDefPvPLeagueReward);
	PU::TLoadTable_AM(rkPacket, m_kContDefJobSkillProbabilityBag);
	PU::TLoadTable_AM(rkPacket, m_kContDefJobSkillItemUpgrade);
	PU::TLoadTable_AM(rkPacket, m_kContDefJobSkillSaveIdx);

	PU::TLoadTable_MM(rkPacket, m_kContDefJobSkillLocationItem);	
	PU::TLoadTable_MM(rkPacket, m_kContDefJobSkillSkill);	
	PU::TLoadArray_M(rkPacket, m_kContDefJobSkillExpertness);
	PU::TLoadTable_MM(rkPacket, m_kContDefJobSkillTool);
	PU::TLoadTable_AM(rkPacket, m_kContDefJobSkillShop);
	PU::TLoadTable_AM(rkPacket, m_kContDefSocketItem);	
	PU::TLoadTable_AM(rkPacket, m_kContDefJobSkillRecipe);	
	PU::TLoadTable_AM(rkPacket, m_kContDefJobSkillProbabilityBag);
	PU::TLoadArray_M(rkPacket, m_kContDefJobSkillSoulExtract);
	PU::TLoadArray_M(rkPacket, m_kContDefJobSkillSoulTrasition);
	PU::TLoadTable_AM(rkPacket, m_kContDefExpeditionNpc);

	PU::TLoadTable_AA(rkPacket, m_kContDefBSGenGround);

	PU::TLoadTable_AM(rkPacket, m_ContDefEventGroup);
	{
		int count = 0;
		rkPacket.Pop(count);
		CONT_DEF_EVENT_MONSTER_GROUP::key_type first;
		CONT_DEF_EVENT_MONSTER_GROUP::mapped_type second;
		for(int i = 0 ; i < count ; ++i)
		{
			rkPacket.Pop(first);
			PU::TLoadTable_AM(rkPacket, second);

			m_ContDefEventMonsterGroup.insert( std::make_pair( first, second ) );
			second.clear();
		}
	}
	PU::TLoadTable_AA(rkPacket, m_ContDefEventRewardItemGroup);


	PU::TLoadTable_AM(rkPacket, m_kContDefPremium);
	PU::TLoadTable_AA(rkPacket, m_kContDefPremiumType);
	PU::TLoadTable_AM(rkPacket, m_ContEventSchedule);
	PU::TLoadTable_AM(rkPacket, m_ContEvent_BossBattle);
	PU::TLoadTable_AM(rkPacket, m_ContEvent_Race);
	
	PU::TLoadTable_AM(rkPacket, m_kContDefQuestLevelReward);
	PU::TLoadArray_M(rkPacket, m_kContJobSkillEventLocation);

	IsInit(true);
//*/
}

bool CTableDataManager::Dump(std::wstring const &wstrFolder)
{//차이없음.
//
	INFO_LOG(BM::LOG_LV7, __FL__<<L"Begin ---");
	//BM::CAutoMutex Lock(GetLock()->kObjectLock);
	BM::CAutoMutex lock(m_kMutex);

{
	BM::Stream kPacket;
	PU::TWriteTable_MM(kPacket,m_DefClass);
	PU::TWriteTable_MM(kPacket,m_DefClassAbil);
	PU::TWriteTable_MM(kPacket,m_DefClassPet);
	PU::TWriteTable_AM(kPacket,m_DefClassPetLevel);
	PU::TWriteTableArray_AMM(kPacket,m_DefClassPetSkill);
	PU::TWriteTable_AM(kPacket,m_DefClassPetItemOption);
	PU::TWriteTable_MM(kPacket,m_DefClassPetAbil);
	PU::TWriteTable_AM(kPacket,m_DefItemBag);
	PU::TWriteTable_MM(kPacket,m_DefAbilType);
	PU::TWriteTable_MM(kPacket,m_DefItem);
	PU::TWriteTable_MM(kPacket,m_DefItemAbil);
	PU::TWriteTable_MM(kPacket,m_DefItemRare);
	PU::TWriteTable_MM(kPacket,m_DefItemRareGroup);
	PU::TWriteTable_MM(kPacket,m_DefItemResConvert);
	PU::TWriteTable_MM(kPacket,m_DefMap);
	PU::TWriteTable_MM(kPacket,m_DefMapAbil);
	PU::TWriteTable_MM(kPacket,m_DefMapItem);
	PU::TWriteTable_MM(kPacket,m_DefMonster);
	PU::TWriteTable_MM(kPacket,m_DefMonsterAbil);
	PU::TWriteTable_MM(kPacket,m_DefMonsterTunningAbil);
	PU::TWriteTable_MM(kPacket,m_DefNPC);
	PU::TWriteTable_MM(kPacket,m_DefNPCAbil);
	PU::TWriteTable_MM(kPacket,m_DefSkill);
	PU::TWriteTable_MM(kPacket,m_DefSkillAbil);
	PU::TWriteTable_MM(kPacket,m_DefSkillSet);
	PU::TWriteTable_MM(kPacket,m_DefRes);
	PU::TWriteTable_MM(kPacket,m_DefEffect);
	PU::TWriteTable_MM(kPacket,m_DefEffectAbil);
	PU::TWriteTable_MM(kPacket,m_DefUpgradeClass);
	PU::TWriteTable_MM(kPacket,m_DefItemEnchant);
	PU::TWriteTable_MM(kPacket,m_DefCharacterBaseWear);
	PU::TWriteTable_MM(kPacket,m_DefItemPlusUpgrade);
	PU::TWriteTable_MM(kPacket,m_DefItemRarityUpgrade);	
	PU::TWriteTable_MM(kPacket,m_DefItemEnchantShift);
	PU::TWriteTable_MM(kPacket,m_DefSuccessRateControl);
	PU::TWriteTable_MM(kPacket,m_DefMonsterBag);
	PU::TWriteArray_M(kPacket,m_DefItemOption);
	PU::TWriteTable_MM(kPacket,m_DefItemOptionAbil);
	PU::TWriteTable_MM(kPacket,m_DefMonsterBagControl);
	PU::TWriteTable_MM(kPacket,m_DefMonsterBagElements);
	PU::TWriteTable_MM(kPacket,m_DefDropMoneyControl);
	PU::TWriteTable_MM(kPacket,m_DefItemBagElements);
	PU::TWriteTable_MM(kPacket,m_DefCountControl);
	PU::TWriteTable_AM(kPacket,m_DefPvPGroundGroup);
	PU::TWriteTable_MM(kPacket,m_DefPvPGroundMode);
	PU::TWriteTable_AA(kPacket,m_kDefPvPPlayTimeInfo);
	PU::TWriteTable_MM(kPacket,m_DefItemMaking);
	PU::TWriteTable_MM(kPacket,m_DefCooking);
	PU::TWriteTable_MM(kPacket,m_DefResultControl);
	PU::TWriteTable_MM(kPacket,m_DefQuestReward);
	PU::TWriteTable_MM(kPacket,m_DefMissionRoot);	
	PU::TWriteTable_MM(kPacket,m_DefMissionCandidate);
	PU::TWriteTable_MM(kPacket, m_DefDefenceAddMonster);
	PU::TWriteTable_MM(kPacket,m_DefMissionResult);
	PU::TWriteTable_MM(kPacket,m_DefItemSet);		
	PU::TWriteTable_MM(kPacket,m_DefSpendMoney);
	PU::TWriteTable_MM(kPacket,m_DefGuildLevel);
	PU::TWriteTable_MM(kPacket,m_DefGuildSkill);
	PU::TWriteTable_MM(kPacket,m_DefObject);	
	PU::TWriteTable_MM(kPacket,m_DefObjectAbil);
	PU::TWriteTable_MM(kPacket,m_kDefProperty);
	PU::TWriteArray_M(kPacket,m_DefFilterUnicode);
	PU::TWriteArray_M(kPacket,m_DefQuestResetSchedule);
	PU::TWriteTable_MM(kPacket,m_DefQuestRandomExp);
	PU::TWriteTable_MM(kPacket,m_DefQuestRandomTacticsExp);
	PU::TWriteTable_MM(kPacket,m_DefQuestWanted);
	PU::TWriteTable_AM(kPacket,m_kDefGemStore);
	PU::TWriteTable_AM(kPacket,m_kDefAntique);
	

	PU::TWriteTable_MM(kPacket,m_DefFiveElementInfo);
	PU::TWriteTable_MM(kPacket,m_DefItemRarityUpgradeCostRate);
	PU::TWriteTable_MM(kPacket,m_DefTacticsLevel);
	PU::TWriteTable_MM(kPacket,m_DefMonKillCountReward);
	PU::TWriteTable_AA(kPacket, m_DefTransTower);
	PU::TWriteTable_AA(kPacket, m_DefParty_Info);	
	PU::TWriteTable_AM(kPacket,m_kDefEmporia);
	PU::TWriteTable_MM(kPacket,m_kDefContAchievements);
	PU::TWriteTable_MM(kPacket,m_kDefAchievements);
	PU::TWriteTable_MM(kPacket,m_DefItemBagGroup);
	PU::TWriteTable_MM(kPacket,m_DefMapItemBag);	
	PU::TWriteTable_MM(kPacket,m_kDefRecommendationItem);
	PU::TWriteTable_MM(kPacket, m_DefItemContainer);
	PU::TWriteTable_MM(kPacket, m_kDefGroundRareMonster);
	PU::TWriteTable_MM(kPacket, m_kDefRareMonsterSpeech);
	PU::TWriteTable_MM(kPacket, m_kCardLocal);
	PU::TWriteTable_MM(kPacket, m_kDefCardKeyString);
	PU::TWriteTable_MM(kPacket, m_kCardAbil);
	PU::TWriteTable_AA(kPacket, m_kDefMonsterCard);
	PU::TWriteTable_AA(kPacket, m_kDefMarryText);
	PU::TWriteTable_AA(kPacket, m_kDefHiddenRewordItem);	
	PU::TWriteTable_AA(kPacket, m_kDefHiddenRewordBag);	
	PU::TWriteTable_AM(kPacket, m_kDefMissionClassReward);	
	PU::TWriteTable_AM(kPacket, m_kDefMissionRankReward);	
	PU::TWriteTable_AM(kPacket, m_kMissionDefenceStage);		
	PU::TWriteTable_AM(kPacket, m_kMissionDefenceWave);		

	PU::TWriteTable_AM(kPacket, m_kMissionDefence7Mission);
	PU::TWriteTable_AM(kPacket, m_kMissionDefence7Stage);
	PU::TWriteTable_AM(kPacket, m_kMissionDefence7Wave);
	PU::TWriteTable_AM(kPacket, m_kMissionDefence7guardian);

	PU::TWriteTable_MM(kPacket, m_kMissionBonusMap);

	PU::TWriteTable_AA(kPacket, m_kDefEmotion);
	PU::TWriteTable_AA(kPacket, m_kDefEmotionGroup);
	PU::TWriteTable_AA(kPacket, m_kDefConvertItem);
	PU::TWriteTable_AM(kPacket, m_kDefPetHatch);
	PU::TWriteTable_AA(kPacket, m_kIdx2SkillNo);
	PU::TWriteTable_AA(kPacket, m_kTown2Ground);
	PU::TWriteTable_AA(kPacket, m_kMyhomeTex);
	PU::TWriteTable_AA(kPacket, m_kHometownToMapCost);
	PU::TWriteTable_AA(kPacket, m_kDefItemEnchantAbilWeight);
	PU::TWriteTable_MM(kPacket, m_DefObjcetBag);
	PU::TWriteTable_MM(kPacket, m_DefObjcetBagElements);
	PU::TWriteTable_AA(kPacket, m_kDefSideJobRate);
	PU::TWriteArray_M(kPacket, m_kDefPartyEventItemSet);
	PU::TWriteTable_AA(kPacket, m_kContDefRediceOptionCost);
	PU::TWriteTable_AA(kPacket, m_kContDefMyHomeSidejobTime);
	PU::TWriteTable_MM(kPacket, m_kContDefMonsterEnchantGrade);
	PU::TWriteTable_AA(kPacket, m_kContDefMyhomeBuildings);
	PU::TWriteTable_AM(kPacket, m_kContDefGroundBuildings);
	PU::TWriteTable_AA(kPacket, m_kContDefBasicOptionAmp);
	PU::TWriteTable_AM(kPacket, m_kContDefItemAmpSpecific);
	PU::TWriteTable_AM(kPacket, m_kContDefAlramMission);
	PU::TWriteTable_AA(kPacket, m_kContDefDeathPenalty);
	PU::TWriteTable_AM(kPacket, m_kContDefSkillExtendItem);
	PU::TWriteArray_M(kPacket, m_kContDefPvPLeagueTime);
	PU::TWriteTable_AA(kPacket, m_kContDefPvPLeagueSession);
	PU::TWriteTable_AA(kPacket, m_kContDefPvPLeagueReward);
	PU::TWriteTable_MM(kPacket, m_kContDefJobSkillSkill);
	PU::TWriteArray_M(kPacket, m_kContDefJobSkillExpertness);
	PU::TWriteTable_AM(kPacket, m_kContDefJobSkillSaveIdx);
	PU::TWriteTable_AM(kPacket, m_kContDefJobSkillItemUpgrade);
	PU::TWriteTable_MM(kPacket, m_kContDefJobSkillTool);
	PU::TWriteTable_AM(kPacket, m_kContDefSocketItem);	
	PU::TWriteTable_AM(kPacket, m_kContDefJobSkillRecipe);	
	PU::TWriteTable_AM(kPacket, m_kContDefJobSkillProbabilityBag);
	PU::TWriteArray_M(kPacket, m_kContDefJobSkillSoulExtract);
	PU::TWriteArray_M(kPacket, m_kContDefJobSkillSoulTrasition);
	PU::TWriteTable_AM(kPacket, m_kContDefExpeditionNpc);
	PU::TWriteTable_AM(kPacket, m_kContDefPremium);
	PU::TWriteTable_AA(kPacket, m_kContDefPremiumType);
	PU::TWriteTable_AM(kPacket, m_kContDefJumpingCharEvent);
	PU::TWriteTableArray_AMM(kPacket, m_kContDefJumpingCharEventReward);
	PU::TWriteTable_AM(kPacket, m_ContEventSchedule);
	PU::TWriteTable_AM(kPacket, m_ContEvent_BossBattle);
	PU::TWriteTable_AM(kPacket, m_ContEvent_Race);
	//PU::TWriteTable_AM(kPacket, m_kContDefJumpingCharEventItem);
	PU::TWriteTable_AM(kPacket, m_kContDefQuestLevelReward);
	PU::TWriteArray_M(kPacket, m_kContJobSkillEventLocation);

	::_wmkdir( wstrFolder.c_str() );
	std::wstring const wstrFileName = wstrFolder + L"TB.BIN";
	if(!BM::EncSave( wstrFileName, kPacket.Data()))
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}
}

{
	BM::Stream kPacket;
	PU::TWriteTable_MM(kPacket,m_DefMapRegenPoint);

	std::wstring const wstrFileName = wstrFolder + L"TB2.BIN";
	if(!BM::EncSave(wstrFileName, kPacket.Data()))
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}
}

{
	std::wstring const wstrFileName = wstrFolder + L"DefStrings.xls";
	
	FILE *fp = NULL;

	errno_t const eRet = ::_wfopen_s( &fp, wstrFileName.c_str(), _T("wt") );

	CONT_DEFSTRINGS::const_iterator itor = m_DefStrings.begin();
	while(itor != m_DefStrings.end())
	{
		::fwprintf_s(fp, _T("%d	%s	%s	Memo\n"), (*itor).first, (*itor).second.strText.c_str(),(*itor).second.strTextEng.c_str());
		++itor;
	}
	SAFE_FCLOSE(fp);
}
	INFO_LOG(BM::LOG_LV7, __FL__<<L"Ended ---");
	return true;
}

bool CTableDataManager::LoadDump(std::wstring const &strFolder)
{//4메가
	//BM::CAutoMutex Lock(GetLock()->kObjectLock);
	BM::CAutoMutex lock(m_kMutex, true);
{
	BM::vstring vstrFileName(strFolder + _T("TB"));//TB 는 파일명
	vstrFileName += _T(".BIN");

	BM::Stream kPacket;
	if(!BM::DecLoad(vstrFileName, kPacket.Data()))
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}
	kPacket.PosAdjust();

	PU::TLoadTable_MM(kPacket, m_DefClass);
	PU::TLoadTable_MM(kPacket, m_DefClassAbil);
	PU::TLoadTable_MM(kPacket, m_DefClassPet);
	PU::TLoadTable_AM(kPacket, m_DefClassPetLevel);
	PU::TLoadTableArray_AMM(kPacket, m_DefClassPetSkill);
	PU::TLoadTable_AM(kPacket, m_DefClassPetItemOption);
	PU::TLoadTable_MM(kPacket, m_DefClassPetAbil);
	PU::TLoadTable_AM(kPacket, m_DefItemBag);
	PU::TLoadTable_MM(kPacket, m_DefAbilType);
	PU::TLoadTable_MM(kPacket, m_DefItem);
	PU::TLoadTable_MM(kPacket, m_DefItemAbil);
	PU::TLoadTable_MM(kPacket, m_DefItemRare);
	PU::TLoadTable_MM(kPacket, m_DefItemRareGroup);
	PU::TLoadTable_MM(kPacket, m_DefItemResConvert);
	PU::TLoadTable_MM(kPacket, m_DefMap);
	PU::TLoadTable_MM(kPacket, m_DefMapAbil);
	PU::TLoadTable_MM(kPacket, m_DefMapItem);
	PU::TLoadTable_MM(kPacket, m_DefMonster);
	PU::TLoadTable_MM(kPacket, m_DefMonsterAbil);
	PU::TLoadTable_MM(kPacket, m_DefMonsterTunningAbil);
	PU::TLoadTable_MM(kPacket, m_DefNPC);
	PU::TLoadTable_MM(kPacket, m_DefNPCAbil);
	PU::TLoadTable_MM(kPacket, m_DefSkill);
	PU::TLoadTable_MM(kPacket, m_DefSkillAbil);	
	PU::TLoadTable_MM(kPacket, m_DefSkillSet);
	PU::TLoadTable_MM(kPacket, m_DefRes);
	PU::TLoadTable_MM(kPacket, m_DefEffect);
	PU::TLoadTable_MM(kPacket, m_DefEffectAbil);
	PU::TLoadTable_MM(kPacket, m_DefUpgradeClass);
	PU::TLoadTable_MM(kPacket, m_DefItemEnchant);
	PU::TLoadTable_MM(kPacket, m_DefCharacterBaseWear);
	PU::TLoadTable_MM(kPacket, m_DefItemPlusUpgrade);
	PU::TLoadTable_MM(kPacket, m_DefItemRarityUpgrade);
	PU::TLoadTable_MM(kPacket, m_DefItemEnchantShift);
	PU::TLoadTable_MM(kPacket, m_DefSuccessRateControl);
	PU::TLoadTable_MM(kPacket, m_DefMonsterBag);
	PU::TLoadArray_M(kPacket, m_DefItemOption);
	PU::TLoadTable_MM(kPacket, m_DefItemOptionAbil);
	PU::TLoadTable_MM(kPacket, m_DefMonsterBagControl);
	PU::TLoadTable_MM(kPacket, m_DefMonsterBagElements);
	PU::TLoadTable_MM(kPacket, m_DefDropMoneyControl);
	PU::TLoadTable_MM(kPacket, m_DefItemBagElements);
	PU::TLoadTable_MM(kPacket, m_DefCountControl);
	PU::TLoadTable_AM(kPacket, m_DefPvPGroundGroup);
	PU::TLoadTable_MM(kPacket, m_DefPvPGroundMode);
	PU::TLoadTable_AA(kPacket, m_kDefPvPPlayTimeInfo);
	PU::TLoadTable_MM(kPacket, m_DefItemMaking);
	PU::TLoadTable_MM(kPacket, m_DefCooking);
	PU::TLoadTable_MM(kPacket, m_DefResultControl);
	PU::TLoadTable_MM(kPacket, m_DefQuestReward);
	PU::TLoadTable_MM(kPacket, m_DefMissionRoot);
	PU::TLoadTable_MM(kPacket, m_DefMissionCandidate);
	PU::TLoadTable_MM(kPacket, m_DefDefenceAddMonster);
	PU::TLoadTable_MM(kPacket, m_DefMissionResult);
	PU::TLoadTable_MM(kPacket, m_DefItemSet);
	PU::TLoadTable_MM(kPacket, m_DefSpendMoney);
	PU::TLoadTable_MM(kPacket, m_DefGuildLevel);
	PU::TLoadTable_MM(kPacket, m_DefGuildSkill);
	PU::TLoadTable_MM(kPacket, m_DefObject);
	PU::TLoadTable_MM(kPacket, m_DefObjectAbil);	
	PU::TLoadTable_MM(kPacket, m_kDefProperty);
	PU::TLoadArray_M(kPacket, m_DefFilterUnicode);
	PU::TLoadArray_M(kPacket, m_DefQuestResetSchedule);
	PU::TLoadTable_MM(kPacket, m_DefQuestRandomExp);
	PU::TLoadTable_MM(kPacket, m_DefQuestRandomTacticsExp);
	PU::TLoadTable_MM(kPacket, m_DefQuestWanted);
	PU::TLoadTable_AM(kPacket, m_kDefGemStore);
	PU::TLoadTable_AM(kPacket, m_kDefAntique);

	PU::TLoadTable_MM(kPacket, m_DefFiveElementInfo);
	PU::TLoadTable_MM(kPacket, m_DefItemRarityUpgradeCostRate);
	PU::TLoadTable_MM(kPacket, m_DefTacticsLevel);
	PU::TLoadTable_MM(kPacket, m_DefMonKillCountReward);
	PU::TLoadTable_AA(kPacket, m_DefTransTower);
	PU::TLoadTable_AA(kPacket, m_DefParty_Info);	
	PU::TLoadTable_AM(kPacket, m_kDefEmporia);
	PU::TLoadTable_MM(kPacket, m_kDefContAchievements);
	PU::TLoadTable_MM(kPacket, m_kDefAchievements);
	PU::TLoadTable_MM(kPacket, m_DefItemBagGroup);
	PU::TLoadTable_MM(kPacket, m_DefMapItemBag);	
	PU::TLoadTable_MM(kPacket, m_kDefRecommendationItem);
	PU::TLoadTable_MM(kPacket, m_DefItemContainer);
	PU::TLoadTable_MM(kPacket, m_kDefGroundRareMonster);
	PU::TLoadTable_MM(kPacket, m_kDefRareMonsterSpeech);
	PU::TLoadTable_MM(kPacket, m_kCardLocal);
	PU::TLoadTable_MM(kPacket, m_kDefCardKeyString);
	PU::TLoadTable_MM(kPacket, m_kCardAbil);
	PU::TLoadTable_AA(kPacket, m_kDefMonsterCard);
	PU::TLoadTable_AA(kPacket, m_kDefMarryText);
	PU::TLoadTable_AA(kPacket, m_kDefHiddenRewordItem);	
	PU::TLoadTable_AA(kPacket, m_kDefHiddenRewordBag);
	PU::TLoadTable_AM(kPacket, m_kDefMissionClassReward);
	PU::TLoadTable_AM(kPacket, m_kDefMissionRankReward);
	PU::TLoadTable_AM(kPacket, m_kMissionDefenceStage);
	PU::TLoadTable_AM(kPacket, m_kMissionDefenceWave);	

	PU::TLoadTable_AM(kPacket, m_kMissionDefence7Mission);
	PU::TLoadTable_AM(kPacket, m_kMissionDefence7Stage);
	PU::TLoadTable_AM(kPacket, m_kMissionDefence7Wave);
	PU::TLoadTable_AM(kPacket, m_kMissionDefence7guardian);

	PU::TLoadTable_MM(kPacket, m_kMissionBonusMap);

	PU::TLoadTable_AA(kPacket, m_kDefEmotion);
	PU::TLoadTable_AA(kPacket, m_kDefEmotionGroup);
	PU::TLoadTable_AA(kPacket, m_kDefConvertItem);
	PU::TLoadTable_AM(kPacket, m_kDefPetHatch);
	PU::TLoadTable_AA(kPacket, m_kIdx2SkillNo);
	PU::TLoadTable_AA(kPacket, m_kTown2Ground);
	PU::TLoadTable_AA(kPacket, m_kMyhomeTex);
	PU::TLoadTable_AA(kPacket, m_kHometownToMapCost);
	PU::TLoadTable_AA(kPacket, m_kDefItemEnchantAbilWeight);
	PU::TLoadTable_MM(kPacket, m_DefObjcetBag);
	PU::TLoadTable_MM(kPacket, m_DefObjcetBagElements);
	PU::TLoadTable_AA(kPacket, m_kDefSideJobRate);
	PU::TLoadArray_M(kPacket, m_kDefPartyEventItemSet);
	PU::TLoadTable_AA(kPacket, m_kContDefRediceOptionCost);
	PU::TLoadTable_AA(kPacket, m_kContDefMyHomeSidejobTime);
	PU::TLoadTable_MM(kPacket, m_kContDefMonsterEnchantGrade);
	PU::TLoadTable_AA(kPacket, m_kContDefMyhomeBuildings);
	PU::TLoadTable_AM(kPacket, m_kContDefGroundBuildings);
	PU::TLoadTable_AA(kPacket, m_kContDefBasicOptionAmp);
	PU::TLoadTable_AM(kPacket, m_kContDefItemAmpSpecific);
	PU::TLoadTable_AM(kPacket, m_kContDefAlramMission);
	PU::TLoadTable_AA(kPacket, m_kContDefDeathPenalty);
	PU::TLoadTable_AM(kPacket, m_kContDefSkillExtendItem);
	PU::TLoadArray_M(kPacket, m_kContDefPvPLeagueTime);
	PU::TLoadTable_AA(kPacket, m_kContDefPvPLeagueSession);
	PU::TLoadTable_AA(kPacket, m_kContDefPvPLeagueReward);
	PU::TLoadTable_MM(kPacket, m_kContDefJobSkillSkill);
	PU::TLoadArray_M(kPacket, m_kContDefJobSkillExpertness);
	PU::TLoadTable_AM(kPacket, m_kContDefJobSkillSaveIdx);
	PU::TLoadTable_AM(kPacket, m_kContDefJobSkillItemUpgrade);
	PU::TLoadTable_MM(kPacket, m_kContDefJobSkillTool);
	PU::TLoadTable_AM(kPacket, m_kContDefSocketItem);	
	PU::TLoadTable_AM(kPacket, m_kContDefJobSkillRecipe);
	PU::TLoadTable_AM(kPacket, m_kContDefJobSkillProbabilityBag);
	PU::TLoadArray_M(kPacket, m_kContDefJobSkillSoulExtract);
	PU::TLoadArray_M(kPacket, m_kContDefJobSkillSoulTrasition);
	PU::TLoadTable_AM(kPacket, m_kContDefExpeditionNpc);
	PU::TLoadTable_AM(kPacket, m_kContDefPremium);
	PU::TLoadTable_AA(kPacket, m_kContDefPremiumType);
	PU::TLoadTable_AM(kPacket, m_kContDefJumpingCharEvent);
	PU::TLoadTableArray_AMM(kPacket, m_kContDefJumpingCharEventReward);
	PU::TLoadTable_AM(kPacket, m_ContEventSchedule);
	PU::TLoadTable_AM(kPacket, m_ContEvent_BossBattle);
	PU::TLoadTable_AM(kPacket, m_ContEvent_Race);
	//PU::TLoadTable_AM(kPacket, m_kContDefJumpingCharEventItem);
	PU::TLoadTable_AM(kPacket, m_kContDefQuestLevelReward);
	PU::TLoadArray_M(kPacket, m_kContJobSkillEventLocation);
}

{
	BM::vstring vstrFileName(strFolder + _T("TB2"));//TB 는 파일명
	vstrFileName += _T(".BIN");

	BM::Stream kPacket;
	if(!BM::DecLoad(vstrFileName, kPacket.Data())){return false;}
	kPacket.PosAdjust();

	PU::TLoadTable_MM(kPacket, m_DefMapRegenPoint);
}

{
	m_kDefAchievements_SaveIdx.clear();
	m_DefItem2Achievement.clear();
	CONT_DEF_ITEM2ACHIEVEMENT::mapped_type kItem;
	for(CONT_DEF_ACHIEVEMENTS::const_iterator c_iter=m_kDefAchievements.begin();c_iter!=m_kDefAchievements.end();++c_iter)
	{
		kItem.iItemNo = c_iter->second.iItemNo;
		kItem.iSaveIdx = c_iter->second.iSaveIdx;
		m_kDefAchievements_SaveIdx.insert(std::make_pair(c_iter->second.iSaveIdx,c_iter->second));
		m_DefItem2Achievement.insert(std::make_pair(kItem.iItemNo,kItem));
	}
}
	return true;
}

bool CTableDataManager::LoadAllDefStringXMLInFolder(std::wstring const& wstrFolderPath)
{
	WIN32_FIND_DATAW kFindData;
	std::wstring wstrFile = wstrFolderPath + L"*.xml";
	HANDLE hFind = FindFirstFileW(wstrFile.c_str(), &kFindData);

	if(INVALID_HANDLE_VALUE == hFind)
	{
		INFO_LOG( BM::LOG_LV1, __FL__ << L"Exist no file in directory");
		FindClose(hFind);
		return false;
	}

	do
	{
		std::wstring wstrExtension = kFindData.cFileName;
		wstrExtension = wstrExtension.substr(wstrExtension.find(L'.') + 1);
		std::transform(wstrExtension.begin(), wstrExtension.end(), wstrExtension.begin(), tolower);

		if( !(kFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			!wstrExtension.compare(L"xml") )
		{
			TiXmlDocument kDoc(MB(std::wstring(wstrFolderPath + kFindData.cFileName)));
			if(!kDoc.LoadFile())
			{
				INFO_LOG( BM::LOG_LV1, __FL__ << kFindData.cFileName 
					<< L" XML Load Error : " << UNI(kDoc.ErrorDesc())
					<< L" Row : " << kDoc.ErrorRow() 
					<< L" Col : " << kDoc.ErrorCol() );
			}

			else
			{
				if(!ParseDefStringXML(kDoc.FirstChild()))
				{
					INFO_LOG( BM::LOG_LV1, __FL__ << L"XML Parsing Error : " << kFindData.cFileName );
				}
			}

			kDoc.Clear();
		}

		wstrExtension.clear();

	}while(FindNextFileW(hFind, &kFindData));

	FindClose(hFind);
	return true;
}

void CTableDataManager::swap(CTableDataManager &rRight, bool bReload)
{
	BM::CAutoMutex lock(m_kMutex, true);

	m_DefClass.swap(rRight.m_DefClass);
	m_DefClassAbil.swap(rRight.m_DefClassAbil);
	m_DefClassPet.swap(rRight.m_DefClassPet);
	m_DefClassPetLevel.swap(rRight.m_DefClassPetLevel);
	m_DefClassPetSkill.swap(rRight.m_DefClassPetSkill);
	m_DefClassPetItemOption.swap(rRight.m_DefClassPetItemOption);
	m_DefClassPetAbil.swap(rRight.m_DefClassPetAbil);
	m_DefItemBag.swap(rRight.m_DefItemBag);
	m_DefAbilType.swap(rRight.m_DefAbilType);
	m_DefBaseCharacter.swap(rRight.m_DefBaseCharacter);
	m_DefItem.swap(rRight.m_DefItem);
	m_DefItemAbil.swap(rRight.m_DefItemAbil);
	m_DefItemRare.swap(rRight.m_DefItemRare);
	m_DefItemRareGroup.swap(rRight.m_DefItemRareGroup);
	m_DefItemResConvert.swap(rRight.m_DefItemResConvert);
	m_DefMap.swap(rRight.m_DefMap);
	m_DefMapAbil.swap(rRight.m_DefMapAbil);
	m_DefMapItem.swap(rRight.m_DefMapItem);
	m_DefMapRegenPoint.swap(rRight.m_DefMapRegenPoint);
	m_DefMonster.swap(rRight.m_DefMonster);
	m_DefMonsterAbil.swap(rRight.m_DefMonsterAbil);
	m_DefMonsterTunningAbil.swap(rRight.m_DefMonsterTunningAbil);
	m_DefNPC.swap(rRight.m_DefNPC);
	m_DefNPCAbil.swap(rRight.m_DefNPCAbil);
	m_DefSkill.swap(rRight.m_DefSkill);
	m_DefSkillAbil.swap(rRight.m_DefSkillAbil);
	m_DefSkillSet.swap(rRight.m_DefSkillSet);
	m_DefRes.swap(rRight.m_DefRes);
	m_DefChannelEffect.swap(rRight.m_DefChannelEffect);
	m_DefEffect.swap(rRight.m_DefEffect);
	m_DefEffectAbil.swap(rRight.m_DefEffectAbil);
	m_DefUpgradeClass.swap(rRight.m_DefUpgradeClass);
	m_DefItemEnchant.swap(rRight.m_DefItemEnchant);
	m_DefCharacterBaseWear.swap(rRight.m_DefCharacterBaseWear);
	m_DefItemPlusUpgrade.swap(rRight.m_DefItemPlusUpgrade);
	m_DefItemRarityUpgrade.swap(rRight.m_DefItemRarityUpgrade);
	m_DefItemRarityControl.swap(rRight.m_DefItemRarityControl);
	m_DefItemPlusUpControl.swap(rRight.m_DefItemPlusUpControl);
	m_DefItemEnchantShift.swap(rRight.m_DefItemEnchantShift);
	m_DefItemDisassemble.swap(rRight.m_DefItemDisassemble);
	m_DefSuccessRateControl.swap(rRight.m_DefSuccessRateControl);
	m_DefMonsterBag.swap(rRight.m_DefMonsterBag);
	m_kDefGmCmd.swap(rRight.m_kDefGmCmd);
	m_DefCountControl.swap(rRight.m_DefCountControl);
	m_DefItemBagElements.swap(rRight.m_DefItemBagElements);
	m_DefMonsterBagElements.swap(rRight.m_DefMonsterBagElements);
	m_DefMonsterBagControl.swap(rRight.m_DefMonsterBagControl);
	m_DefMissionRoot.swap(rRight.m_DefMissionRoot);
	m_DefMissionCandidate.swap(rRight.m_DefMissionCandidate);
	m_DefItemSet.swap(rRight.m_DefItemSet);
	m_DefDefenceAddMonster.swap(rRight.m_DefDefenceAddMonster);
    m_DefShopInEmporia.swap(rRight.m_DefShopInEmporia);
	m_DefShopInGame.swap(rRight.m_DefShopInGame);
	m_DefShopInStock.swap(rRight.m_DefShopInStock);
	m_DefItemOption.swap(rRight.m_DefItemOption);
	m_DefItemOptionAbil.swap(rRight.m_DefItemOptionAbil);
	m_DefDropMoneyControl.swap(rRight.m_DefDropMoneyControl);
	m_DefPvPGroundGroup.swap(rRight.m_DefPvPGroundGroup);
	m_DefPvPGroundMode.swap(rRight.m_DefPvPGroundMode);
	m_kDefPvPPlayTimeInfo.swap(rRight.m_kDefPvPPlayTimeInfo);
	m_DefItemMaking.swap(rRight.m_DefItemMaking);
	m_DefCooking.swap(rRight.m_DefCooking);
	m_DefResultControl.swap(rRight.m_DefResultControl);
	m_DefQuestReward.swap(rRight.m_DefQuestReward);
	m_DefQuestResetSchedule.swap(rRight.m_DefQuestResetSchedule);
	m_DefQuestRandom.swap(rRight.m_DefQuestRandom);
	m_DefQuestRandomExp.swap(rRight.m_DefQuestRandomExp);
	m_DefQuestRandomTacticsExp.swap(rRight.m_DefQuestRandomTacticsExp);
	m_DefQuestWanted.swap(rRight.m_DefQuestWanted);
	m_DefSpendMoney.swap(rRight.m_DefSpendMoney);
	m_DefGuildLevel.swap(rRight.m_DefGuildLevel);
	m_DefGuildSkill.swap(rRight.m_DefGuildSkill);
	m_DefObject.swap(rRight.m_DefObject);
	m_DefObjectAbil.swap(rRight.m_DefObjectAbil);
	m_DefItemBagGroup.swap(rRight.m_DefItemBagGroup);
	m_DefMapItemBag.swap(rRight.m_DefMapItemBag);
	m_kDefProperty.swap(rRight.m_kDefProperty);
	m_DefFilterUnicode.swap(rRight.m_DefFilterUnicode);
	m_DefFiveElementInfo.swap(rRight.m_DefFiveElementInfo);
	m_DefItemRarityUpgradeCostRate.swap(rRight.m_DefItemRarityUpgradeCostRate);
	m_DefTacticsLevel.swap(rRight.m_DefTacticsLevel);
	m_DefTacticsQuestPseudo.swap(rRight.m_DefTacticsQuestPseudo);
	m_DefMonKillCountReward.swap(rRight.m_DefMonKillCountReward);
	m_DefTransTower.swap(rRight.m_DefTransTower);
	m_DefParty_Info.swap(rRight.m_DefParty_Info);
	m_DefCashShop.swap(rRight.m_DefCashShop);
	m_kDefEmporia.swap(rRight.m_kDefEmporia);
	m_DefObjcetBag.swap(rRight.m_DefObjcetBag);
	m_DefObjcetBagElements.swap(rRight.m_DefObjcetBagElements);
	m_kDefPvPReward.swap(rRight.m_kDefPvPReward);
	m_kDefPvPRewardItem.swap(rRight.m_kDefPvPRewardItem);
	m_DefItemContainer.swap(rRight.m_DefItemContainer);
	m_DefMissionResult.swap(rRight.m_DefMissionResult);
	m_DefDynamicAbilRate.swap(rRight.m_DefDynamicAbilRate);
	m_DefDynamicAbilRateBag.swap(rRight.m_DefDynamicAbilRateBag);
	m_DefMapEffect.swap(rRight.m_DefMapEffect);
	m_DefMapEntity.swap(rRight.m_DefMapEntity);
	m_DefMapStoneControl.swap(rRight.m_DefMapStoneControl);
	m_DefCashShopArticle.swap(rRight.m_DefCashShopArticle);
	m_DefCashShopLimitSell.swap(rRight.m_DefCashShopLimitSell);	
	m_kDefContAchievements.swap(rRight.m_kDefContAchievements);
	m_kDefAchievements.swap(rRight.m_kDefAchievements);
	m_kDefAchievements_SaveIdx.swap(rRight.m_kDefAchievements_SaveIdx);
	m_kDefRecommendationItem.swap(rRight.m_kDefRecommendationItem);
	m_DefItem2Achievement.swap(rRight.m_DefItem2Achievement);
	m_kDefGroundRareMonster.swap(rRight.m_kDefGroundRareMonster);
	m_kDefRareMonsterSpeech.swap(rRight.m_kDefRareMonsterSpeech);
	m_kCardLocal.swap(rRight.m_kCardLocal);
	m_kDefCardKeyString.swap(rRight.m_kDefCardKeyString);
	m_kOXQuizInfo.swap(rRight.m_kOXQuizInfo);
	m_kOXQuizReward.swap(rRight.m_kOXQuizReward);
	m_kOXQuizEventInfo.swap(rRight.m_kOXQuizEventInfo);
	m_kCardAbil.swap(rRight.m_kCardAbil);
	m_kGemStore.swap(rRight.m_kGemStore);
	m_kDefGemStore.swap(rRight.m_kDefGemStore);	
	m_kDefAntique.swap(rRight.m_kDefAntique);
	m_kDefMonsterCard.swap(rRight.m_kDefMonsterCard);
	m_kDefMarryText.swap(rRight.m_kDefMarryText);
	m_kDefHiddenRewordItem.swap(rRight.m_kDefHiddenRewordItem);	
	m_kDefHiddenRewordBag.swap(rRight.m_kDefHiddenRewordBag);
	m_kDefMissionClassReward.swap(rRight.m_kDefMissionClassReward);	
	m_kDefMissionRankReward.swap(rRight.m_kDefMissionRankReward);	
	m_kMissionDefenceStage.swap(rRight.m_kMissionDefenceStage);		
	m_kMissionDefenceWave.swap(rRight.m_kMissionDefenceWave);		

	m_kMissionDefence7Mission.swap(rRight.m_kMissionDefence7Mission);
	m_kMissionDefence7Stage.swap(rRight.m_kMissionDefence7Stage);
	m_kMissionDefence7Wave.swap(rRight.m_kMissionDefence7Wave);
	m_kMissionDefence7guardian.swap(rRight.m_kMissionDefence7guardian);

	m_kMissionBonusMap.swap(rRight.m_kMissionBonusMap);

	m_kDefEmotion.swap(rRight.m_kDefEmotion);
	m_kDefEmotionGroup.swap(rRight.m_kDefEmotionGroup);
	m_kDefCashItemAbilFilter.swap(rRight.m_kDefCashItemAbilFilter);
	m_kDefGamble.swap(rRight.m_kDefGamble);
	m_kContLimitedItem.swap(rRight.m_kContLimitedItem);
	m_kContLimitedItemCtrl.swap(rRight.m_kContLimitedItemCtrl);
	m_kPCRoom.swap(rRight.m_kPCRoom);
	m_kPCCafe.swap(rRight.m_kPCCafe);
	m_kPCCafeAbil.swap(rRight.m_kPCCafeAbil);
	m_kDefConvertItem.swap(rRight.m_kDefConvertItem);
	m_kDefGambleShoutItem.swap(rRight.m_kDefGambleShoutItem);
	m_kDefPetHatch.swap(rRight.m_kDefPetHatch);
	m_kDefPetBonusStatus.swap(rRight.m_kDefPetBonusStatus);
	m_kCCERewardTable.swap(rRight.m_kCCERewardTable);
	m_kRealtyDealer.swap(rRight.m_kRealtyDealer);
	m_kRareOptSkill.swap(rRight.m_kRareOptSkill);
	m_kRareOptMagic.swap(rRight.m_kRareOptMagic);
	m_kIdx2SkillNo.swap(rRight.m_kIdx2SkillNo);
	m_kMixupItem.swap(rRight.m_kMixupItem);
	m_kTown2Ground.swap(rRight.m_kTown2Ground);
	m_kMyHomeDefaultItem.swap(rRight.m_kMyHomeDefaultItem);
	m_kMyhomeTex.swap(rRight.m_kMyhomeTex);
	m_kHometownToMapCost.swap(rRight.m_kHometownToMapCost);
	m_DefShopNpcGuid.swap(rRight.m_DefShopNpcGuid);
	m_kLuckyStarInfo.swap(rRight.m_kLuckyStarInfo);
	m_kLuckyStarReward.swap(rRight.m_kLuckyStarReward);
	m_kLuckyStarRewardStep.swap(rRight.m_kLuckyStarRewardStep);
	m_kLuckyStarEventJoinReward.swap(rRight.m_kLuckyStarEventJoinReward);
	m_kDefItemEnchantAbilWeight.swap(rRight.m_kDefItemEnchantAbilWeight);
	m_kContEventItemReward.swap(rRight.m_kContEventItemReward);
	m_kContTreasureChest.swap(rRight.m_kContTreasureChest);
	m_DefItemByLevel.swap(rRight.m_DefItemByLevel);
	m_kContDefCharCardEffect.swap(rRight.m_kContDefCharCardEffect);
	m_kContDefAlramMission.swap(rRight.m_kContDefAlramMission);
	m_kDefSideJobRate.swap(rRight.m_kDefSideJobRate);
	m_kDefPartyEventItemSet.swap(rRight.m_kDefPartyEventItemSet);
	m_kContDefRediceOptionCost.swap(rRight.m_kContDefRediceOptionCost);
	m_kContDefMyHomeSidejobTime.swap(rRight.m_kContDefMyHomeSidejobTime);
	m_kContDefMonsterEnchantGrade.swap(rRight.m_kContDefMonsterEnchantGrade);
	m_kContDefMonsterGradeProbabilityGroup.swap(rRight.m_kContDefMonsterGradeProbabilityGroup);
	m_kContDefSuperGroundGroup.swap(rRight.m_kContDefSuperGroundGroup);
	m_kContDefMyhomeBuildings.swap(rRight.m_kContDefMyhomeBuildings);
	m_kContDefGroundBuildings.swap(rRight.m_kContDefGroundBuildings);
	m_kContDefBasicOptionAmp.swap(rRight.m_kContDefBasicOptionAmp);
	m_kContDefItemAmpSpecific.swap(rRight.m_kContDefItemAmpSpecific);
	m_kContDefDeathPenalty.swap(rRight.m_kContDefDeathPenalty);
	m_kContDefSkillExtendItem.swap(rRight.m_kContDefSkillExtendItem);
	m_kContDefNpcTalkMapMove.swap(rRight.m_kContDefNpcTalkMapMove);
	m_kContDefSpecificReward.swap(rRight.m_kContDefSpecificReward);
	m_kContDefPvPLeagueTime.swap(rRight.m_kContDefPvPLeagueTime);
	m_kContDefPvPLeagueSession.swap(rRight.m_kContDefPvPLeagueSession);
	m_kContDefPvPLeagueReward.swap(rRight.m_kContDefPvPLeagueReward);
	m_kContDefJobSkillLocationItem.swap(rRight.m_kContDefJobSkillLocationItem);	
	m_kContDefJobSkillSkill.swap(rRight.m_kContDefJobSkillSkill);	
	m_kContDefJobSkillExpertness.swap(rRight.m_kContDefJobSkillExpertness);	
	m_kContDefJobSkillTool.swap(rRight.m_kContDefJobSkillTool);
	m_kContDefJobSkillProbabilityBag.swap(rRight.m_kContDefJobSkillProbabilityBag);
	m_kContDefJobSkillItemUpgrade.swap(rRight.m_kContDefJobSkillItemUpgrade);
	m_kContDefJobSkillSaveIdx.swap(rRight.m_kContDefJobSkillSaveIdx);
	m_kContDefJobSkillShop.swap(rRight.m_kContDefJobSkillShop);
	m_kContDefSocketItem.swap(rRight.m_kContDefSocketItem);
	m_kContDefJobSkillRecipe.swap(rRight.m_kContDefJobSkillRecipe);	
	m_kContDefJobSkillProbabilityBag.swap(rRight.m_kContDefJobSkillProbabilityBag);	
	m_kContDefJobSkillSoulExtract.swap(rRight.m_kContDefJobSkillSoulExtract);
	m_kContDefJobSkillSoulTrasition.swap(rRight.m_kContDefJobSkillSoulTrasition);
	m_kContDefExpeditionNpc.swap(rRight.m_kContDefExpeditionNpc);
	m_kContDefBSGenGround.swap(rRight.m_kContDefBSGenGround);
	m_kContDefPremium.swap(rRight.m_kContDefPremium);
	m_kContDefPremiumType.swap(rRight.m_kContDefPremiumType);
	m_ContDefEventGroup.swap(rRight.m_ContDefEventGroup);
	m_ContDefEventMonsterGroup.swap(rRight.m_ContDefEventMonsterGroup);
	m_ContDefEventRewardItemGroup.swap(rRight.m_ContDefEventRewardItemGroup);
	m_ContDefSpecificReward.swap(rRight.m_ContDefSpecificReward);
	m_kContDefQuestLevelReward.swap(rRight.m_kContDefQuestLevelReward);
	m_kContJobSkillEventLocation.swap(rRight.m_kContJobSkillEventLocation);
}


void CTableDataManager::Clear(bool bReload)
{//5메가
///*
	BM::CAutoMutex lock(m_kMutex, true);

	IsInit(false);

	m_DefClass.clear();
	m_DefClassAbil.clear();
	m_DefClassPet.clear();
	m_DefClassPetLevel.clear();
	m_DefClassPetSkill.clear();
	m_DefClassPetItemOption.clear();
	m_DefClassPetAbil.clear();
	m_DefItemBag.clear();
	m_DefAbilType.clear();
	m_DefBaseCharacter.clear();
	m_DefItem.clear();
	m_DefItemAbil.clear();
	m_DefItemRare.clear();
	m_DefItemRareGroup.clear();
	m_DefItemResConvert.clear();
	m_DefMap.clear();
	m_DefMapAbil.clear();
	m_DefMapItem.clear();
	m_DefMapRegenPoint.clear();
	m_DefMonster.clear();
	m_DefMonsterAbil.clear();
	m_DefMonsterTunningAbil.clear();
	m_DefNPC.clear();
	m_DefNPCAbil.clear();
	m_DefSkill.clear();
	m_DefSkillAbil.clear();
	m_DefSkillSet.clear();
	m_DefRes.clear();
	m_DefChannelEffect.clear();
	m_DefEffect.clear();
	m_DefEffectAbil.clear();
	m_DefUpgradeClass.clear();
	m_DefItemEnchant.clear();
	m_DefCharacterBaseWear.clear();
	m_DefItemPlusUpgrade.clear();
	m_DefItemRarityUpgrade.clear();
	m_DefItemRarityControl.clear();
	m_DefItemPlusUpControl.clear();
	m_DefItemEnchantShift.clear();
	m_DefItemDisassemble.clear();
	m_DefSuccessRateControl.clear();
	m_DefMonsterBag.clear();
	m_kDefGmCmd.clear();
	m_DefCountControl.clear();
	m_DefItemBagElements.clear();
	m_DefMonsterBagElements.clear();
	m_DefMonsterBagControl.clear();
	m_DefMissionRoot.clear();
	m_DefMissionCandidate.clear();
	m_DefMissionResult.clear();
	m_DefItemSet.clear();
	m_DefDefenceAddMonster.clear();
    m_DefShopInEmporia.clear();
	m_DefShopInGame.clear();
	m_DefShopInStock.clear();
	m_DefItemOption.clear();
	m_DefItemOptionAbil.clear();
	m_DefDropMoneyControl.clear();
	m_DefPvPGroundGroup.clear();
	m_DefPvPGroundMode.clear();
	m_kDefPvPPlayTimeInfo.clear();
	m_DefItemMaking.clear();
	m_DefCooking.clear();
	m_DefResultControl.clear();
	m_DefQuestReward.clear();
	m_DefQuestResetSchedule.clear();
	m_DefQuestRandom.clear();
	m_DefQuestRandomExp.clear();
	m_DefQuestRandomTacticsExp.clear();
	m_DefQuestWanted.clear();

	m_DefSpendMoney.clear();
	m_DefGuildLevel.clear();
	m_DefGuildSkill.clear();
	m_DefObject.clear();
	m_DefObjectAbil.clear();
	m_kDefProperty.clear();
	m_DefFilterUnicode.clear();
	m_DefFiveElementInfo.clear();
	m_DefMapStoneControl.clear();
	m_DefItemRarityUpgradeCostRate.clear();
	m_DefTacticsLevel.clear();
	m_DefTacticsQuestPseudo.clear();
	m_DefMonKillCountReward.clear();
	m_DefTransTower.clear();
	m_DefParty_Info.clear();
	m_DefCashShop.clear();
	m_kDefEmporia.clear();
	m_kDefRecommendationItem.clear();
	m_DefObjcetBag.clear();
	m_DefObjcetBagElements.clear();
	m_DefItemBagGroup.clear();
	m_DefMapItemBag.clear();
	m_kDefPvPReward.clear();
	m_kDefPvPRewardItem.clear();
	m_DefItemContainer.clear();
	m_DefMissionResult.clear();
	m_DefDynamicAbilRate.clear();
	m_DefDynamicAbilRateBag.clear();
	m_DefMapEffect.clear();
	m_DefMapEntity.clear();
	m_DefCashShopArticle.clear();
	m_DefCashShopLimitSell.clear();
	m_kDefContAchievements.clear();
	m_kDefAchievements.clear();
	m_kDefAchievements_SaveIdx.clear();
	m_DefItem2Achievement.clear();
	m_kDefGroundRareMonster.clear();
	m_kDefRareMonsterSpeech.clear();
	m_kCardLocal.clear();
	m_kDefCardKeyString.clear();
	m_kOXQuizInfo.clear();
	m_kOXQuizReward.clear();
	m_kOXQuizEventInfo.clear();
	m_kCardAbil.clear();
	m_kGemStore.clear();
	m_kDefGemStore.clear();
	m_kDefAntique.clear();
	m_kDefMonsterCard.clear();
	m_kDefMarryText.clear();
	m_kDefHiddenRewordItem.clear();
	m_kDefHiddenRewordBag.clear();
	m_kDefMissionClassReward.clear();	
	m_kDefMissionRankReward.clear();
	m_kMissionDefenceStage.clear();
	m_kMissionDefenceWave.clear();

	m_kMissionDefence7Mission.clear();
	m_kMissionDefence7Stage.clear();
	m_kMissionDefence7Wave.clear();
	m_kMissionDefence7guardian.clear();

	m_kMissionBonusMap.clear();

	m_kDefEmotion.clear();
	m_kDefEmotionGroup.clear();
	m_kDefCashItemAbilFilter.clear();
	m_kDefGamble.clear();
	m_kContLimitedItem.clear();
	m_kContLimitedItemCtrl.clear();
	m_kPCRoom.clear();
	m_kPCCafe.clear();
	m_kPCCafeAbil.clear();
	m_kDefConvertItem.clear();
	m_kDefGambleShoutItem.clear();
	m_kDefPetHatch.clear();
	m_kDefPetBonusStatus.clear();
	m_kCCERewardTable.clear();
	m_kRealtyDealer.clear();
	m_kRareOptSkill.clear();
	m_kRareOptMagic.clear();
	m_kIdx2SkillNo.clear();
	m_kMixupItem.clear();
	m_kTown2Ground.clear();
	m_kMyHomeDefaultItem.clear();
	m_kMyhomeTex.clear();
	m_kHometownToMapCost.clear();
	m_DefShopNpcGuid.clear();
	m_kLuckyStarInfo.clear();
	m_kLuckyStarReward.clear();
	m_kLuckyStarRewardStep.clear();
	m_kLuckyStarEventJoinReward.clear();
	m_kDefItemEnchantAbilWeight.clear();
	m_kContEventItemReward.clear();
	m_kContTreasureChest.clear();
	m_DefItemByLevel.clear();
	m_kContDefCharCardEffect.clear();
	m_kContDefAlramMission.clear();
	m_kDefSideJobRate.clear();
	m_kDefPartyEventItemSet.clear();
	m_kContDefRediceOptionCost.clear();
	m_kContDefMyHomeSidejobTime.clear();
	m_kContDefMonsterEnchantGrade.clear();
	m_kContDefMonsterGradeProbabilityGroup.clear();
	m_kContDefSuperGroundGroup.clear();
	m_kContDefMyhomeBuildings.clear();
	m_kContDefGroundBuildings.clear();
	m_kContDefBasicOptionAmp.clear();
	m_kContDefItemAmpSpecific.clear();
	m_kContDefDeathPenalty.clear();
	m_kContDefSkillExtendItem.clear();
	m_kContDefNpcTalkMapMove.clear();
	m_kContDefSpecificReward.clear();
	m_kContDefPvPLeagueTime.clear();
	m_kContDefPvPLeagueSession.clear();
	m_kContDefPvPLeagueReward.clear();
	m_kContDefJobSkillLocationItem.clear();
	m_kContDefJobSkillSkill.clear();
	m_kContDefJobSkillExpertness.clear();
	m_kContDefJobSkillTool.clear();
	m_kContDefJobSkillProbabilityBag.clear();
	m_kContDefJobSkillItemUpgrade.clear();
	m_kContDefJobSkillSaveIdx.clear();
	m_kContDefJobSkillShop.clear();
	m_kContDefSocketItem.clear();
	m_kContDefJobSkillRecipe.clear();	
	m_kContDefJobSkillProbabilityBag.clear();
	m_kContDefJobSkillSoulExtract.clear();
	m_kContDefJobSkillSoulTrasition.clear();
	m_kContDefExpeditionNpc.clear();
	m_kContDefBSGenGround.clear();
	m_kContDefPremium.clear();
	m_kContDefPremiumType.clear();
	m_kContDefJumpingCharEvent.clear();
	m_kContDefJumpingCharEventReward.clear();
	m_ContEventSchedule.clear();
	m_ContEvent_BossBattle.clear();
	//m_kContDefJumpingCharEventItem.clear();
	m_kContDefQuestLevelReward.clear();
	m_kContJobSkillEventLocation.clear();
}

bool CTableDataManager::GetStringName(int const iID, std::wstring& rkName)
{
	CONT_DEFSTRINGS::const_iterator kItor = m_DefStrings.find(iID);
	if (kItor == m_DefStrings.end())
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}
	rkName = kItor->second.strText;
	return true;
}

void CTableDataManager::GetReloadDef(SReloadDef& rkDef, int iUpdateType )
{
	rkDef.kLockWrapper.Set(&m_kMutex);

	//PgControlDefMgr::Update 랑 맞추어 주어야 한다.
	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_MonsterDefMgr ) )
	{
		GetContDef(rkDef.pContDefMonster);
		GetContDef(rkDef.pContDefMonsterAbil);
		GetContDef(rkDef.pContDefMonsterTunningAbil);
		GetContDef(rkDef.pkDefStrings);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_SkillDefMgr ) )
	{
		GetContDef(rkDef.pContDefSkill);
		GetContDef(rkDef.pContDefSkillAbil);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_ItemDefMgr ) )
	{
		GetContDef(rkDef.pContDefItem);
		GetContDef(rkDef.pContDefItemAbil);
		GetContDef(rkDef.pkDefItemResConvert);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_RareDefMgr ) )
	{
		GetContDef(rkDef.pContDefRare);
		if ( NULL == rkDef.pContDefItemAbil )
		{
			GetContDef(rkDef.pContDefItemAbil);//
		}
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_ItemEnchantDefMgr ) )
	{
		GetContDef(rkDef.pContDefItemEnchant);
		if ( NULL == rkDef.pContDefItemAbil )
		{
			GetContDef(rkDef.pContDefItemAbil);//
		}
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_ClassDefMgr ) )
	{
		GetContDef(rkDef.pkDefClass);
		GetContDef(rkDef.pkDefClassAbil);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_ItemBagMgr ) )
	{
		GetContDef(rkDef.pkItemBagGroup);
		GetContDef(rkDef.pkItemBag);
		GetContDef(rkDef.pkItemBagElements);
		GetContDef(rkDef.pkSuccessRateControl);
		GetContDef(rkDef.pkCountControl);
		GetContDef(rkDef.pkMoneyControl);
		GetContDef(rkDef.pkItemContainer);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_StoreMgr ) )
	{
		// 위에서 이미 Lock을 한것이기 때문에 여기 Lock
        TABLE_LOCK(CONT_TBL_SHOP_IN_EMPORIA) kObjLock0;
		GetContDef(kObjLock0);
		rkDef.pkShopInEmporia = kObjLock0.Get();
		TABLE_LOCK(CONT_TBL_SHOP_IN_GAME) kObjLock1;
		GetContDef(kObjLock1);
		rkDef.pkShopInGame = kObjLock1.Get();
		TABLE_LOCK(CONT_TBL_SHOP_IN_STOCK) kObjLock2;
		GetContDef(kObjLock2);
		rkDef.pkShopInStock = kObjLock2.Get();
		TABLE_LOCK(CONT_SHOPNPC_GUID) kObjLock3;
		GetContDef(kObjLock3);
		rkDef.pkShopNpcGuid = kObjLock3.Get();
		GetContDef(rkDef.pkJobSkillShop);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_ItemOptionMgr ) )
	{
		GetContDef(rkDef.pkItemOption);
		GetContDef(rkDef.pkItemOptionAbil);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_SpendMoneyMgr ) )
	{
		GetContDef(rkDef.pkSpendMoney);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_ItemSetDefMgr ) )
	{
		GetContDef(rkDef.pkItemSet);
		if ( NULL == rkDef.pkItemOptionAbil )
		{
			GetContDef(rkDef.pkItemOptionAbil);//
		}
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_DynamicDefMgr ) )
	{
		GetContDef(rkDef.pkDynamicAbilRate);
		GetContDef(rkDef.pkDynamicAbilRateBag);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_EffectDefMgr ) )
	{
		GetContDef(rkDef.pkContDefEffect);
		GetContDef(rkDef.pkContDefEffectAbil);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_ItemMakingDefMgr ) )
	{
		GetContDef(rkDef.pkDefItemMaking);
		GetContDef(rkDef.pkDefResultControl);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_MonsterBag ) )
	{
		GetContDef(rkDef.pkRegenPPoint);
		GetContDef(rkDef.pContDefMonsterBag);
		GetContDef(rkDef.pContDefMonsterBagControl);
		GetContDef(rkDef.pkMonsterBagElements);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_MonsterBag ) )
	{
		GetContDef(rkDef.pkRegenPPoint);
		GetContDef(rkDef.pContDefMonsterBag);
		GetContDef(rkDef.pContDefMonsterBagControl);
		GetContDef(rkDef.pkMonsterBagElements);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_ObjectDefMgr ) )
	{
		GetContDef(rkDef.pkDefObject);
		GetContDef(rkDef.pkDefObjectAbil);
		if ( rkDef.pkDefStrings == NULL ){GetContDef(rkDef.pkDefStrings);}
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_PropertyMgr ) )
	{
		GetContDef(rkDef.pkDefProperty);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_GroundEffect ) )
	{
		GetContDef(rkDef.pkDefMapEffect);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_RecommendationItem ) )
	{
		GetContDef(rkDef.pkDefRecommendationItem);
	}

	// CUSTOM
	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_GenPointMgr ) )
	{
		if ( NULL == rkDef.pkRegenPPoint ){GetContDef(rkDef.pkRegenPPoint);}//
		if ( NULL == rkDef.pContDefMonsterBag ){GetContDef(rkDef.pContDefMonsterBag);}//
		if ( NULL == rkDef.pContDefMonsterBagControl ){GetContDef(rkDef.pContDefMonsterBagControl);}//
		if ( NULL == rkDef.pkMonsterBagElements ){GetContDef(rkDef.pkMonsterBagElements);}//
		if ( NULL == rkDef.pkSuccessRateControl ){GetContDef(rkDef.pkSuccessRateControl);}//
		GetContDef(rkDef.pkDefObjectBag);
		GetContDef(rkDef.pkDefObjectBagElements);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_ExtMgr ) )
	{
		GetContDef(rkDef.pkQuestReward);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_OnlyFirst ) )
	{
		GetContDef(rkDef.pkContMap);
		GetContDef(rkDef.pkMissionResult);
		GetContDef(rkDef.pkMissionCandi);
		GetContDef(rkDef.pkMissionRoot);
		GetContDef(rkDef.pkSuperGroundGrp);		
		GetContDef(rkDef.pkMissionBonusMap);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_PropertyMgr ) )
	{
		GetContDef(rkDef.pkDefProperty);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_Pet ) )
	{
		GetContDef(rkDef.pkDefClassPet);
		GetContDef(rkDef.pkDefClassPetLevel);
		GetContDef(rkDef.pkDefClassPetSkill);
		GetContDef(rkDef.pkDefClassPetAbil);
		GetContDef(rkDef.pkDefPetHatch);
		GetContDef(rkDef.pkDefPetBonusStatus);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr( iUpdateType, PgControlDefMgr::EDef_Default ) )
	{
		GetContDef(rkDef.pkContDefRes);
		GetContDef(rkDef.pkContDefUpgradeClass);	
		GetContDef(rkDef.pkContMissionLevelRoot);
		GetContDef(rkDef.pkContMissionCandidate);
		GetContDef(rkDef.pkPvPGroundMode);
		GetContDef(rkDef.pkPvPReward);
		GetContDef(rkDef.pkPvPRewardItem);
		GetContDef(rkDef.pkItemBagGroup);
		GetContDef(rkDef.pkDefGroundRareMonster);
		GetContDef(rkDef.pkDefRareMonsterSpeech);
		GetContDef(rkDef.pkCardLocal);
		GetContDef(rkDef.pkDefCardKeyString);
		GetContDef(rkDef.pkCardAbil);
		GetContDef(rkDef.pkGemStore);
		GetContDef(rkDef.pkDefGemStore);		
		GetContDef(rkDef.pkMonsterCard);
		GetContDef(rkDef.pkEmotion);
		GetContDef(rkDef.pkEmotionGroup);
		GetContDef(rkDef.pkCashItemAbilFilter);
		GetContDef(rkDef.pkGamble);
		GetContDef(rkDef.pkPCRoom);
		GetContDef(rkDef.pkPCCafe);
		GetContDef(rkDef.pkPCCafeAbil);
		GetContDef(rkDef.pkDefConvertItem);
		GetContDef(rkDef.pkDefGambleShoutItem);
		GetContDef(rkDef.pkCCERewardTable);
		GetContDef(rkDef.pkRealtyDealer);
		GetContDef(rkDef.pkRareOptSkill);
		GetContDef(rkDef.pkRareOptMagic);
		GetContDef(rkDef.pkIdx2SkillNo);
		GetContDef(rkDef.pkMixupItem);
		GetContDef(rkDef.pkTown2Ground);
		GetContDef(rkDef.pkMyHomeDefaultItem);
		GetContDef(rkDef.pkMyHomeTex);
		GetContDef(rkDef.pkHometownToMapCost);
		GetContDef(rkDef.pkDefItemEnchantAbilWeight);
		GetContDef(rkDef.pkContMapItemBag);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr(iUpdateType, PgControlDefMgr::EDef_MapDefMgr ) )
	{
		GetContDef(rkDef.pkDefMap);
		GetContDef(rkDef.pkDefMapAbil);
	}

	if ( PgControlDefMgr::IsIncludeDefMgr(iUpdateType, PgControlDefMgr::EDef_PremiumMgr ) )
	{
		GetContDef(rkDef.pkDefPremium);
		GetContDef(rkDef.pkDefPremiumType);
	}
}

bool CTableDataManager::ParseDefStringXML(TiXmlNode const* pkNode)
{
	while(pkNode)
	{
		switch(pkNode->Type())
		{
		case TiXmlNode::ELEMENT:
			{
				TiXmlElement* pkElement = (TiXmlElement*)pkNode;
				assert(pkElement);

				char const* pcTagName = pkElement->Value();
				if(0 == strcmp(pcTagName, XML_ELEMENT_TEXT))
				{
					ParseTEXTElement(pkElement->FirstAttribute());
				}
				else if(0 == strcmp(pcTagName, XML_ELEMENT_STRING_TABLE_LOCAL))
				{
					TiXmlNode const* pkChildNode = pkNode->FirstChild();
					if(pkChildNode != NULL)
					{
						if(!ParseDefStringXML(pkChildNode))
						{
							return false;
						}
					}
				}
			}break;

		case TiXmlNode::DECLARATION:
			{				
				TiXmlDeclaration const* pDecl = dynamic_cast<TiXmlDeclaration const*>(pkNode);
				if(pDecl && pDecl->Encoding())
				{
					std::string strEncoding = pDecl->Encoding();
					UPR(strEncoding);

					if( 0 == strEncoding.compare(std::string("UTF-8")) || 
						0 == strEncoding.compare(std::string("UTF8")) )
					{
						m_bUTF8 = true;
					}
				}	
			}break;

		default:
			{

			}break;
		}

		pkNode = pkNode->NextSibling();
	}

	return true;
}

void CTableDataManager::ParseTEXTElement(TiXmlAttribute const* pkAttribute)
{
	CONT_DEFSTRINGS::mapped_type kElement;
	char const* pcText = NULL;

	while(pkAttribute)
	{
		char const* pcAttrName = pkAttribute->Name();

		if(0 == _stricmp(pcAttrName, XML_ATTRIBUTE_ID))
		{
			kElement.StringNo = pkAttribute->IntValue();
		}
		else if(0 == _stricmp(pcAttrName, XML_ATTRIBUTE_TEXT))
		{
			pcText = pkAttribute->Value();
		}
		else
		{
			// 파싱할 수 없는 엘레먼트
		}

		pkAttribute = pkAttribute->Next();
	}

	if(m_bUTF8)
	{
		kElement.strText = BM::vstring::ConvToUnicodeFromUTF8(pcText);
	}
	else
	{
		kElement.strText = UNI(pcText);
	}

	if( kElement.StringNo &&
		!kElement.strText.empty() )
	{
		std::pair<CONT_DEFSTRINGS::iterator, bool> kRet = m_DefStrings.insert( std::make_pair(kElement.StringNo, kElement) );
		if(!kRet.second)
		{
			INFO_LOG( BM::LOG_LV1, __FL__ << L"DefString Duplicated StringNo[" << kElement.StringNo << "]" );
		}
	}
}

bool const RouletteRate(int const iRateTblNo, size_t &riOutResult, int const IN_MAX_INDEX, int const iAddRate)//CONT_DEF_SUCCESS_RATE_CONTROL 를 이용한 인덱스 뽑기.
{
	const CONT_DEF_SUCCESS_RATE_CONTROL* pCont = NULL;
	g_kTblDataMgr.GetContDef(pCont);
	
	CONT_DEF_SUCCESS_RATE_CONTROL::const_iterator itor = pCont->find(iRateTblNo);
	if(itor == pCont->end())
	{//확률 테이블 없음.
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	TBL_DEF_SUCCESS_RATE_CONTROL const *pRateTbl = &itor->second;

	if(pRateTbl
	&&	pRateTbl->iTotal
	)
	{
		size_t const kAddRate = ((pRateTbl->iTotal * iAddRate)/ABILITY_RATE_VALUE);//첫번째 인덱스가 성공한다는 예외임.
		int const kTotalRate = std::max(static_cast<int>(1),static_cast<int>(pRateTbl->iTotal - kAddRate));
		int const iResultRate = BM::Rand_Index(kTotalRate);

		size_t iAccRate = 0;
		for( int i = 0; MAX_SUCCESS_RATE_ARRAY > i; ++i )
		{
			iAccRate += pRateTbl->aRate[i];//누적값이 넘어 서는 순간. 간다.
			if( static_cast<int>(iAccRate) > iResultRate )
			{
				if( 0 <= i
				&&	IN_MAX_INDEX > i)
				{
					riOutResult = i;
					return true;
				}
				else
				{
					LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
					return false;
				}
			}
		}
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}
	//돌 확률이 없음.
	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
	return false;
}

bool const RouletteRate(int const iRateTblNo, int const iCount, std::vector<int> &rOutResult)//종류 몇가지 고르기
{
	const CONT_DEF_SUCCESS_RATE_CONTROL* pCont = NULL;
	g_kTblDataMgr.GetContDef(pCont);
	
	CONT_DEF_SUCCESS_RATE_CONTROL::const_iterator itor = pCont->find(iRateTblNo);
	if(itor == pCont->end())
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	const TBL_DEF_SUCCESS_RATE_CONTROL *pRateTbl = &itor->second;

	TBL_DEF_SUCCESS_RATE_CONTROL kTempTbl = *pRateTbl;

	int iTempCount = iCount;
	if(0 >= iTempCount)
	{
		LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
		return false;
	}

	while(iTempCount--)
	{
		if(kTempTbl.iTotal)
		{
			size_t const iResultRate = BM::Rand_Index(kTempTbl.iTotal);
			
			size_t iAccRate = 0;
			for(int i = 0; MAX_SUCCESS_RATE_ARRAY > i; ++i)
			{
				iAccRate += kTempTbl.aRate[i];//누적값이 넘어 서는 순간. 간다.
				if( iAccRate > iResultRate )
				{
					rOutResult.push_back(i);
					kTempTbl.iTotal -= kTempTbl.aRate[i];
					kTempTbl.aRate[i] = 0;
					break;
				}
			}
		}
		else
		{//수량만큼 뽑지 못했다.
			rOutResult.clear();
			LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
			return false;
		}
	}

	return true;
}

bool const RouletteRateEx( std::list<int> const &kListRateTblNo, int &riOutResult, int const IN_MAX_INDEX )
{
	if ( kListRateTblNo.size() && (IN_MAX_INDEX < MAX_SUCCESS_RATE_ARRAY * static_cast<int>(kListRateTblNo.size())) )
	{
		CONT_DEF_SUCCESS_RATE_CONTROL const *pCont = NULL;
		g_kTblDataMgr.GetContDef( pCont );

		if ( pCont )
		{
			unsigned int iTotalRate = 0;

			std::vector<TBL_DEF_SUCCESS_RATE_CONTROL const *> kContSuccessRateCtrl;
			kContSuccessRateCtrl.reserve( kListRateTblNo.size() );

			std::list<int>::const_iterator list_itr = kListRateTblNo.begin();
			for ( ; list_itr != kListRateTblNo.end() ; ++list_itr )
			{
				CONT_DEF_SUCCESS_RATE_CONTROL::const_iterator def_itr = pCont->find( *list_itr );
				if ( def_itr != pCont->end() )
				{
					iTotalRate += static_cast<unsigned int>(def_itr->second.iTotal);
					kContSuccessRateCtrl.push_back( &(def_itr->second) );
				}
				else
				{
					CAUTION_LOG( BM::LOG_LV4, __FL__ << L"Not Found SUCCESS_RATE_CONTROL ID<" << *list_itr << "L>" );
					LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
					return false;
				}
			}

			unsigned int const iRandValue = static_cast<unsigned int>(BM::Rand_Index( iTotalRate ));
			unsigned int iAccRate = 0;

			int iCheckIndex = 0;

			std::vector<TBL_DEF_SUCCESS_RATE_CONTROL const *>::const_iterator ctrl_itr = kContSuccessRateCtrl.begin();
			for ( ; ctrl_itr != kContSuccessRateCtrl.end() ; ++ctrl_itr )
			{
				for ( int i = 0 ; i < MAX_SUCCESS_RATE_ARRAY ; ++i )
				{
					iAccRate += static_cast<unsigned int>((*ctrl_itr)->aRate[i]);
					if ( iAccRate > iRandValue )
					{
						riOutResult = iCheckIndex;
						return true;
					}

					if ( ++iCheckIndex > IN_MAX_INDEX )
					{
						return false;//
					}
				}
			}
		}
	}

	LIVE_CHECK_LOG(BM::LOG_LV1, __FL__ << _T("Return false"));
	return false;
}