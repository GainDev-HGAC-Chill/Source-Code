USE [DR2_Local]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEvent_BossBattle]') )
BEGIN
	CREATE TABLE [dbo].[TB_DefEvent_BossBattle](
		[IDX] [int] IDENTITY(1,1) NOT NULL,
		[Memo] [nvarchar](200) NULL,
		[BossBattleEventNo] [int] NOT NULL,
		[MapNo] [int] NOT NULL,
		[LimitTime] [int] NOT NULL,
		[MonsterRegenType] [smallint] NOT NULL,
		[BossMonsterGroup] [int] NOT NULL,
		[HarvestLumberEventItemNo] [int] NOT NULL,
		[HarvestGemEventItemNo] [int] NOT NULL,
		[HarvestHerbEventItemNo] [int] NOT NULL,
		[HarvestFishEventItemNo] [int] NOT NULL,
		[HarvestExpMin] [int] NOT NULL
	 CONSTRAINT [PK_TB_DefEvent_BossBattle] PRIMARY KEY CLUSTERED 
	(
		[IDX] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEvent_BossBattle]') )
BEGIN
	ALTER TABLE [dbo].[TB_DefEvent_BossBattle]
		DROP CONSTRAINT [PK_TB_DefEvent_BossBattle]
	
	DROP TABLE [dbo].[TB_DefEvent_BossBattle]
END

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEvent_BossBattle]') )
BEGIN
	CREATE TABLE [dbo].[TB_DefEvent_BossBattle](
		[IDX] [int] IDENTITY(1,1) NOT NULL,
		[Event_No] [int] DEFAULT(0) NOT NULL,
		[Memo] [nvarchar](200) NULL,
		[Start_Effect] [int] DEFAULT(0) NOT NULL,
		[Limit_Time] [int] DEFAULT(0) NOT NULL,
		[Monster_Regen_Type] [tinyint] DEFAULT(0) NOT NULL,
		[MonsterGroup_No] [int] DEFAULT(0) NOT NULL,
		[Harvest_Lumber_EventItemNo] [int] DEFAULT(0) NOT NULL,
		[Harvest_Gem_EventItemNo] [int] DEFAULT(0) NOT NULL,
		[Harvest_Herb_EventItemNo] [int] DEFAULT(0) NOT NULL,
		[Harvest_Fish_EventItemNo] [int] DEFAULT(0) NOT NULL,
		[Harvest_Exp_Min] [int] DEFAULT(0) NOT NULL
	 CONSTRAINT [PK_TB_DefEvent_BossBattle] PRIMARY KEY CLUSTERED 
	(
		[IDX] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END