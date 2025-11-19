USE DR2_USER
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_UpdateWebCharacterInfo]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_UpdateWebCharacterInfo]
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
CREATE PROCEDURE dbo.[UP_UpdateWebCharacterInfo]
@f_RealmNo int,
@f_CharGuid uniqueidentifier,
@f_Strength int,
@f_Intelligence int,
@f_Constitution  int,
@f_Dexterity int,
@f_Physical_Attack_Min int,
@f_Physical_Attack_Max int,
@f_Magical_Attack_Min int,
@f_Magical_Attack_Max int,
@f_Accuracy_Rate int,
@f_Dodge_Rate int,
@f_Physical_Defence int,
@f_Magical_Defence int,
@f_Recovery_HP int,
@f_Recovery_MP int,
@f_Max_HP int,
@f_Max_MP int
AS
BEGIN
	SET NOCOUNT ON;

	IF EXISTS(SELECT 1 FROM [dbo].[TB_Web_UserCharacter] WHERE [f_RealmNo] = @f_RealmNo AND [f_CharGuid] = @f_CharGuid)
	BEGIN
		UPDATE [dbo].[TB_Web_UserCharacter]
		   SET [f_RealmNo] = @f_RealmNo
			  ,[f_CharGuid] = @f_CharGuid
			  ,[f_Strength] = @f_Strength
			  ,[f_Intelligence] = @f_Intelligence
			  ,[f_Constitution] = @f_Constitution
			  ,[f_Dexterity] = @f_Dexterity
			  ,[f_Physical_Attack_Min] = @f_Physical_Attack_Min
			  ,[f_Physical_Attack_Max] = @f_Physical_Attack_Max
			  ,[f_Magical_Attack_Min] = @f_Magical_Attack_Min
			  ,[f_Magical_Attack_Max] = @f_Magical_Attack_Max
			  ,[f_Accuracy_Rate] = @f_Accuracy_Rate
			  ,[f_Dodge_Rate] = @f_Dodge_Rate
			  ,[f_Physical_Defence] = @f_Physical_Defence
			  ,[f_Magical_Defence] = @f_Magical_Defence
			  ,[f_Recovery_HP] = @f_Recovery_HP
			  ,[f_Recovery_MP] = @f_Recovery_MP
			  ,[f_Max_HP] = @f_Max_HP
			  ,[f_Max_MP] = @f_Max_MP
		 WHERE [f_RealmNo] = @f_RealmNo AND [f_CharGuid] = @f_CharGuid
	END
	ELSE
	BEGIN
		INSERT INTO [dbo].[TB_Web_UserCharacter]
				   ([f_RealmNo]
				   ,[f_CharGuid]
				   ,[f_Strength]
				   ,[f_Intelligence]
				   ,[f_Constitution]
				   ,[f_Dexterity]
				   ,[f_Physical_Attack_Min]
				   ,[f_Physical_Attack_Max]
				   ,[f_Magical_Attack_Min]
				   ,[f_Magical_Attack_Max]
				   ,[f_Accuracy_Rate]
				   ,[f_Dodge_Rate]
				   ,[f_Physical_Defence]
				   ,[f_Magical_Defence]
				   ,[f_Recovery_HP]
				   ,[f_Recovery_MP]
				   ,[f_Max_HP]
				   ,[f_Max_MP] )
			 VALUES
				   (@f_RealmNo
				   ,@f_CharGuid
				   ,@f_Strength
				   ,@f_Intelligence
				   ,@f_Constitution
				   ,@f_Dexterity
				   ,@f_Physical_Attack_Min
				   ,@f_Physical_Attack_Max
				   ,@f_Magical_Attack_Min
				   ,@f_Magical_Attack_Max
				   ,@f_Accuracy_Rate
				   ,@f_Dodge_Rate
				   ,@f_Physical_Defence
				   ,@f_Magical_Defence
				   ,@f_Recovery_HP
				   ,@f_Recovery_MP
				   ,@f_Max_HP
				   ,@f_Max_MP)
	END
END
GO
