USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_ExpCard]    Script Date: 07/01/2009 14:16:03 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_ExpCard](
	[ItemGuid] [uniqueidentifier] NOT NULL,
	[CurExp] [bigint] NOT NULL,
	[MaxExp] [bigint] NOT NULL,
 CONSTRAINT [PK_TB_ExpCard] PRIMARY KEY CLUSTERED 
(
	[ItemGuid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[TB_ExpCard] ADD
[ExpPer] [smallint] NOT NULL CONSTRAINT [DF_TB_ExpCard_ExpPer] DEFAULT ((100))
GO