USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefMyhomeBuildings]    Script Date: 02/04/2010 20:42:04 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefMyhomeBuildings](
	[BuildingNo] [int] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[groundno] [int] NULL,
	[Grade] [int] NULL,
	[MaxRoom] [int] NULL,
 CONSTRAINT [PK_TB_DefMyhomeBuildings] PRIMARY KEY CLUSTERED 
(
	[BuildingNo] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
