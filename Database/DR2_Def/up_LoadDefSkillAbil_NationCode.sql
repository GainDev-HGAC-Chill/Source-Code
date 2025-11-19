USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefSkillAbil_Item]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefSkillAbil_Item]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefSkillAbil_NationCode]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefSkillAbil_NationCode]
GO

CREATE PROCEDURE [dbo].[up_LoadDefSkillAbil_NationCode]
AS

BEGIN
	SELECT [NationCodeStr], [SkillAbilID], 
		[Type01], [Value01], [Type02], [Value02], [Type03], [Value03], 
		[Type04], [Value04], [Type05], [Value05], [Type06], [Value06], 
		[Type07], [Value07], [Type08], [Value08], [Type09], [Value09], 
		[Type10], [Value10] 
		FROM [dbo].[TB_DefSkillAbil_Player] WITH(NOLOCK)
	SELECT [NationCodeStr], [SkillAbilID], 
		[Type01], [Value01], [Type02], [Value02], [Type03], [Value03], 
		[Type04], [Value04], [Type05], [Value05], [Type06], [Value06], 
		[Type07], [Value07], [Type08], [Value08], [Type09], [Value09], 
		[Type10], [Value10] 
		FROM [dbo].[TB_DefSkillAbil_Item] WITH(NOLOCK)
END
GO
