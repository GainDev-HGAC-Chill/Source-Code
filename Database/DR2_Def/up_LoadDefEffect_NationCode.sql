USE [DR2_Def]
GO

/* Nation Code 추가 때문에 up_LoadDefEffect2에서 따로 분리 */

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefEffect_Item]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefEffect_Item]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefEffect_NationCode]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefEffect_NationCode]
GO

CREATE PROCEDURE [dbo].[up_LoadDefEffect_NationCode]
AS

BEGIN
	SELECT [NationCodeStr], [EffectID] ,[Name] ,[ActionName] ,[Type] ,[Interval] ,[DurationTime], [Toggle]
		,[Abil01] ,[Abil02] ,[Abil03] ,[Abil04] ,[Abil05]
		,[Abil06] ,[Abil07] ,[Abil08] ,[Abil09] ,[Abil10]
		FROM [dbo].[TB_DefEffect_Player] with(nolock)
	SELECT [NationCodeStr], [EffectID] ,[Name] ,[ActionName] ,[Type] ,[Interval] ,[DurationTime], [Toggle]
		,[Abil01] ,[Abil02] ,[Abil03] ,[Abil04] ,[Abil05]
		,[Abil06] ,[Abil07] ,[Abil08] ,[Abil09] ,[Abil10]
		FROM [dbo].[TB_DefEffect_Item] with(nolock)
END
