USE DR2_Def
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_LoadDefMonsterEnchantGrade]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_LoadDefMonsterEnchantGrade]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2010-02-06
-- Description:	
-- =============================================
CREATE PROCEDURE dbo.[UP_LoadDefMonsterEnchantGrade]
AS
BEGIN
	SET NOCOUNT ON;

	SELECT
	[f_MonsterEnchant_GradeNo]
	,[f_EnchantLevel]
	,[f_Prefix_Name]
	,[f_StatusEffect_ID1]
	,[f_StatusEffect_Root1]
	,[f_StatusEffect_ID2]
	,[f_StatusEffect_Root2]
	,[f_StatusEffect_ID3]
	,[f_StatusEffect_Root3]
	,[f_AddAbil01]
	,[f_AddAbil02]
	,[f_AddAbil03]
	,[f_AddAbil04]
	,[f_AddAbil05]
	,[f_AddAbil06]
	,[f_AddAbil07]
	,[f_SetAbil01]
	,[f_SetAbil02]
	,[f_SetAbil03]
	FROM [dbo].[TB_DefMonsterEnchantGrade]
END
GO
