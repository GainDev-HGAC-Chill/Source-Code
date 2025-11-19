USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SelectMissionGroundCount]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_SelectMissionGroundCount]
END 

/****** Object:  StoredProcedure [dbo].[up_SelectMissionGroundCount]    Script Date: 04/01/2009 19:15:25 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_SelectMissionGroundCount]

@MissionNo int

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DECLARE @L1 int,@L2 INT ,@L3 INT ,@L4 INT ,@L5 INT ,@L6 INT
	
	SELECT 
	@L1 = Level01,
	@L2 = Level02,
	@L3 = Level03,
	@L4 = Level04,
	@L5 = HiddenLevel01,
	@L6 = HiddenLevel02 FROM [dbo].[TB_DefMission_LevelRoot] WHERE MissionNo = @MissionNo

	CREATE TABLE #TMPTABLE([Candidate_End] INT)
	CREATE TABLE #TMPTABLE2([Candidate_End] INT)

	INSERT INTO #TMPTABLE SELECT [Candidate_End] FROM dbo.TB_DefMission_LevelCandidate WHERE LevelNo = @L1 OR LevelNo = @L2 OR LevelNo = @L3 OR LevelNo = @L4 OR LevelNo = @L5 OR LevelNo = @L6 GROUP BY [Candidate_End]
	INSERT INTO #TMPTABLE SELECT [Candidate01] FROM dbo.TB_DefMission_LevelCandidate WHERE LevelNo = @L1 OR LevelNo = @L2 OR LevelNo = @L3 OR LevelNo = @L4 OR LevelNo = @L5 OR LevelNo = @L6 GROUP BY [Candidate01]
	INSERT INTO #TMPTABLE SELECT [Candidate02] FROM dbo.TB_DefMission_LevelCandidate WHERE LevelNo = @L1 OR LevelNo = @L2 OR LevelNo = @L3 OR LevelNo = @L4 OR LevelNo = @L5 OR LevelNo = @L6 GROUP BY [Candidate02]
	INSERT INTO #TMPTABLE SELECT [Candidate03] FROM dbo.TB_DefMission_LevelCandidate WHERE LevelNo = @L1 OR LevelNo = @L2 OR LevelNo = @L3 OR LevelNo = @L4 OR LevelNo = @L5 OR LevelNo = @L6 GROUP BY [Candidate03]
	INSERT INTO #TMPTABLE SELECT [Candidate04] FROM dbo.TB_DefMission_LevelCandidate WHERE LevelNo = @L1 OR LevelNo = @L2 OR LevelNo = @L3 OR LevelNo = @L4 OR LevelNo = @L5 OR LevelNo = @L6 GROUP BY [Candidate04]
	INSERT INTO #TMPTABLE SELECT [Candidate05] FROM dbo.TB_DefMission_LevelCandidate WHERE LevelNo = @L1 OR LevelNo = @L2 OR LevelNo = @L3 OR LevelNo = @L4 OR LevelNo = @L5 OR LevelNo = @L6 GROUP BY [Candidate05]
	INSERT INTO #TMPTABLE SELECT [Candidate06] FROM dbo.TB_DefMission_LevelCandidate WHERE LevelNo = @L1 OR LevelNo = @L2 OR LevelNo = @L3 OR LevelNo = @L4 OR LevelNo = @L5 OR LevelNo = @L6 GROUP BY [Candidate06]
	INSERT INTO #TMPTABLE SELECT [Candidate07] FROM dbo.TB_DefMission_LevelCandidate WHERE LevelNo = @L1 OR LevelNo = @L2 OR LevelNo = @L3 OR LevelNo = @L4 OR LevelNo = @L5 OR LevelNo = @L6 GROUP BY [Candidate07]
	INSERT INTO #TMPTABLE SELECT [Candidate08] FROM dbo.TB_DefMission_LevelCandidate WHERE LevelNo = @L1 OR LevelNo = @L2 OR LevelNo = @L3 OR LevelNo = @L4 OR LevelNo = @L5 OR LevelNo = @L6 GROUP BY [Candidate08]
	
	INSERT INTO #TMPTABLE2 SELECT [Candidate_End] FROM #TMPTABLE WHERE Candidate_End <> 0 GROUP BY [Candidate_End]
	SELECT COUNT(*) AS [TOTAL COUNT],@MissionNo AS MISSIONNO FROM #TMPTABLE2
	
	DROP TABLE #TMPTABLE
	DROP TABLE #TMPTABLE2


END
