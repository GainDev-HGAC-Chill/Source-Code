USE DR2_User

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Item_Add_UnbindDate]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_Item_Add_UnbindDate]
END 

GO

-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Item_Add_UnbindDate]
@CharacterGuid UNIQUEIDENTIFIER,
@ItemGuid UNIQUEIDENTIFIER,
@DelayDays TINYINT
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	INSERT INTO dbo.TB_UserItem_UnbindDate (CharacterGuid,ItemGuid,UnbindDate)
	VALUES(@CharacterGuid,@ItemGuid,DATEADD(DAY,@DelayDays,GETDATE()))

END


GO