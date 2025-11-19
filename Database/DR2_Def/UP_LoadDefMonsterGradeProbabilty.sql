USE DR2_Def
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_LoadDefMonsterGradeProbabilty]') and [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_LoadDefMonsterGradeProbabilty]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2010-02-26
-- Description:	
-- =============================================
CREATE PROCEDURE dbo.[UP_LoadDefMonsterGradeProbabilty]
AS
BEGIN
	SET NOCOUNT ON;

	SELECT
	[f_Probablity_Group]
	,[f_Probabilty]
	,[f_MonsterEnchant_Grade]
	FROM [dbo].[TB_DefMonsterGradeProbabilty]
END
GO
