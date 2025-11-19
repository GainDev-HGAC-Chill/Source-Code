USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefRareOptMagic]    Script Date: 07/10/2009 15:08:01 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefRareOptMagic]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefRareOptMagic]

USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefRareOptMagic]    Script Date: 07/10/2009 15:08:09 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefRareOptMagic]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;


	SELECT [MagicOptNo]
		  ,[SuccessControlNo]
		  ,[MagicNo01]
		  ,[MagicNo02]
		  ,[MagicNo03]
		  ,[MagicNo04]
		  ,[MagicNo05]
		  ,[MagicNo06]
		  ,[MagicNo07]
		  ,[MagicNo08]
		  ,[MagicNo09]
		  ,[MagicNo10]
	  FROM [dbo].[TB_DefRareOptMagic]
  
END
