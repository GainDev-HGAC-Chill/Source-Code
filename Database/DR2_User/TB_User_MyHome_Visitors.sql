USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_User_MyHome_Visitors]    Script Date: 08/12/2009 13:30:59 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_User_MyHome_Visitors](
	[StreetNo] [smallint] NOT NULL,
	[HouseNo] [smallint] NOT NULL,
	[VisitorGuid] [uniqueidentifier] NOT NULL,
	[VisitTime] [datetime] NOT NULL
) ON [PRIMARY]
go

CREATE NONCLUSTERED INDEX [IX_TB_User_MyHome_Visitors] ON [dbo].[TB_User_MyHome_Visitors] ([StreetNo], [HouseNo])
GO

DROP INDEX [IX_TB_User_MyHome_Visitors] ON [dbo].[TB_User_MyHome_Visitors]
GO
ALTER TABLE [dbo].[TB_User_MyHome_Visitors] ALTER COLUMN [HouseNo] [int] NOT NULL
GO
CREATE NONCLUSTERED INDEX [IX_TB_User_MyHome_Visitors] ON [dbo].[TB_User_MyHome_Visitors] ([StreetNo], [HouseNo])
GO