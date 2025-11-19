USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_PvPLeague_Tournament]    Script Date: 05/13/2010 18:41:15 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/****** Object:  Table [dbo].[TB_PvPLeague_Tournament]    Script Date: 05/13/2010 18:47:04 ******/
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_PvPLeague_Tournament]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_PvPLeague_Tournament](
		[LeagueGuid] [uniqueidentifier] NOT NULL,
		[TournamentGuid] [uniqueidentifier] NOT NULL,
		[LeagueLevel] [int] NOT NULL,
		[GameType] [int] NOT NULL,
		[GameMode] [int] NOT NULL,
		[GameTime] [int] NOT NULL,
		[BeginTime] [datetime] NOT NULL,
		CONSTRAINT [PK_TB_PvPLeague_Tournament] PRIMARY KEY CLUSTERED 
		(
			[LeagueGuid] ASC,
			[TournamentGuid] ASC
		)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
GO