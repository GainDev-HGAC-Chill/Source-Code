USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_PvPLeague]    Script Date: 05/13/2010 18:41:15 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/****** Object:  Table [dbo].[TB_PvPLeague]    Script Date: 05/13/2010 18:47:04 ******/
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_PvPLeague]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_PvPLeague](
		[LeagueGuid] [uniqueidentifier] NOT NULL,
		[TounamentGuid] [uniqueidentifier] NULL,
		[LeagueState] [int] NOT NULL,
		[RegistDate] [datetime] NOT NULL,
		[Session] [int] NOT NULL CONSTRAINT [DF_TB_PvPLeague_Session]  DEFAULT ((1))
		CONSTRAINT [PK_TB_PvPLeague] PRIMARY KEY CLUSTERED 
		(
			[LeagueGuid] ASC
		)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_PvPLeague]') AND [name] = N'Session')
BEGIN
	ALTER TABLE [dbo].[TB_PvPLeague]
		ADD [Session] [int] NOT NULL CONSTRAINT [DF_TB_PvPLeague_Session]  DEFAULT ((1))
END