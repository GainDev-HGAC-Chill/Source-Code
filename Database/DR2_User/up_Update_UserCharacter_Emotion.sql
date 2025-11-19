USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_TB_UserCharacter_Emotion]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_TB_UserCharacter_Emotion]
go

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

create PROC [dbo].[up_Update_TB_UserCharacter_Emotion] 
	@CharacterID uniqueidentifier,
	@Value BINARY(20)
AS
SET NOCOUNT ON
SET XACT_ABORT ON	

UPDATE dbo.TB_CharacterSub SET Emotion = @Value WHERE CharacterID = @CharacterID

