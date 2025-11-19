USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_OXQuizEventState]    Script Date: 06/22/2009 14:11:27 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_OXQuizEventState](
	[EventID] [int] NOT NULL,
	[State] [tinyint] NOT NULL,
 CONSTRAINT [PK_TB_OXQuizEventState] PRIMARY KEY CLUSTERED 
(
	[EventID] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
