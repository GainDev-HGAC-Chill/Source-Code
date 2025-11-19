USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefSkill_Pet]'))
BEGIN

	CREATE TABLE [dbo].[TB_DefSkill_Pet](
		[SkillNo] [int] NOT NULL,
		[Level] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_Level]  DEFAULT ((0)),
		[NameNo] [int] NOT NULL,
		[RscNameNo] [int] NOT NULL,
		[ActionName] [nvarchar](30) COLLATE Korean_Wansung_CI_AS NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_ActionName]  DEFAULT (' '),
		[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
		[Type] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_Type]  DEFAULT ((0)),
		[ClassLimit] [bigint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_ClassLimit]  DEFAULT ((0)),
		[LevelLimit] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_LevelLimit]  DEFAULT ((0)),
		[WeaponLimit] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_WeaponLimit]  DEFAULT ((0)),
		[StateLimit] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_StateLimit]  DEFAULT ((0)),
		[ParentSkill] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_ParentSkill]  DEFAULT ((0)),
		[Target] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_Target]  DEFAULT ((0)),
		[Range] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_Range]  DEFAULT ((0)),
		[CastTime] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_CastTime]  DEFAULT ((0)),
		[CoolTime] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_CoolTime]  DEFAULT ((0)),
		[AnimationTime] [int] NULL,
		[MP] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_MP]  DEFAULT ((0)),
		[HP] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_HP]  DEFAULT ((0)),
		[EffectID] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_EffectID]  DEFAULT ((0)),
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
	 CONSTRAINT [PK_TB_DefSkill_Pet] PRIMARY KEY CLUSTERED 
	(
		[SkillNo] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]

	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Skill definition (Pet)' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'TB_DefSkill_Pet'
	
END
ELSE
BEGIN

	IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefSkill_Pet_Target]') AND type = 'D')
	BEGIN
		ALTER TABLE [dbo].[TB_DefSkill_Pet] DROP CONSTRAINT [DF_TB_DefSkill_Pet_Target]
	END

	ALTER TABLE [dbo].[TB_DefSkill_Pet]
	ALTER COLUMN [Target] [int] NOT NULL

	ALTER TABLE [dbo].[TB_DefSkill_Pet] ADD  CONSTRAINT [DF_TB_DefSkill_Pet_Target] DEFAULT ((0)) FOR [Target]
	
END
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE NAME = N'[DF_TB_DefSkill_Pet_CmdStringNo]')
BEGIN
	ALTER TABLE [dbo].[TB_DefSkill_Pet] ADD [CmdStringNo] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Pet_CmdStringNo]  DEFAULT ((0))
END
GO
