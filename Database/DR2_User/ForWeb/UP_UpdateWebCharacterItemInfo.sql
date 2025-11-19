USE DR2_USER
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_UpdateWebCharacterItemInfo]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_UpdateWebCharacterItemInfo]
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
CREATE PROCEDURE dbo.[UP_UpdateWebCharacterItemInfo]
@f_RealmNo int
,@f_CharGuid uniqueidentifier
,@f_ItemNo int
,@f_ItemGuid uniqueidentifier
,@f_CurCount int
,@f_InvType int
,@f_InvPos int
,@f_PhysAttackMin int
,@f_PhysAttackMax int
,@f_MagicAttackMin int
,@f_MagicAttackMax int
,@f_PhysDefence int
,@f_MagicDefence int
,@f_EnchantLevel int
,@f_RarityLevel int
,@f_RarityValue int
,@f_RapairMoney bigint
AS
BEGIN
	INSERT INTO [dbo].[TB_Web_UserItemInfo]
           ([f_RealmNo]
           ,[f_CharGuid]
           ,[f_ItemNo]
           ,[f_ItemGuid]
           ,[f_CurCount]
           ,[f_InvType]
           ,[f_InvPos])
     VALUES
           (@f_RealmNo
           ,@f_CharGuid
           ,@f_ItemNo
           ,@f_ItemGuid
           ,@f_CurCount
           ,@f_InvType
           ,@f_InvPos)

	IF @f_ItemGuid <> N'00000000-0000-0000-0000-000000000000' AND 
		(@f_PhysAttackMin <> 0 OR 
		@f_PhysAttackMax <> 0 OR 
		@f_MagicAttackMin <> 0 OR 
		@f_MagicAttackMax <> 0 OR 
		@f_PhysDefence <> 0 OR 
		@f_MagicDefence <> 0 OR 
		@f_EnchantLevel <> 0 OR 
		@f_RarityLevel <> 0 OR 
		@f_RarityValue <> 0 OR 
		@f_RapairMoney <> 0)
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
			   ,@f_ItemGuid
			   ,@f_PhysAttackMin
			   ,@f_PhysAttackMax
			   ,@f_MagicAttackMin
			   ,@f_MagicAttackMax
			   ,@f_PhysDefence
			   ,@f_MagicDefence
			   ,@f_EnchantLevel
			   ,@f_RarityLevel
			   ,@f_RarityValue
			   ,@f_RapairMoney)
	END
END
GO
