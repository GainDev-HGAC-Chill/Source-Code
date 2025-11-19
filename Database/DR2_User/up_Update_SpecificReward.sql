USE [DR2_User]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_SpecificReward]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_SpecificReward]
GO

CREATE PROCEDURE [dbo].[up_Update_SpecificReward]
(
	@Type INT,
	@CharacterID UNIQUEIDENTIFIER,
	@LastRewardTime DATETIME
)
AS	
BEGIN
	SET NOCOUNT ON;
	IF NOT EXISTS( SELECT 1 FROM [dbo].[TB_SpecificReward] WHERE [Type] = @Type AND [CharacterID] = @CharacterID )
	BEGIN
		INSERT INTO [dbo].[TB_SpecificReward] ( [Type], [CharacterID], [LastRewardTime] )
		VALUES( @Type, @CharacterID, @LastRewardTime )
	END
	ELSE
	BEGIN
		UPDATE [dbo].[TB_SpecificReward] SET [LastRewardTime] = @LastRewardTime
		WHERE [Type] = @Type AND [CharacterID] = @CharacterID
	END
	SET NOCOUNT OFF;
END
