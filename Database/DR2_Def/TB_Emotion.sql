USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefEmotion]    Script Date: 04/30/2009 10:46:59 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefEmotion](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[Type] [tinyint] NULL,
	[GroupNo] [int] NOT NULL,
	[ActionNo] [int] NOT NULL,
	[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
 CONSTRAINT [PK_TB_DefEmotionGroup] PRIMARY KEY CLUSTERED 
(
	[Idx] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
