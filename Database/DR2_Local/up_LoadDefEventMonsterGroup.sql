USE [DR2_local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefEventMonsterGroup]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefEventMonsterGroup]
GO

CREATE Proc [dbo].[up_LoadDefEventMonsterGroup]
AS

BEGIN
	SELECT 
	[MonsterGroup],
	[MapNo],
	[MonsterNo],
	[Gen_Delay],
	[Order],
	[Monster_Level],
	[Difficulty_HP],
	[Difficulty_Damage],
	[Difficulty_Defence],
	[Difficulty_Exp],
	[Difficulty_AttackSpeed],
	[Difficulty_Evade],
	[Difficulty_Hitrate],
	[PosX],
	[PosY],
	[PosZ],
	[RewardItemGroup],
	[RewardItemCount]
	from [dbo].[TB_DefEventMonsterGroup] WITH(NOLOCK)
END
