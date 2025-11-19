USE DR2_User
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UserJobSkill_Expertness_Update]') AND [type] IN (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_UserJobSkill_Expertness_Update]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UP_UserJobSkill_Expertness_Update]
	@CharGuid UNIQUEIDENTIFIER,
	@SkillNo INT,
	@Expertness INT
AS
BEGIN
	SET NOCOUNT ON;

    IF EXISTS(SELECT 1 FROM dbo.TB_UserJobSkill_Expertness WHERE [f_CharGuid] = @CharGuid AND [f_SkillNo] = @SkillNo)
	BEGIN
		UPDATE dbo.TB_UserJobSkill_Expertness SET [f_Expertness] = @Expertness WHERE [f_CharGuid] = @CharGuid AND [f_SkillNo] = @SkillNo
	END
	ELSE
	BEGIN
		INSERT INTO dbo.TB_UserJobSkill_Expertness([f_CharGuid], [f_SkillNo], [f_Expertness]) VALUES(@CharGuid, @SkillNo, @Expertness)
	END
END
GO
