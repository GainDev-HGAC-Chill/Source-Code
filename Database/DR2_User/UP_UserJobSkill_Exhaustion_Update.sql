USE DR2_User
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UserJobSkill_Exhaustion_Update]') AND [type] IN (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_UserJobSkill_Exhaustion_Update]
END


SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UP_UserJobSkill_Exhaustion_Update]
	@CharGuid UNIQUEIDENTIFIER,
	@Exhaustion INT,
	@BlessPoint INT,
	@LastResetExhaustionTime DATETIME,
	@LastResetBlessPointTime DATETIME
AS
BEGIN
	SET NOCOUNT ON;

    IF EXISTS(SELECT 1 FROM dbo.TB_UserJobSkill_Exhaustion WHERE [f_CharGuid] = @CharGuid)
	BEGIN
		UPDATE dbo.TB_UserJobSkill_Exhaustion SET
			[f_Exhaustion] = @Exhaustion
			, [f_BlessPoint] = @BlessPoint
			, [f_LastResetExhaustionTime] = @LastResetExhaustionTime
			, [f_LastResetBlessPointTime] = @LastResetBlessPointTime
			WHERE [f_CharGuid] = @CharGuid
	END
	ELSE
	BEGIN
		INSERT INTO dbo.TB_UserJobSkill_Exhaustion
		([f_CharGuid], [f_Exhaustion], [f_BlessPoint], [f_LastResetExhaustionTime], [f_LastResetBlessPointTime])
		VALUES(@CharGuid, @Exhaustion, @BlessPoint, @LastResetExhaustionTime, @LastResetBlessPointTime)
	END
END
GO
