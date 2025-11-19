USE [DR2_User]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UserWantedQuest_Init]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_UserWantedQuest_Init]
END
GO

CREATE PROCEDURE [dbo].[up_UserWantedQuest_Init]
	@CharacterID	UNIQUEIDENTIFIER
AS
BEGIN
	DELETE dbo.TB_UserWantedQuest WHERE CharacterID = @CharacterID
END

