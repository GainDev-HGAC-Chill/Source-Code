USE [DR2_User]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_UserAchievement_TimeLimit](
	[OwnerGuid] [uniqueidentifier] NOT NULL,
	[AchievementIdx] [int] NOT NULL,
	[TimeLimit] [int] NULL,
 CONSTRAINT [PK_TB_UserAchievement_TimeLimit] PRIMARY KEY CLUSTERED 
(
	[OwnerGuid] ASC,
	[AchievementIdx] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO


CREATE NONCLUSTERED INDEX [IX_TB_UserAchievement_TimeLimit] ON [dbo].[TB_UserAchievement_TimeLimit] 
(
	[OwnerGuid] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF) ON [PRIMARY]