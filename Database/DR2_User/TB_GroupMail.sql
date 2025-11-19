USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_GroupMail]    Script Date: 12/22/2009 15:52:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'TB_GroupMail'))
BEGIN
CREATE TABLE [dbo].[TB_GroupMail](
	[CmdGuid] [uniqueidentifier] NOT NULL,
	[LevelMin] [int] NULL,
	[LevelMax] [int] NULL,
	[Class] [int] NULL,
	[title] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[text] [nvarchar](200) COLLATE Korean_Wansung_CI_AS NULL,
	[ItemNo] [int] NULL,
	[Count] [smallint] NULL,
	[Money] [bigint] NULL,
	[StartDate] [datetime] NULL,
	[EndDate] [datetime] NULL,
	[FromName] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL
) ON [PRIMARY]

ALTER TABLE [dbo].[TB_GroupMail] ADD FromName NVARCHAR(50) NULL

CREATE NONCLUSTERED INDEX [IX_TB_GroupMail_Class] ON [dbo].[TB_GroupMail] ([Class])
CREATE NONCLUSTERED INDEX [IX_TB_GroupMail_Guid] ON [dbo].[TB_GroupMail] ([CmdGuid])
CREATE NONCLUSTERED INDEX [IX_TB_GroupMail_Level] ON [dbo].[TB_GroupMail] ([LevelMin], [LevelMax])
CREATE NONCLUSTERED INDEX [IX_TB_GroupMail_Date] ON [dbo].[TB_GroupMail] ([StartDate], [EndDate])

IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_GroupMail]') AND name = N'PK_TB_GroupMail')
	ALTER TABLE [dbo].[TB_GroupMail] DROP CONSTRAINT [PK_TB_GroupMail]

END


IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_GroupMail]') AND [name] = N'Class' and max_length = 4)
BEGIN
	DROP INDEX [IX_TB_GroupMail_Class] ON [dbo].[TB_GroupMail]
	ALTER TABLE [dbo].[TB_GroupMail] ALTER COLUMN Class [BIGINT]
	CREATE NONCLUSTERED INDEX [IX_TB_GroupMail_Class] ON [dbo].[TB_GroupMail] ([Class])
	ALTER INDEX ALL ON [dbo].[TB_GroupMail] REBUILD WITH (PAD_INDEX = ON, FILLFACTOR = 90) 
END
GO
