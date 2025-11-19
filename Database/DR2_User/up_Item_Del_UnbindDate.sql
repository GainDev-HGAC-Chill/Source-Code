USE DR2_User

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Item_Del_UnbindDate]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_Item_Del_UnbindDate]
END 
GO

-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Item_Del_UnbindDate]
@ItemGuid UNIQUEIDENTIFIER
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	DELETE FROM dbo.TB_UserItem_UnbindDate WHERE ItemGuid = @ItemGuid

END

GO