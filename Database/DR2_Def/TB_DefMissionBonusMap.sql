USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMissionBonusMap]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefMissionBonusMap](
		[LevelNo] [int] NOT NULL CONSTRAINT [DF_TB_DefMissionBonusMap_LevelNo] DEFAULT ((0)),
		[Use] [int] NOT NULL CONSTRAINT [DF_TB_DefMissionBonusMap_Use] DEFAULT ((0)),
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,		
		[TimeLimit] [int] NOT NULL CONSTRAINT [DF_TB_DefMissionBonusMap_TimeLimit] DEFAULT ((0)),
		[ChanceRate] [int] NOT NULL CONSTRAINT [DF_TB_DefMissionBonusMap_ChanceRate] DEFAULT ((0)),
		[Bonus1stMapRate] [int] NOT NULL CONSTRAINT [DF_TB_DefMissionBonusMap_Bonus1stMapRate] DEFAULT ((0)),
		[BonusMap1] [int] NOT NULL CONSTRAINT [DF_TB_DefMissionBonusMap_BonusMap1] DEFAULT ((0)),
		[BonusMap2] [int] NOT NULL CONSTRAINT [DF_TB_DefMissionBonusMap_BonusMap2] DEFAULT ((0))
		
	CONSTRAINT [PK_TB_DefMissionBonusMap] PRIMARY KEY CLUSTERED 
	(
		[LevelNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

GO

