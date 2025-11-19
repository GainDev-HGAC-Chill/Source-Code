USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_DefMyHomeTex]    Script Date: 08/31/2009 18:18:37 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefMyHomeTex](
	[AuctionLevelLimit] [smallint] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[MyHomeTex] [int] NULL,
 CONSTRAINT [PK_TB_DefMyHomeTex] PRIMARY KEY CLUSTERED 
(
	[AuctionLevelLimit] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
