USE [DR2_Def]
GO

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefMissionLevels]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefMissionLevels]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefMissionLevels]
AS
begin
	SELECT     
		[MissionNo],
		[MissionKey],   
		[Level01],
		[Level01_AbilRateBagID],
		[Level01_ResultTableNo],
		[TB_DefMission_LevelLimit].[Level01_Min],
		[TB_DefMission_LevelLimit].[Level01_Max],
		[TB_DefMission_LevelLimit].[Level01_Avg_Min],
		[TB_DefMission_LevelLimit].[Level01_Avg_Max],
		[Level02],
		[Level02_AbilRateBagID],    
		[Level02_ResultTableNo],
		[TB_DefMission_LevelLimit].[Level02_Min],
		[TB_DefMission_LevelLimit].[Level02_Max],
		[TB_DefMission_LevelLimit].[Level02_Avg_Min],
		[TB_DefMission_LevelLimit].[Level02_Avg_Max],
		[Level03],
		[Level03_AbilRateBagID],
		[Level03_ResultTableNo], 
		[TB_DefMission_LevelLimit].[Level03_Min],
		[TB_DefMission_LevelLimit].[Level03_Max],
		[TB_DefMission_LevelLimit].[Level03_Avg_Min],
		[TB_DefMission_LevelLimit].[Level03_Avg_Max],    
		[Level04],     	
		[Level04_AbilRateBagID],
		[Level04_ResultTableNo],
		[TB_DefMission_LevelLimit].[Level04_Min],
		[TB_DefMission_LevelLimit].[Level04_Max],
		[TB_DefMission_LevelLimit].[Level04_Avg_Min],
		[TB_DefMission_LevelLimit].[Level04_Avg_Max],
		[HiddenLevel01],
		[HiddenLevel01_AbilRateBagID],
		[HiddenLevel01_ResultTableNo],
		[TB_DefMission_LevelLimit].[HiddenLevel01_Min],
		[TB_DefMission_LevelLimit].[HiddenLevel01_Max],
		[TB_DefMission_LevelLimit].[HiddenLevel01_Avg_Min],
		[TB_DefMission_LevelLimit].[HiddenLevel01_Avg_Max],
		[HiddenLevel02],
		[HiddenLevel02_AbilRateBagID],
		[HiddenLevel02_ResultTableNo],
		[TB_DefMission_LevelLimit].[HiddenLevel02_Min],
		[TB_DefMission_LevelLimit].[HiddenLevel02_Max],
		[TB_DefMission_LevelLimit].[HiddenLevel02_Avg_Min],
		[TB_DefMission_LevelLimit].[HiddenLevel02_Avg_Max],
		[Level_Defence],
		[Level_Defence7],
		[Level_Defence8]

		FROM [dbo].[TB_DefMission_LevelRoot] LEFT OUTER JOIN [dbo].[TB_DefMission_LevelLimit]
		ON [dbo].[TB_DefMission_LevelRoot].[LevelLimitTableNo] = [dbo].[TB_DefMission_LevelLimit].[No]
end

GO






