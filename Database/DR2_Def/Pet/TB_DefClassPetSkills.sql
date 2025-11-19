USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefClassPetSkills]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefClassPetSkills](
		[ID] [int] NOT NULL,
		[Level] [smallint] NOT NULL,
		[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
		[Skill01] [int] NOT NULL,
		[Skill02] [int] NOT NULL,
		[Skill03] [int] NOT NULL,
		[Skill04] [int] NOT NULL,
		[Skill05] [int] NOT NULL,
		[Skill06] [int] NOT NULL,
		[Skill07] [int] NOT NULL,
		[Skill08] [int] NOT NULL,
		[Skill09] [int] NOT NULL,
		[Skill10] [int] NOT NULL,
		[Skill11] [int] NOT NULL,
		[Skill12] [int] NOT NULL,
		[Skill13] [int] NOT NULL,
		[Skill14] [int] NOT NULL,
		[Skill15] [int] NOT NULL,
		[Skill16] [int] NOT NULL,
		[Skill17] [int] NOT NULL,
		[Skill18] [int] NOT NULL,
		[UseTime01] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime01] DEFAULT((0)),
		[UseTime02] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime02] DEFAULT((0)),
		[UseTime03] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime03] DEFAULT((0)),
		[UseTime04] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime04] DEFAULT((0)),
		[UseTime05] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime05] DEFAULT((0)),
		[UseTime06] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime06] DEFAULT((0)),
		[UseTime07] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime07] DEFAULT((0)),
		[UseTime08] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime08] DEFAULT((0)),
		[UseTime09] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime09] DEFAULT((0)),
		[UseTime10] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime10] DEFAULT((0)),
		[UseTime11] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime11] DEFAULT((0)),
		[UseTime12] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime12] DEFAULT((0)),
		[UseTime13] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime13] DEFAULT((0)),
		[UseTime14] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime14] DEFAULT((0)),
		[UseTime15] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime15] DEFAULT((0)),
		[UseTime16] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime16] DEFAULT((0)),
		[UseTime17] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime17] DEFAULT((0)),
		[UseTime18] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime18] DEFAULT((0)),
	CONSTRAINT [PK_TB_DefClassPetSkills] PRIMARY KEY CLUSTERED
	(
		[ID] ASC,
		[Level] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
ELSE
BEGIN

	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime01] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime01] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime02] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime02] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime03] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime03] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime04] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime04] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime05] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime05] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime06] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime06] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime07] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime07] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime08] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime08] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime09] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime09] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime10] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime10] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime11] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime11] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime12] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime12] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime13] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime13] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime14] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime14] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime15] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime15] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime16] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime16] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime17] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime17] DEFAULT((0))
	ALTER TABLE [dbo].[TB_DefClassPetSkills] ADD [UseTime18] [bit] NOT NULL CONSTRAINT [DF_TB_DefClassPetSkills_UseTime18] DEFAULT((0))
	
END
GO
