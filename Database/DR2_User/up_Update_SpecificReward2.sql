USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Update_SpecificReward2]    Script Date: 11/15/2011 10:45:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_SpecificReward2]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_SpecificReward2]
GO

CREATE PROCEDURE [dbo].[up_Update_SpecificReward2]
(
	@Type INT,
	@CharacterID UNIQUEIDENTIFIER,
	@LastRewardTime DATETIME,
	@LastRewardCount SMALLINT
)
AS	
BEGIN
	SET NOCOUNT ON;
	IF NOT EXISTS( SELECT 1 FROM [dbo].[TB_SpecificReward] WHERE [Type] = @Type AND [CharacterID] = @CharacterID )
	BEGIN
		INSERT INTO [dbo].[TB_SpecificReward] ( [Type], [CharacterID], [LastRewardTime], [LastRewardCount] )
		VALUES( @Type, @CharacterID, @LastRewardTime, @LastRewardCount )
	END
	ELSE
	BEGIN
		UPDATE [dbo].[TB_SpecificReward] SET [LastRewardTime] = @LastRewardTime, [LastRewardCount] = @LastRewardCount
		WHERE [Type] = @Type AND [CharacterID] = @CharacterID
	END
	SET NOCOUNT OFF;
END
