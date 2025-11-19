USE DR2_Def
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_LoadDefSuperGround]') AND type IN (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_LoadDefSuperGround]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2009-02-06
-- Description:	
-- =============================================
CREATE PROCEDURE dbo.[UP_LoadDefSuperGround]
AS
BEGIN
	SET NOCOUNT ON;

    SELECT
		[f_iSuperGroundNo]
		,[f_iGroundNo]
		,[f_iOrderNo]
		,[f_Level1_MonsterEnchantGroupNo]
		,[f_Level2_MonsterEnchantGroupNo]
		,[f_Level3_MonsterEnchantGroupNo]
		,[f_Level1_ItemRairityNo]
		,[f_Level2_ItemRairityNo]
		,[f_Level3_ItemRarityNo]
		,[f_Level1_ItemEnchantControlNo]
		,[f_Level2_ItemEnchantControlNo]
		,[f_Level3_ItemEnchantControlNo]
		,[f_Level1_BossItemContainerNo]
		,[f_Level2_BossItemContainerNo]
		,[f_Level3_BossItemContainerNo]
	FROM [dbo].[TB_DefSuperGround]
END
GO
