USE DR2_User
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UserJobSkill_HistoryItem_Update]') AND [type] IN (N'P'))
BEGIN
	DROP PROCEDURE [dbo].[UP_UserJobSkill_HistoryItem_Update]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UP_UserJobSkill_HistoryItem_Update]
	@CharGuid UNIQUEIDENTIFIER,
	@HistoryItemBinary binary(40)
AS
BEGIN
	SET NOCOUNT ON;

	-- table(row) is exits any time
    UPDATE [dbo].[TB_UserCharacter_Extern] SET [f_JobSkill_HistoryItem] = @HistoryItemBinary WHERE [CharacterID] = @CharGuid
END
GO
