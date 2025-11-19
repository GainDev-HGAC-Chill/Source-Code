USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[UP_CS_ADDGIFT2]    Script Date: 04/09/2009 21:39:38 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_Check_EanbleSend2]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Post_Check_EanbleSend2]
GO

/****** Object:  StoredProcedure [dbo].[up_Post_Check_EanbleSend2]    Script Date: 04/16/2009 12:20:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[up_Post_Check_EanbleSend2]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : 아이템 첨부 메일 발송
// 작 성 자 : Richard Kim(tigerjune@barunsoninter.com)
// 작 성 일 : 2008-05-20
// 최종수정자 :
// 수 정 일 : 
// 파 일 명 : 
// N O T E : 
//	2008-10-08 : character DB 두개로 나누어 진것 적용
//	2009-04-16 : 이름 검색시 캐릭터 상태값 확인 하도록 수정
////////////////////////////////////////////////////////////////////////
*/
(
	@FromName			NVARCHAR(20),		--메시지 발송자 캐릭터 이름
	@FromGuid			UNIQUEIDENTIFIER,	--메시지 발송자 메일 guid
	@ToName				NVARCHAR(20),		--메시지 수신자 캐릭터 이름
	@Annex				TINYINT
)
AS

BEGIN

	SET NOCOUNT ON
	SET Xact_Abort ON
	SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

	DECLARE @MAX_MAIL_COUNT INT
	DECLARE @ret INT
	DECLARE @frommailcount INT
	DECLARE @ToMailCount INT
	DECLARE @errVal INT
	DECLARE @toguid UNIQUEIDENTIFIER

	SET @frommailcount = 0

	-- 텍스트 아이템 포함 최대 100통 이것 저것 나누는게 더 골 아픈것 같아서 통합
	SET @MAX_MAIL_COUNT = 100

	IF @Annex <> 0
	BEGIN
		SELECT @frommailcount = COUNT(*) FROM dbo.tb_usermail AS A
		LEFT JOIN [dbo].[TB_UserItem] AS B ON A.ItemGuid = B.ItemGuid
		WHERE fromguid = @fromguid 
		AND AnnexBit  = 0
		AND (ISNULL(B.ItemNo,0) <> 0 OR A.[Money] <> 0)	

		-- 1. 먼저 보내는 사람이 메일을 전송 할 수 있는 상태인지 검사한다.	
		IF @frommailcount >= @MAX_MAIL_COUNT
		BEGIN 
			SET @errVal = 4
			GOTO RESULT
		END
	END
	
	-- 2. 받는 캐릭터가 존재 하는지 검사
	SELECT @toguid = characterid FROM [dbo].[TB_CharacterBasic] WHERE name = @toname AND [State] = 0
	
	IF @toguid IS NULL
	BEGIN
		SET @errVal = 9
		GOTO RESULT
	END

	SELECT @ToMailCount = COUNT(*) FROM dbo.tb_usermail WHERE toguid = @toguid

	-- 4. 받을 사람의 우편함이 더 받을수 있는지 검사
	IF @ToMailCount >= @MAX_MAIL_COUNT 
	BEGIN
		SET @errVal = 10
		GOTO RESULT
	END

RESULT:

	SELECT @errVal,@toguid

END
