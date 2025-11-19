USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefTacticsQuestPseudo]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[UP_LoadDefTacticsQuestPseudo]
GO

/****** Object:  StoredProcedure [dbo].[UP_LoadDefTacticsQuestPseudo]    Script Date: 07/09/2009 11:25:44 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<>
-- Create date: <2008.8.27>
-- Description:	<>
-- =============================================
CREATE PROCEDURE [dbo].[UP_LoadDefTacticsQuestPseudo] 
AS
BEGIN
	SET NOCOUNT ON;

	SELECT
		[TacticsLevel]
		,[Group1]
		,[Group2]
		,[Group3]
		,[Group4]
		,[Group5]
		,[Group6]
		,[Group7]
		,[Group8]
		,[Group9]
		,[Group10]
	FROM
		[TB_DefTacticsQuestPseudo]
END
GO