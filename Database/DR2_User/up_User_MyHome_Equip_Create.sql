USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_User_MyHome_Equip_Create]    Script Date: 08/07/2009 22:09:59 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_Equip_Create]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_Equip_Create]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_User_MyHome_Equip_Create]
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

	-- 있는것에 다시 덥어 써도 상관 없는 정보임	
	EXEC dbo.up_User_MyHome_Equip_Delete @ItemGuid
	
	INSERT INTO [dbo].[TB_User_MyHome_EquipItem]
			   ([ItemGuid]
			   ,[x]
			   ,[y]
			   ,[z]
			   ,[Dir]
			   ,[ParentGuid]
			   ,[LinkIdx])
		 VALUES
			   (@ItemGuid
			   ,@x
			   ,@y
			   ,@z
			   ,@dir
			   ,@ParentGuid
			   ,@LinkIdx)
           
END


