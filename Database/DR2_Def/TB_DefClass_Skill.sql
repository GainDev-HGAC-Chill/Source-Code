USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefClass_Skill]    Script Date: 06/30/2010 10:49:28 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefClass_Skill]') AND [type] IN (N'U'))
BEGIN
CREATE TABLE [dbo].[TB_DefClass_Skill](
	[iClass] [int] NOT NULL,
	[iLevel] [smallint] NOT NULL,
	[ClassName] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_ClassName]  DEFAULT ((0)),
	[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
	[Experience] [bigint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Experience_1]  DEFAULT ((0)),
	[MaxHP] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_MaxHP_1]  DEFAULT ((0)),
	[MaxMP] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_MaxMP_1]  DEFAULT ((0)),
	[Str] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Str_1]  DEFAULT ((0)),
	[Int] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Int_1]  DEFAULT ((0)),
	[Dex] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Dex_1]  DEFAULT ((0)),
	[Con] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Con_1]  DEFAULT ((0)),
	[HP_Recovery_Speed] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_HP_Recovery_Speed_1]  DEFAULT ((0)),
	[HP_Recovery] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_HP_Recovery_1]  DEFAULT ((0)),
	[MP_Recovery_Speed] [smallint] NOT NULL,
	[MP_Recovery] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_MP_Recovery_1]  DEFAULT ((0)),
	[MoveSpeed] [smallint] NOT NULL,
	[Abil01] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil01_1]  DEFAULT ((0)),
	[Abil02] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil02_1]  DEFAULT ((0)),
	[Abil03] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil03_1]  DEFAULT ((0)),
	[Abil04] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil04_1]  DEFAULT ((0)),
	[Abil05] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil05_1]  DEFAULT ((0)),
	[Abil06] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil06_1]  DEFAULT ((0)),
	[Abil07] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil07_1]  DEFAULT ((0)),
	[Abil08] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil08_1]  DEFAULT ((0)),
	[Abil09] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil09_1]  DEFAULT ((0)),
	[Abil10] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil10_1]  DEFAULT ((0)),
 CONSTRAINT [PK_TB_DefClass_Skill] PRIMARY KEY CLUSTERED 
(
	[iClass] ASC,
	[iLevel] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Character class Skill and level definition' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefClass_Skill'

END
GO

IF NOT EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefClass_Skill]') AND [name] = N'NationCodeStr')
BEGIN
	CREATE TABLE [dbo].[Tmp_TB_DefClass_Skill](
	[NationCodeStr] nvarchar(50) NOT NULL,
	[iClass] [int] NOT NULL,
	[iLevel] [smallint] NOT NULL,
	[ClassName] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_ClassName2]  DEFAULT ((0)),
	[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
	[Experience] [bigint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Experience_2]  DEFAULT ((0)),
	[MaxHP] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_MaxHP_2]  DEFAULT ((0)),
	[MaxMP] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_MaxMP_2]  DEFAULT ((0)),
	[Str] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Str_2]  DEFAULT ((0)),
	[Int] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Int_2]  DEFAULT ((0)),
	[Dex] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Dex_2]  DEFAULT ((0)),
	[Con] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Con_2]  DEFAULT ((0)),
	[HP_Recovery_Speed] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_HP_Recovery_Speed_2]  DEFAULT ((0)),
	[HP_Recovery] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_HP_Recovery_2]  DEFAULT ((0)),
	[MP_Recovery_Speed] [smallint] NOT NULL,
	[MP_Recovery] [smallint] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_MP_Recovery_2]  DEFAULT ((0)),
	[MoveSpeed] [smallint] NOT NULL,
	[Abil01] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil01_2]  DEFAULT ((0)),
	[Abil02] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil02_2]  DEFAULT ((0)),
	[Abil03] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil03_2]  DEFAULT ((0)),
	[Abil04] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil04_2]  DEFAULT ((0)),
	[Abil05] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil05_2]  DEFAULT ((0)),
	[Abil06] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil06_2]  DEFAULT ((0)),
	[Abil07] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil07_2]  DEFAULT ((0)),
	[Abil08] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil08_2]  DEFAULT ((0)),
	[Abil09] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil09_2]  DEFAULT ((0)),
	[Abil10] [int] NOT NULL CONSTRAINT [DF_TB_DefClass_Skill_Abil10_2]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_DefClass_Skill2] PRIMARY KEY CLUSTERED 
	(
		[iClass] ASC,
		[iLevel] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
	
	IF EXISTS (SELECT * FROM dbo.TB_DefClass_Skill)
	EXEC ('INSERT INTO dbo.Tmp_TB_DefClass_Skill (NationCodeStr, iClass, iLevel, ClassName, Memo, Experience, MaxHP, MaxMP, Str, Int, Dex, Con,
												  HP_Recovery_Speed, HP_Recovery, MP_Recovery_Speed, MP_Recovery, MoveSpeed, Abil01, Abil02, Abil03,
												  Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10)
		   SELECT 0, iClass, iLevel, ClassName, Memo, Experience, MaxHP, MaxMP, Str, Int, Dex, Con, HP_Recovery_Speed, HP_Recovery, MP_Recovery_Speed, 
		          MP_Recovery, MoveSpeed, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10
		   FROM dbo.TB_DefClass_Skill WITH (HOLDLOCK TABLOCKX)')
	
	DROP TABLE TB_DefClass_Skill
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefClass_Skill', 'TB_DefClass_Skill', 'OBJECT'
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Character class Skill and level definition' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefClass_Skill'
END
GO

IF EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefClass_Skill]') AND [name] = N'NationCodeStr')
BEGIN
	ALTER TABLE dbo.TB_DefClass_Skill
		DROP CONSTRAINT PK_TB_DefClass_Skill2
	ALTER TABLE dbo.TB_DefClass_Skill ADD CONSTRAINT
		PK_TB_DefClass_Skill2 PRIMARY KEY CLUSTERED 
		(
		NationCodeStr,
		iClass,
		iLevel
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
GO