USE DR2_Def

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

ALTER Proc [dbo].[up_LoadDefMissionResult2]
AS

begin
	select [f_ResultNo], [f_RankSSS], [f_RankSS], [f_RankS], [f_RankA], [f_RankB], [f_RankC], [f_RankD], [f_RankE], [f_RankF],
	f_RouletteBagGrpNo,
	f_ResultCountMinSSS,
	f_ResultCountMaxSSS,
	f_ResultCountMinSS,
	f_ResultCountMaxSS,
	f_ResultCountMinS,
	f_ResultCountMaxS,
	f_ResultCountMinA,
	f_ResultCountMaxA,
	f_ResultCountMinB,
	f_ResultCountMaxB,
	f_ResultCountMinC,
	f_ResultCountMinC,
	f_ResultCountMaxD,
	f_ResultCountMinD,
	f_ResultCountMaxE,
	f_ResultCountMaxE,
	f_ResultCountMaxF,
	f_ResultCountMaxF
		FROM [dbo].[TB_DefMission_Result]
end
GO