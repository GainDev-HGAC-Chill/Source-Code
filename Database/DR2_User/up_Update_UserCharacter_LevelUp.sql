USE [DR2_User]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_UserCharacter_LevelUp]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_Update_UserCharacter_LevelUp]
END
GO

CREATE PROC [dbo].[up_Update_UserCharacter_LevelUp] 
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : DR2_User.dbo.[up_Update_UserCharacter_LevelUp]
// 작 성 자 : YonMy(yonmy@barunsoninter.com)
// 작 성 일 : 2010-01-18
// 최종수정자 :
// 수 정 일 : 
// 파 일 명 : 
// N O T E : 레벨업 처리
//
////////////////////////////////////////////////////////////////////////
*/
(
	@MemberID		uniqueidentifier
,	@CharacterID	uniqueidentifier
,	@NewLevel		smallint
,	@TotalPlayTimeSec bigint
)
AS
SET NOCOUNT ON
SET LOCK_TIMEOUT 5000
SET XACT_ABORT ON	

DECLARE @Err INT
SET @Err = 0

BEGIN
	UPDATE [dbo].[TB_CharacterSub] SET [Lv] = @NewLevel WHERE [CharacterID] = @CharacterID

	IF NOT EXISTS (SELECT 1 FROM [dbo].[TB_Record_LevelUp_PlayTimeSec] WHERE [CharacterID] = @CharacterID AND [Level] = @NewLevel)
	BEGIN
		INSERT INTO [dbo].[TB_Record_LevelUp_PlayTimeSec]
		(
			[CharacterID],
			[Level],
			[PlayTimeSec],
			[UpdateTime]
		)
		VALUES
		(
			@CharacterID,
			@NewLevel,
			@TotalPlayTimeSec,
			GetDate()
		)
	END

	EXEC [dbo].[up_SelectCharacterLevel_Rank] @MemberID, @NewLevel
END

RETURN @Err
GO
