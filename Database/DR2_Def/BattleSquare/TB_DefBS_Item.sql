USE [DR2_Def]
GO

/******* ************/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefBS_Item]') AND [type] = N'U')
BEGIN
	CREATE TABLE [dbo].[TB_DefBS_Item](
		[f_IDX] [int] IDENTITY(1,1) NOT NULL,
		[f_ItemNo] [int] NOT NULL,
		[f_EffectNo1] [int] NOT NULL,
		[f_EffectNo2] [int] NOT NULL,
		[f_EffectNo3] [int] NOT NULL,
		[f_MinimapIconNo] [int] NOT NULL,
		[f_Memo] [nvarchar](50) NULL,
	 CONSTRAINT [IX_TB_DefBS_Item] UNIQUE CLUSTERED 
	(
		[f_ItemNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
GO