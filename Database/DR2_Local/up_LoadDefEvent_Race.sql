USE [DR2_local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefEvent_Race]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefEvent_Race]
GO

CREATE Proc [dbo].[up_LoadDefEvent_Race]
AS

BEGIN
	SELECT 
	[EventNo],
	[Start_Effect],
	[Limit_Time],
	[Speed_Value],
	[Skill_Use],
	[Race_Type],
	[Track_Around],
	[MP_Max],
	[Reward_Group_No1],
	[Reward_Item1_1],
	[Reward_Item1_2],
	[Reward_Item1_3],
	[Reward_Item1_4],
	[Reward_Group_No2],
	[Reward_Item2_1],
	[Reward_Item2_2],
	[Reward_Item2_3],
	[Reward_Item2_4],
	[Reward_Group_No3],
	[Reward_Item3_1],
	[Reward_Item3_2],
	[Reward_Item3_3],
	[Reward_Item3_4],
	[Reward_Group_No4],
	[Reward_Item4_1],
	[Reward_Item4_2],
	[Reward_Item4_3],
	[Reward_Item4_4],
	[Reward_Group_No5],
	[Reward_Item5_1],
	[Reward_Item5_2],
	[Reward_Item5_3],
	[Reward_Item5_4]
	FROM [dbo].[TB_DefEvent_Race] WITH(NOLOCK)
END