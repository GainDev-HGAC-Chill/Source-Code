USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_PvPLeague_Reward]    Script Date: 05/13/2010 18:41:15 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/****** Object:  Table [dbo].[TB_PvPLeague_Reward]    Script Date: 05/13/2010 18:47:04 ******/
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_PvPLeague_Reward]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_PvPLeague_Reward](
		[LeagueLevel] [int] NOT NULL,
		[ItemNo1] [int] NULL,
		[ItemCount1] [int] NULL,
		[ItemNo2] [int] NULL,
		[ItemCount2] [int] NULL,
		[ItemNo3] [int] NULL,
		[ItemCount3] [int] NULL,
		[ItemNo4] [int] NULL,
		[ItemCount4] [int] NULL,
		[ItemNo5] [int] NULL,
		[ItemCount5] [int] NULL,
		CONSTRAINT [PK_TB_PvPLeague_Reward] PRIMARY KEY CLUSTERED 
		(
			[LeagueLevel] ASC
		)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END
GO