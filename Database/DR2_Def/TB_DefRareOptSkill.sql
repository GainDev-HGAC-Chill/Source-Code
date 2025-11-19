USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefRareOptSkill]    Script Date: 07/10/2009 14:59:05 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[dbo].[TB_DefRareOptSkill]') AND type = N'U')
BEGIN
CREATE TABLE [dbo].[TB_DefRareOptSkill](
	[RareOptSkillNo] [int] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[SkillSuccessControlNo] [int] NOT NULL,
	[SkllLvSuccessControlNo] [int] NOT NULL,
	[SkillIdx01] [int] NULL,
	[SkillIdx02] [int] NULL,
	[SkillIdx03] [int] NULL,
	[SkillIdx04] [int] NULL,
	[SkillIdx05] [int] NULL,
	[SkillIdx06] [int] NULL,
	[SkillIdx07] [int] NULL,
	[SkillIdx08] [int] NULL,
	[SkillIdx09] [int] NULL,
	[SkillIdx10] [int] NULL
) ON [PRIMARY]
END

IF NOT EXISTS(SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'dbo.TB_DefRareOptSkill') and [name] = N'PK_TB_DefRareOptSkill')
BEGIN
ALTER TABLE dbo.TB_DefRareOptSkill ADD CONSTRAINT
	PK_TB_DefRareOptSkill PRIMARY KEY CLUSTERED 
	(
	RareOptSkillNo
	) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
GO
