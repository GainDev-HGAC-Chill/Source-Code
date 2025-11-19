USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEffect_Player]') AND [name] = N'NationCodeStr')
BEGIN

	CREATE TABLE [dbo].[Tmp_TB_DefEffect_Player](
		[NationCodeStr] [nvarchar](50) NOT NULL,
		[EffectID] [int] NOT NULL,
		[Name] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_Name2] DEFAULT ((0)),
		[ActionName] [nvarchar](100) NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_ActionName2] DEFAULT ((0)),
		[Memo] [nvarchar](100) NULL,
		[Type] [smallint] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_Type2] DEFAULT ((0)),
		[Interval] [smallint] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_Interval2] DEFAULT ((0)),
		[DurationTime] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_DurationTime2] DEFAULT ((0)),
		[Toggle] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_Toggle2] DEFAULT ((0)),
		[Abil01] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_Abil01_2] DEFAULT ((0)),
		[Abil02] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_Abil02_2]  DEFAULT ((0)),
		[Abil03] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_Abil03_2]  DEFAULT ((0)),
		[Abil04] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_Abil04_2]  DEFAULT ((0)),
		[Abil05] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_Abil05_2]  DEFAULT ((0)),
		[Abil06] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_Abil06_2]  DEFAULT ((0)),
		[Abil07] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_Abil07_2]  DEFAULT ((0)),
		[Abil08] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_Abil08_2]  DEFAULT ((0)),
		[Abil09] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_Abil09_2]  DEFAULT ((0)),
		[Abil10] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Player_Abil10_2]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_DefEffect_Player2] PRIMARY KEY CLUSTERED 
	(
		[EffectID] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
	
	IF EXISTS (SELECT * FROM dbo.TB_DefEffect_Player)
	EXEC('INSERT INTO dbo.Tmp_TB_DefEffect_Player (NationCodeStr, EffectID, Name, ActionName, Memo, Type, Interval, DurationTime, Toggle, Abil01, Abil02, Abil03,
												   Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10)
		  SELECT 0, EffectID, Name, ActionName, Memo, Type, Interval, DurationTime, Toggle, Abil01, Abil02, Abil03,
												   Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10
		  FROM dbo.TB_DefEffect_Player WITH (HOLDLOCK TABLOCKX)')
		  
	DROP TABLE TB_DefEffect_Player
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefEffect_Player', 'TB_DefEffect_Player', 'OBJECT'

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Buf/Debuf Definition(Player)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefEffect_Player'
END
GO

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEffect_Player]') AND [name] = N'NationCodeStr')
BEGIN
	ALTER TABLE dbo.TB_DefEffect_Player
	DROP CONSTRAINT PK_TB_DefEffect_Player2
	ALTER TABLE dbo.TB_DefEffect_Player ADD CONSTRAINT
		PK_TB_DefEffect_Player2 PRIMARY KEY CLUSTERED 
		(
		NationCodeStr,
		EffectID
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
GO