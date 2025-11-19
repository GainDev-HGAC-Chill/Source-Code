USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBS_PtReward]') AND [type] = N'U')
BEGIN
	CREATE TABLE [dbo].[TB_DefBS_PtReward] (
		[f_IDX] [int] IDENTITY(1,1) NOT NULL,
		[f_BS_GAME_IDX] [int] NOT NULL,
		[f_PointMin] [int] NOT NULL,
		[f_ItemNo1] [int] NOT NULL,
		[f_ItemCount1] [int] NOT NULL,
		[f_ItemNo2] [int] NOT NULL,
		[f_ItemCount2] [int] NOT NULL,
		[f_Memo] [nvarchar](50) NULL,
	 CONSTRAINT [IX_TB_DefBS_PtReward] UNIQUE CLUSTERED 
	(
		[f_BS_GAME_IDX] ASC,
		[f_PointMin] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

GO

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBS_PtReward]') and name = N'f_BS_GAME_IDX')
BEGIN
	exec sp_rename N'[dbo].[TB_DefBS_PtReward].f_BS_GAME_IDX', N'Tmp_f_BS_GAME_IDX', N'COLUMN'
	exec sp_rename N'[dbo].[TB_DefBS_PtReward].Tmp_f_BS_GAME_IDX', N'f_PtRewardIdx', N'COLUMN'
END