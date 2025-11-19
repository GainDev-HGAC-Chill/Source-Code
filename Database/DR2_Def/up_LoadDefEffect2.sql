USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefEffect2]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefEffect2]
GO

CREATE PROCEDURE [dbo].[up_LoadDefEffect2]
AS

BEGIN	
	SELECT [EffectID] ,[Name] ,[ActionName] ,[Type] ,[Interval] ,[DurationTime], [Toggle]
		,[Abil01] ,[Abil02] ,[Abil03] ,[Abil04] ,[Abil05]
		,[Abil06] ,[Abil07] ,[Abil08] ,[Abil09] ,[Abil10]
		FROM [dbo].[TB_DefEffect_Mon] with(nolock)
	SELECT [EffectID] ,[Name] ,[ActionName] ,[Type] ,[Interval] ,[DurationTime], [Toggle]
		,[Abil01] ,[Abil02] ,[Abil03] ,[Abil04] ,[Abil05]
		,[Abil06] ,[Abil07] ,[Abil08] ,[Abil09] ,[Abil10]
		FROM [dbo].[TB_DefEffect_Pet] with(nolock)
END
