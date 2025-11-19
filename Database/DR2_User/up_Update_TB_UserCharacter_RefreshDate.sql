USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Update_TB_UserCharacter_RefreshDate]    Script Date: 03/19/2009 11:43:38 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_TB_UserCharacter_RefreshDate]'))
BEGIN
	DROP PROCEDURE [dbo].[up_Update_TB_UserCharacter_RefreshDate]
END
GO

-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Update_TB_UserCharacter_RefreshDate]
	@CharacterID UNIQUEIDENTIFIER,
	@RefreshDate int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	UPDATE dbo.TB_CharacterSub SET RefreshDate = @RefreshDate WHERE CharacterID = @CharacterID

END
GO