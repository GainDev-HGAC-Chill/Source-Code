USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefCashItemAbilFilter]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefCashItemAbilFilter]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE dbo.up_LoadDefCashItemAbilFilter
AS
BEGIN

	SET NOCOUNT ON;

	SELECT [AbilType]
	  FROM [dbo].[TB_DefCashItemAbilFilter]

END
GO
