USE [DR2_Local]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefGambleMachine]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefGambleMachine]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefGambleMachine]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Coin]
		  ,[ItemNo1]
		  ,[ItemNo2]
		  ,[Count]
		  ,[Rate]
		  ,[Broadcast]
		  ,[TimeType]
		  ,[UseTime]
		  ,[GroupNo]
	  FROM [dbo].[TB_DefGambleMachine]

	SELECT CoinType,Cost from [dbo].[TB_DefGambleMachineCost]

	SELECT [GroupNo]
      ,[U]
      ,[V]
      ,[UVIndex]
      ,[IconPath]
	  ,[Description]
	  ,[DisplayRank]
	  ,[Title]
	FROM [dbo].[TB_DefGambleMachineGroupRes] 

	SELECT [MixPoint]
		  ,[GradeNo]
		  ,[Rate]
	  FROM [dbo].[TB_DefGambleMachineMixup]

	SELECT [Grade]
      	,[MixPoint]
  	FROM [dbo].[TB_DefGambleMachineMixupPoint]

END
