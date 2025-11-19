USE [DR2_Local]
GO

/****** Object:  StoredProcedure [dbo].[up_LoadDefJumpingCharEvent]    Script Date: 01/10/2012 11:17:28 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefJumpingCharEvent]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefJumpingCharEvent]
GO

CREATE PROCEDURE [dbo].[up_LoadDefJumpingCharEvent]
AS
BEGIN

	SELECT [EventNo],[StartTime],[EndTime],[LevelLimit],[MaxRewardCount],[RewardGroupNo]
	FROM [TB_JumpingCharEvent]

	SELECT [RewardGroupNo],[Class],[Level],[MapNo],[IngQuest],[EndQuest],[EndQuest2],[EndQuestExt],[EndQuestExt2],[ItemGroupNo]
	FROM [TB_JumpingCharEvent_Reward]

END
GO

