USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_TB_UserCharacter_SkillExtend]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_TB_UserCharacter_SkillExtend]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROC [dbo].[up_Update_TB_UserCharacter_SkillExtend] 
	@CharacterID uniqueidentifier,
	@Second tinyint,
	@Value binary(560)
AS
SET NOCOUNT ON
SET XACT_ABORT ON	

IF 1 = @Second
BEGIN
	UPDATE dbo.TB_CharacterSub Set SkillExtend_Sec = @Value Where CharacterID = @CharacterID
END
ELSE
BEGIN
	UPDATE dbo.TB_CharacterSub Set SkillExtend = @Value Where CharacterID = @CharacterID
END


GO