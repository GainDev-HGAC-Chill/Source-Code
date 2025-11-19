USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefJobSkill_SkillExpertness]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefJobSkill_SkillExpertness]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefJobSkill_SkillExpertness]

AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT [f_SkillNo], [f_Skill_Expertness_Min], [f_Skill_Expertness_Max], [f_Expertness_Gain_Min], [f_Expertness_Gain_Max], [f_Expertness_Gain_Probability], [f_Expertness_Gain_TotalProbability],
		[f_Use_Duration], [f_Use_Duration_Probability], [f_Use_Duration_TotalProbability], [f_Basic_Turn_Time], [f_Max_Exgaustion], [f_Use_Exgaustion], [f_Max_Machine], [f_Need_CharLevel]
		,[f_Skill_Probaility]
	FROM [dbo].[TB_DefJobSkill_SkillExpertness]
END

GO
