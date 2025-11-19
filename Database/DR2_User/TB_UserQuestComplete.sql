USE [DR2_User]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'TB_UserQuestComplete'))
BEGIN
/****** Object:  Table [dbo].[TB_UserQuestComplete]    Script Date: 08/06/2013 15:28:35 ******/

CREATE TABLE [dbo].[TB_UserQuestComplete](
	[CharacterID] [uniqueidentifier] NOT NULL,
	[QuestID] [int] NOT NULL,
	[Complete] [tinyint] NOT NULL,
	[CompleteDate] [datetime] NULL,
 CONSTRAINT [PK_TB_UserQuestComplete] PRIMARY KEY CLUSTERED 
(
	[CharacterID] ASC,
	[QuestID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

END
GO
