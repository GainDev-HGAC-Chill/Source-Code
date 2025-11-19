USE DR2_USER
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_UpdateWebCharacterComboInfo]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_UpdateWebCharacterComboInfo]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE dbo.[UP_UpdateWebCharacterComboInfo]
@f_RealmNo int
,@f_CharGuid uniqueidentifier
,@f_Latest_Combo int
,@f_Highest_Combo_Date datetime
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @HighestCombo INT

	SELECT @HighestCombo = [f_Highest_Combo] FROM [dbo].[TB_Web_UserCharacter_ComboInfo] WHERE [f_RealmNo] = @f_RealmNo AND [f_CharGuid] = @f_CharGuid
	IF @@rowcount <> 0
	BEGIN
		IF @HighestCombo < @f_Latest_Combo
		BEGIN
			UPDATE [dbo].[TB_Web_UserCharacter_ComboInfo]
			SET [f_Latest_Combo] = @f_Latest_Combo
				,[f_Highest_Combo] = @f_Latest_Combo
				,[f_Highest_Combo_Date] = @f_Highest_Combo_Date
			WHERE [f_RealmNo] = @f_RealmNo AND [f_CharGuid] = @f_CharGuid
		END
		ELSE
		BEGIN
			UPDATE [dbo].[TB_Web_UserCharacter_ComboInfo]
			SET [f_Latest_Combo] = @f_Latest_Combo
			WHERE [f_RealmNo] = @f_RealmNo AND [f_CharGuid] = @f_CharGuid
		END
	END
	ELSE
	BEGIN
		INSERT INTO [dbo].[TB_Web_UserCharacter_ComboInfo]
			([f_RealmNo]
			,[f_CharGuid]
			,[f_Latest_Combo]
			,[f_Highest_Combo]
			,[f_Highest_Combo_Date])
		VALUES
			(@f_RealmNo
			,@f_CharGuid
			,@f_Latest_Combo
			,@f_Latest_Combo
			,@f_Highest_Combo_Date)
	END
END
GO
