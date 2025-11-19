USE [DR2_local]
GO
/****** 개체:  StoredProcedure [dbo].[up_LoadDefShopInStock]    스크립트 날짜: 05/17/2009 16:10:04 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefShopInStock]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefShopInStock]
GO

/****** 개체:  StoredProcedure [dbo].[up_LoadDefShopInStock]    스크립트 날짜: 05/17/2009 16:10:04 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefShopInStock]') AND type in (N'P', N'PC'))
BEGIN
EXEC dbo.sp_executesql @statement = N'
Create PROC [dbo].[up_LoadDefShopInStock]
AS
	SELECT [IDX], [ShopGuid], [Category], [ItemNo], [Price],[SellPrice],[CP],[Coin],[TimeType],[UseTime], [state]
	FROM dbo.TB_DefShopInStock WITH(NOLOCK) ORDER BY [IDX] '
END
GO
