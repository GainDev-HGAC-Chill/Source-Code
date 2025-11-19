USE DR2_User
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UserJobSkill_SaveIdx_Update]') AND [type] IN (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_UserJobSkill_SaveIdx_Update]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UP_UserJobSkill_SaveIdx_Update]
	@CharGuid UNIQUEIDENTIFIER,
	@SaveIdxBinary binary(256)
AS
BEGIN
	SET NOCOUNT ON;

	-- table(row) is exits any time
    UPDATE [dbo].[TB_UserCharacter_Extern] SET [f_JobSkill_SaveIdx] = @SaveIdxBinary WHERE [CharacterID] = @CharGuid
END
GO
