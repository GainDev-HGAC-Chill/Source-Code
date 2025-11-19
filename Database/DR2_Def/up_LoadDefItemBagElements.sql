USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemBagElements]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefItemBagElements]
GO

CREATE Proc [dbo].[up_LoadDefItemBagElements]
AS

BEGIN
	SELECT [f_NationCodeStr], [BagNo], [ItemNo01], [ItemNo02], [ItemNo03], [ItemNo04], [ItemNo05],
		[ItemNo06], [ItemNo07], [ItemNo08], [ItemNo09], [ItemNo10], [ItemNoTypeFlag] FROM [dbo].[TB_DefItemBagElements] WITH(NOLOCK)

END
GO
