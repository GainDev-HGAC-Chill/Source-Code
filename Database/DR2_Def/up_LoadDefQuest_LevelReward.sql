USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefQuest_LevelReward]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefQuest_LevelReward]
GO

CREATE PROCEDURE [dbo].[up_LoadDefQuest_LevelReward]
AS
BEGIN
	SET NOCOUNT ON;

	SELECT 	iLevel,
	iLevelPerExp,
	iLevelPerMoney
	FROM [dbo].[TB_DefQuest_LevelReward]
	WITH(NOLOCK)
END