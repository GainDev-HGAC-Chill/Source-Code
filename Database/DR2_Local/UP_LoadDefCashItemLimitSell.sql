USE [DR2_Local]
GO

/****** Object:  StoredProcedure [dbo].[UP_LoadDefCashItemLimitSell]    Script Date: 11/08/2010 16:56:18 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefCashItemLimitSell]'))
BEGIN
	DROP PROCEDURE [dbo].[UP_LoadDefCashItemLimitSell]
END
GO

CREATE PROCEDURE [dbo].[UP_LoadDefCashItemLimitSell]
	@MemberGuid uniqueidentifier,
	@ItemIdx int
AS
BEGIN
	SELECT ISNULL(ItemTotalCount,0), ISNULL(ItemLimitCount,0), ISNULL(ItemBuyLimitCount,0) FROM [dbo].[TB_Common_CashItemLimitSell] WHERE CashItemIdx = @ItemIdx
	
	SELECT ISNULL(SUM(ItemBuyCount),0) FROM [dbo].[TB_Common_CashItemLimitSellMember] WHERE MemberGuid = @MemberGuid and CashItemIdx = @ItemIdx
	
	SELECT [CashItemIdx]
		  ,[ItemTotalCount]
		  ,[ItemLimitCount]
		  ,[ItemBuyLimitCount]
	  FROM [dbo].[TB_Common_CashItemLimitSell]
END

GO
