USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefMixupItem]    Script Date: 07/14/2009 22:09:08 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefMixupItem]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefMixupItem]

USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefMixupItem]    Script Date: 07/14/2009 22:09:18 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefMixupItem]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT     [ItemGrade]
		  ,[EquipPos]
		  ,[GenderLimit]
		  ,[SuccessControlNo]
		  ,[RarityControlNo]
		  ,[ItemBagNo01]
		  ,[ItemBagNo02]
		  ,[ItemBagNo03]
		  ,[ItemBagNo04]
		  ,[ItemBagNo05]
		  ,[ItemBagNo06]
		  ,[ItemBagNo07]
		  ,[ItemBagNo08]
		  ,[ItemBagNo09]
		  ,[ItemBagNo10]
	  FROM [dbo].[TB_DefMixupItem]

END
