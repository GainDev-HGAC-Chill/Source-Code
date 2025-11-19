USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefClassPet]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefClassPet]-- 기존에 나가있는 1차펫을 패치할려면 Drop해야한다.
GO

CREATE TABLE [dbo].[TB_DefClassPet](
	[ClassNo] [int] NOT NULL,
	[ClassName] [int] NOT NULL,
	[Memo] [nvarchar](100) NULL,
	[PetType] [tinyint] NOT NULL,
	[f_LevelID] [int] NOT NULL,
	[f_SkillID] [int] NOT NULL,
	[f_ItemOptionID] [int] NOT NULL,
	[Hair] [int] NOT NULL CONSTRAINT [DF_TB_DefClassPet_Hair] DEFAULT((0)),
	[Face] [int] NOT NULL CONSTRAINT [DF_TB_DefClassPet_Face] DEFAULT((0)),
	[Body] [int] NOT NULL CONSTRAINT [DF_TB_DefClassPet_Body] DEFAULT((0)),
 CONSTRAINT [PK_TB_DefClassPet] PRIMARY KEY CLUSTERED
(
	[ClassNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO