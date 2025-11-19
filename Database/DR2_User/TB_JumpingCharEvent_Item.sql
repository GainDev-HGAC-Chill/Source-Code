USE [DR2_User]
GO

/****** Object:  Table [dbo].[TB_JumpingCharEvent_Item]    Script Date: 01/10/2012 11:17:02 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_JumpingCharEvent_Item]') AND type in (N'U'))
BEGIN

	CREATE TABLE [dbo].[TB_JumpingCharEvent_Item](
		[ItemGroupNo] [int] NOT NULL,
		[InvType] [tinyint] NOT NULL,
		[InvPos] [tinyint] NOT NULL,
		[ItemNo] [int] NOT NULL,
		[Count] [smallint] NOT NULL,
		[Enchant_01] [bigint] NOT NULL DEFAULT ((0)),
		[Enchant_02] [bigint] NOT NULL DEFAULT ((0)),
		[Enchant_03] [bigint] NOT NULL DEFAULT ((0)),
		[Enchant_04] [bigint] NOT NULL DEFAULT ((0)),
		[State] [tinyint] NOT NULL DEFAULT ((0))
	) ON [PRIMARY]

END
GO


IF EXISTS(SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'dbo.TB_JumpingCharEvent_Item') and [name] = N'PK_TB_JumpCharEvent_Item')
BEGIN
ALTER TABLE dbo.TB_JumpingCharEvent_Item
	DROP CONSTRAINT PK_TB_JumpCharEvent_Item
END
GO