USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[UP_CS_ADDGIFT2]    Script Date: 04/09/2009 21:39:38 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_CS_ADDGIFT2]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[UP_CS_ADDGIFT2]
GO

/****** Object:  StoredProcedure [dbo].[UP_CS_ADDGIFT2]    Script Date: 04/16/2009 12:20:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/*
-- =============================================
-- Author:		
-- Create date: 
-- Description:	
--	2008-10-07 : Eric Kim
--		Character DB 가 두개로 나누어 진 것 적용
--		2009-04-16 : 이름 검색시 캐릭터 상태값 확인 하도록 수정		
-- =============================================
*/
CREATE PROC [dbo].[UP_CS_ADDGIFT2]
(
	@SENDERGUID UNIQUEIDENTIFIER
	,@SENDERNAME NVARCHAR(50)
	,@RECVERNAME NVARCHAR(50)
	,@COMMENT NVARCHAR(50)
	,@ITEMIDX INT
	,@TIMETYPE TINYINT
	,@USETIME INT
)
AS
SET NOCOUNT ON;
SET XACT_ABORT ON

DECLARE @RECVERGUID UNIQUEIDENTIFIER,
@errCode int

select @RECVERGUID = CharacterID from dbo.TB_CharacterBasic WHERE [NAME] = @RECVERNAME AND [State] = 0

if @@ROWCOUNT = 0
BEGIN
	SELECT 3
	RETURN 3;
END

BEGIN TRAN
	INSERT INTO [dbo].[TB_UserCashGift]
			   ([GiftGuId]
			   ,[CharGuId]
			   ,[CharName]
			   ,[SendTime]
			   ,[CashItemIdx]
			   ,[Comment]
			   ,[Type]
			   ,[TimeType]
			   ,[UseTime])
		 VALUES
			   (newid()
			   ,@SENDERGUID
			   ,@RECVERNAME
			   ,GETDATE()
			   ,@ITEMIDX
			   ,@COMMENT
			   ,cast(0 as tinyint)
			   ,@TIMETYPE
			   ,@USETIME)
	
	IF @@error <> 0
	BEGIN 
		SET @errCode = @@error
		GOTO ErrorHandler
	END

	INSERT INTO [dbo].[TB_UserCashGift]
           ([GiftGuId]
           ,[CharGuId]
           ,[CharName]
           ,[SendTime]
           ,[CashItemIdx]
           ,[Comment]
           ,[Type]
           ,[TimeType]
           ,[UseTime])
     VALUES
           (NEWID()
           ,@RECVERGUID
           ,@SENDERNAME
           ,GETDATE()
           ,@ITEMIDX
           ,@COMMENT
           ,cast(1 as tinyint)
           ,@TIMETYPE
           ,@USETIME)

	IF @@error <> 0
	BEGIN 
		SET @errCode = @@error
		GOTO ErrorHandler
	END

COMMIT TRAN
SELECT 0,@RECVERGUID
RETURN 0

ErrorHandler:
	ROLLBACK
	SELECT @errCode
	RETURN @errCode

GO