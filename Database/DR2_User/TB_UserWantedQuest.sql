USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_UserWantedQuest]    Script Date: 02/04/2010 18:10:37 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserWantedQuest]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_UserWantedQuest](
		[CharacterID] [uniqueidentifier] NOT NULL,
		[QuestID] [int] NOT NULL,
		[ClearCount] [int] NOT NULL,
	 CONSTRAINT [PK_TB_UserWantedQuest] PRIMARY KEY CLUSTERED 
	(
		[CharacterID] ASC,
		[QuestID] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END
