USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefItemByLevel]') AND type in (N'U'))
BEGIN

	CREATE TABLE [dbo].[TB_DefPvPRewardItem](
		[ID] [int] NOT NULL,
		[Memo] [nvarchar](100) NULL,
		[GiveItem_Win] [tinyint] NULL,
		[GiveItem_Draw] [tinyint] NULL,
		[GiveItem_Lose] [tinyint] NULL,
		[ItemBagNo_Win] [int] NULL,
		[ItemBagNo_Draw] [int] NULL,
		[ItemBagNo_Lose] [int] NULL,
	CONSTRAINT [UC_TB_DefPvPRewardItem] UNIQUE CLUSTERED 
	(
		[ID] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
	
END
ELSE
BEGIN
	
	ALTER TABLE [dbo].[TB_DefPvPRewardItem]
	DROP COLUMN [ItemBagNo]
	
	ALTER TABLE [dbo].[TB_DefPvPRewardItem]
	ADD [ItemBagNo_Win] [int] NULL
	
	ALTER TABLE [dbo].[TB_DefPvPRewardItem]
	ADD [ItemBagNo_Draw] [int] NULL
	
	ALTER TABLE [dbo].[TB_DefPvPRewardItem]
	ADD [ItemBagNo_Lose] [int] NULL
END
GO
