USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_User_MyHome_Equip_Modify]    Script Date: 08/07/2009 22:07:35 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_Equip_Modify]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_Equip_Modify]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_User_MyHome_Equip_Modify]
@ItemGuid UNIQUEIDENTIFIER,
@x FLOAT,
@y FLOAT,
@z FLOAT,
@dir SMALLINT,
@ParentGuid UNIQUEIDENTIFIER,
@LinkIdx TINYINT

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	UPDATE [dbo].[TB_User_MyHome_EquipItem]
	   SET 
		  [x] = @x
		  ,[y] = @y
		  ,[z] = @z
		  ,[Dir] = @dir
		  ,[ParentGuid] = @ParentGuid
		  ,[LinkIdx] = @LinkIdx
	 WHERE [ItemGuid] = @ItemGuid
END


