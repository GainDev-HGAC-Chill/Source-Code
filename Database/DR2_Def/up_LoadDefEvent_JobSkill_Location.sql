USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_DefEvent_JobSkill_Location]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_DefEvent_JobSkill_Location]
GO

CREATE Proc [dbo].[up_DefEvent_JobSkill_Location]
AS

BEGIN
	SELECT 
	[f_NationCodeStr],
	[Start_Date], 
	[End_Date], 
	[f_JobGrade], 
	[RewardItemGroup], 
	[Rate] 
	from [dbo].[TB_DefEvent_JobSkill_Location] WITH(NOLOCK)
END
