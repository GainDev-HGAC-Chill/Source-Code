USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefJobSkill_Skill]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefJobSkill_Skill]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefJobSkill_Skill]

AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT [f_SkillNo], [f_GatherType], [f_JobSkill_Type], [f_01NeedParent_JobSkill_No], [f_01NeedParent_JobSkill_Expertness], [f_02NeedParent_JobSkill_No], [f_02NeedParent_JobSkill_Expertness],
		[f_03NeedParent_JobSkill_No], [f_03NeedParent_JobSkill_Expertness]
	FROM [dbo].[TB_DefJobSkill_Skill]
END

GO
