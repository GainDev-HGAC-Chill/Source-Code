USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_GemStore]    Script Date: 04/08/2009 21:29:16 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_GemStore](
	[idx] [int] IDENTITY(1,1) NOT NULL,
	[NpcGuid] [uniqueidentifier] NOT NULL,
	[ItemNo] [int] NOT NULL,
	[Gem1] [int] NULL,
	[GemCount1] [smallint] NULL,
	[Gem2] [int] NULL,
	[GemCount2] [smallint] NULL,
	[Gem3] [int] NULL,
	[GemCount3] [smallint] NULL,
	[Gem4] [int] NULL,
	[GemCount4] [smallint] NULL,
	[Gem5] [int] NULL,
	[GemCount5] [smallint] NULL,
 CONSTRAINT [PK_TB_GemStore] PRIMARY KEY CLUSTERED 
(
	[idx] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[TB_GemStore] ADD [CP] [int] NULL
GO
