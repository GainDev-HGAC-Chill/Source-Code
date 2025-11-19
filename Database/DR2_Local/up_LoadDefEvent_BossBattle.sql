USE [DR2_local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefEvent_BossBattle]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefEvent_BossBattle]
GO

CREATE Proc [dbo].[up_LoadDefEvent_BossBattle]
AS

BEGIN
	SELECT 
	[Event_No],
	[Start_Effect],
	[Limit_Time],
	[Monster_Regen_Type],
	[MonsterGroup_No],
	[Harvest_Lumber_EventItemNo],
	[Harvest_Gem_EventItemNo],
	[Harvest_Herb_EventItemNo],
	[Harvest_Fish_EventItemNo],
	[Harvest_Exp_Min]
	FROM [dbo].[TB_DefEvent_BossBattle] WITH(NOLOCK)
END