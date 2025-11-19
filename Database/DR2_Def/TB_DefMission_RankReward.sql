USE [DR2_Def]
GO
IF  NOT EXISTS (SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'TB_DefMission_RankReward'))
BEGIN
	/****** 개체:  Table [dbo].[TB_DefMission_RankReward]    스크립트 날짜: 10/28/2009 16:04:05 ******/
	SET ANSI_NULLS ON
	SET QUOTED_IDENTIFIER ON
	CREATE TABLE [dbo].[TB_DefMission_RankReward](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[Memo] [nchar](50) COLLATE Korean_Wansung_CI_AS NULL,
		[MissionNo] [int] NOT NULL,
		[LevelNo] [int] NOT NULL,
		[RankNo] [int] NOT NULL,
		[ItemNo] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_RankReward_ItemNo]  DEFAULT ((0)),
		[Rate] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_RankReward_Rate]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_DefMission_RankReward] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefMission_RankReward') and [name] = N'Count')
BEGIN
	ALTER TABLE [dbo].[TB_DefMission_RankReward] ADD
	[Count] [smallint] NOT NULL CONSTRAINT [DF_TB_DefMission_RankReward_Count] DEFAULT ((1))
END
GO