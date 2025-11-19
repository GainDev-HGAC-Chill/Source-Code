USE [DR2_Local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

TRUNCATE TABLE [dbo].[TB_DefGmCommand]
GO

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 1, N'/Net_GiveItem(ItemNo,Count,RarityControlNo,isCurse,isSeal)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 2, N'/Net_GiveItemSet(ItemSetNo)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 3, N'/Net_SetItemCount(InvType,InvPos,Count)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4, N'/Net_ChangeClass(Class,Level,IsGod)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 5, N'/Net_SkillPoint(Point)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 6, N'/Net_GmAbil(Type,IsAdd)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 7, N'/Net_HealMe()', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 8, N'/Net_Quest(StartID,EndID,IsComplete)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 9, N'/Net_GiveSetAbil64(LowValue,HighValue)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 10, N'/Net_DropItem(itemNo)', 2 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 12, N'/Net_ReqNotice(Content)', 2 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 13, N'/Net_KickUser(Name)', 2 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 15, N'/Net_BlockUser(Name,Time)', 2 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 16, N'/Net_QuestState(QuestID,ParamNo,Count)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 18, N'/Net_SpeedChange(Speed)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 19, N'/Net_SkillCoolTimeInit()', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 20, N'/Net_KillUnit(UnitGuid,IsNoRegen)', 2 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 21, N'/Net_AddMonster(MonsterNo,Count,Type)', 2 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 23, N'/Net_Mute(Name,Time)', 2 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 24, N'/Net_BeginQuest(QuestID)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 25, N'/Net_SetAbil(Type,Value)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 26, N'/Net_SetEnchant(InvType,InvPos,ModifyType,V1,V2)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 27, N'/Net_MissionMove(MissionNo,Level)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 28, N'/Net_MissionStage(StageNo)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 29, N'/Net_AddGuildExp(Value)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 30, N'/Net_FailDailyQuest()', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 31, N'/Net_MissionScore(Score)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 32, N'/Net_GroundMute(True/False)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 33, N'/Net_SetDGAttr(Attr, True/False)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 34, N'/Net_AddBSPoint(iPoint, iTeamPoint)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 35, N'/Net_SetBSState(iGameIDX, iState)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 41, N'/Net_ReqAddEffect(EffectNo)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 42, N'/Net_ReqDeleteEffect(EffectNo)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 43, N'/Net_SetRealmQuest(RealmQuestID, Count)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 44, N'/Net_SGMove(SuperGroundNo, ModeNo)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 45, N'/Net_SGFloor(iFloor, iSpawn)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 50, N'/Net_NewAlramMission( iMissionNo )', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 51, N'/Net_ClearIngQuest()', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 52, N'/Net_GuildBoardRefresh()', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 60, N'/Net_UnitSetAbil(kGuid,iType,iValue)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 80, N'/Net_ReqMapMove(MapNo,SpawnNo)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 81, N'/Net_ReqMapMove_ReCall(Name,IsParty)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 82, N'/Net_ReqMapMove_Target(Name)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 83, N'/Net_ReqMapMove_TargetToMap(Name,IsParty,TargetMapNo,SpawnNo)', 2 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 84, N'/Net_ReqMapMove_TargetToMap(Name,IsParty,TargetMapNo,SpawnNo)', 2 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 90, N'/Net_CoupleInit()', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 91, N'/Net_TeleportToMon(iMonsterNo,iCount)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 92, N'/Net_CopyThat(CharName)', 1 )
INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level]) -- same "Net_CopyThat"
VALUES ( 93, N'/Net_CopyThat(CharName)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 94, N'/Net_LimitHP(NewHP)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 101, N'/Net_GameStart()', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 102, N'/Net_GameEnd()', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 110, N'/Net_GameAddPoint( nPoint )', 2 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 111, N'/Net_KOH_TriggerUnitPoint(kTriggerID, iPoint)', 2 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 120, N'/Net_LoveRoundWin(WinTeam)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 150, N'/Net_StartCommunityEvent(EventNo)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 151, N'/Net_EndComuunityEvent()', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 152, N'/Net_MoveToEventGround(EventNo)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 201, N'/Net_SetAchievement(Idx,Value)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 202, N'/Net_ClearItem(InvType,InvPos)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 203, N'/Net_SetAchievementTime(idx,value)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 204, N'/Net_CompleteAchievement(idx)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 2001, N'/Net_SetArticleState(State)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 3001, N'/Net_EmporiaOpen(kEmporiaID,wYear,wMonth,wDay,wHour,wMin,iOpenLevel,iBattleWeek,iBattleTime)', 2 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 3002, N'/Net_EmporiaClose(EmporiaID)', 2 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 3004, N'/Net_EmporiaReady(EmporiaID)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 3104, N'/Net_PetChangeClass(iGrade,sLevel)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 3109, N'/Net_PetAddAbil(wType,iValue)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 3125, N'/Net_PetSetAbil(wType,iValue)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4001, N'/Net_OXOpen(EventID)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4002, N'/Net_OXStep(Step)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4010, N'/Net_SetItemTime(InvType,InvPos,Year,Month,Day)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4011, N'/Net_SetItemLimitTime(byInv,byPos,iUseTime,iTimeType)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4020, N'/Net_SetTexTime(street,house,year,mon,day)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4021, N'/Net_AuctionEnd(street,house)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4022, N'/Net_LuckyStarOpen(EventID)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4023, N'/Net_LuckyStarStep(Step)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4024, N'/Net_ServerTime(iTimeType)', 1 )


INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4025, N'/Net_CashItemGiftAdd(CashItemNo,UseTime,StartDate,EndDate,Sender,Memo,MailTitle,MailBody)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4026, N'/Net_CashItemGiftDel(EventNo)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4027, N'/Net_GodHand(bSet)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4028, N'/Net_PlayerPlayTimeStep(Step)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4029, N'/Net_SetPlayerPlayTime(strID,iAccConSec,iAccDisSec,bMember)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4100, N'/Net_PvPLeague_SetEvent(iEventType)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 4200, N'/Net_SetPointCopy(value)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 5001, N'/Net_JSAddExp(iSkillNo, iValue)', 1 )
INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 5002, N'/Net_JSAddExh(iValue)', 1 )
INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 5003, N'/Net_JSResetExh(iMinute)', 1 )
INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 5004, N'Net_JSAlwaysUseSubTool(bUse)', 1 )
INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 5012, N'/Net_JSSetSaveIdx(iSaveIdx,bSet)', 1 )

INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 5020, N'/Net_PremiumInsert(Name,iServiceNo)', 1 )
INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 5021, N'/Net_PremiumModify(Name,AddMin)', 1 )
INSERT INTO [dbo].[TB_DefGmCommand] ([CmdNo],[Memo],[Level])
VALUES ( 5022, N'/Net_PremiumRemove(Name)', 1 )
