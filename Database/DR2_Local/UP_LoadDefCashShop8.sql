USE [DR2_Local]

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefCashShop8]'))
BEGIN
	DROP PROCEDURE [dbo].[UP_LoadDefCashShop8]
END
GO

CREATE PROCEDURE [dbo].[UP_LoadDefCashShop8]

AS
BEGIN

	SELECT [Idx]
		  ,[Step]
		  ,[Rank]
		  ,[RootIdx]
		  ,[ParentIdx]
		  ,cast([IsUsed] as tinyint)
		  ,[Name]
	  FROM [dbo].[TB_Common_CashItemCategory]

	SELECT [Idx]
		  ,[CashItemCategoryIdx]
		  ,[U]
		  ,[V]
		  ,[UVIndex]
		  ,[IconPath]
		  ,[ItemName]
		  ,[Description]
		  ,[Status]
		  ,[SaleType]
		  ,[SaleStartDate]
		  ,[SaleEndDate]
		  ,[Mileage]
		  ,isnull([CashItemDisplayTypeIdx],0)
          ,isnull([DisplayRank],0)
	  FROM [dbo].[TB_Common_CashItem]

	SELECT [CashItemIdx]
		  ,[ItemUseTime]
		  ,[Cash]
		  ,isnull([DiscountCash],0)
		  ,cast([IsDiscount] as tinyint)
		  ,[TimeType]
		  ,ISNULL([ExtendCash],0)
		  ,CAST([IsExtendDiscount] AS TINYINT)
		  ,ISNULL([DiscountExtendCash],0)
		  ,CAST([IsOnlyMileage] AS TINYINT)
		  ,[PriceIdx]
	  FROM [dbo].[TB_Common_CashItemPrice]

	SELECT [CashItemIdx]
		  ,[ItemNo]
		  ,[ItemCount]
	  FROM [dbo].[TB_Common_CashItemRef]
	  
	SELECT [CashItemIdx]
		  ,[ItemTotalCount]
		  ,[ItemLimitCount]
		  ,[ItemBuyLimitCount]
	  FROM [dbo].[TB_Common_CashItemLimitSell]

END
