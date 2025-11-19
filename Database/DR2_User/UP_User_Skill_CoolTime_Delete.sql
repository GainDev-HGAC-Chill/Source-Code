USE DR2_User
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_User_Skill_CoolTime_Delete]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_User_Skill_CoolTime_Delete]
END


SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UP_User_Skill_CoolTime_Delete]
	@CharacterID UNIQUEIDENTIFIER
AS
BEGIN
	SET NOCOUNT ON;

    DELETE FROM dbo.TB_User_Skill_CoolTime WHERE [CharacterID] = @CharacterID
END
GO
