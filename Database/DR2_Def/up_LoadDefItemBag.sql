USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemBag]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefItemBag]
GO

CREATE PROCEDURE [dbo].[up_LoadDefItemBag]
AS
BEGIN
	SELECT
			[f_NationCodeStr]
		,	[BagNo]
		,	[Level]
		,	[ElementsNo]
		,	[SuccessRateControlNo]
		,	[CountControlNo]
		,	[DropMoneyControlNo]
	FROM [dbo].[TB_DefItemBag] WITH(NOLOCK)
END
GO
