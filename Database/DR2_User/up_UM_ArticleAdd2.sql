USE DR2_USER
GO
/****** 개체:  StoredProcedure [dbo].[up_UM_ArticleAdd2]    스크립트 날짜: 07/17/2009 11:24:33 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UM_ArticleAdd2]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_UM_ArticleAdd2]
GO

/****** ü:  StoredProcedure [dbo].[up_UM_ArticleAdd2]    ũƮ ¥: 07/17/2009 11:24:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UM_ArticleAdd2]') AND type in (N'P', N'PC'))
BEGIN
EXEC dbo.sp_executesql @statement = N'CREATE PROCEDURE [dbo].[up_UM_ArticleAdd2]
(
	@SellerGuid uniqueidentifier,
	@SellCost bigint,
	@CostType tinyint,
	@ItemGuid uniqueidentifier,
	@ItemName nvarchar(20),
	@LimitLevel int,

	@ArticleClass bigint,
	@ItemGrade int,
	@InvType int,
	@ItemType int
)

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	insert into dbo.TB_UserMarket 
	(SellerGuid, SellCost, CostType, ItemGuid, ItemName,
	 LimitLevel, ItemGrade, InvType, ItemType,
	ClassLimit)
	values
	(@SellerGuid, @SellCost, @CostType, @ItemGuid, @ItemName,
	 @LimitLevel, @ItemGrade, @InvType, @ItemType, 
	@ArticleClass)

	select @@error
	
END'END