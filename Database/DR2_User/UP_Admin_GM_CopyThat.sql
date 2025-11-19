USE DR2_User
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.UP_Admin_GM_CopyThat') AND [Type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.UP_Admin_GM_CopyThat
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE dbo.UP_Admin_GM_CopyThat
	@CharName NVARCHAR(20)
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @CharacterGuid UNIQUEIDENTIFIER
	--DECLARE @MemberGuid UNIQUEIDENTIFIER

	SELECT @CharacterGuid = CharacterID FROM dbo.tb_characterbasic where [name] = @CharName

	select B.Lv, B.Class, B.Skills, B.SkillExtend
	from dbo.tb_characterbasic AS A INNER JOIN dbo.tb_charactersub AS B ON A.CharacterID = B.CharacterID
	where A.CharacterID = @CharacterGuid

	EXEC [dbo].[up_Item_Select] @CharacterGuid
	--EXEC [dbo].[up_Item_Select] @MemberID -- only character item
END
GO
