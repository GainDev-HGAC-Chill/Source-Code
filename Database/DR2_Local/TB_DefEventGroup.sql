USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_DefEventGroup]    Script Date: 08/05/2011 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEventGroup]') )
BEGIN
	CREATE TABLE [dbo].[TB_DefEventGroup](
		[IDX] [int] IDENTITY(1,1) NOT NULL,
		[EventGroup] [int] NOT NULL,
		[MonsterGroup] [int] NOT NULL,
		[StartTime] [datetime] NOT NULL,
		[EndTime] [datetime] NOT NULL,
		[RegenPeriod] [int] NOT NULL,
		[DelayGenTime] [int] NOT NULL,
		[Message] [nvarchar](255) NULL
	 CONSTRAINT [PK_TB_DefEventGroup] PRIMARY KEY CLUSTERED 
	(
		[EventGroup] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END