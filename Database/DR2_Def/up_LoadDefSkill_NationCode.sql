USE [DR2_Def]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefSkill_Item]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefSkill_Item]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefSkill_NationCode]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefSkill_NationCode]
GO

CREATE PROC [dbo].[up_LoadDefSkill_NationCode]
AS

begin
	SELECT [NationCodeStr], [SkillNo] ,[Level] ,[NameNo] ,[RscNameNo], [f_ActionCategory] ,[ActionName]
		,[Type] ,[ClassLimit] ,[DraClassLimit], [LevelLimit] ,[WeaponLimit]
		,[StateLimit] ,[ParentSkill] ,[Target] ,[Range] ,[CastTime]
		,[CoolTime] ,[AnimationTime] ,[MP] ,[HP] ,[EffectID],[CmdStringNo]
		,[Abil01] ,[Abil02] ,[Abil03] ,[Abil04] ,[Abil05]
		,[Abil06] ,[Abil07] ,[Abil08] ,[Abil09] ,[Abil10]
		FROM [dbo].[TB_DefSkill_Player] WITH(NOLOCK)
	SELECT [NationCodeStr], [SkillNo] ,[Level] ,[NameNo] ,[RscNameNo], 0 ,[ActionName]
		,[Type] ,[ClassLimit] ,CONVERT(bigint, 0), [LevelLimit] ,[WeaponLimit]
		,[StateLimit] ,[ParentSkill] ,[Target] ,[Range] ,[CastTime]
		,[CoolTime] ,[AnimationTime] ,[MP] ,[HP] ,[EffectID],[CmdStringNo]
		,[Abil01] ,[Abil02] ,[Abil03] ,[Abil04] ,[Abil05]
		,[Abil06] ,[Abil07] ,[Abil08] ,[Abil09] ,[Abil10]
		FROM [dbo].[TB_DefSkill_Item] WITH(NOLOCK)
end
GO