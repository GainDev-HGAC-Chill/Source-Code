USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemSoulExtract]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefItemSoulExtract]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefItemSoulExtract]

AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT
		[f_EquipPos],
		[f_LevelLimit],
		[f_SuccessRate],
		[f_ExtractItemNo],
		[f_ResultItemNo]
	FROM [dbo].[TB_DefItemSoulExtract]
END
GO