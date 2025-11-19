USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_UserAchievementFirstComplete]    Script Date: 10/22/2009 18:56:29 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_UserAchievementFirstComplete](
	[FirstCompleteAchievement] [int] NOT NULL,
	[OwnerGuid] [uniqueidentifier] NULL,
	[CompleteDate] [datetime] NULL CONSTRAINT [DF_TB_UserAchievementFirstComplete_CompleteDate]  DEFAULT (getdate()),
 CONSTRAINT [PK_TB_UserAchievementFirstComplete] PRIMARY KEY CLUSTERED 
(
	[FirstCompleteAchievement] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
