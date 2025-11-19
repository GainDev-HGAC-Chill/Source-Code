USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefClassAbil_Skill]    Script Date: 06/30/2010 11:24:09 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefClassAbil_Skill]') AND [type] IN (N'U'))
BEGIN
CREATE TABLE [dbo].[TB_DefClassAbil_Skill](
	[AbilNo] [int] NOT NULL,
	[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
	[Type01] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type01]  DEFAULT ((0)),
	[Value01] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value01]  DEFAULT ((0)),
	[Type02] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type02]  DEFAULT ((0)),
	[Value02] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value02]  DEFAULT ((0)),
	[Type03] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type03]  DEFAULT ((0)),
	[Value03] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value03]  DEFAULT ((0)),
	[Type04] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type04]  DEFAULT ((0)),
	[Value04] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value04]  DEFAULT ((0)),
	[Type05] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type05]  DEFAULT ((0)),
	[Value05] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value05]  DEFAULT ((0)),
	[Type06] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type06]  DEFAULT ((0)),
	[Value06] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value06]  DEFAULT ((0)),
	[Type07] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type07]  DEFAULT ((0)),
	[Value07] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value07]  DEFAULT ((0)),
	[Type08] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type08]  DEFAULT ((0)),
	[Value08] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value08]  DEFAULT ((0)),
	[Type09] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type09]  DEFAULT ((0)),
	[Value09] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value09]  DEFAULT ((0)),
	[Type10] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type10]  DEFAULT ((0)),
	[Value10] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value10]  DEFAULT ((0)),
 CONSTRAINT [PK_TB_DefClassAbil_Skill] PRIMARY KEY CLUSTERED 
(
	[AbilNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Ability table of TB_DefClass_Skill' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefClassAbil_Skill'
END

IF NOT EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefClassAbil_Skill]') AND [name] = N'NationCodeStr')
BEGIN
	CREATE TABLE [dbo].[Tmp_TB_DefClassAbil_Skill](
	[NationCodeStr] [nvarchar](50) NOT NULL,
	[AbilNo] [int] NOT NULL,
	[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
	[Type01] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type01_2]  DEFAULT ((0)),
	[Value01] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value01_2]  DEFAULT ((0)),
	[Type02] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type02_2]  DEFAULT ((0)),
	[Value02] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value02_2]  DEFAULT ((0)),
	[Type03] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type03_2]  DEFAULT ((0)),
	[Value03] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value03_2]  DEFAULT ((0)),
	[Type04] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type04_2]  DEFAULT ((0)),
	[Value04] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value04_2]  DEFAULT ((0)),
	[Type05] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type05_2]  DEFAULT ((0)),
	[Value05] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value05_2]  DEFAULT ((0)),
	[Type06] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type06_2]  DEFAULT ((0)),
	[Value06] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value06_2]  DEFAULT ((0)),
	[Type07] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type07_2]  DEFAULT ((0)),
	[Value07] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value07_2]  DEFAULT ((0)),
	[Type08] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type08_2]  DEFAULT ((0)),
	[Value08] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value08_2]  DEFAULT ((0)),
	[Type09] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type09_2]  DEFAULT ((0)),
	[Value09] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value09_2]  DEFAULT ((0)),
	[Type10] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Type10_2]  DEFAULT ((0)),
	[Value10] [int] NOT NULL CONSTRAINT [DF_TB_DefClassAbil_Skill_Value10_2]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_DefClassAbil_Skill2] PRIMARY KEY CLUSTERED 
	(
		[AbilNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
	
	IF EXISTS (SELECT * FROM dbo.TB_DefClassAbil_Skill)
	EXEC('INSERT INTO dbo.Tmp_TB_DefClassAbil_Skill (NationCodeStr, AbilNo, Memo, Type01, Value01, Type02, Value02, Type03, Value03, Type04, Value04, Type05, Value05,
													 Type06, Value06, Type07, Value07, Type08, Value08, Type09, Value09, Type10, Value10)
		  SELECT 0, AbilNo, Memo, Type01, Value01, Type02, Value02, Type03, Value03, Type04, Value04, Type05, Value05,
													 Type06, Value06, Type07, Value07, Type08, Value08, Type09, Value09, Type10, Value10
		  FROM dbo.TB_DefClassAbil_Skill WITH (HOLDLOCK TABLOCKX)')
			  
	DROP TABLE TB_DefClassAbil_Skill
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefClassAbil_Skill', 'TB_DefClassAbil_Skill', 'OBJECT'
	
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Ability table of TB_DefClass_Skill' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefClassAbil_Skill'
END
GO

IF EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefClassAbil_Skill]') AND [name] = N'NationCodeStr')
BEGIN
	ALTER TABLE dbo.TB_DefClassAbil_Skill
	DROP CONSTRAINT PK_TB_DefClassAbil_Skill2
	ALTER TABLE dbo.TB_DefClassAbil_Skill ADD CONSTRAINT
		PK_TB_DefClassAbil_Skill2 PRIMARY KEY CLUSTERED 
		(
		NationCodeStr,
		AbilNo
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
GO