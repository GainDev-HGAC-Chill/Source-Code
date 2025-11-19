USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_User_Myhome_SideJob]    Script Date: 12/10/2009 16:50:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_User_Myhome_SideJob](
	[OwnerGuid] [uniqueidentifier] NOT NULL,
	[SideJob] [int] NOT NULL,
	[EndDate] [datetime] NULL,
	[SellCost] [bigint] NULL,
	[JobType] [int] NULL,
	[JobRate] [int] NULL,
 CONSTRAINT [PK_TB_User_Myhome_SideJob] PRIMARY KEY CLUSTERED 
(
	[OwnerGuid] ASC,
	[SideJob] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]

CREATE NONCLUSTERED INDEX [IX_TB_User_Myhome_SideJob] ON [dbo].[TB_User_Myhome_SideJob] ([OwnerGuid])
GO