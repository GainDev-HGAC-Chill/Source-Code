USE DR2_Def

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMission_LevelCandidate]') AND [name] = N'RankSSS_Point')
BEGIN
	ALTER TABLE [dbo].[TB_DefMission_LevelCandidate] ADD
	[RankSSS_Point] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_LevelCandidate_RankSSS_Point] DEFAULT ((0)),
	[RankSS_Point] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_LevelCandidate_RankSS_Point] DEFAULT ((0))
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMission_LevelCandidate]') AND [name] = N'MonsterTunningNo')
BEGIN
	ALTER TABLE [dbo].[TB_DefMission_LevelCandidate] ADD
	[MonsterTunningNo] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_LevelCandidate_MonsterTunningNo] DEFAULT ((0))
END

GO
