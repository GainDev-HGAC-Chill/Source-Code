USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_User_MyHome_Equip_Delete]    Script Date: 08/07/2009 22:06:58 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_Equip_Delete]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_Equip_Delete]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_User_MyHome_Equip_Delete]
@ItemGuid UNIQUEIDENTIFIER
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	DELETE FROM [dbo].[TB_User_MyHome_EquipItem]
		  WHERE ItemGuid = @ItemGuid
		  
END

