USE [DR2_local]
GO

/****** Object:  Table [dbo].[TB_OXQuizEvent]    Script Date: 04/09/2009 20:40:06 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_OXQuizEvent](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[EventId] [int] NOT NULL,
	[Memo] [nvarchar](50) NULL,
	[QuizMin] [int] NOT NULL,
	[QuizMax] [int] NOT NULL,
	[UserLimit] [int] NOT NULL,
	[StartDate] [datetime] NOT NULL,
	[EndDate] [datetime] NOT NULL,
	[MaxStep] [int] NOT NULL,
	[EventNoti30] [nvarchar](200) NULL,
	[EventNoti10] [nvarchar](200) NULL,
	[EventNoti5] [nvarchar](200) NULL,
	[EventNotiStart] [nvarchar](200) NULL,
	[SaveLimit] [int] NOT NULL CONSTRAINT [DF_TB_OXQuizEvent_SaveLimit]  DEFAULT ((50)),
	[EventState] [tinyint] NOT NULL CONSTRAINT [DF_TB_OXQuizEvent_EventState]  DEFAULT ((0)),
	[EventNotiClose] [nvarchar](200) NULL,
	[EventEndDate] [datetime] NULL,
	[MailTitle] [nvarchar](50) NULL,
	[MailText] [nvarchar](200) NULL,
 CONSTRAINT [PK_TB_OXQuizEvent_Idx] PRIMARY KEY CLUSTERED 
(
	[Idx] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
go

ALTER TABLE [dbo].[TB_OXQuizEvent] ADD
[AnsTime] [int] NULL,
[Repeat] [tinyint] NULL,
[EventNoti1] [nvarchar] (200) COLLATE Korean_Wansung_CI_AS NULL,
[EventNotiTime1] [int] NULL,
[EventNoti2] [nvarchar] (200) COLLATE Korean_Wansung_CI_AS NULL,
[EventNotiTime2] [int] NULL,
[EventNoti3] [nvarchar] (200) COLLATE Korean_Wansung_CI_AS NULL,
[EventNotiTime3] [int] NULL,
[EventNoti4] [nvarchar] (200) COLLATE Korean_Wansung_CI_AS NULL,
[EventNotiTime4] [int] NULL,
[EventNotiTime5] [int] NULL,
[EventNoti6] [nvarchar] (200) COLLATE Korean_Wansung_CI_AS NULL,
[EventNotiTime6] [int] NULL,
[EventNoti7] [nvarchar] (200) COLLATE Korean_Wansung_CI_AS NULL,
[EventNotiTime7] [int] NULL,
[EventNoti8] [nvarchar] (200) COLLATE Korean_Wansung_CI_AS NULL,
[EventNotiTime8] [int] NULL,
[EventNoti9] [nvarchar] (200) COLLATE Korean_Wansung_CI_AS NULL,
[EventNotiTime9] [int] NULL,
[EventNotiTime10] [int] NULL
GO

ALTER TABLE [dbo].[TB_OXQuizEvent] DROP
COLUMN [EventNoti30],
COLUMN [EventNotiStart]
GO
