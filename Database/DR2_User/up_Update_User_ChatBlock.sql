USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_User_ChatBlock]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_User_ChatBlock]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Update_User_ChatBlock]
(
	@CharacterID	UNIQUEIDENTIFIER,
	@BlockName		nvarchar(20),
	@BlockType		tinyint,
	@UpdateType		tinyint
)
AS
BEGIN
	SET NOCOUNT ON;
	IF @UpdateType = 1
	BEGIN
		INSERT INTO [dbo].[TB_User_ChatBlock] ( [CharacterID], [BlockName], [BlockType] )
		VALUES ( @CharacterID, @BlockName, @BlockType )
	END
	
	IF @UpdateType = 2
	BEGIN
		UPDATE [dbo].[TB_User_ChatBlock] SET [BlockType] = @BlockType 
		WHERE [CharacterID]	= @CharacterID AND [BlockName] = @BlockName
	END
	
	IF @UpdateType = 3
	BEGIN
		DELETE FROM [dbo].[TB_User_ChatBlock]
		WHERE @CharacterID = [CharacterID] AND [BlockName] = @BlockName
	END
	SET NOCOUNT OFF;
END