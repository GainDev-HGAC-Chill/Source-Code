USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefMission_ClassReward]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefMission_ClassReward]
END
GO

/****** ��ü:  StoredProcedure [dbo].[up_LoadDefMission_ClassReward]    ��ũ��Ʈ ��¥: 08/15/2009 18:05:47 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefMission_ClassReward]

AS
BEGIN
	SELECT [MissionNo],[LevelNo],[ClassNo],[ItemBagNo],[Rate]
	FROM [dbo].[TB_DefMission_ClassReward] WITH(NOLOCK)

END
