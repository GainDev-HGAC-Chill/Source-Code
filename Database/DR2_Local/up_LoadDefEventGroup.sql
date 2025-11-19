USE [DR2_local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefEventGroup]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefEventGroup]
GO

CREATE Proc [dbo].[up_LoadDefEventGroup]
AS

BEGIN
	SELECT 
	[EventGroup], 
	[MonsterGroup], 
	[StartTime], 
	[EndTime], 
	[RegenPeriod], 
	[DelayGenTime], 
	[Message] 
	from [dbo].[TB_DefEventGroup] WITH(NOLOCK)
END
