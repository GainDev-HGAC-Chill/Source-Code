USE DR2_USER
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_DeleteWebCharacterItemInfo]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_DeleteWebCharacterItemInfo]
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
CREATE PROCEDURE dbo.[UP_DeleteWebCharacterItemInfo]
@f_RealmNo int,
@f_CharGuid UNIQUEIDENTIFIER
AS
BEGIN
	DELETE FROM dbo.TB_Web_UserItemInfo_Status WHERE f_RealmNo = @f_RealmNo AND f_ItemGuid IN
		( SELECT [f_ItemGuid] FROM dbo.TB_Web_UserItemInfo WHERE f_RealmNo = @f_RealmNo AND f_CharGuid = @f_CharGuid )
	DELETE FROM dbo.TB_Web_UserItemInfo WHERE f_RealmNo = @f_RealmNo AND f_CharGuid = @f_CharGuid
END
GO
