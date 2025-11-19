USE [DR2_Local]
GO

/****** Object:  StoredProcedure [dbo].[UP_UPDATE_CS_ITEM_LIMIT_SELL]    Script Date: 11/08/2010 16:56:18 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UPDATE_CS_ITEM_LIMIT_SELL]'))
BEGIN
	DROP PROCEDURE [dbo].[UP_UPDATE_CS_ITEM_LIMIT_SELL]
END
GO

CREATE PROCEDURE [dbo].[UP_UPDATE_CS_ITEM_LIMIT_SELL]
	@MemberGuid uniqueidentifier,
	@ItemIdx int
AS
BEGIN
	SET NOCOUNT ON
	
	DECLARE @CalcItemCount INT
	SET @CalcItemCount = (SELECT [ItemLimitCount] FROM [dbo].[TB_Common_CashItemLimitSell] WHERE [CashItemIdx] = @ItemIdx) - 1
	IF 0 > @CalcItemCount
	BEGIN
		SET @CalcItemCount = 0
	END
	
	IF EXISTS(SELECT 1 FROM [dbo].[TB_Common_CashItemLimitSell] WHERE [CashItemIdx] = @ItemIdx)
	BEGIN
		UPDATE [dbo].[TB_Common_CashItemLimitSell] SET
			[ItemLimitCount] = @CalcItemCount
			WHERE [CashItemIdx] = @ItemIdx
	END
	
	INSERT INTO [dbo].[TB_Common_CashItemLimitSellMember]
		([MemberGuid], [CashItemIdx], [ItemBuyCount], [CreateDate])
		VALUES(@MemberGuid, @ItemIdx, 1, GETDATE())					
		
	SELECT [CashItemIdx]
		  ,[ItemTotalCount]
		  ,[ItemLimitCount]
		  ,[ItemBuyLimitCount]
	  FROM [dbo].[TB_Common_CashItemLimitSell]
END

GO
