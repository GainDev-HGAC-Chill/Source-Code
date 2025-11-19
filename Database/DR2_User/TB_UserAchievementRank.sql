USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_UserAchievementRank]    Script Date: 10/30/2009 10:41:56 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_UserAchievementRank](
	[OwnerGuid] [uniqueidentifier] NOT NULL,
	[Category] [int] NOT NULL,
	[Point] [int] NULL CONSTRAINT [DF_Table_1_AchievementPoint]  DEFAULT ((0)),
 CONSTRAINT [PK_TB_UserAchievementRank_1] PRIMARY KEY CLUSTERED 
(
	[OwnerGuid] ASC,
	[Category] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
