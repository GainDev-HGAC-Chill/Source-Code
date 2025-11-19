USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefSkillIdxToSkillNo]    Script Date: 07/10/2009 14:59:44 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefSkillIdxToSkillNo](
	[SkillIdx] [int] NOT NULL,
	[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[SkillNo] [int] NOT NULL
) ON [PRIMARY]
