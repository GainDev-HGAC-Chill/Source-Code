USE DR2_USER
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_UpdateWebBaseItemInfo]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_UpdateWebBaseItemInfo]
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
CREATE PROCEDURE dbo.[UP_UpdateWebBaseItemInfo]
@f_ItemNo int,
@f_ItemName nvarchar(100),
@f_IsEquipItem bit,
@f_MaxCount int,
@f_BasePhysAttackMin int,
@f_BasePhysAttackMax int,
@f_BaseMagicAttackMin int,
@f_BaseMagicAttackMax int,
@f_BasePhysDefence int,
@f_BaseMagicDefence int
AS
BEGIN
	SET NOCOUNT ON;

	IF EXISTS( SELECT * FROM [dbo].[TB_Web_BaseItemInfo] WHERE [f_ItemNo] = @f_ItemNo )
	BEGIN
		UPDATE [dbo].[TB_Web_BaseItemInfo] SET 
			[f_ItemName]				= @f_ItemName
			,[f_IsEquipItem]			= @f_IsEquipItem
			,[f_MaxCount]				= @f_MaxCount
			,[f_BasePhysAttackMin]		= @f_BasePhysAttackMin
			,[f_BasePhysAttackMax]		= @f_BasePhysAttackMax
			,[f_BaseMagicAttackMin]		= @f_BaseMagicAttackMin
			,[f_BaseMagicAttackMax]		= @f_BaseMagicAttackMax
			,[f_BasePhysDefence]		= @f_BasePhysDefence
			,[f_BaseMagicDefence]		= @f_BaseMagicDefence
		WHERE 
			[f_ItemNo] = @f_ItemNo
	END
	ELSE
	BEGIN
		INSERT INTO [dbo].[TB_Web_BaseItemInfo]
			([f_ItemNo]
			,[f_ItemName]
			,[f_IsEquipItem]
			,[f_MaxCount]
			,[f_BasePhysAttackMin]
			,[f_BasePhysAttackMax]
			,[f_BaseMagicAttackMin]
			,[f_BaseMagicAttackMax]
			,[f_BasePhysDefence]
			,[f_BaseMagicDefence])
		VALUES
			(@f_ItemNo
			,@f_ItemName
			,@f_IsEquipItem
			,@f_MaxCount
			,@f_BasePhysAttackMin
			,@f_BasePhysAttackMax
			,@f_BaseMagicAttackMin
			,@f_BaseMagicAttackMax
			,@f_BasePhysDefence
			,@f_BaseMagicDefence)
	END
END
GO
