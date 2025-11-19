USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_Change_Character_HiddenOpen]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[UP_Change_Character_HiddenOpen]

/****** 개체:  StoredProcedure [dbo].[UP_Change_Character_HiddenOpen]    스크립트 날짜: 11/10/2009 18:20:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[UP_Change_Character_HiddenOpen]
@CharGuid UNIQUEIDENTIFIER,
@HiddenOpen BINARY(125),
@SetDate DATETIME
AS
BEGIN
	SET NOCOUNT ON;
	UPDATE [dbo].[TB_UserCharacter_Extern] 
	SET 
		[Hidden_Open] = @HiddenOpen,
		[LastHiddenUpdate] = @SetDate
	WHERE [CharacterID] = @CharGuid
END

GO
