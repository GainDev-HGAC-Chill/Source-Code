USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_DefGambleMachineCost]    Script Date: 09/14/2009 18:34:43 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefGambleMachineCost](
	[CoinType] [tinyint] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[Cost] [int] NULL,
 CONSTRAINT [PK_TB_DefGambleMachineCost] PRIMARY KEY CLUSTERED 
(
	[CoinType] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
