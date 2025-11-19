USE [DR2_Def]
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.UP_LoadDefEventItemSet') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.UP_LoadDefEventItemSet
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2010-01-20
-- Description:	
-- =============================================
CREATE PROCEDURE dbo.UP_LoadDefEventItemSet
AS
BEGIN
	SET NOCOUNT ON;

	SELECT 
		[f_EventItemSetID]
		,[f_IsUse]
		,[f_IsAbsoluteCount]
		,[f_EquipItemNo]
		,[f_EquipItemCount]
		,[f_RewardEffectNo1]
		,[f_RewardEffectNo2]
		,[f_RewardEffectNo3]
	FROM [dbo].[TB_DefEventItemSet]
END
GO
