USE DR2_User
GO


IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_CLEAR_UserCharacter_Channel]') and [type] in (N'U'))
BEGIN
	DROP PROCEDURE dbo.[UP_CLEAR_UserCharacter_Channel]
END
Go

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE dbo.[UP_CLEAR_UserCharacter_Channel]
	@MemberGuid UNIQUEIDENTIFIER = NULL
AS
BEGIN
	SET NOCOUNT ON;

	IF @MemberGuid IS NULL
		UPDATE dbo.TB_CharacterSub SET [f_ConnectionChannel] = 0
	ELSE
		UPDATE dbo.TB_CharacterSub SET [f_ConnectionChannel] = 0 WHERE CharacterID IN (SELECT CharacterID FROM dbo.TB_CharacterBasic WHERE [MemberID] = @MemberGuid)
END
GO