USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_UserItem_MonsterCard]    Script Date: 09/28/2009 18:50:03 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_UserItem_MonsterCard](
	[ItemGuid] [uniqueidentifier] NOT NULL,
	[LimitTime] [datetime] NULL,
 CONSTRAINT [PK_TB_UserItem_MonsterCard] PRIMARY KEY CLUSTERED 
(
	[ItemGuid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
