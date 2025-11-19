USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_GroupMailRecvedCharacter]    Script Date: 11/30/2009 19:20:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_GroupMailRecvedCharacter](
	[CharGuid] [uniqueidentifier] NOT NULL,
	[GroupMailGuid] [uniqueidentifier] NOT NULL,
 CONSTRAINT [PK_TB_GroupMailRecvedCharacter] PRIMARY KEY CLUSTERED 
(
	[CharGuid] ASC,
	[GroupMailGuid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]

CREATE NONCLUSTERED INDEX [IX_TB_GroupMailRecvedCharacter] ON [dbo].[TB_GroupMailRecvedCharacter] ([CharGuid])
GO
CREATE NONCLUSTERED INDEX [IX_TB_GroupMailRecvedCharacter_1] ON [dbo].[TB_GroupMailRecvedCharacter] ([GroupMailGuid])
GO