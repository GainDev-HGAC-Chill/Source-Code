USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefSkill_Player]    Script Date: 03/27/2009 20:01:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefSkill_Player]'))
BEGIN

	CREATE TABLE [dbo].[TB_DefSkill_Player](
		[SkillNo] [int] NOT NULL,
		[Level] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefSkill2_Level]  DEFAULT ((0)),
		[NameNo] [int] NOT NULL,
		[RscNameNo] [int] NOT NULL,
		[ActionName] [nvarchar](30) COLLATE Korean_Wansung_CI_AS NOT NULL CONSTRAINT [DF_TB_DefSkill2_ActionName]  DEFAULT (' '),
		[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
		[Type] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefSkill2_Type]  DEFAULT ((0)),
		[ClassLimit] [bigint] NOT NULL CONSTRAINT [DF_TB_DefSkill2_ClassLimit]  DEFAULT ((0)),
		[LevelLimit] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill2_LevelLimit]  DEFAULT ((0)),
		[WeaponLimit] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill2_WeaponLimit]  DEFAULT ((0)),
		[StateLimit] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill2_StateLimit]  DEFAULT ((0)),
		[ParentSkill] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill2_ParentSkill]  DEFAULT ((0)),
		[Target] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill2_Target]  DEFAULT ((0)),
		[Range] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill2_Range]  DEFAULT ((0)),
		[CastTime] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill2_CastTime]  DEFAULT ((0)),
		[CoolTime] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill2_CoolTime]  DEFAULT ((0)),
		[AnimationTime] [int] NULL,
		[MP] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill2_MP]  DEFAULT ((0)),
		[HP] [smallint] NOT NULL CONSTRAINT [DF_TB_DefSkill2_HP]  DEFAULT ((0)),
		[EffectID] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill2_EffectID]  DEFAULT ((0)),
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
	 CONSTRAINT [PK_TB_DefSkill_Player] PRIMARY KEY CLUSTERED 
	(
		[SkillNo] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]

	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Skill definition (Player)' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'TB_DefSkill_Player'
	
END
ELSE
BEGIN

	IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefSkill2_Target]') AND type = 'D')
	BEGIN
		ALTER TABLE [dbo].[TB_DefSkill_Player] DROP CONSTRAINT [DF_TB_DefSkill2_Target]
	END
	
	IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefSkill_Target]') AND type = 'D')
	BEGIN
		ALTER TABLE [dbo].[TB_DefSkill_Player] DROP CONSTRAINT [DF_TB_DefSkill_Target]
	END

	ALTER TABLE [dbo].[TB_DefSkill_Player]
	ALTER COLUMN [Target] [int] NOT NULL

	ALTER TABLE [dbo].[TB_DefSkill_Player] ADD  CONSTRAINT [DF_TB_DefSkill_Target] DEFAULT ((0)) FOR [Target]
	
END
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE parent_object_id = OBJECT_ID(N'[dbo].[TB_DefSkill_Player]') and object_id = OBJECT_ID(N'[DF_TB_DefSkill_Player_CmdStringNo]'))
BEGIN
	ALTER TABLE [dbo].[TB_DefSkill_Player] ADD [CmdStringNo] [int] NOT NULL CONSTRAINT [DF_TB_DefSkill_Player_CmdStringNo]  DEFAULT ((0))
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.[TB_DefSkill_Player]') and name = N'f_ActionCategory')
BEGIN
	ALTER TABLE [dbo].[TB_DefSkill_Player] ADD f_ActionCategory INT NOT NULL CONSTRAINT DF_TB_DefSkill_Player_f_ActionCategory DEFAULT 0
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.[TB_DefSkill_Player]') and name = N'DraClassLimit')
BEGIN
	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill2_Level

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill2_ActionName

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill2_Type

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill2_ClassLimit

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill2_LevelLimit

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill2_WeaponLimit

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill2_StateLimit

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill2_ParentSkill

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill_Target

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill2_Range

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill2_CastTime

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill2_CoolTime

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill2_MP

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill2_HP

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill2_EffectID

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill_Player_CmdStringNo

	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT DF_TB_DefSkill_Player_f_ActionCategory
						
	CREATE TABLE dbo.Tmp_TB_DefSkill_Player
		(
		SkillNo int NOT NULL,
		[Level] tinyint NOT NULL,
		NameNo int NOT NULL,
		RscNameNo int NOT NULL,
		ActionName nvarchar(30) NOT NULL,
		Memo nvarchar(100) NULL,
		Type tinyint NOT NULL,
		ClassLimit bigint NOT NULL,
		DraClassLimit bigint NOT NULL,
		LevelLimit smallint NOT NULL,
		WeaponLimit int NOT NULL,
		StateLimit int NOT NULL,
		ParentSkill int NOT NULL,
		Target int NOT NULL,
		Range smallint NOT NULL,
		CastTime int NOT NULL,
		CoolTime int NOT NULL,
		AnimationTime int NULL,
		MP smallint NOT NULL,
		HP smallint NOT NULL,
		EffectID int NOT NULL,
		Abil01 int NOT NULL,
		Abil02 int NOT NULL,
		Abil03 int NOT NULL,
		Abil04 int NOT NULL,
		Abil05 int NOT NULL,
		Abil06 int NOT NULL,
		Abil07 int NOT NULL,
		Abil08 int NOT NULL,
		Abil09 int NOT NULL,
		Abil10 int NOT NULL,
		CmdStringNo int NOT NULL,
		f_ActionCategory int NOT NULL
		)  ON [PRIMARY]

	DECLARE @v sql_variant 
	SET @v = N'Skill definition (Player)'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefSkill_Player', NULL, NULL

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_Level DEFAULT ((0)) FOR [Level]

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_ActionName DEFAULT (' ') FOR ActionName

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_Type DEFAULT ((0)) FOR Type

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_ClassLimit DEFAULT ((0)) FOR ClassLimit

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill_Player_DraClassLimit DEFAULT 0 FOR DraClassLimit

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_LevelLimit DEFAULT ((0)) FOR LevelLimit

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_WeaponLimit DEFAULT ((0)) FOR WeaponLimit

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_StateLimit DEFAULT ((0)) FOR StateLimit

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_ParentSkill DEFAULT ((0)) FOR ParentSkill

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill_Target DEFAULT ((0)) FOR Target

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_Range DEFAULT ((0)) FOR Range

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_CastTime DEFAULT ((0)) FOR CastTime

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_CoolTime DEFAULT ((0)) FOR CoolTime

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_MP DEFAULT ((0)) FOR MP

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_HP DEFAULT ((0)) FOR HP

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_EffectID DEFAULT ((0)) FOR EffectID

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill_Player_CmdStringNo DEFAULT ((0)) FOR CmdStringNo

	ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill_Player_f_ActionCategory DEFAULT ((0)) FOR f_ActionCategory

	IF EXISTS(SELECT * FROM dbo.TB_DefSkill_Player)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefSkill_Player (SkillNo, [Level], NameNo, RscNameNo, ActionName, Memo, Type, ClassLimit, LevelLimit, WeaponLimit, StateLimit, ParentSkill, Target, Range, CastTime, CoolTime, AnimationTime, MP, HP, EffectID, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10, CmdStringNo, f_ActionCategory)
			SELECT SkillNo, [Level], NameNo, RscNameNo, ActionName, Memo, Type, ClassLimit, LevelLimit, WeaponLimit, StateLimit, ParentSkill, Target, Range, CastTime, CoolTime, AnimationTime, MP, HP, EffectID, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10, CmdStringNo, f_ActionCategory FROM dbo.TB_DefSkill_Player WITH (HOLDLOCK TABLOCKX)')

	DROP TABLE dbo.TB_DefSkill_Player

	EXECUTE sp_rename N'dbo.Tmp_TB_DefSkill_Player', N'TB_DefSkill_Player', 'OBJECT' 

	ALTER TABLE dbo.TB_DefSkill_Player ADD CONSTRAINT
		PK_TB_DefSkill_Player PRIMARY KEY CLUSTERED 
		(
		SkillNo
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]


	CREATE NONCLUSTERED INDEX IX_NC_TB_DefSkill_Player_ClassLimit ON dbo.TB_DefSkill_Player
		(
		ClassLimit
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.[TB_DefSkill_Player]') and name = N'NationCodeStr')
BEGIN
	CREATE TABLE dbo.Tmp_TB_DefSkill_Player(
		NationCodeStr nvarchar(50) NOT NULL,
		SkillNo int NOT NULL,
		Level tinyint NOT NULL,
		NameNo int NOT NULL,
		RscNameNo int NOT NULL,
		ActionName nvarchar(30) NOT NULL,
		Memo nvarchar(100) NULL,
		Type tinyint NOT NULL,
		ClassLimit bigint NOT NULL,
		DraClassLimit bigint NOT NULL,
		LevelLimit smallint NOT NULL,
		WeaponLimit int NOT NULL,
		StateLimit int NOT NULL,
		ParentSkill int NOT NULL,
		Target int NOT NULL,
		Range smallint NOT NULL,
		CastTime int NOT NULL,
		CoolTime int NOT NULL,
		AnimationTime int NULL,
		MP smallint NOT NULL,
		HP smallint NOT NULL,
		EffectID int NOT NULL,
		Abil01 int NOT NULL,
		Abil02 int NOT NULL,
		Abil03 int NOT NULL,
		Abil04 int NOT NULL,
		Abil05 int NOT NULL,
		Abil06 int NOT NULL,
		Abil07 int NOT NULL,
		Abil08 int NOT NULL,
		Abil09 int NOT NULL,
		Abil10 int NOT NULL,
		CmdStringNo int NOT NULL,
		f_ActionCategory int NOT NULL
		CONSTRAINT PK_TB_DefSkill_Player2 PRIMARY KEY CLUSTERED 
		(
		SkillNo
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
		) ON [PRIMARY]
		
		IF EXISTS (SELECT * FROM dbo.TB_DefSkill_Player)
		EXEC('INSERT INTO dbo.Tmp_TB_DefSkill_Player (NationCodeStr, SkillNo, Level, NameNo, RscNameNo, ActionName, Memo, Type, ClassLimit, DraClassLimit, LevelLimit, WeaponLimit, 
													  StateLimit, ParentSkill, Target, Range, CastTime, CoolTime, AnimationTime, MP, HP, EffectID, Abil01, Abil02, Abil03, Abil04,
													  Abil05, Abil06, Abil07, Abil08, Abil09, Abil10, CmdStringNo, f_ActionCategory)
			  SELECT 0, SkillNo, Level, NameNo, RscNameNo, ActionName, Memo, Type, ClassLimit, DraClassLimit, LevelLimit, WeaponLimit, 
													  StateLimit, ParentSkill, Target, Range, CastTime, CoolTime, AnimationTime, MP, HP, EffectID, Abil01, Abil02, Abil03, Abil04,
													  Abil05, Abil06, Abil07, Abil08, Abil09, Abil10, CmdStringNo, f_ActionCategory
			  FROM dbo.TB_DefSkill_Player WITH (HOLDLOCK TABLOCKX)')
		
		DROP TABLE TB_DefSkill_Player
		
		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
		DF_TB_DefSkill2_Level DEFAULT ((0)) FOR [Level]

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill2_ActionName DEFAULT (' ') FOR ActionName

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill2_Type DEFAULT ((0)) FOR Type

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill2_ClassLimit DEFAULT ((0)) FOR ClassLimit

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill_Player_DraClassLimit DEFAULT 0 FOR DraClassLimit

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill2_LevelLimit DEFAULT ((0)) FOR LevelLimit

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill2_WeaponLimit DEFAULT ((0)) FOR WeaponLimit

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill2_StateLimit DEFAULT ((0)) FOR StateLimit

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill2_ParentSkill DEFAULT ((0)) FOR ParentSkill

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill_Target DEFAULT ((0)) FOR Target

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill2_Range DEFAULT ((0)) FOR Range

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill2_CastTime DEFAULT ((0)) FOR CastTime

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill2_CoolTime DEFAULT ((0)) FOR CoolTime

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill2_MP DEFAULT ((0)) FOR MP

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill2_HP DEFAULT ((0)) FOR HP

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill2_EffectID DEFAULT ((0)) FOR EffectID

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill_Player_CmdStringNo DEFAULT ((0)) FOR CmdStringNo

		ALTER TABLE dbo.Tmp_TB_DefSkill_Player ADD CONSTRAINT
			DF_TB_DefSkill_Player_f_ActionCategory DEFAULT ((0)) FOR f_ActionCategory
		
		EXECUTE sp_rename N'dbo.Tmp_TB_DefSkill_Player', 'TB_DefSkill_Player', 'OBJECT'
		
		CREATE NONCLUSTERED INDEX IX_NC_TB_DefSkill_Player_ClassLimit2 ON dbo.TB_DefSkill_Player
		(
		ClassLimit
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.[TB_DefSkill_Player]') and name = N'NationCodeStr')
BEGIN
	ALTER TABLE dbo.TB_DefSkill_Player
		DROP CONSTRAINT PK_TB_DefSkill_Player2
	
	ALTER TABLE dbo.TB_DefSkill_Player ADD CONSTRAINT
		PK_TB_DefSkill_Player2 PRIMARY KEY CLUSTERED 
		(
		NationCodeStr,
		SkillNo
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
GO