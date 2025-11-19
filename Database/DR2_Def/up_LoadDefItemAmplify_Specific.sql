USE [DR2_Def]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemAmplify_Specific]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefItemAmplify_Specific]
GO

CREATE PROCEDURE [dbo].[up_LoadDefItemAmplify_Specific]
AS

BEGIN
	SELECT [f_NationCodeStr], [EquipType], [Abil_Type], [AmplifyRate_Specific]
		FROM [dbo].[TB_DefItemAmplify_Specific] WITH(nolock)
END
GO
