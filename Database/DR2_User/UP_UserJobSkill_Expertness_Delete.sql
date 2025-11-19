USE DR2_User
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UserJobSkill_Expertness_Delete]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_UserJobSkill_Expertness_Delete]
END


SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UP_UserJobSkill_Expertness_Delete]
	@CharGuid UNIQUEIDENTIFIER,
	@SkillNo INT
AS
BEGIN
	SET NOCOUNT ON;

    DELETE FROM dbo.TB_UserJobSkill_Expertness WHERE [f_CharGuid] = @CharGuid AND [f_SkillNo] = @SkillNo
END
GO
