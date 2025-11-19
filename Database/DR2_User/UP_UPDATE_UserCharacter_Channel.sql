USE DR2_User
GO


IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_UPDATE_UserCharacter_Channel]') and [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_UPDATE_UserCharacter_Channel]
END
Go

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE dbo.[UP_UPDATE_UserCharacter_Channel]
	@CharGuid UNIQUEIDENTIFIER,
	@ChannelNo SMALLINT
AS
BEGIN
	SET NOCOUNT ON;

	IF EXISTS(SELECT 1 FROM dbo.TB_CharacterSub WHERE [CharacterID] = @CharGuid)
	BEGIN
		UPDATE dbo.TB_CharacterSub SET [f_ConnectionChannel] = @ChannelNo WHERE [CharacterID] = @CharGuid
	END
END
GO