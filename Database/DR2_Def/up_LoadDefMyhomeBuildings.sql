USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefMyhomeBuildings]    Script Date: 02/04/2010 20:43:03 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefMyhomeBuildings]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefMyhomeBuildings]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefMyhomeBuildings]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [BuildingNo]
		  ,[groundno]
		  ,[Grade]
		  ,[MaxRoom]
	  FROM [dbo].[TB_DefMyhomeBuildings]

END
