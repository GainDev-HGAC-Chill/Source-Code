USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefenceWave]') AND type in (N'U'))
BEGIN

	CREATE TABLE [dbo].[TB_DefDefenceWave](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[Wave_GroupNo] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_Wave_GroupNo] DEFAULT ((0)),
		[Wave_No] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_Wave_No] DEFAULT ((0)),
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
		[Wave_Delay] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_Wave_Delay] DEFAULT ((0)),
		[Monster01] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_Monster01] DEFAULT ((0)),
		[Monster02] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_Monster02] DEFAULT ((0)),
		[Monster03] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_Monster03] DEFAULT ((0)),
		[Monster04] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_Monster04] DEFAULT ((0)),
		[Monster05] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_Monster05] DEFAULT ((0)),
		[Monster06] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_Monster06] DEFAULT ((0)),
		[Monster07] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_Monster07] DEFAULT ((0)),
		[Monster08] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_Monster08] DEFAULT ((0)),
		[Monster09] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_Monster09] DEFAULT ((0)),
		[Monster10] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_Monster10] DEFAULT ((0))
	CONSTRAINT [PK_TB_DefDefenceWave] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefDefenceWave') AND [name] = N'AddMoveSpeedPercent')
BEGIN
	ALTER TABLE [dbo].[TB_DefDefenceWave] ADD
		[AddMoveSpeedPercent] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_AddMoveSpeedPercent]  DEFAULT ((0))
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefDefenceWave') AND [name] = N'TunningNo')
BEGIN
	ALTER TABLE [dbo].[TB_DefDefenceWave] ADD
		[TunningNo] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_TunningNo]  DEFAULT ((0))	
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefDefenceWave') AND [name] = N'AddExpPercent')
BEGIN
	ALTER TABLE [dbo].[TB_DefDefenceWave] ADD
		[AddExpPercent] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_AddExpPercent]  DEFAULT ((0))	
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefDefenceWave') AND [name] = N'AddHPPercent')
BEGIN
	ALTER TABLE [dbo].[TB_DefDefenceWave] ADD
		[AddHPPercent] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_AddHPPercent]  DEFAULT ((0))	
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefDefenceWave') AND [name] = N'AddDamagePercent')
BEGIN
	ALTER TABLE [dbo].[TB_DefDefenceWave] ADD
		[AddDamagePercent] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceWave_AddDamagePercent]  DEFAULT ((0))	
END

GO

