USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_UserAchievementRankTotal]    Script Date: 10/28/2009 19:33:04 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_UserAchievementRankTotal](
	[OwnerGuid] [uniqueidentifier] NOT NULL,
	[TotalPoint] [int] NULL CONSTRAINT [DF_TB_UserAchievementRankTotal_TotalPoint]  DEFAULT ((0)),
 CONSTRAINT [PK_TB_UserAchievementRankTotal] PRIMARY KEY CLUSTERED 
(
	[OwnerGuid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

CREATE NONCLUSTERED INDEX [IX_TB_UserAchievementRankTotal] ON [dbo].[TB_UserAchievementRankTotal] ([TotalPoint])
GO