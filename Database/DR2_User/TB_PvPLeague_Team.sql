USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_PvPLeague_Team]    Script Date: 05/13/2010 18:41:15 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/****** Object:  Table [dbo].[TB_PvPLeague_Team]    Script Date: 05/13/2010 18:47:04 ******/
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_PvPLeague_Team]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_PvPLeague_Team](
		[LeagueGuid] [uniqueidentifier] NOT NULL,
		[TeamGuid] [uniqueidentifier] NOT NULL,
		[TeamName] [nvarchar](100) NOT NULL,
		[UserGuid1] [uniqueidentifier] NULL,
		[UserGuid2] [uniqueidentifier] NULL,
		[UserGuid3] [uniqueidentifier] NULL,
		[UserGuid4] [uniqueidentifier] NULL,
		[RegistDate] [datetime] NOT NULL,
		[TournamentIndex] [int] NULL,
		[LeagueLevel] [int] NULL,
		[Point]		[int] NULL
		CONSTRAINT [PK_TB_PvPLeague_Team] PRIMARY KEY CLUSTERED 
		(
			[TeamGuid] ASC
		)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END
GO