USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DeleteAchievementsTable]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DeleteAchievementsTable]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DeleteAchievementsTable](
	[SaveIdx] [int] NULL,
	[itemno] [int] NULL,
	[DeleteItemNo] [int] NULL
) ON [PRIMARY]
