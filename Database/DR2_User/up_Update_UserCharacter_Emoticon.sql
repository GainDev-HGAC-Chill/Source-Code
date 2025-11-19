USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_TB_UserCharacter_Emoticon]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_TB_UserCharacter_Emoticon]
go

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

create PROC [dbo].[up_Update_TB_UserCharacter_Emoticon] 
	@CharacterID uniqueidentifier,
	@Value BINARY(20)
AS
SET NOCOUNT ON
SET XACT_ABORT ON	

UPDATE dbo.TB_CharacterSub SET Emoticon = @Value WHERE CharacterID = @CharacterID

