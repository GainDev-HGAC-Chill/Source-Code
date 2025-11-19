USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefRediceCost]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefRediceCost]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefRediceCost]
AS
BEGIN

	SET NOCOUNT ON;
	select ItemGrade, NeedItemCount from dbo.TB_DefRediceOptionCost

END
