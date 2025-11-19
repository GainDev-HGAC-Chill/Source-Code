USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_Update_ItemGroupCoolTime]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].UP_Update_ItemGroupCoolTime
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].UP_Update_ItemGroupCoolTime
(
	@CharGuid UNIQUEIDENTIFIER,
	@ItemGroupCoolTime BINARY(256)
)
AS
BEGIN
	UPDATE [dbo].[TB_CharacterSub] SET f_ItemGroupCoolTime = @ItemGroupCoolTime WHERE [CharacterID] = @CharGuid
END