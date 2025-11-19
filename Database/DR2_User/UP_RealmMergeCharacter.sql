USE [DR2_User]
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_RealmMergeCharacter]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[UP_RealmMergeCharacter]
END
GO

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

CREATE PROC [dbo].[UP_RealmMergeCharacter]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명: 캐릭터명 변경
// 작성자: 육정범
// 작성일: 2009-03-30
// 파일명: 
// N O T E : 
//	2009-03-30 캐릭터 이름을 변경 할 수 있도록
//  2011-08-29 조현건 : 확장 슬롯 갯수 체크 추가.
////////////////////////////////////////////////////////////////////////
*/
(
	@MemberID		UNIQUEIDENTIFIER,	-- MemberGuid
	@CharacterID	UNIQUEIDENTIFIER,	-- CharacterGuid
	@NewName		NVARCHAR(20)	-- 캐릭터이름
)
AS
SET NOCOUNT ON
SET XACT_ABORT ON

DECLARE @Err INT
DECLARE @OrgState tinyint
DECLARE @OrgName nvarchar(20)
DECLARE @Class smallint
DECLARE @LV	smallint
SET @Err = 0

DECLARE @BasicSlot	tinyint
SET @BasicSlot = 3
DECLARE @ExtendSlot	tinyint
SET @ExtendSlot = 0

IF NOT EXISTS (SELECT 1 FROM dbo.TB_CharacterBasic WHERE [MemberID] = @MemberID AND [CharacterID] = @CharacterID AND 0 <> ([State] & 0x0C) )
BEGIN
	SET @Err = 0  -- 통합대상의 캐릭터가 아님(C소스와에러번호같음 UCRR_None)
	GOTO ErrorReturn
END

SELECT @OrgName = [Name], @OrgState = [State] FROM dbo.TB_CharacterBasic WHERE [CharacterID] = @CharacterID
SELECT @Class = [Class], @LV = [LV] FROM dbo.TB_Charactersub WHERE [CharacterID] = @CharacterID
SELECT @ExtendSlot = [ExtendCharacterNum] FROM dbo.TB_Member_ShareData WHERE MemberKey = @MemberID

--1. 캐릭터이름중복검사
IF 0 <> (@OrgState & 0x04) AND EXISTS (SELECT 1 FROM dbo.TB_CharacterBasic WHERE [CharacterID] <> @CharacterID AND [Name] = @NewName AND [State] <> 1 )
BEGIN
	SET @Err = 3  -- 중복되는캐릭터이름이있음(C소스와에러번호같음 UCRR_Duplicate)
	GOTO ErrorReturn
END

--2. 캐릭갯수 초과체크
-- 2.1. 삭제 예정을, 통합하는 것이라면, 노멀(0), 이름변경대기(4) 상태의 캐릭터들이 3개 이하여야 함
-- 2.2. 이름 변경 뿐이라면, 숫자
-- 추가 : dbo.TB_Member_ShareData.ExtendCharacterNum를 확인하여 추가 슬롯이 있는지 체크
-- 수정 : 기본 슬롯 갯수 + 확장 갯수 슬롯보다 캐릭터 갯수가 많지 않아야 함 - 으로 수정
IF ((0 <> (@OrgState & 0x04)) OR (0 <> (@OrgState & 0x08))) AND 1 = (SELECT (CASE WHEN COUNT(1) > (@BasicSlot+@ExtendSlot) THEN 1 ELSE 0 END) FROM dbo.TB_CharacterBasic WHERE MemberID = @MemberID AND [State] in (0))
BEGIN
	SET @Err = 6--캐릭터갯수제한을초과하였음(max : 5개) (C소스와에러번호같음 UCRR_MaxSlot)
	GOTO ErrorReturn
END


BEGIN TRAN
	IF 0 <> (@OrgState & 0x04)
	BEGIN
		UPDATE dbo.TB_CharacterBasic
			SET [Name] = @NewName, [State] = 0
			WHERE [CharacterID] = @CharacterID
	END
	ELSE
	BEGIN
		UPDATE dbo.TB_CharacterBasic
			SET [State] = 0
			WHERE [CharacterID] = @CharacterID

		SET @NewName = @OrgName
	END
		
	COMMIT TRAN
	SET @Err = 1 -- 성공 (UCCR_Success)
	SELECT @Err, @CharacterID, @NewName, @OrgName, @Class, @LV
	RETURN

--ErrorHandler:
--BEGIN
--	ROLLBACK TRAN
--	SELECT @Err, @CharacterID, @NewName, @OrgName, @Class, @LV
--	RETURN
--END

ErrorReturn:
BEGIN
	SELECT @Err, @CharacterID, @NewName, @OrgName, @Class, @LV
	RETURN
END
GO
