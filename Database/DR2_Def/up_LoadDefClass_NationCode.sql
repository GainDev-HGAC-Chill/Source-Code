USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefClass_NationCode]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefClass_NationCode]
GO

CREATE Proc [dbo].[up_LoadDefClass_NationCode]
AS
SET Nocount On;
begin
	SELECT	A.[NationCodeStr],
			A.[iClass],
			A.[iLevel],
			A.[Experience],
			A.[MaxHP],
			A.[HP_Recovery_Speed],
			A.[HP_Recovery],
			A.[MaxMP],
			A.[MP_Recovery_Speed],
			A.[MP_Recovery],
			A.[Str],
			A.[Int],
			A.[Con],
			A.[Dex],
			A.[MoveSpeed],
			A.[Abil01],
			A.[Abil02],
			A.[Abil03],
			A.[Abil04],
			A.[Abil05],
			A.[Abil06],
			A.[Abil07],
			A.[Abil08],
			A.[Abil09],
			A.[Abil10],
			ISNULL(B.[BonusStatus], 0),
			ISNULL(B.[Limit_STR_ADD], 0),
			ISNULL(B.[Limit_INT_ADD], 0),
			ISNULL(B.[Limit_CON_ADD], 0),
			ISNULL(B.[Limit_DEX_ADD], 0)
		FROM [dbo].[TB_DefClass] AS A WITH(NOLOCK)
		LEFT JOIN [dbo].[TB_DefClass_Bonus] AS B ON A.[iClass] = B.[Class] AND A.[iLevel] = B.[Level] 

	SELECT	A.[NationCodeStr],
			A.[iClass],
			A.[iLevel],
			A.[Experience],
			A.[MaxHP],
			A.[HP_Recovery_Speed],
			A.[HP_Recovery],
			A.[MaxMP],
			A.[MP_Recovery_Speed],
			A.[MP_Recovery],
			A.[Str],
			A.[Int],
			A.[Con],
			A.[Dex],
			A.[MoveSpeed],
			A.[Abil01],
			A.[Abil02],
			A.[Abil03],
			A.[Abil04],
			A.[Abil05],
			A.[Abil06],
			A.[Abil07],
			A.[Abil08],
			A.[Abil09],
			A.[Abil10],
			ISNULL(B.[BonusStatus], 0),
			ISNULL(B.[Limit_STR_ADD], 0),
			ISNULL(B.[Limit_INT_ADD], 0),
			ISNULL(B.[Limit_CON_ADD], 0),
			ISNULL(B.[Limit_DEX_ADD], 0)
		FROM [dbo].[TB_DefClass_Monster] AS A WITH(NOLOCK)
		LEFT JOIN [dbo].[TB_DefClass_Bonus] AS B ON A.[iClass] = B.[Class] AND A.[iLevel] = B.[Level] 

	SELECT	A.[NationCodeStr],
			A.[iClass],
			A.[iLevel],
			A.[Experience],
			A.[MaxHP],
			A.[HP_Recovery_Speed],
			A.[HP_Recovery],
			A.[MaxMP],
			A.[MP_Recovery_Speed],
			A.[MP_Recovery],
			A.[Str],
			A.[Int],
			A.[Con],
			A.[Dex],
			A.[MoveSpeed],
			A.[Abil01],
			A.[Abil02],
			A.[Abil03],
			A.[Abil04],
			A.[Abil05],
			A.[Abil06],
			A.[Abil07],
			A.[Abil08],
			A.[Abil09],
			A.[Abil10],
			ISNULL(B.[BonusStatus], 0),
			ISNULL(B.[Limit_STR_ADD], 0),
			ISNULL(B.[Limit_INT_ADD], 0),
			ISNULL(B.[Limit_CON_ADD], 0),
			ISNULL(B.[Limit_DEX_ADD], 0)
		FROM [dbo].[TB_DefClass_Skill] AS A WITH(NOLOCK)
		LEFT JOIN [dbo].[TB_DefClass_Bonus] AS B ON A.[iClass] = B.[Class] AND A.[iLevel] = B.[Level] 
end
