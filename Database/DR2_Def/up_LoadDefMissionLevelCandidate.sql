USE DR2_Def
Go

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefMissionLevelCandidate]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefMissionLevelCandidate]
GO

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

CREATE PROCEDURE [dbo].[up_LoadDefMissionLevelCandidate]
AS
begin
	SELECT [LevelNo], [Type],	[USE], [Candidate_End],
		[Candidate01], [Candidate02], [Candidate03], [Candidate04],	[Candidate05],	[Candidate06], [Candidate07],	[Candidate08], 
		[RankSSS_Point], [RankSS_Point], [RankS_Point], [RankA_Point], [RankB_Point], [RankC_Point],	[RankD_Point], [RankE_Point],
		[MonsterTunningNo]
		FROM [dbo].[TB_DefMission_LevelCandidate] WITH(NOLOCK)
end
go



