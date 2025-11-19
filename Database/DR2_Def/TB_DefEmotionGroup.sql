USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefEmotionGroup]    Script Date: 04/30/2009 10:46:52 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefEmotionGroup](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[GroupNo] [int] NOT NULL,
	[Type] [tinyint] NOT NULL,
	[NameNo] [int] NOT NULL,
	[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
 CONSTRAINT [PK_TB_DefEmotionGroup_1] PRIMARY KEY CLUSTERED 
(
	[Idx] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
