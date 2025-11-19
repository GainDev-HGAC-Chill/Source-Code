USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UserQuestComplete_Add]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_UserQuestComplete_Add]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROC [dbo].[up_UserQuestComplete_Add]
(
	@CharGuid		UNIQUEIDENTIFIER,
	@QuestID		INT,
	@bComplete		TINYINT
)
AS
BEGIN

	 IF EXISTS (SELECT 1 FROM [TB_UserQuestComplete] WHERE [CharacterID] = @CharGuid AND [QuestID] = @QuestID )
	 BEGIN
		 UPDATE [TB_UserQuestComplete]
		    SET [Complete] = @bComplete, [CompleteDate] = NULL
		  WHERE [CharacterID] = @CharGuid AND [QuestID] = @QuestID
	 END
	 ELSE
	 BEGIN
		 INSERT INTO [TB_UserQuestComplete]
			   ([CharacterID],[QuestID],[Complete],[CompleteDate])
		 VALUES
			   (@CharGuid,@QuestID,@bComplete,NULL)
	 END
END

