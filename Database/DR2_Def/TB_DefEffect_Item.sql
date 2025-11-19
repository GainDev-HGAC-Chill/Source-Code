USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEffect_Item]') AND [type] IN (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefEffect_Item](
		[EffectID] [int] NOT NULL,
		[Name] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Name] DEFAULT ((0)),
		[ActionName] [nvarchar](100) NOT NULL,
		[Memo] [nvarchar](100) NULL,
		[Type] [smallint] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Type]  DEFAULT ((0)),
		[Interval] [smallint] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Interval]  DEFAULT ((0)),
		[DurationTime] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_DurationTime]  DEFAULT ((0)),
		[Toggle] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Toggle]  DEFAULT ((0)),
		[Abil01] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil01]  DEFAULT ((0)),
		[Abil02] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil02]  DEFAULT ((0)),
		[Abil03] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil03]  DEFAULT ((0)),
		[Abil04] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil04]  DEFAULT ((0)),
		[Abil05] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil05]  DEFAULT ((0)),
		[Abil06] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil06]  DEFAULT ((0)),
		[Abil07] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil07]  DEFAULT ((0)),
		[Abil08] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil08]  DEFAULT ((0)),
		[Abil09] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil09]  DEFAULT ((0)),
		[Abil10] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil10]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_DefEffect_Item] PRIMARY KEY CLUSTERED 
	(
		[EffectID] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Buf/Debuf Definition(Item)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefEffect_Item'

	ALTER TABLE [dbo].[TB_DefEffect_Item] ADD  CONSTRAINT [DF_TB_DefEffect_Item_ActionName]  DEFAULT (' ') FOR [ActionName]

END
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEffect_Item]') AND [name] = N'NationCodeStr')
BEGIN

	CREATE TABLE dbo.Tmp_TB_DefEffect_Item(
	[NationCodeStr] [nvarchar](50) NOT NULL,
	[EffectID] [int] NOT NULL,
	[Name] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Name2] DEFAULT ((0)),
	[ActionName] [nvarchar](100) NOT NULL,
	[Memo] [nvarchar](100) NULL,
	[Type] [smallint] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Type2]  DEFAULT ((0)),
	[Interval] [smallint] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Interval2]  DEFAULT ((0)),
	[DurationTime] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_DurationTime2]  DEFAULT ((0)),
	[Toggle] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Toggle2]  DEFAULT ((0)),
	[Abil01] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil01_2]  DEFAULT ((0)),
	[Abil02] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil02_2]  DEFAULT ((0)),
	[Abil03] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil03_2]  DEFAULT ((0)),
	[Abil04] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil04_2]  DEFAULT ((0)),
	[Abil05] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil05_2]  DEFAULT ((0)),
	[Abil06] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil06_2]  DEFAULT ((0)),
	[Abil07] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil07_2]  DEFAULT ((0)),
	[Abil08] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil08_2]  DEFAULT ((0)),
	[Abil09] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil09_2]  DEFAULT ((0)),
	[Abil10] [int] NOT NULL CONSTRAINT [DF_TB_DefEffect_Item_Abil10_2]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_DefEffect_Item2] PRIMARY KEY CLUSTERED 
	(
		[EffectID] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]

	IF EXISTS (SELECT * FROM dbo.TB_DefEffect_Item)
	EXEC('INSERT INTO dbo.Tmp_TB_DefEffect_Item (NationCodeStr, EffectID, Name, ActionName, Memo, Type, Interval, DurationTime, Toggle, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10)
		  SELECT 0, EffectID, Name, ActionName, Memo, Type, Interval, DurationTime, Toggle, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10
		  FROM dbo.TB_DefEffect_Item WITH (HOLDLOCK TABLOCKX)')
		
	DROP TABLE TB_DefEffect_Item
		
	EXECUTE sp_rename N'dbo.Tmp_TB_DefEffect_Item', 'TB_DefEffect_Item', 'OBJECT'
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Buf/Debuf Definition(Item)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefEffect_Item'

	ALTER TABLE [dbo].[TB_DefEffect_Item] ADD  CONSTRAINT [DF_TB_DefEffect_Item_ActionName]  DEFAULT (' ') FOR [ActionName]

END
GO


USE [DR2_Def]
GO

/****** Object:  Index [PK_TB_DefEffect_Item2]    Script Date: 01/09/2013 11:57:05 ******/
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEffect_Item]') AND name = N'PK_TB_DefEffect_Item2')
ALTER TABLE [dbo].[TB_DefEffect_Item] DROP CONSTRAINT [PK_TB_DefEffect_Item2]
GO

USE [DR2_Def]
GO

/****** Object:  Index [PK_TB_DefEffect_Item2]    Script Date: 01/09/2013 11:57:05 ******/
ALTER TABLE [dbo].[TB_DefEffect_Item] ADD  CONSTRAINT [PK_TB_DefEffect_Item2] PRIMARY KEY CLUSTERED 
(
	[NationCodeStr] ASC,
	[EffectID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
GO


