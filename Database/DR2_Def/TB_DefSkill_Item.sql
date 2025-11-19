USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefSkill_Item]'))
BEGIN

	CREATE TABLE [dbo].[TB_DefSkill_Item](
		[SkillNo] [int] NOT NULL,
		[Level] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_Level]  DEFAULT ((0)),
		[NameNo] [int] NOT NULL,
		[RscNameNo] [int] NOT NULL,
		[ActionName] [nvarchar](30) COLLATE Korean_Wansung_CI_AS NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_ActionName]  DEFAULT (' '),
		[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
		[Type] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_Type]  DEFAULT ((0)),
		[ClassLimit] [bigint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_ClassLimit]  DEFAULT ((0)),
		[LevelLimit] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_LevelLimit]  DEFAULT ((0)),
		[WeaponLimit] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_WeaponLimit]  DEFAULT ((0)),
		[StateLimit] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_StateLimit]  DEFAULT ((0)),
		[ParentSkill] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_ParentSkill]  DEFAULT ((0)),
		[Target] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_Target]  DEFAULT ((0)),
		[Range] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_Range]  DEFAULT ((0)),
		[CastTime] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_CastTime]  DEFAULT ((0)),
		[CoolTime] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_CoolTime]  DEFAULT ((0)),
		[AnimationTime] [int] NULL,
		[MP] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_MP]  DEFAULT ((0)),
		[HP] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_HP]  DEFAULT ((0)),
		[EffectID] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_EffectID]  DEFAULT ((0)),
		[Abil01] [int] NOT NULL,
		[Abil02] [int] NOT NULL,
		[Abil03] [int] NOT NULL,
		[Abil04] [int] NOT NULL,
		[Abil05] [int] NOT NULL,
		[Abil06] [int] NOT NULL,
		[Abil07] [int] NOT NULL,
		[Abil08] [int] NOT NULL,
		[Abil09] [int] NOT NULL,
		[Abil10] [int] NOT NULL,
		[CmdStringNo] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_CmdStringNo]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_DefSkill_Item] PRIMARY KEY CLUSTERED 
	(
		[SkillNo] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]

	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Skill definition (Item)' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'TB_DefSkill_Item'
END
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefSkill_Item]') AND [name] = N'NationCodeStr')
BEGIN

	CREATE TABLE [dbo].[Tmp_TB_DefSkill_Item](
		[NationCodeStr] [nvarchar](50) NOT NULL,
		[SkillNo] [int] NOT NULL,
		[Level] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_Level2]  DEFAULT ((0)),
		[NameNo] [int] NOT NULL,
		[RscNameNo] [int] NOT NULL,
		[ActionName] [nvarchar](30) COLLATE Korean_Wansung_CI_AS NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_ActionName2]  DEFAULT (' '),
		[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
		[Type] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_Type2]  DEFAULT ((0)),
		[ClassLimit] [bigint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_ClassLimit2]  DEFAULT ((0)),
		[LevelLimit] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_LevelLimit2]  DEFAULT ((0)),
		[WeaponLimit] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_WeaponLimit2]  DEFAULT ((0)),
		[StateLimit] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_StateLimit2]  DEFAULT ((0)),
		[ParentSkill] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_ParentSkill2]  DEFAULT ((0)),
		[Target] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_Target2]  DEFAULT ((0)),
		[Range] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_Range2]  DEFAULT ((0)),
		[CastTime] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_CastTime2]  DEFAULT ((0)),
		[CoolTime] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_CoolTime2]  DEFAULT ((0)),
		[AnimationTime] [int] NULL,
		[MP] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_MP2]  DEFAULT ((0)),
		[HP] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_HP2]  DEFAULT ((0)),
		[EffectID] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_EffectID2]  DEFAULT ((0)),
		[Abil01] [int] NOT NULL,
		[Abil02] [int] NOT NULL,
		[Abil03] [int] NOT NULL,
		[Abil04] [int] NOT NULL,
		[Abil05] [int] NOT NULL,
		[Abil06] [int] NOT NULL,
		[Abil07] [int] NOT NULL,
		[Abil08] [int] NOT NULL,
		[Abil09] [int] NOT NULL,
		[Abil10] [int] NOT NULL,
		[CmdStringNo] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Item_CmdStringNo2]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_DefSkill_Item2] PRIMARY KEY CLUSTERED 
	(
		[SkillNo] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]

	IF EXISTS (SELECT * FROM dbo.TB_DefSkill_Item)
	EXEC('INSERT INTO dbo.Tmp_TB_DefSkill_Item (NationCodeStr, SkillNo, Level, NameNo, RscNameNo, ActionName, Memo, Type, ClassLimit, LevelLimit, WeaponLimit, StateLimit, ParentSkill,
												Target, Range, CastTime, CoolTime, AnimationTime, MP, HP, EffectID, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10, CmdStringNo)
		  SELECT 0, SkillNo, Level, NameNo, RscNameNo, ActionName, Memo, Type, ClassLimit, LevelLimit, WeaponLimit, StateLimit, ParentSkill,
												Target, Range, CastTime, CoolTime, AnimationTime, MP, HP, EffectID, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10, CmdStringNo
		  FROM dbo.TB_DefSkill_Item WITH (HOLDLOCK TABLOCKX)')
		
	DROP TABLE TB_DefSkill_Item
		
	EXECUTE sp_rename N'dbo.Tmp_TB_DefSkill_Item', 'TB_DefSkill_Item', 'OBJECT'

	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Skill definition (Item)' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'TB_DefSkill_Item'
END



USE [DR2_Def]
GO

/****** Object:  Index [PK_TB_DefSkill_Item2]    Script Date: 01/09/2013 12:01:38 ******/
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefSkill_Item]') AND name = N'PK_TB_DefSkill_Item2')
ALTER TABLE [dbo].[TB_DefSkill_Item] DROP CONSTRAINT [PK_TB_DefSkill_Item2]
GO

USE [DR2_Def]
GO

/****** Object:  Index [PK_TB_DefSkill_Item2]    Script Date: 01/09/2013 12:01:38 ******/
ALTER TABLE [dbo].[TB_DefSkill_Item] ADD  CONSTRAINT [PK_TB_DefSkill_Item2] PRIMARY KEY CLUSTERED 
(
	[SkillNo] ASC, [NationCodeStr] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
GO


