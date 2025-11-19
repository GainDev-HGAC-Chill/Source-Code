USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefence7_Wave]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefDefence7_Wave](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[Mission_No] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_MissionNo] DEFAULT ((0)),
		[Mission_Type] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Mission_Type] DEFAULT ((0)),
		[Party_Number] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Party_Number] DEFAULT ((0)),
		[Stage_No] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Stage_No] DEFAULT ((0)),
		[Wave_No] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Wave_No] DEFAULT ((0)),
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,		
		[Wave_Delay] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Wave_Delay] DEFAULT ((0)),
		[Give_StrategicPoint] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Give_StrategicPoint] DEFAULT ((0)),
		[Monster01] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Monster01] DEFAULT ((0)),
		[Monster02] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Monster02] DEFAULT ((0)),
		[Monster03] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Monster03] DEFAULT ((0)),
		[Monster04] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Monster04] DEFAULT ((0)),
		[Monster05] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Monster05] DEFAULT ((0)),
		[Monster06] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Monster06] DEFAULT ((0)),
		[Monster07] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Monster07] DEFAULT ((0)),
		[Monster08] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Monster08] DEFAULT ((0)),
		[Monster09] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Monster09] DEFAULT ((0)),
		[Monster10] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_Monster10] DEFAULT ((0)),
		[TunningNo] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_TunningNo] DEFAULT ((0)),
		[AddMoveSpeedPercent] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_AddMoveSpeedPercent] DEFAULT ((0)),
		[AddExpPercent] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_AddExpPercent] DEFAULT ((0)),
		[AddHPPercent] [int] NOT NULL CONSTRAINT [DF_TB_DefDefence7_Wave_AddHPPercent] DEFAULT ((0))
	CONSTRAINT [PK_TB_DefDefence7_Wave] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefDefence7_Wave') and [name] = N'DamageDecRate')
BEGIN
	ALTER TABLE dbo.TB_DefDefence7_Wave ADD [DamageDecRate] int NOT NULL CONSTRAINT DF_TB_DefDefence7_Wave_DamageDecRate DEFAULT(0)
END

GO

