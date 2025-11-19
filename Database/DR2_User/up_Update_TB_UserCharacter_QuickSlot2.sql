USE DR2_User

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_TB_UserCharacter_QuickSlot2]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_Update_TB_UserCharacter_QuickSlot2] 
END 


set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

CREATE PROC [dbo].[up_Update_TB_UserCharacter_QuickSlot2] 
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명: DR2_User.dbo.up_Update_TB_UserCharacter_Field
// 작성자: Richard Kim(tigerjune@barunsoninter.com)
// 작성일: 2008-09-19
// 최종수정자:
// 수정일: 
// 파일명: 
// N O T E : 캐릭테이블의해당컬럼값을변경한다.
//
//	2008-10-08 : Eric Kim, Character Table 두개로나누어진것적용
//	2009-04-01 : 심헌섭, 전략스킬 추가로 Second 퀵슬롯 저장할 수 있도록 적용
////////////////////////////////////////////////////////////////////////
*/
	@CharacterID uniqueidentifier,
	@Second	tinyint,
	@QuickSlot	binary(281)
AS
SET NOCOUNT ON
SET XACT_ABORT ON	

IF 1 = @Second
BEGIN
	UPDATE dbo.TB_CharacterSub Set QuickSlot_Sec = @QuickSlot Where CharacterID = @CharacterID
END
ELSE
BEGIN
	UPDATE dbo.TB_CharacterSub Set QuickSlot = @QuickSlot Where CharacterID = @CharacterID
END


GO

