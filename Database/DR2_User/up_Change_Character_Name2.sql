USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[UP_CS_ADDGIFT2]    Script Date: 04/09/2009 21:39:38 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Change_Character_Name2]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Change_Character_Name2]
GO

/****** Object:  StoredProcedure [dbo].[up_Change_Character_Name2]    Script Date: 04/16/2009 12:20:25 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


/*
////////////////////////////////////////////////////////////////////////
// Lasst Update by : Eric Kim
// Update date  : 2008-06-30
// Description : 
// [PARAMETER] : 
// [RETURN] : 
//	2009-04-16 : 이름 검색시 캐릭터 상태값 확인 하도록 수정
//	2009-12-15 : Eric Kim, 이름 검색시 캐릭터 상태값 무시하고 검색 
			대신, 찾은 캐릭터가 자신인가 검사하기 추가
////////////////////////////////////////////////////////////////////////
*/
CREATE PROCEDURE [dbo].[up_Change_Character_Name2]
(
	@MemberId			UNIQUEIDENTIFIER,
	@CharacterId		UNIQUEIDENTIFIER,
	@Name				nvarchar(20)
)
AS
BEGIN
	DECLARE @Err int;
	SET @Err = 0;
	SET NOCOUNT ON;

	--해당 유저가 존재하는가?
	IF NOT EXISTS (SELECT 1 FROM [dbo].[TB_CharacterBasic] WHERE [CharacterID] = @CharacterId)
	BEGIN
		SET @Err = 1;
		GOTO ErrorHandler;
	END

	IF EXISTS (SELECT 1 FROM [dbo].[TB_CharacterBasic] WHERE [Name] = @Name AND [CharacterID] <> @CharacterId)
	BEGIN
		SET @Err = 2	--존재하는 캐릭명
		GOTO ErrorHandler;
	END 

	--저장
	UPDATE [DBO].[TB_CharacterBasic]
		SET [Name] = @Name
		WHERE [CharacterID] = @CharacterId;
	IF @@error <> 0
	BEGIN
		SET @Err = 2;
		GOTO ErrorHandler;
	END

ErrorHandler:
	SELECT @Err
	RETURN @Err
END

GO