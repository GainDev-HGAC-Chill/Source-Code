USE [DR2_USER]
GO
/****** Object:  Table [dbo].[TB_PvPLeague_Battle]    Script Date: 05/13/2010 18:41:15 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/****** Object:  Table [dbo].[TB_PvPLeague_Battle]    Script Date: 05/13/2010 18:47:04 ******/
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_PvPLeague_Battle]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_PvPLeague_Battle](
		[TournamentGuid] [uniqueidentifier] NOT NULL,
		[BattleGuid] [uniqueidentifier] NOT NULL,
		[TournamentIndex] [int] NOT NULL,
		[TeamGuid1] [uniqueidentifier] NULL,
		[TeamGuid2] [uniqueidentifier] NULL,
		[WinTeamGuid] [uniqueidentifier] NULL,
		[GroupIndex] [int] NOT NULL
		CONSTRAINT [PK_TB_PvPLeague_Battle] PRIMARY KEY CLUSTERED 
		(
			[TournamentGuid] ASC,
			[BattleGuid] ASC
		)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_PvPLeague_Battle]') AND [name] = N'GroupIndex')
BEGIN
	ALTER TABLE [dbo].[TB_PvPLeague_Battle]
		ADD [GroupIndex] [int] NOT NULL
END
