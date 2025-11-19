USE [DR2_User]
GO

/****** 개체:  StoredProcedure [dbo].[up_UM_MarketRemove2]    스크립트 날짜: 07/17/2009 11:24:34 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UM_MarketRemove2]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_UM_MarketRemove2]
GO

/****** ü:  StoredProcedure [dbo].[up_UM_MarketRemove2]    ũƮ ¥: 07/17/2009 11:24:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UM_MarketRemove2]') AND type in (N'P', N'PC'))
BEGIN
EXEC dbo.sp_executesql @statement = N'





/*
////////////////////////////////////////////////////////////////////////
// Lasst Update by : 
// Update date  : 
// Description : 
// [PARAMETER] : 
// [RETURN] : 
// [REMARK]
////////////////////////////////////////////////////////////////////////
*/
create PROCEDURE [dbo].[up_UM_MarketRemove2]
(
	@CharGuId UNIQUEIDENTIFIER
)
AS
SET XACT_ABORT ON
SET NOCOUNT ON;
DECLARE @ERR INT


BEGIN TRAN
	DELETE FROM dbo.TB_UserMarketInfo2 WHERE charguid = @charguid
	DELETE FROM DBO.TB_USERMARKET WHERE SellerGuid = @charguid
	DELETE FROM DBO.TB_USERDEALINGS WHERE CharacterGuid = @charguid
SELECT @ERR = @@error
COMMIT TRAN
'
END
GO