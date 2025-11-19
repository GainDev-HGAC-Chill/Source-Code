USE [DR2_User]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Admin_ClearAllCharacter]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Admin_ClearAllCharacter]
GO

CREATE PROCEDURE [dbo].[up_Admin_ClearAllCharacter]
/*
////////////////////////////////////////////////////////////////////////
// Lasst Update by : Eric Kim
// Update date  : 2008-10-06
// Description : 모든 Character정보와 관련 정보 삭제하기
// [PARAMETER] : 
// [RETURN] : 
// [REMARK]
//	2009-5-6, YonMy 수정
////////////////////////////////////////////////////////////////////////
*/
	@Confirm nvarchar(20)	-- 실수 방지 하기 위한 확인 메시지

AS
set nocount on
SET XACT_ABORT ON

BEGIN

	IF @Confirm = 'ImSure'
	BEGIN
		
		BEGIN TRAN

		-- Emporia
		EXEC [dbo].[up_Admin_ClearEmporia] @Confirm
		
		-- Guild
		TRUNCATE TABLE [dbo].[TB_Guild_Set_Mercenary]
		TRUNCATE TABLE [dbo].[TB_Guild_Extern_Info]
		TRUNCATE TABLE [dbo].[TB_Guild_Member_Grade]
		TRUNCATE TABLE [dbo].[TB_Guild_Member]
		TRUNCATE TABLE [dbo].[TB_Guild_Applicant]
		TRUNCATE TABLE [dbo].[TB_Guild_EntranceOpen]
		TRUNCATE TABLE [dbo].[TB_Guild_Inventory_Log]
		
		DELETE FROM [dbo].[TB_Guild_Basic_Info]
		
		-- Couple
		TRUNCATE TABLE [dbo].[TB_UserCouple]
		
		-- Friend
		TRUNCATE TABLE [dbo].[TB_UserFriend]

		-- Cash
		TRUNCATE TABLE [dbo].[TB_UserCash_Rank]
		TRUNCATE TABLE [dbo].[TB_UserCashGift]
		TRUNCATE TABLE [dbo].[TB_RewardCashItemByGuid]

		-- Mission
		TRUNCATE TABLE [dbo].[TB_Mission_Rank]
		TRUNCATE TABLE [dbo].[TB_Mission_Report]
		
		-- PVP
		TRUNCATE TABLE [dbo].[TB_PvP_Ranking_SeasonLog]
		IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_PvP_Ranking_Season_0]') AND type in (N'U'))
			TRUNCATE TABLE [dbo].[TB_PvP_Ranking_Season_0]
		IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_PvP_Ranking_Season_1]') AND type in (N'U'))
			TRUNCATE TABLE [dbo].[TB_PvP_Ranking_Season_1]
		TRUNCATE TABLE [dbo].[TB_PvPLeague]
		TRUNCATE TABLE [dbo].[TB_PvPLeague_Battle]
		TRUNCATE TABLE [dbo].[TB_PvPLeague_Team]
		TRUNCATE TABLE [dbo].[TB_PvPLeague_Tournament]

		
		-- Etc
		TRUNCATE TABLE [dbo].[TB_Record_LevelUp_PlayTimeSec]
		TRUNCATE TABLE [dbo].[TB_RealmQuestStatus]
		TRUNCATE TABLE [dbo].[TB_UserWantedQuest]
		TRUNCATE TABLE [dbo].[TB_QueryDeadlockLog]
		TRUNCATE TABLE [dbo].[TB_SpecificReward]
		TRUNCATE TABLE [dbo].[TB_User_Skill_CoolTime]
		TRUNCATE TABLE [dbo].[TB_User_ChatBlock]


		-- Mail / Market
		TRUNCATE TABLE [dbo].[TB_UserMarketInfo2]
		TRUNCATE TABLE [dbo].[TB_GroupMailRecvedCharacter]
		TRUNCATE TABLE [dbo].[TB_UserMarket]
		TRUNCATE TABLE [dbo].[TB_GroupMail]
		TRUNCATE TABLE [dbo].[TB_Sys_MailName]
		TRUNCATE TABLE [dbo].[TB_UserMail]

		-- MyHome
		TRUNCATE TABLE [dbo].[TB_User_MyHome_EquipItem]
		TRUNCATE TABLE [dbo].[TB_User_MyHome_TodayVisitors]
		TRUNCATE TABLE [dbo].[TB_User_MyHome_VisitLog]
		TRUNCATE TABLE [dbo].[TB_User_MyHome_Visitors]
		TRUNCATE TABLE [dbo].[TB_User_MyHome_WriteLog_Visitors]
		TRUNCATE TABLE [dbo].[TB_User_MyHome_Base]
		TRUNCATE TABLE [dbo].[TB_User_MyHome_Invitation]
		TRUNCATE TABLE [dbo].[TB_User_Myhome_SideJob]

		-- Achievement
		TRUNCATE TABLE [dbo].[TB_UserAchievement_TimeLimit]
		TRUNCATE TABLE [dbo].[TB_UserAchievementFirstComplete]
		TRUNCATE TABLE [dbo].[TB_UserAchievementRank]
		TRUNCATE TABLE [dbo].[TB_UserAchievementRankTotal]
		TRUNCATE TABLE [dbo].[TB_UserAchievementRankView]
		TRUNCATE TABLE [dbo].[TB_UserAchievements]
		
		-- Pet
		TRUNCATE TABLE [dbo].[TB_Pet]
		
		-- Item
		TRUNCATE TABLE [dbo].[TB_LimitedItemRecord]
		TRUNCATE TABLE [dbo].[TB_Member_ShareData]
		TRUNCATE TABLE [dbo].[TB_UserDealings]
		TRUNCATE TABLE [dbo].[TB_UserItem_UnbindDate]
		TRUNCATE TABLE [dbo].[TB_UserItem]
		TRUNCATE TABLE [dbo].[TB_UserItem_Enchant]
		TRUNCATE TABLE [dbo].[TB_ExpCard]
		TRUNCATE TABLE [dbo].[TB_UserItem_MonsterCard]
		
		-- Event
		TRUNCATE TABLE [dbo].[TB_LuckyStarEventSub]
		TRUNCATE TABLE [dbo].[TB_LuckyStarJoinedUser]
		TRUNCATE TABLE [dbo].[TB_Event]
		TRUNCATE TABLE [dbo].[TB_EventUserState]
		TRUNCATE TABLE [dbo].[TB_OXQuizEventState]

		-- User Basic info
		TRUNCATE TABLE [dbo].[TB_Penalty]
		TRUNCATE TABLE [dbo].[TB_UserCharacter_Card]
		TRUNCATE TABLE [dbo].[TB_UserCharacter_DateContents]
		TRUNCATE TABLE [dbo].[TB_UserCharacter_Extern]
		TRUNCATE TABLE [dbo].[TB_UserCharacter_Point]
		TRUNCATE TABLE [dbo].[TB_UserPortal]
		TRUNCATE TABLE [dbo].[TB_UserSkillSet]
		TRUNCATE TABLE [dbo].[TB_CharacterReward]
		TRUNCATE TABLE [dbo].[TB_CharacterSub]
		DELETE FROM [dbo].[TB_CharacterBasic]

		IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_JumpingCharEvent_State]') AND type in (N'U'))
			TRUNCATE TABLE [dbo].[TB_JumpingCharEvent_State]

		-- JobSkill
		TRUNCATE TABLE [dbo].[TB_UserJobSkill_Expertness]
		TRUNCATE TABLE [dbo].[TB_UserJobSkill_Exhaustion]
		IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_JobSkill_WorkBench_Log]') AND type in (N'U'))
			DROP TABLE [dbo].[TB_JobSkill_WorkBench_Log]
		IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_JobSkill_WorkBench_Status]') AND type in (N'U'))
			DROP TABLE [dbo].[TB_JobSkill_WorkBench_Status]
		IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserJobSkill_WB_OfflineHistory]') AND type in (N'U'))
			DROP TABLE [dbo].[TB_UserJobSkill_WB_OfflineHistory]

		-- Temp table
		IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DeleteAchievementsTable]') AND type in (N'U'))
			DROP TABLE [dbo].[TB_DeleteAchievementsTable]
		IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_RemoveCharacter]') AND type in (N'U'))
			DROP TABLE [dbo].[TB_RemoveCharacter]

		-- web
		TRUNCATE TABLE [dbo].[TB_Web_IndunClearUserCountInfo]
		TRUNCATE TABLE [dbo].[TB_Web_UserCharacter]
		TRUNCATE TABLE [dbo].[TB_Web_UserCharacter_ComboInfo]
		TRUNCATE TABLE [dbo].[TB_Web_UserItemInfo]
		TRUNCATE TABLE [dbo].[TB_Web_UserItemInfo_Status]
		TRUNCATE TABLE [dbo].[TB_Web_BaseItemInfo]
		
		--Premium
		TRUNCATE TABLE [dbo].[TB_UserPremium]

	INSERT INTO [dbo].[TB_Guild_Basic_Info]
           ([GuildGuid]
           ,[MasterCharacterGuid]
           ,[GuildName]
           ,[CurrentLevel]
           ,[CurrentExp]
           ,[Emblem]
           ,[CreateDate]
           ,[TaxExpRate]
           ,[TaxModifyDate]
           ,[SkillPoint]
           ,[Skills])
     VALUES
           ('00000000-0000-0000-0000-000000000000'
           ,'00000000-0000-0000-0000-000000000000'
           ,'NullGuild'
           ,0
           ,0
           ,0
           ,NULL
           ,0
           ,NULL
           ,0
           ,0x00)

		COMMIT TRAN
	END
	ELSE
	BEGIN
		print('This procedure will delete ALL CHARACTER')
		print('If you are convinced that you know well what you will do and you are sure')
		print('EXEC UP_ClearAllMember ImSure or ImSurePerfect')
		return
	END
	

END
GO
