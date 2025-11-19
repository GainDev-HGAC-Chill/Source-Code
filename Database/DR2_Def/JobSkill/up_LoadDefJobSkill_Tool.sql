USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefJobSkill_Tool]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefJobSkill_Tool]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefJobSkill_Tool]

AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT
		[f_ItemNo], 
		[f_ToolType], 
		[f_GatherType],
		[f_01Need_Skill_No], 
		[f_01Need_Skill_Expertness],
		[f_02Need_Skill_No], 
		[f_02Need_Skill_Expertness], 
		[f_03Need_Skill_No], 
		[f_03Need_Skill_Expertness],
		[f_GetCount], 
		[f_GetCount_Max], 
		[f_Option_TurnTime], 
		[f_Option_CoolTime], 
		[f_Option_User_Exhaustion],
		[f_Result_No_Min], 
		[f_Result_No_Max]
	FROM [dbo].[TB_DefJobSkill_Tool]
END

GO
