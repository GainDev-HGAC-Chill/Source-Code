USE DR2_Def
GO
/* To prevent any potential data loss issues, you should review this script in detail before running it outside the context of the database designer.*/
/*
BEGIN TRANSACTION
SET QUOTED_IDENTIFIER ON
SET ARITHABORT ON
SET NUMERIC_ROUNDABORT OFF
SET CONCAT_NULL_YIELDS_NULL ON
SET ANSI_NULLS ON
SET ANSI_PADDING ON
SET ANSI_WARNINGS ON
COMMIT
BEGIN TRANSACTION
GO
ALTER TABLE dbo.TB_DefQuestReward
	DROP CONSTRAINT DF_TB_DefQuestReward_NationCode
GO
ALTER TABLE dbo.TB_DefQuestReward
	DROP CONSTRAINT DF_TB_DefQuestReward_GroupNo
GO
ALTER TABLE dbo.TB_DefQuestReward
	DROP CONSTRAINT DF_TB_DefQuestReward_IsType
GO
ALTER TABLE dbo.TB_DefQuestReward
	DROP CONSTRAINT DF_TB_DefQuestReward_LevelMin
GO
ALTER TABLE dbo.TB_DefQuestReward
	DROP CONSTRAINT DF_TB_DefQuestReward_LevelMax
GO
ALTER TABLE dbo.TB_DefQuestReward
	DROP CONSTRAINT DF_TB_DefQuestReward_TacticsLevel
GO
ALTER TABLE dbo.TB_DefQuestReward
	DROP CONSTRAINT DF_TB_DefQuestReward_TacticsExp
GO
ALTER TABLE dbo.TB_DefQuestReward
	DROP CONSTRAINT DF_TB_DefQuestReward_GuildExp
GO
ALTER TABLE dbo.TB_DefQuestReward
	DROP CONSTRAINT DF_TB_DefQuestReward_QuestDifficult
GO
ALTER TABLE dbo.TB_DefQuestReward
	DROP CONSTRAINT DF_TB_DefQuestReward_OrderIndex
GO
CREATE TABLE dbo.Tmp_TB_DefQuestReward
	(
	QuestID int NOT NULL,
	Memo nvarchar(50) NULL,
	NationCode int NOT NULL,
	XmlPath nvarchar(100) NULL,
	GroupNo int NOT NULL,
	QuestType int NOT NULL,
	RewardExp int NOT NULL,
	RewardGold int NOT NULL,
	LevelMin int NOT NULL,
	LevelMax int NOT NULL,
	LimitLevelMax int NOT NULL,
	TacticsLevel int NOT NULL,
	TacticsExp int NOT NULL,
	GuildExp int NOT NULL,
	QuestDifficult int NOT NULL,
	f_OrderIndex int NOT NULL
	)  ON [PRIMARY]
GO
DECLARE @v sql_variant 
SET @v = N'Quest reward definition'
EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefQuestReward', NULL, NULL
GO
ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
	DF_TB_DefQuestReward_NationCode DEFAULT ((-1)) FOR NationCode
GO
ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
	DF_TB_DefQuestReward_GroupNo DEFAULT ((0)) FOR GroupNo
GO
ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
	DF_TB_DefQuestReward_IsType DEFAULT ((0)) FOR QuestType
GO
ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
	DF_TB_DefQuestReward_LevelMin DEFAULT ((1)) FOR LevelMin
GO
ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
	DF_TB_DefQuestReward_LevelMax DEFAULT ((9999)) FOR LevelMax
GO
ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
	DF_TB_DefQuestReward_LimitLevelMax DEFAULT 0 FOR LimitLevelMax
GO
ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
	DF_TB_DefQuestReward_TacticsLevel DEFAULT ((0)) FOR TacticsLevel
GO
ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
	DF_TB_DefQuestReward_TacticsExp DEFAULT ((0)) FOR TacticsExp
GO
ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
	DF_TB_DefQuestReward_GuildExp DEFAULT ((0)) FOR GuildExp
GO
ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
	DF_TB_DefQuestReward_QuestDifficult DEFAULT ((0)) FOR QuestDifficult
GO
ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
	DF_TB_DefQuestReward_OrderIndex DEFAULT ((0)) FOR f_OrderIndex
GO
IF EXISTS(SELECT * FROM dbo.TB_DefQuestReward)
	 EXEC('INSERT INTO dbo.Tmp_TB_DefQuestReward (QuestID, Memo, NationCode, XmlPath, GroupNo, QuestType, RewardExp, RewardGold, LevelMin, LevelMax, TacticsLevel, TacticsExp, GuildExp, QuestDifficult, f_OrderIndex)
		SELECT QuestID, Memo, NationCode, XmlPath, GroupNo, QuestType, RewardExp, RewardGold, LevelMin, LevelMax, TacticsLevel, TacticsExp, GuildExp, QuestDifficult, f_OrderIndex FROM dbo.TB_DefQuestReward WITH (HOLDLOCK TABLOCKX)')
GO
DROP TABLE dbo.TB_DefQuestReward
GO
EXECUTE sp_rename N'dbo.Tmp_TB_DefQuestReward', N'TB_DefQuestReward', 'OBJECT' 
GO
ALTER TABLE dbo.TB_DefQuestReward ADD CONSTRAINT
	PK_TB_DefQuestReward_QuestID_NationCode PRIMARY KEY CLUSTERED 
	(
	QuestID,
	NationCode
	) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

GO
COMMIT
*/

-- Add Remote Complete
--BEGIN TRANSACTION
GO
IF NOT EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefQuestReward') AND [name] = 'f_IsCanRemoteComplete')
BEGIN
	ALTER TABLE dbo.TB_DefQuestReward ADD
		f_IsCanRemoteComplete tinyint NOT NULL CONSTRAINT DF_TB_DefQuestReward_f_IsCanRemoteComplete DEFAULT 0
END
GO
IF NOT EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefQuestReward') AND [name] = 'f_IsCanShare')
BEGIN
	ALTER TABLE dbo.TB_DefQuestReward ADD
		f_IsCanShare tinyint NOT NULL CONSTRAINT DF_TB_DefQuestReward_f_IsCanShare DEFAULT 1
END
GO
--COMMIT

/*
	2010.12.28 퀘스트 테이블 통합 작업
*/
-----------------------------------------------------------------------------------------------------------------------------------BEGIN
IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefQuestReward]') AND [Name] = 'NationCodeStr')
BEGIN
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_NationCode
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_GroupNo
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_IsType
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_LevelMin
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_LevelMax
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_LimitLevelMax
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_TacticsLevel
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_TacticsExp
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_GuildExp
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_QuestDifficult
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_OrderIndex
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_f_IsCanRemoteComplete
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_f_IsCanShare
	
	CREATE TABLE dbo.Tmp_TB_DefQuestReward
		(
		NationCodeStr nvarchar(50) NOT NULL,
		QuestID int NOT NULL,
		Memo nvarchar(50) NULL,
		XmlPath nvarchar(100) NULL,
		GroupNo int NOT NULL,
		QuestType int NOT NULL,
		RewardExp int NOT NULL,
		RewardGold int NOT NULL,
		LevelMin int NOT NULL,
		LevelMax int NOT NULL,
		LimitLevelMax int NOT NULL,
		TacticsLevel int NOT NULL,
		TacticsExp int NOT NULL,
		GuildExp int NOT NULL,
		QuestDifficult int NOT NULL,
		f_OrderIndex int NOT NULL,
		f_IsCanRemoteComplete tinyint NOT NULL,
		f_IsCanShare tinyint NOT NULL,
		TitleText int NOT NULL,
		GroupName int NOT NULL,
		Class bigint NOT NULL,
		PreQuestAnd nvarchar(50) NOT NULL,
		PreQuestOr nvarchar(50) NOT NULL,
		NotQuest nvarchar(50) NOT NULL,
		MinParty int NOT NULL,
		MaxParty int NOT NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'Quest reward definition'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefQuestReward', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_NationCodeStr DEFAULT ((0)) FOR NationCodeStr
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_GroupNo DEFAULT ((0)) FOR GroupNo
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_IsType DEFAULT ((0)) FOR QuestType
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_LevelMin DEFAULT ((1)) FOR LevelMin
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_LevelMax DEFAULT ((9999)) FOR LevelMax
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_LimitLevelMax DEFAULT ((0)) FOR LimitLevelMax
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_TacticsLevel DEFAULT ((0)) FOR TacticsLevel
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_TacticsExp DEFAULT ((0)) FOR TacticsExp
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_GuildExp DEFAULT ((0)) FOR GuildExp
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_QuestDifficult DEFAULT ((0)) FOR QuestDifficult
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_OrderIndex DEFAULT ((0)) FOR f_OrderIndex
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_f_IsCanRemoteComplete DEFAULT ((0)) FOR f_IsCanRemoteComplete
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_f_IsCanShare DEFAULT ((1)) FOR f_IsCanShare
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_TitleText DEFAULT ((0)) FOR TitleText
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_GroupName DEFAULT ((0)) FOR GroupName
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_Class DEFAULT ((0)) FOR Class
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_PreQuestAnd DEFAULT ((0)) FOR PreQuestAnd
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_PreQuestOr DEFAULT ((0)) FOR PreQuestOr
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_NotQuest DEFAULT ((0)) FOR NotQuest
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_MinParty DEFAULT ((0)) FOR MinParty
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_MaxParty DEFAULT ((0)) FOR MaxParty
	
	IF EXISTS(SELECT * FROM dbo.TB_DefQuestReward)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefQuestReward (QuestID, Memo, XmlPath, GroupNo, QuestType, RewardExp, RewardGold, LevelMin, LevelMax, LimitLevelMax, TacticsLevel, TacticsExp, GuildExp, QuestDifficult, f_OrderIndex, f_IsCanRemoteComplete, f_IsCanShare)
			SELECT QuestID, Memo, XmlPath, GroupNo, QuestType, RewardExp, RewardGold, LevelMin, LevelMax, LimitLevelMax, TacticsLevel, TacticsExp, GuildExp, QuestDifficult, f_OrderIndex, f_IsCanRemoteComplete, f_IsCanShare FROM dbo.TB_DefQuestReward WITH (HOLDLOCK TABLOCKX)')
	
	DROP TABLE dbo.TB_DefQuestReward
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefQuestReward', N'TB_DefQuestReward', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefQuestReward ADD CONSTRAINT
		PK_TB_DefQuestReward PRIMARY KEY CLUSTERED 
		(
		NationCodeStr,
		QuestID
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
GO
-----------------------------------------------------------------------------------------------------------------------------------END


IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefQuestReward]') AND [Name] = 'DraClassLimit')
BEGIN
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_NationCodeStr
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_GroupNo
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_IsType
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_LevelMin
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_LevelMax
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_LimitLevelMax
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_TacticsLevel
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_TacticsExp
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_GuildExp
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_QuestDifficult
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_OrderIndex
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_f_IsCanRemoteComplete
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_f_IsCanShare
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_TitleText
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_GroupName
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_Class
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_PreQuestAnd
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_PreQuestOr
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_NotQuest
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_MinParty
	
	ALTER TABLE dbo.TB_DefQuestReward
		DROP CONSTRAINT DF_TB_DefQuestReward_MaxParty
	
	CREATE TABLE dbo.Tmp_TB_DefQuestReward
		(
		NationCodeStr nvarchar(50) NOT NULL,
		QuestID int NOT NULL,
		Memo nvarchar(50) NULL,
		XmlPath nvarchar(100) NULL,
		GroupNo int NOT NULL,
		QuestType int NOT NULL,
		RewardExp int NOT NULL,
		RewardGold int NOT NULL,
		LevelMin int NOT NULL,
		LevelMax int NOT NULL,
		LimitLevelMax int NOT NULL,
		TacticsLevel int NOT NULL,
		TacticsExp int NOT NULL,
		GuildExp int NOT NULL,
		QuestDifficult int NOT NULL,
		f_OrderIndex int NOT NULL,
		f_IsCanRemoteComplete tinyint NOT NULL,
		f_IsCanShare tinyint NOT NULL,
		TitleText int NOT NULL,
		GroupName int NOT NULL,
		Class bigint NOT NULL,
		DraClassLimit bigint NOT NULL,
		PreQuestAnd nvarchar(50) NOT NULL,
		PreQuestOr nvarchar(50) NOT NULL,
		NotQuest nvarchar(50) NOT NULL,
		MinParty int NOT NULL,
		MaxParty int NOT NULL
		)  ON [PRIMARY]	
	
	DECLARE @v sql_variant 
	SET @v = N'Quest reward definition'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefQuestReward', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_NationCodeStr DEFAULT ((0)) FOR NationCodeStr
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_GroupNo DEFAULT ((0)) FOR GroupNo
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_IsType DEFAULT ((0)) FOR QuestType
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_LevelMin DEFAULT ((1)) FOR LevelMin
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_LevelMax DEFAULT ((9999)) FOR LevelMax
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_LimitLevelMax DEFAULT ((0)) FOR LimitLevelMax
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_TacticsLevel DEFAULT ((0)) FOR TacticsLevel
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_TacticsExp DEFAULT ((0)) FOR TacticsExp
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_GuildExp DEFAULT ((0)) FOR GuildExp
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_QuestDifficult DEFAULT ((0)) FOR QuestDifficult
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_OrderIndex DEFAULT ((0)) FOR f_OrderIndex
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_f_IsCanRemoteComplete DEFAULT ((0)) FOR f_IsCanRemoteComplete
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_f_IsCanShare DEFAULT ((1)) FOR f_IsCanShare
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_TitleText DEFAULT ((0)) FOR TitleText
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_GroupName DEFAULT ((0)) FOR GroupName
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_Class DEFAULT ((0)) FOR Class
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_DraClassLimit DEFAULT ((0)) FOR DraClassLimit
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_PreQuestAnd DEFAULT ((0)) FOR PreQuestAnd
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_PreQuestOr DEFAULT ((0)) FOR PreQuestOr
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_NotQuest DEFAULT ((0)) FOR NotQuest
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_MinParty DEFAULT ((0)) FOR MinParty
	
	ALTER TABLE dbo.Tmp_TB_DefQuestReward ADD CONSTRAINT
		DF_TB_DefQuestReward_MaxParty DEFAULT ((0)) FOR MaxParty
	
	IF EXISTS(SELECT * FROM dbo.TB_DefQuestReward)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefQuestReward (NationCodeStr, QuestID, Memo, XmlPath, GroupNo, QuestType, RewardExp, RewardGold, LevelMin, LevelMax, LimitLevelMax, TacticsLevel, TacticsExp, GuildExp, QuestDifficult, f_OrderIndex, f_IsCanRemoteComplete, f_IsCanShare, TitleText, GroupName, Class, PreQuestAnd, PreQuestOr, NotQuest, MinParty, MaxParty)
			SELECT NationCodeStr, QuestID, Memo, XmlPath, GroupNo, QuestType, RewardExp, RewardGold, LevelMin, LevelMax, LimitLevelMax, TacticsLevel, TacticsExp, GuildExp, QuestDifficult, f_OrderIndex, f_IsCanRemoteComplete, f_IsCanShare, TitleText, GroupName, Class, PreQuestAnd, PreQuestOr, NotQuest, MinParty, MaxParty FROM dbo.TB_DefQuestReward WITH (HOLDLOCK TABLOCKX)')
	
	DROP TABLE dbo.TB_DefQuestReward
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefQuestReward', N'TB_DefQuestReward', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefQuestReward ADD CONSTRAINT
		PK_TB_DefQuestReward PRIMARY KEY CLUSTERED 
		(
		NationCodeStr,
		QuestID
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]		
END

-- TB_DefQuest_Wanted 테이블과 통합
IF NOT EXISTS( SELECT * FROM sys.all_columns WHERE OBJECT_ID = OBJECT_ID(N'[dbo].[TB_DefQuestReward]') AND [name] = N'f_Wanted_ClearCount')
BEGIN
	ALTER TABLE dbo.TB_DefQuestReward ADD f_Wanted_ClearCount INT NOT NULL
		CONSTRAINT DF_TB_DefQuestReward_f_Wanted_ClearCount DEFAULT((0))	
END

IF NOT EXISTS( SELECT * FROM sys.all_columns WHERE OBJECT_ID = OBJECT_ID(N'[dbo].[TB_DefQuestReward]') AND [name] = N'f_Wanted_ItemNo')
BEGIN
	ALTER TABLE dbo.TB_DefQuestReward ADD f_Wanted_ItemNo INT NOT NULL
		CONSTRAINT DF_TB_DefQuestReward_f_Wanted_ItemNo DEFAULT((0))	
END

IF NOT EXISTS( SELECT * FROM sys.all_columns WHERE OBJECT_ID = OBJECT_ID(N'[dbo].[TB_DefQuestReward]') AND [name] = N'f_Wanted_ItemCount')
BEGIN
	ALTER TABLE dbo.TB_DefQuestReward ADD f_Wanted_ItemCount INT NOT NULL
		CONSTRAINT DF_TB_DefQuestReward_f_Wanted_ItemCount DEFAULT((0))	
END

IF NOT EXISTS( SELECT * FROM sys.all_columns WHERE OBJECT_ID = OBJECT_ID(N'[dbo].[TB_DefQuestReward]') AND [name] = N'f_Wanted_CoolTime')
BEGIN
	ALTER TABLE dbo.TB_DefQuestReward ADD f_Wanted_CoolTime INT NOT NULL
		CONSTRAINT DF_TB_DefQuestReward_f_Wanted_CoolTime DEFAULT((0))	
END

IF NOT EXISTS( SELECT * FROM sys.all_columns WHERE OBJECT_ID = OBJECT_ID(N'[dbo].[TB_DefQuestReward]') AND [name] = N'f_Dra_Wanted_ItemNo')
BEGIN
	ALTER TABLE dbo.TB_DefQuestReward ADD f_Dra_Wanted_ItemNo INT NOT NULL
		CONSTRAINT DF_TB_DefQuestReward_f_Dra_Wanted_ItemNo DEFAULT((0))	
END

IF NOT EXISTS( SELECT * FROM sys.all_columns WHERE OBJECT_ID = OBJECT_ID(N'[dbo].[TB_DefQuestReward]') AND [name] = N'f_Dra_Wanted_ItemCount')
BEGIN
	ALTER TABLE dbo.TB_DefQuestReward ADD f_Dra_Wanted_ItemCount INT NOT NULL
		CONSTRAINT DF_TB_DefQuestReward_f_Dra_Wanted_ItemCount DEFAULT((0))	
END

 
USE [dr2_def]
go
 
 IF not  EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='TB_DefQuestReward' AND COLUMN_NAME='iRewardPerLevel_Exp')
begin
BEGIN TRY
BEGIN TRAN

create table #temp(

[NationCodeStr] [nvarchar](50) NOT NULL,
	[QuestID] [int] NOT NULL,
	[Memo] [nvarchar](50) NULL,
	[XmlPath] [nvarchar](100) NULL,
	[GroupNo] [int] NOT NULL,
	[QuestType] [int] NOT NULL,
	[RewardExp] [int] NOT NULL,
	[RewardGold] [int] NOT NULL,
	iRewardPerLevel_Exp float not null  default 0,
	 iRewardPerLevel_Money float not null default 0,
 	[LevelMin] [int] NOT NULL,
	[LevelMax] [int] NOT NULL,
	[LimitLevelMax] [int] NOT NULL,
	[TacticsLevel] [int] NOT NULL,
	[TacticsExp] [int] NOT NULL,
	[GuildExp] [int] NOT NULL,
	[QuestDifficult] [int] NOT NULL,
	[f_OrderIndex] [int] NOT NULL,
	[f_IsCanRemoteComplete] [tinyint] NOT NULL,
	[f_IsCanShare] [tinyint] NOT NULL,
	[TitleText] [int] NOT NULL,
	[GroupName] [int] NOT NULL,
	[Class] [bigint] NOT NULL,
	[PreQuestAnd] [nvarchar](50) NOT NULL,
	[PreQuestOr] [nvarchar](50) NOT NULL,
	[NotQuest] [nvarchar](50) NOT NULL,
	[MinParty] [int] NOT NULL,
	[MaxParty] [int] NOT NULL,
	[DraClassLimit] [bigint] NOT NULL,
	[f_Wanted_ClearCount] [int] NOT NULL,
	[f_Wanted_ItemNo] [int] NOT NULL,
	[f_Wanted_ItemCount] [int] NOT NULL,
	[f_Wanted_CoolTime] [int] NOT NULL,
	[f_Dra_Wanted_ItemNo] [int] NOT NULL,
	[f_Dra_Wanted_ItemCount] [int] NOT NULL
 ) 
	insert into #temp(
	NationCodeStr,	QuestID,	Memo,	XmlPath,	GroupNo,	QuestType,	RewardExp,	RewardGold,iRewardPerLevel_Exp, iRewardPerLevel_Money,	LevelMin,	LevelMax,	LimitLevelMax,	TacticsLevel,	TacticsExp,	GuildExp,	QuestDifficult,	f_OrderIndex,	f_IsCanRemoteComplete,	f_IsCanShare,	TitleText,	GroupName,	Class,	PreQuestAnd,	PreQuestOr,	NotQuest,	MinParty,	MaxParty,	DraClassLimit,	f_Wanted_ClearCount,	f_Wanted_ItemNo,	f_Wanted_ItemCount,	f_Wanted_CoolTime,	f_Dra_Wanted_ItemNo,	f_Dra_Wanted_ItemCount
)	select NationCodeStr,	QuestID,	Memo,	XmlPath,	GroupNo,	QuestType,	RewardExp,	RewardGold,	0, 0,LevelMin,	LevelMax,	LimitLevelMax,	TacticsLevel,	TacticsExp,	GuildExp,	QuestDifficult,	f_OrderIndex,	f_IsCanRemoteComplete,	f_IsCanShare,	TitleText,	GroupName,	Class,	PreQuestAnd,	PreQuestOr,	NotQuest,	MinParty,	MaxParty,	DraClassLimit,	f_Wanted_ClearCount,	f_Wanted_ItemNo,	f_Wanted_ItemCount,	f_Wanted_CoolTime,	f_Dra_Wanted_ItemNo,	f_Dra_Wanted_ItemCount
 from [TB_DefQuestReward]

 
IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_NationCodeStr]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_NationCodeStr]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_GroupNo]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_GroupNo]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_IsType]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_IsType]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_LevelMin]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_LevelMin]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_LevelMax]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_LevelMax]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_LimitLevelMax]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_LimitLevelMax]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_TacticsLevel]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_TacticsLevel]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_TacticsExp]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_TacticsExp]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_GuildExp]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_GuildExp]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_QuestDifficult]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_QuestDifficult]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_OrderIndex]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_OrderIndex]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_f_IsCanRemoteComplete]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_f_IsCanRemoteComplete]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_f_IsCanShare]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_f_IsCanShare]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_TitleText]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_TitleText]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_GroupName]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_GroupName]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_Class]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_Class]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_PreQuestAnd]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_PreQuestAnd]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_PreQuestOr]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_PreQuestOr]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_NotQuest]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_NotQuest]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_MinParty]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_MinParty]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_MaxParty]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_MaxParty]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_DraClassLimit]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_DraClassLimit]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_f_Wanted_ClearCount]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_f_Wanted_ClearCount]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_f_Wanted_ItemNo]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_f_Wanted_ItemNo]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_f_Wanted_ItemCount]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_f_Wanted_ItemCount]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_f_Wanted_CoolTime]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_f_Wanted_CoolTime]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_f_Dra_Wanted_ItemNo]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_f_Dra_Wanted_ItemNo]
END

 

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefQuestReward_f_Dra_Wanted_ItemCount]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefQuestReward] DROP CONSTRAINT [DF_TB_DefQuestReward_f_Dra_Wanted_ItemCount]
END

 

USE [dr2_def]
 

/****** Object:  Table [dbo].[TB_DefQuestReward]    Script Date: 05/23/2012 19:42:21 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefQuestReward]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefQuestReward]
 

USE [dr2_def]
 

/****** Object:  Table [dbo].[TB_DefQuestReward]    Script Date: 05/23/2012 19:42:21 ******/
SET ANSI_NULLS ON
 

SET QUOTED_IDENTIFIER ON
 

CREATE TABLE [dbo].[TB_DefQuestReward](
	[NationCodeStr] [nvarchar](50) NOT NULL,
	[QuestID] [int] NOT NULL,
	[Memo] [nvarchar](50) NULL,
	[XmlPath] [nvarchar](100) NULL,
	[GroupNo] [int] NOT NULL,
	[QuestType] [int] NOT NULL,
	[RewardExp] [int] NOT NULL,
	[RewardGold] [int] NOT NULL,
	[iRewardPerLevel_Exp] [int] not null  default 0,
	[iRewardPerLevel_Money] [int] not null default 0,
	[LevelMin] [int] NOT NULL,
	[LevelMax] [int] NOT NULL,
	[LimitLevelMax] [int] NOT NULL,
	[TacticsLevel] [int] NOT NULL,
	[TacticsExp] [int] NOT NULL,
	[GuildExp] [int] NOT NULL,
	[QuestDifficult] [int] NOT NULL,
	[f_OrderIndex] [int] NOT NULL,
	[f_IsCanRemoteComplete] [tinyint] NOT NULL,
	[f_IsCanShare] [tinyint] NOT NULL,
	[TitleText] [int] NOT NULL,
	[GroupName] [int] NOT NULL,
	[Class] [bigint] NOT NULL,
	[PreQuestAnd] [nvarchar](50) NOT NULL,
	[PreQuestOr] [nvarchar](50) NOT NULL,
	[NotQuest] [nvarchar](50) NOT NULL,
	[MinParty] [int] NOT NULL,
	[MaxParty] [int] NOT NULL,
	[DraClassLimit] [bigint] NOT NULL,
	[f_Wanted_ClearCount] [int] NOT NULL,
	[f_Wanted_ItemNo] [int] NOT NULL,
	[f_Wanted_ItemCount] [int] NOT NULL,
	[f_Wanted_CoolTime] [int] NOT NULL,
	[f_Dra_Wanted_ItemNo] [int] NOT NULL,
	[f_Dra_Wanted_ItemCount] [int] NOT NULL,
 CONSTRAINT [PK_TB_DefQuestReward] PRIMARY KEY CLUSTERED 
(
	[NationCodeStr] ASC,
	[QuestID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

 

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Quest reward definition' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefQuestReward'
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_NationCodeStr]  DEFAULT ((0)) FOR [NationCodeStr]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_GroupNo]  DEFAULT ((0)) FOR [GroupNo]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_IsType]  DEFAULT ((0)) FOR [QuestType]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_LevelMin]  DEFAULT ((1)) FOR [LevelMin]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_LevelMax]  DEFAULT ((9999)) FOR [LevelMax]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_LimitLevelMax]  DEFAULT ((0)) FOR [LimitLevelMax]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_TacticsLevel]  DEFAULT ((0)) FOR [TacticsLevel]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_TacticsExp]  DEFAULT ((0)) FOR [TacticsExp]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_GuildExp]  DEFAULT ((0)) FOR [GuildExp]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_QuestDifficult]  DEFAULT ((0)) FOR [QuestDifficult]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_OrderIndex]  DEFAULT ((0)) FOR [f_OrderIndex]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_f_IsCanRemoteComplete]  DEFAULT ((0)) FOR [f_IsCanRemoteComplete]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_f_IsCanShare]  DEFAULT ((1)) FOR [f_IsCanShare]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_TitleText]  DEFAULT ((0)) FOR [TitleText]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_GroupName]  DEFAULT ((0)) FOR [GroupName]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_Class]  DEFAULT ((0)) FOR [Class]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_PreQuestAnd]  DEFAULT ((0)) FOR [PreQuestAnd]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_PreQuestOr]  DEFAULT ((0)) FOR [PreQuestOr]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_NotQuest]  DEFAULT ((0)) FOR [NotQuest]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_MinParty]  DEFAULT ((0)) FOR [MinParty]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_MaxParty]  DEFAULT ((0)) FOR [MaxParty]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_DraClassLimit]  DEFAULT ((0)) FOR [DraClassLimit]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_f_Wanted_ClearCount]  DEFAULT ((0)) FOR [f_Wanted_ClearCount]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_f_Wanted_ItemNo]  DEFAULT ((0)) FOR [f_Wanted_ItemNo]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_f_Wanted_ItemCount]  DEFAULT ((0)) FOR [f_Wanted_ItemCount]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_f_Wanted_CoolTime]  DEFAULT ((0)) FOR [f_Wanted_CoolTime]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_f_Dra_Wanted_ItemNo]  DEFAULT ((0)) FOR [f_Dra_Wanted_ItemNo]
 

ALTER TABLE [dbo].[TB_DefQuestReward] ADD  CONSTRAINT [DF_TB_DefQuestReward_f_Dra_Wanted_ItemCount]  DEFAULT ((0)) FOR [f_Dra_Wanted_ItemCount]
 
 
insert into [TB_DefQuestReward](
	NationCodeStr,	QuestID,	Memo,	XmlPath,	GroupNo,	QuestType,	RewardExp,	RewardGold, iRewardPerLevel_Exp, iRewardPerLevel_Money,	LevelMin,	LevelMax,	LimitLevelMax,	TacticsLevel,	TacticsExp,	GuildExp,	QuestDifficult,	f_OrderIndex,	f_IsCanRemoteComplete,	f_IsCanShare,	TitleText,	GroupName,	Class,	PreQuestAnd,	PreQuestOr,	NotQuest,	MinParty,	MaxParty,	DraClassLimit,	f_Wanted_ClearCount,	f_Wanted_ItemNo,	f_Wanted_ItemCount,	f_Wanted_CoolTime,	f_Dra_Wanted_ItemNo,	f_Dra_Wanted_ItemCount
)	select NationCodeStr,	QuestID,	Memo,	XmlPath,	GroupNo,	QuestType,	RewardExp,	RewardGold,	iRewardPerLevel_Exp, iRewardPerLevel_Money,LevelMin,	LevelMax,	LimitLevelMax,	TacticsLevel,	TacticsExp,	GuildExp,	QuestDifficult,	f_OrderIndex,	f_IsCanRemoteComplete,	f_IsCanShare,	TitleText,	GroupName,	Class,	PreQuestAnd,	PreQuestOr,	NotQuest,	MinParty,	MaxParty,	DraClassLimit,	f_Wanted_ClearCount,	f_Wanted_ItemNo,	f_Wanted_ItemCount,	f_Wanted_CoolTime,	f_Dra_Wanted_ItemNo,	f_Dra_Wanted_ItemCount
 from   #temp
 drop table  #temp 
 
COMMIT TRAN
-- select * from [TB_DefQuestReward]
END TRY
BEGIN CATCH
ROLLBACK TRAN
END CATCH
END


IF NOT EXISTS( SELECT * FROM sys.all_columns WHERE OBJECT_ID = OBJECT_ID(N'[dbo].[TB_DefQuestReward]') AND [name] = N'f_IsCanRemoteAccept')
BEGIN
	ALTER TABLE dbo.TB_DefQuestReward ADD f_IsCanRemoteAccept tinyint NOT NULL
		CONSTRAINT DF_TB_DefQuestReward_f_IsCanRemoteAccept DEFAULT((0))	
END
