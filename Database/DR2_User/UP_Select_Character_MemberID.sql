USE DR2_User
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.UP_Select_Character_MemberID') and [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.UP_Select_Character_MemberID
END
Go

-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE dbo.UP_Select_Character_MemberID
	@CharacterID UNIQUEIDENTIFIER
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	SELECT [MemberID] FROM dbo.TB_CharacterBasic WHERE [CharacterID] = @CharacterID
END
GO
