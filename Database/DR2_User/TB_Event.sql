USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_Event]    Script Date: 05/18/2009 18:49:01 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_Event](
	[IDX] [int] IDENTITY(1,1) NOT NULL,
	[EventNo] [int] NOT NULL,
	[EventType] [int] NOT NULL,
	[Title] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[Description] [nvarchar](200) COLLATE Korean_Wansung_CI_AS NULL,
	[Memo] [NVARCHAR](50) COLLATE Korean_Wansung_CI_AS NULL,
	[StartDate] [datetime] NULL,
	[EndDate] [datetime] NULL,
	[Period] [int] NULL,
	[intData01] [int] NULL,
	[intData02] [int] NULL,
	[intData03] [int] NULL,
	[bigintData01] [bigint] NULL,
	[bigintData02] [bigint] NULL,
	[bigintData03] [bigint] NULL,
	[guidData01] [uniqueidentifier] NULL,
	[guidData02] [uniqueidentifier] NULL,
	[guidData03] [uniqueidentifier] NULL,
	[stringData01] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
	[stringData02] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
	[stringData03] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
 CONSTRAINT [PK_TB_Event_EventNo] PRIMARY KEY NONCLUSTERED 
(
	[EventNo] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Event table' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'TB_Event'

ALTER TABLE [dbo].[TB_Event] ADD [Title] [nvarchar] (50) COLLATE Korean_Wansung_CI_AS NULL,[Description] [nvarchar] (200) COLLATE Korean_Wansung_CI_AS NULL
GO