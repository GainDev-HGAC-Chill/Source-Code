USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UserQuestComplete_Select]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_UserQuestComplete_Select]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROC [dbo].[up_UserQuestComplete_Select]
(
	@CharGuid		UNIQUEIDENTIFIER
)
AS
BEGIN

	SELECT [CharacterID],[QuestID],[Complete]
	  FROM [TB_UserQuestComplete]
	 WHERE CharacterID = @CharGuid AND CompleteDate IS NULL

END

