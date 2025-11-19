USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefHometownToMapCost]    Script Date: 08/31/2009 20:52:59 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefHometownToMapCost](
	[LevelLimit] [smallint] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[Cost] [int] NULL,
 CONSTRAINT [PK_TB_DefHometownToMapCost] PRIMARY KEY CLUSTERED 
(
	[LevelLimit] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
