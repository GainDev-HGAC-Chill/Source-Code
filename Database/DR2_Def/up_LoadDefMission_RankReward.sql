USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefMission_RankReward]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefMission_RankReward]
END
GO

/****** 개체:  StoredProcedure [dbo].[up_LoadDefMission_RankReward]    스크립트 날짜: 10/28/2009 16:05:47 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefMission_RankReward]

AS
BEGIN
	SELECT [MissionNo],[LevelNo],[RankNo],[ItemNo],[Rate],[Count]
	FROM [dbo].[TB_DefMission_RankReward] WITH(NOLOCK)

END

GO
