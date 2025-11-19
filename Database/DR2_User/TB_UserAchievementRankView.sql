USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_UserAchievementRankView]    Script Date: 12/17/2009 15:58:57 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_UserAchievementRankView](
	[Rank] [int] IDENTITY(1,1) NOT NULL,
	[OwnerGuid] [uniqueidentifier] NOT NULL,
	[TotalPoint] [int] NULL,
 CONSTRAINT [PK_TB_User_AchievementRankView] PRIMARY KEY CLUSTERED 
(
	[OwnerGuid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
