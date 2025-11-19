USE [DR2_User]
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_UPDATE_TB_UserCharacter_DateContents]') AND [TYPE] IN (N'P', N'PC'))
BEGIN
	DROP PROCEDURE dbo.[UP_UPDATE_TB_UserCharacter_DateContents]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2009-11-03
-- Description:	
-- =============================================
CREATE PROCEDURE dbo.[UP_UPDATE_TB_UserCharacter_DateContents]
	@CharacterID uniqueidentifier,
	@FieldName nvarchar(50),
	@DateTime datetime
AS
BEGIN
	SET NOCOUNT ON
	SET LOCK_TIMEOUT 5000
	SET XACT_ABORT ON

	DECLARE @SQL nvarchar(1000)
	DECLARE @SQL_Params nvarchar(100)

	IF NOT EXISTS(SELECT 1 FROM dbo.[TB_UserCharacter_DateContents] WHERE [f_CharacterID] = @CharacterID)
	BEGIN
		SET @SQL = N'INSERT INTO dbo.[TB_UserCharacter_DateContents] ([f_CharacterID],' + @FieldName + ') VALUES (@CharacterID, @DateTime)'
		SET @SQL_Params = N'@DateTime datetime, @CharacterID uniqueidentifier'
	END
	ELSE
	BEGIN
		SET @SQL = N'UPDATE dbo.[TB_UserCharacter_DateContents] Set ' + @FieldName + ' = @DateTime Where [f_CharacterID] = @CharacterID'
		SET @SQL_Params = N'@DateTime datetime, @CharacterID uniqueidentifier'
	END

	EXEC sp_executesql @SQL, @SQL_Params, @DateTime, @CharacterID
END
GO