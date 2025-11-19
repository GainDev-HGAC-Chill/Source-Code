USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemSoulTransition]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefItemSoulTransition]

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefItemSoulTransition]

AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT
		[f_NationCode],
		[f_EquipType],
		[f_LevelLimit],
		[f_Rairity_Grade],
		[f_SuccessRate],
		[f_SoulItemCount],
		[f_NeedMoney],
		[f_InsuranceItemNo],
		[f_ProbabilityUpItemNo],
		[f_ProbabilityUpRate],
		[f_ProbabilityUpItemCount]
	FROM [dbo].[TB_DefItemSoulTransition]
END

GO



