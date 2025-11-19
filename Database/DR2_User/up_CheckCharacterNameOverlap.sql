USE [DR2_User]
GO


SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_CheckCharacterNameOverlap]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_CheckCharacterNameOverlap]
GO
-- 캐릭터 이름 중복확인
CREATE PROC [dbo].[up_CheckCharacterNameOverlap]
(
	@Name	NVARCHAR(20)
)
AS
BEGIN	
	
	DECLARE @Err INT
	SET @Err = 0
	
	IF EXISTS ( SELECT 1 FROM dbo.TB_CharacterBasic WHERE [Name] = @Name )
	BEGIN
		SET @Err = 3
		SELECT @Err, @Name
		RETURN
	END
	SELECT @Err, @Name
	RETURN
END
GO