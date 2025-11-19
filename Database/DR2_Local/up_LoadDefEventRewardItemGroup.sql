USE [DR2_local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefEventRewardItemGroup]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefEventRewardItemGroup]
GO

CREATE Proc [dbo].[up_LoadDefEventRewardItemGroup]
AS

BEGIN
	SELECT 
	[RewardItemGroup], 
	[ItemNo], 
	[Rate], 
	[Count]	
	from [dbo].[TB_DefEventRewardItemGroup] WITH(NOLOCK)
END
