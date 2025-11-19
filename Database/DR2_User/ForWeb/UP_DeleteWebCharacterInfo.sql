USE DR2_USER
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_DeleteWebCharacterInfo]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_DeleteWebCharacterInfo]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE dbo.[UP_DeleteWebCharacterInfo]
@f_RealmNo int,
@f_CharGuid UNIQUEIDENTIFIER
AS
BEGIN
	DELETE FROM dbo.TB_Web_UserCharacter WHERE f_RealmNo = @f_RealmNo AND f_CharGuid = @f_CharGuid
	DELETE FROM dbo.TB_Web_UserCharacter_ComboInfo WHERE f_RealmNo = @f_RealmNo AND f_CharGuid = @f_CharGuid
	EXEC dbo.UP_DeleteWebCharacterItemInfo @f_RealmNo, @f_CharGuid
END
GO
