USE [DR2_Def]
GO
IF  NOT EXISTS (SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'TB_DefMission_ClassReward'))
BEGIN
	/****** ��ü:  Table [dbo].[TB_DefMission_ClassReward]    ��ũ��Ʈ ��¥: 10/26/2009 18:50:05 ******/
	SET ANSI_NULLS ON
	SET QUOTED_IDENTIFIER ON
	CREATE TABLE [dbo].[TB_DefMission_ClassReward](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[Memo] [nchar](50) COLLATE Korean_Wansung_CI_AS NULL,
		[MissionNo] [int] NOT NULL,
		[LevelNo] [int] NOT NULL,
		[ClassNo] [int] NOT NULL,
		[ItemNo] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_ClassReward_ItemNo]  DEFAULT ((0)),
		[Rate] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_ClassReward_Rate]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_DefMission_ClassReward] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMission_ClassReward]') AND [name] = N'LevelNo')
BEGIN
	ALTER TABLE dbo.TB_DefMission_ClassReward
		DROP CONSTRAINT DF_TB_DefMission_ClassReward_LevelNo
	ALTER TABLE dbo.TB_DefMission_ClassReward
		DROP CONSTRAINT DF_TB_DefMission_ClassReward_ClassNo
	ALTER TABLE dbo.TB_DefMission_ClassReward
		DROP CONSTRAINT DF_TB_DefMission_ClassReward_ItemBagNo

	ALTER TABLE dbo.TB_DefMission_ClassReward
		DROP COLUMN LevelNo, ClassNo, ItemBagNo
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMission_ClassReward]') and [name] = N'Rate')
BEGIN
	ALTER TABLE [dbo].[TB_DefMission_ClassReward] ADD [LevelNo] [nchar](50) NOT NULL CONSTRAINT [DF_TB_DefMission_ClassReward_LevelNo]DEFAULT N'0'	
	ALTER TABLE [dbo].[TB_DefMission_ClassReward] ADD [ClassNo] [nchar](50) NOT NULL CONSTRAINT [DF_TB_DefMission_ClassReward_ClassNo]DEFAULT N'0'
	ALTER TABLE [dbo].[TB_DefMission_ClassReward] ADD [ItemBagNo] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_ClassReward_ItemBagNo] DEFAULT (0)
	ALTER TABLE [dbo].[TB_DefMission_ClassReward] ADD [Rate] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_ClassReward_Rate] DEFAULT (0)
END

GO

