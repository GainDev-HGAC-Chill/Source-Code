USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_User_MyHome_EquipItem]    Script Date: 08/12/2009 13:30:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_User_MyHome_EquipItem](
	[ItemGuid] [uniqueidentifier] NOT NULL,
	[x] [float] NOT NULL,
	[y] [float] NOT NULL,
	[z] [float] NOT NULL,
	[Dir] [smallint] NOT NULL,
	[ParentGuid] [uniqueidentifier] NULL,
	[LinkIdx] [tinyint] NULL,
 CONSTRAINT [PK_TB_User_MyHome_Equip] PRIMARY KEY CLUSTERED 
(
	[ItemGuid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
