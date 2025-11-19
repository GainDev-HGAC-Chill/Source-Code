USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefTacticsLevel]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[UP_LoadDefTacticsLevel]
GO

/****** Object:  StoredProcedure [dbo].[UP_LoadDefTacticsLevel]    Script Date: 07/09/2009 11:25:43 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<>
-- Create date: <2008.8.27>
-- Description:	<>
-- =============================================
CREATE PROCEDURE [dbo].[UP_LoadDefTacticsLevel] 
AS
BEGIN
	SET NOCOUNT ON;

	SELECT [TacticsLevel]
	,[Exp]
	,[TacticsLevelTextID]
	FROM [TB_DefTacticsLevel]
END
GO