USE [DR2_Local]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefShopInGame3]    Script Date: 09/17/2009 14:16:22 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefShopInGame3]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefShopInGame3]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROC [dbo].[up_LoadDefShopInGame3]
AS
	SELECT [IDX], [f_NationCodeStr], [ShopGuid], [Category], [ItemNo], [Price],[CP],[Coin],[TimeType],[UseTime]
	FROM dbo.TB_DefShopInGame WITH(NOLOCK) ORDER BY [IDX]

	SELECT [ShopID],[NpcGuid] FROM [dbo].[TB_DefShopNpc] with(nolock)

