USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefQuest_Wanted]    Script Date: 02/06/2010 19:08:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefQuest_Wanted]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefQuest_Wanted](
		[QuestID] [int] NOT NULL,
		[ClearCount] [int] NOT NULL,		
		[ItemNo] [int] NOT NULL,
		[ItemCount] [int] NOT NULL,
		[CoolTime] [int] NOT NULL,
	 CONSTRAINT [PK_TB_DefQuest_Wanted] PRIMARY KEY CLUSTERED 
	(
		[QuestID] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END
