USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Guardian]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefDefence7_Guardian](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[Guardian_No] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Guardian_No] DEFAULT ((0)),
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,		
		[Monster_No] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Monster_No] DEFAULT ((0)),
		[Guardian_Abil01] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Guardian_Abil01] DEFAULT ((0)),
		[Guardian_Abil02] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Guardian_Abil02] DEFAULT ((0)),
		[Guardian_TunningNo] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Guardian_TunningNo] DEFAULT ((0)),
		[Need_StrategicPoint] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Need_StrategicPoint] DEFAULT ((0)),
		[Upgrade_Type] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Upgrade_Type] DEFAULT ((0)),
		[Upgrade_Step] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Upgrade_Step] DEFAULT ((0)),
		[Upgrade_01] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Upgrade_01] DEFAULT ((0)),
		[Upgrade_02] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Upgrade_02] DEFAULT ((0)),
		[Upgrade_03] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Upgrade_03] DEFAULT ((0)),
		[Upgrade_04] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Upgrade_04] DEFAULT ((0)),
		[Upgrade_05] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Upgrade_05] DEFAULT ((0))
	CONSTRAINT [PK_TB_DefDefence7_Guardian] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Guardian]') AND [name] = N'Upgrade_03')
BEGIN
	ALTER TABLE dbo.TB_DefDefence7_Guardian
		DROP CONSTRAINT DF_TB_DefDefence7_Guardian_Upgrade_03
	ALTER TABLE dbo.TB_DefDefence7_Guardian
		DROP CONSTRAINT DF_TB_DefDefence7_Guardian_Upgrade_04
	ALTER TABLE dbo.TB_DefDefence7_Guardian
		DROP CONSTRAINT DF_TB_DefDefence7_Guardian_Upgrade_05
	ALTER TABLE dbo.TB_DefDefence7_Guardian
		DROP COLUMN Upgrade_03, Upgrade_04, Upgrade_05
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Guardian]') AND [name] = N'Skill01_No')
BEGIN
	ALTER TABLE dbo.TB_DefDefence7_Guardian ADD
		Skill01_No int NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Skill01_No] DEFAULT ((0)),
		Skill01_StrategicPoint int NOT NULL CONSTRAINT [DF_TB_DefDefence7_Skill01_StrategicPoint] DEFAULT ((0)),
		Skill02_No int NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Skill02_No] DEFAULT ((0)),
		Skill02_StrategicPoint int NOT NULL CONSTRAINT [DF_TB_DefDefence7_Skill02_StrategicPoint] DEFAULT ((0)),
		Sell_StrategicPoint int NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_Sell_StrategicPoint] DEFAULT ((0))
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Guardian]') AND [name] = N'GuardianType')
BEGIN
	ALTER TABLE dbo.TB_DefDefence7_Guardian ADD
		GuardianType int NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_GuardianType] DEFAULT ((0))
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Guardian]') AND [name] = N'AutoSell_StrategicPoint')
BEGIN
	ALTER TABLE dbo.TB_DefDefence7_Guardian ADD
		AutoSell_StrategicPoint int NOT NULL CONSTRAINT [DF_TB_DefDefence7_Guardian_AutoSell_StrategicPoint] DEFAULT ((0))
END

GO

