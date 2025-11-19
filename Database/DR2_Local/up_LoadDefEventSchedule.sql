USE [DR2_local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefEventSchedule]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefEventSchedule]
GO

CREATE Proc [dbo].[up_LoadDefEventSchedule]
AS

BEGIN
	SELECT
	[Menu_Txt],
	[Event_Type],
	[Event_No],
	[Event_Ground],
	[Level_Min],
	[Level_Max],
	[Class_Limit_Human],
	[Class_Limit_Dragon],
	[Party_Member_Min],
	[UserCount_Max],
	[IS_PK],
	[Need_Quest],
	[Need_Quest_State],
	[Need_ItemNo],
	[Need_ItemCount],
	[Unusable_ConsumeItem],
	[Unusable_ReviveItem],
	[Start_Date],
	[Start_Time],
	[End_Date],
	[Event_Period],
	[Event_Count],
	[DayofWeek]
	FROM [dbo].[TB_DefEventSchedule] WITH(NOLOCK)
END
