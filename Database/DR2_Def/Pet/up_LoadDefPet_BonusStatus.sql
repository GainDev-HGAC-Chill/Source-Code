USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefPet_BonusStatus]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefPet_BonusStatus]
GO

CREATE PROCEDURE [dbo].[up_LoadDefPet_BonusStatus]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명: [dbo].[up_LoadDefPet_BonusStatus]
// 작성자: YonMy(yonmy@barunsoninter.com)
// 작성일: 2009-06-22
// 파일명: 
////////////////////////////////////////////////////////////////////////
*/ 
AS
SET Nocount On;
BEGIN
	SELECT	[ID]
		,	[Select_Rate]
		,	[ItemOpt2_OptionType_01]
		,	[ItemOpt2_Rate_01]
		,	[ItemOpt2_OptionType_02]
		,	[ItemOpt2_Rate_02]
		,	[ItemOpt2_OptionType_03]
		,	[ItemOpt2_Rate_03]
		,	[ItemOpt2_OptionType_04]
		,	[ItemOpt2_Rate_04]
		,	[ItemOpt2_OptionType_05]
		,	[ItemOpt2_Rate_05]
		,	[ItemOpt2_ValueLv1_Rate]
		,	[ItemOpt2_ValueLv2_Rate]
		,	[ItemOpt2_ValueLv3_Rate]
		,	[ItemOpt2_ValueLv4_Rate]
		,	[ItemOpt2_ValueLv5_Rate]
		,	[ItemOpt2_ValueLv6_Rate]
		,	[ItemOpt2_ValueLv7_Rate]
		,	[ItemOpt2_ValueLv8_Rate]
		,	[ItemOpt2_ValueLv9_Rate]
		,	[ItemOpt2_ValueLv10_Rate]
		,	[ItemOpt2_ValueLv11_Rate]
		,	[ItemOpt2_ValueLv12_Rate]
		,	[ItemOpt2_ValueLv13_Rate]
		,	[ItemOpt2_ValueLv14_Rate]
		,	[ItemOpt2_ValueLv15_Rate]
		,	[ItemOpt2_ValueLv16_Rate]
		,	[ItemOpt2_ValueLv17_Rate]
		,	[ItemOpt2_ValueLv18_Rate]
		,	[ItemOpt2_ValueLv19_Rate]
		,	[ItemOpt2_ValueLv20_Rate]
		,	[ItemOpt2_ValueLv21_Rate]
		,	[ItemOpt2_ValueLv22_Rate]
		,	[ItemOpt2_ValueLv23_Rate]
		,	[ItemOpt2_ValueLv24_Rate]
		,	[ItemOpt2_ValueLv25_Rate]
		,	[ItemOpt2_ValueLv26_Rate]
		,	[ItemOpt2_ValueLv27_Rate]
		,	[ItemOpt2_ValueLv28_Rate]
		,	[ItemOpt2_ValueLv29_Rate]
		,	[ItemOpt2_ValueLv30_Rate]
		,	[ItemOpt2_ValueLv31_Rate]
		FROM [dbo].[TB_DefPet_BonusStatus] WITH(NOLOCK)
END

GO


