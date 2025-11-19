USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefSkillExtendItem]    Script Date: 02/23/2010 10:14:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefSkillExtendItem](
	[ExtendIdx] [int] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[SkillNo01] [int] NULL,
	[SkillNo02] [int] NULL,
	[SkillNo03] [int] NULL,
	[SkillNo04] [int] NULL,
	[SkillNo05] [int] NULL,
	[SkillNo06] [int] NULL,
	[SkillNo07] [int] NULL,
	[SkillNo08] [int] NULL,
	[SkillNo09] [int] NULL,
	[SkillNo10] [int] NULL,
 CONSTRAINT [PK_TB_DefSkillExtendItem] PRIMARY KEY CLUSTERED 
(
	[ExtendIdx] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
