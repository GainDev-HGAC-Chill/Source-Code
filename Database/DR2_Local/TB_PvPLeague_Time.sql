USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_PvPLeague_Time]    Script Date: 05/13/2010 18:41:15 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/****** Object:  Table [dbo].[TB_PvPLeague_Time]    Script Date: 05/13/2010 18:47:04 ******/
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_PvPLeague_Time]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_PvPLeague_Time](
		[WeekOfDay] [int] NOT NULL,
		[LeagueState] [int] NOT NULL,
		[LeagueLevel] [int] NOT NULL,
		[BeginTime_Hour] [tinyint] NOT NULL,
		[BeginTime_Minute] [tinyint] NOT NULL,
		[EndTime_Hour] [tinyint] NOT NULL,
		[EndTime_Minute] [tinyint] NOT NULL,
		CONSTRAINT [PK_TB_PvPLeague_Time] PRIMARY KEY CLUSTERED 
		(
			[WeekOfDay] ASC,
			[LeagueState] ASC,
			[LeagueLevel] ASC
		)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_PvPLeague_Time]') AND [name] = N'GameType')
BEGIN
	ALTER TABLE [dbo].[TB_PvPLeague_Time]
		DROP COLUMN [GameType]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_PvPLeague_Time]') AND [name] = N'GameMode')
BEGIN
	ALTER TABLE [dbo].[TB_PvPLeague_Time]
		DROP COLUMN [GameMode]
END


IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_PvPLeague_Time]') AND [name] = N'GameTime')
BEGIN
	ALTER TABLE [dbo].[TB_PvPLeague_Time]
		DROP COLUMN [GameTime]
END
