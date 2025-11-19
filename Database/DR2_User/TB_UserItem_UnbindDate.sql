USE [DR2_User]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserItem_UnbindDate]'))
BEGIN

/****** Object:  Table [dbo].[TB_UserItem_UnbindDate]    Script Date: 03/06/2009 21:03:32 ******/
CREATE TABLE [dbo].[TB_UserItem_UnbindDate](
	[CharacterGuid] [uniqueidentifier] NOT NULL,
	[ItemGuid] [uniqueidentifier] NOT NULL,
	[UnbindDate] [datetime] NOT NULL
) ON [PRIMARY]

END 

IF NOT EXISTS (SELECT * FROM sys.indexes WHERE [NAME] = N'IX_TB_UserItem_UnbindDate')
BEGIN

CREATE NONCLUSTERED INDEX [IX_TB_UserItem_UnbindDate] ON [dbo].[TB_UserItem_UnbindDate] ([CharacterGuid])

END

GO

CREATE NONCLUSTERED INDEX [IX_TB_UserItem_UnbindDate_ItemGuid] ON [dbo].[TB_UserItem_UnbindDate] ([ItemGuid])
GO