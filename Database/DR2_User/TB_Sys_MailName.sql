USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_Sys_MailName]    Script Date: 12/21/2009 14:29:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_Sys_MailName](
	[NameGuid] [uniqueidentifier] NOT NULL,
	[MailName] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
 CONSTRAINT [PK_TB_Sys_MailName] PRIMARY KEY CLUSTERED 
(
	[NameGuid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
