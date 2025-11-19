USE [DR2_Local]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefSpecificRewardEvent]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefSpecificRewardEvent]
GO

CREATE PROCEDURE [dbo].[up_LoadDefSpecificRewardEvent]
AS

BEGIN
	SELECT [EventNo]
      ,[EventStartTime]
      ,[EventEndTime]
      ,[LevelLimit]
      ,[DraLevelLimit]
      ,[RewardCount]
      ,[RewardPeriod]
      ,[RewardItemGroupNo]
  FROM [dbo].[TB_DefEventSpecificReward]
END
