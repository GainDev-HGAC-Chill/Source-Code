USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Update_TB_UserCharacter_RefreshDate]    Script Date: 03/19/2009 11:43:38 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_TB_UserCharacter_RecommandPoint]'))
BEGIN
	DROP PROCEDURE [dbo].[up_Update_TB_UserCharacter_RecommandPoint]
END
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_TB_UserCharacter_RecommendPoint]'))
BEGIN
	DROP PROCEDURE [dbo].[up_Update_TB_UserCharacter_RecommendPoint]
END
GO

CREATE PROCEDURE [dbo].[up_Update_TB_UserCharacter_RecommendPoint]
	@CharacterID UNIQUEIDENTIFIER,
	@RecommendPoint int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE dbo.TB_CharacterSub SET RecommendPoint = @RecommendPoint WHERE CharacterID = @CharacterID

END
