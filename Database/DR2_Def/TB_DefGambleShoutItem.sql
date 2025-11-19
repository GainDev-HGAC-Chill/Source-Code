USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefGambleShoutItem]    Script Date: 06/01/2009 20:02:26 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefGambleShoutItem](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[GambleNo] [int] NOT NULL,
	[ItemNo] [int] NOT NULL,
	[Grade] [tinyint] NOT NULL,
 CONSTRAINT [PK_TB_DefGambleShoutItem_1] PRIMARY KEY CLUSTERED 
(
	[GambleNo] ASC,
	[ItemNo] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
