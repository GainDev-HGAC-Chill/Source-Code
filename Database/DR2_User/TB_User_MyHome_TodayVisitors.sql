USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_User_MyHome_TodayVisitors]    Script Date: 09/09/2009 18:04:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_User_MyHome_TodayVisitors](
	[TownNo] [smallint] NOT NULL,
	[HouseNo] [smallint] NOT NULL,
	[VisitorGuid] [uniqueidentifier] NOT NULL,
	[VisitDay] [tinyint] NOT NULL,
 CONSTRAINT [PK_TB_User_MyHome_TodayVisitors] PRIMARY KEY CLUSTERED 
(
	[TownNo] ASC,
	[HouseNo] ASC,
	[VisitorGuid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[TB_User_MyHome_TodayVisitors] DROP CONSTRAINT [PK_TB_User_MyHome_TodayVisitors]
GO
ALTER TABLE [dbo].[TB_User_MyHome_TodayVisitors] ALTER COLUMN [HouseNo] [int] NOT NULL
GO
ALTER TABLE [dbo].[TB_User_MyHome_TodayVisitors] ADD CONSTRAINT [PK_TB_User_MyHome_TodayVisitors] PRIMARY KEY CLUSTERED ([TownNo], [HouseNo], [VisitorGuid])
GO