USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefDefenceStage]') AND type in (N'U'))
BEGIN

	CREATE TABLE [dbo].[TB_DefDefenceStage](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[MissionNo] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceStage_MissionNo] DEFAULT ((0)),
		[Party_Number] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceStage_Party_Number] DEFAULT ((0)),
		[Stage_No] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceStage_Stage_No] DEFAULT ((0)),
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,		
		[Stage_Time] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceStage_Stage_Time] DEFAULT ((0)),
		[Wave_GroupNo] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceStage_Wave_GroupNo] DEFAULT ((0)),
		[AddMonster_GroupNo] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceStage_AddMonster_GroupNo] DEFAULT ((0)),
		[TimeToExp_Rate] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceStage_TimeToExp_Rate] DEFAULT ((0)),
		[ResultNo] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceStage_ResultNo] DEFAULT ((0)),
		[ResultCount] [int] NOT NULL CONSTRAINT [DF_TB_DefDefenceStage_ResultCount] DEFAULT ((0))
	CONSTRAINT [PK_TB_DefDefenceStage] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
GO


IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME='TB_DefDefenceStage' AND COLUMN_NAME='Direction_Item')
BEGIN
	ALTER TABLE [dbo].[TB_DefDefenceStage] ADD [Direction_Item] int NOT NULL DEFAULT ((0))
END
GO