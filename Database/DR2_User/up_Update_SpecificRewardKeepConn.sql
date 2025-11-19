USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Update_SpecificRewardKeepConn]    Script Date: 11/15/2011 10:45:02 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_SpecificRewardKeepConn]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_SpecificRewardKeepConn]
GO

CREATE PROCEDURE [dbo].[up_Update_SpecificRewardKeepConn]
(
	@Type INT,
	@CharacterID UNIQUEIDENTIFIER,
	@IsKeepConn SMALLINT
)
AS	
BEGIN
	SET NOCOUNT ON;
	BEGIN
		UPDATE [dbo].[TB_SpecificReward] SET [IsKeepConn] = @IsKeepConn
		WHERE [Type] = @Type AND [CharacterID] = @CharacterID
	END
	SET NOCOUNT OFF;
END
