USE [DR2_Def]
GO
/****** 개체:  Table [dbo].[TB_DefMonsterBagControl]    스크립트 날짜: 02/06/2010 15:39:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMonsterBagControl]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefMonsterBagControl](
		[IDX] [int] IDENTITY(1,1) NOT FOR REPLICATION NOT NULL,
		[Memo] [nchar](100) COLLATE Korean_Wansung_CI_AS NULL,
		[ParentBagNo] [int] NOT NULL,
		[DefaultBagNo] [int] NOT NULL,
		[Level01BagNo] [int] NOT NULL,
		[Level02BagNo] [int] NOT NULL,
		[Level03BagNo] [int] NOT NULL,
		[Level04BagNo] [int] NOT NULL,
		[Level05BagNo] [int] NOT NULL CONSTRAINT [DF_TB_DefMonsterBagControl_Level05BagNo]  DEFAULT ((0)),
		[Level06BagNo] [int] NOT NULL CONSTRAINT [DF_TB_DefMonsterBagControl_Level06BagNo]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_DefMonsterBagControl] PRIMARY KEY CLUSTERED 
	(
		[ParentBagNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

IF NOT EXISTS (SELECT * FROM sys.all_objects WHERE NAME = 'DF_TB_DefMonsterBagControl_Level07BagNo')
BEGIN
	ALTER TABLE [dbo].[TB_DefMonsterBagControl] ADD
		[Level07BagNo] [int] NOT NULL CONSTRAINT [DF_TB_DefMonsterBagControl_Level07BagNo] DEFAULT ((0))
END

IF NOT EXISTS (SELECT * FROM sys.all_objects WHERE NAME = 'DF_TB_DefMonsterBagControl_Level08BagNo')
BEGIN
	ALTER TABLE [dbo].[TB_DefMonsterBagControl] ADD
		[Level08BagNo] [int] NOT NULL CONSTRAINT [DF_TB_DefMonsterBagControl_Level08BagNo] DEFAULT ((0))
END

IF NOT EXISTS (SELECT * FROM sys.all_objects WHERE NAME = 'DF_TB_DefMonsterBagControl_Level09BagNo')
BEGIN
	ALTER TABLE [dbo].[TB_DefMonsterBagControl] ADD
		[Level09BagNo] [int] NOT NULL CONSTRAINT [DF_TB_DefMonsterBagControl_Level09BagNo] DEFAULT ((0))
END

GO
