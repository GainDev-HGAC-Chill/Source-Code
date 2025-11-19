USE [DR2_User]

IF EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'UP_CS_SELECTGIFTLIST'))
BEGIN
	DROP PROCEDURE [dbo].[UP_CS_SELECTGIFTLIST]
END
GO

/****** Object:  StoredProcedure [dbo].[UP_CS_SELECTGIFTLIST]    Script Date: 01/05/2012 16:54:20 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[UP_CS_SELECTGIFTLIST]
/*
////////////////////////////////ㅁ////////////////////////////////////////
//
// 프로시져명 : Active Login Stat.
// 작 성 자 : ??
// 작 성 일 : ??
// 최종수정자 : Richard Kim(tigerjune@barunsoninter.com)
// 수 정 일 : 2008-10-31
// 파 일 명 : 
// N O T E : 
//
////////////////////////////////////////////////////////////////////////
*/
(
	@CHARGUID UNIQUEIDENTIFIER
)
AS
SET XACT_ABORT ON
SET NOCOUNT ON;

-- 보낸 기록은 30일 지나면 삭제
DELETE FROM [dbo].[TB_UserCashGift] 
WHERE [CharGuId] = @CHARGUID AND [Type] = 0 AND [SendTime] <= DATEADD(day,-30,GETDATE())


--보낸선물
SELECT TOP 400 [GiftGuId]
  ,[CharName]
  ,[SendTime]
  ,[CashItemIdx]
  ,[Comment]
  ,[Type]
  ,[TimeType]
  ,[UseTime]
FROM [dbo].[TB_UserCashGift] WHERE Type=0 AND [CharGuId] = @CHARGUID order by sendtime desc

--받은선물
SELECT TOP 600 [GiftGuId]
  ,[CharName]
  ,[SendTime]
  ,[CashItemIdx]
  ,[Comment]
  ,[Type]
  ,[TimeType]
  ,[UseTime]
FROM [dbo].[TB_UserCashGift] WHERE Type=1 AND [CharGuId] = @CHARGUID order by sendtime desc
