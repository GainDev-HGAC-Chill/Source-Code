USE [DR2_User]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_User_WantedQuest_ClearCount]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_Update_User_WantedQuest_ClearCount]
END
GO

CREATE PROCEDURE [dbo].[up_Update_User_WantedQuest_ClearCount]
	@CharacterID	UNIQUEIDENTIFIER
,	@QuestID		INT	
AS
BEGIN
	SET NOCOUNT ON;
	
	IF NOT EXISTS(SELECT 1 FROM dbo.TB_UserWantedQuest WHERE CharacterID = @CharacterID AND QuestID = @QuestID)
	BEGIN
		INSERT INTO dbo.TB_UserWantedQuest(CharacterID, QuestID, ClearCount)
		VALUES(@CharacterID, @QuestID, 1)
	END
	ELSE
	BEGIN
		UPDATE dbo.TB_UserWantedQuest SET ClearCount = ( ClearCount + 1 ) WHERE CharacterID = @CharacterID AND QuestID = @QuestID 
	END
END

