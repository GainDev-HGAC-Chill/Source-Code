USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UserQuestComplete_Update]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_UserQuestComplete_Update]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROC [dbo].[up_UserQuestComplete_Update]
(
	@CharGuid		UNIQUEIDENTIFIER,
	@QuestID		INT
)
AS
BEGIN

	UPDATE [TB_UserQuestComplete]
       SET [CompleteDate] = GETDATE()
     WHERE CharacterID = @CharGuid AND QuestID = @QuestID

END

