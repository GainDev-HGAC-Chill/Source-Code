USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_User_MyHome_Invitation]    Script Date: 08/12/2009 13:30:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_User_MyHome_Invitation](
	[CardGuid] [uniqueidentifier] NOT NULL,
	[OwnerGuid] [uniqueidentifier] NOT NULL,
	[StreetNo] [smallint] NOT NULL,
	[HouseNo] [smallint] NOT NULL,
	[LimitTime] [datetime] NOT NULL,
	[GenYear] [int] NULL,
	[GenMon] [tinyint] NULL,
	[GenDay] [tinyint] NULL,
	[Used] [tinyint] NULL CONSTRAINT [DF_TB_User_MyHome_Invitation_Used]  DEFAULT ((0)),
 CONSTRAINT [PK_TB_User_MyHome_Invitation] PRIMARY KEY NONCLUSTERED 
(
	[CardGuid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[TB_User_MyHome_Invitation] ALTER COLUMN [HouseNo] [int] NOT NULL
GO
