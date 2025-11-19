USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_Member_ShareData]    Script Date: 09/18/2009 19:10:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_Member_ShareData](
	[MemberKey] [uniqueidentifier] NOT NULL,
	[ExtendCharacterNum] [tinyint] NULL,
	[ShareRentalTime1] [datetime] NULL,
	[ShareRentalTime2] [datetime] NULL,
	[ShareRentalTime3] [datetime] NULL,
	[ShareRentalTime4] [datetime] NULL,
 CONSTRAINT [PK_TB_Member_ShareData] PRIMARY KEY CLUSTERED 
(
	[MemberKey] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
