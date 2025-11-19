USE DR2_USER
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_UpdateWebCharacterNItemInfo_Null]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_UpdateWebCharacterNItemInfo_Null]
END
IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_UpdateWebCharacterItemInfo_Null]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_UpdateWebCharacterItemInfo_Null]
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
CREATE PROCEDURE dbo.[UP_UpdateWebCharacterItemInfo_Null]
@f_RealmNo INT
AS
BEGIN
	IF NOT EXISTS(SELECT 1 FROM [dbo].[TB_Web_UserItemInfo_Status] WHERE [f_ItemGuid] = N'00000000-0000-0000-0000-000000000000')
	BEGIN
		INSERT INTO [dbo].[TB_Web_UserItemInfo_Status]
			   ([f_RealmNo]
			   ,[f_ItemGuid]
			   ,[f_PhysAttackMin]
			   ,[f_PhysAttackMax]
			   ,[f_MagicAttackMin]
			   ,[f_MagicAttackMax]
			   ,[f_PhysDefence]
			   ,[f_MagicDefence]
			   ,[f_EnchantLevel]
			   ,[f_RarityLevel]
			   ,[f_RarityValue]
			   ,[f_RapairMoney])
		 VALUES
			   (@f_RealmNo
			   ,N'00000000-0000-0000-0000-000000000000'
			   ,0
			   ,0
			   ,0
			   ,0
			   ,0
			   ,0
			   ,0
			   ,0
			   ,0
			   ,0)
	END
END
GO
