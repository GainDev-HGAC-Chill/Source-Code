USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_User_MyHome_WriteLog_Visitors]    Script Date: 02/08/2010 15:13:27 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_User_MyHome_WriteLog_Visitors](
	[HomeOwnerGuid] [uniqueidentifier] NOT NULL,
	[VisitorGuid] [uniqueidentifier] NOT NULL,
	[VisitTime] [datetime] NULL,
 CONSTRAINT [PK_TB_User_MyHome_WriteLog_Visitors] PRIMARY KEY CLUSTERED 
(
	[HomeOwnerGuid] ASC,
	[VisitorGuid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

CREATE NONCLUSTERED INDEX [IX_Table_VisitTime] ON [dbo].[TB_User_MyHome_WriteLog_Visitors] 
(
	[VisitTime] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF) ON [PRIMARY]
go

USE [DR2_User]
GO