USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemEnchant]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefItemEnchant]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE Proc [dbo].[up_LoadDefItemEnchant]
AS

BEGIN

	SELECT [TypeNo], [Level], [NameNo], 
		[Abil01], [Abil02], [Abil03], [Abil04], [Abil05], 
		[Abil06], [Abil07], [Abil08], [Abil09], [Abil10]
		FROM [dbo].[TB_DefItemEnchant] WITH(NOLOCK)
		
	SELECT [TypeNo], [Level], [NameNo], 
		[Abil01], [Abil02], [Abil03], [Abil04], [Abil05], 
		[Abil06], [Abil07], [Abil08], [Abil09], [Abil10]
		FROM [dbo].[TB_DefItemEnchant_Pet] WITH(NOLOCK)

	SELECT EnchantLv,Weight FROM [dbo].[TB_DefItemEnchantAbilWeight] WITH(NOLOCK)

END
