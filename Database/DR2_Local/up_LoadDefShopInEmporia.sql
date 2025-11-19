USE [DR2_Local]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefShopInEmporia]    Script Date: 09/17/2009 14:16:22 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefShopInEmporia]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefShopInEmporia]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROC [dbo].[up_LoadDefShopInEmporia]
AS
	SELECT [IDX], [ShopGuid], [Category], [ItemNo], [Price], [CP], [Coin], [TimeType], [UseTime]
	FROM dbo.TB_DefShopInEmporia WITH(NOLOCK) ORDER BY [IDX]
