USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefJobSkill_LocationItem]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefJobSkill_LocationItem]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefJobSkill_LocationItem]

AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT  [f_JobGrade], 
			[f_GatherType], 
			[f_Spot_Probability], 
			[f_Spot_TotalProbability], 
			[f_Spot_Cycle_Min], 
			[f_Spot_Cycle_Max], 
			[f_Spot_Duration_Min], 
			[f_Spot_Duration_Max],
			[f_01ResultProbability_No], 
			[f_02ResultProbability_No], 
			[f_03ResultProbability_No], 
			[f_04ResultProbability_No], 
			[f_05ResultProbability_No], 
			[f_06ResultProbability_No],
			[f_07ResultProbability_No], 
			[f_08ResultProbability_No], 
			[f_09ResultProbability_No], 
			[f_10ResultProbability_No], 
			[f_Base_Expertness], 
			[f_01Need_SaveIdx], 
			[f_02Need_SaveIdx], 
			[f_03Need_SaveIdx], 
			[f_01Need_Skill_No], 
			[f_01Need_Expertness], 
			[f_02Need_Skill_No], 
			[f_02Need_Expertness], 
			[f_03Need_Skill_No], 
			[f_03Need_Expertness], 
			[f_Probability_UpRate]
	FROM [dbo].[TB_DefJobSkill_LocationItem]
END

GO




