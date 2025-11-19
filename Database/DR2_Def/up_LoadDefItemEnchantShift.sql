USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemEnchantShift]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefItemEnchantShift]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[up_LoadDefItemEnchantShift]
AS

BEGIN

	SELECT [f_NationCode],[EquipType], [LevelLimit], [EnchnatGrade],
		[EnchantItemNo], [EnchantItemCount], [NeedMoney], [EnchantShiftGemNo], [EnchantShiftGemCount], [InsuranceItemNo],
		[EnchantShiftRatePlus2], 
		[EnchantShiftRatePlus1], 
		[EnchantShiftRateSame], 
		[EnchantShiftRateMinus1], 
		[EnchantShiftRateMinus2], 
		[EnchantShiftRateDelete]
		FROM [dbo].[TB_DefItemEnchantShift] WITH(NOLOCK)

END
