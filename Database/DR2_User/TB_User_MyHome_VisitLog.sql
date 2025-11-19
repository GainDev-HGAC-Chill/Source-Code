USE [DR2_User]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * from sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_User_MyHome_VisitLog]') AND [type] in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_User_MyHome_VisitLog](
		[LogGuid] [uniqueidentifier] NOT NULL,
		[OwnerGuid] [uniqueidentifier] NOT NULL,
		[VisitorGuid] [uniqueidentifier] NOT NULL,
		[VisitorLog] [nvarchar](80) NOT NULL,
		[LogTime] [datetime] NULL CONSTRAINT [DF_TB_User_MyHome_VisitLog_LogTime]  DEFAULT (getdate()),
		[Private] [tinyint] NULL,
	 CONSTRAINT [PK_TB_User_MyHome_VisitLog] PRIMARY KEY CLUSTERED 
	(
		[LogGuid] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
GO

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_User_MyHome_VisitLog]') and [name] = N'VisitorLog')
BEGIN
	ALTER TABLE [dbo].[TB_User_MyHome_VisitLog] ALTER COLUMN [VisitorLog] [nvarchar](80) NOT NULL
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_User_MyHome_VisitLog]') and [name] = N'Private')
BEGIN
	ALTER TABLE [dbo].[TB_User_MyHome_VisitLog] ADD [Private] [tinyint] NULL
END