USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefSpecificReward]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefSpecificReward]
GO

USE [DR2_Local]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefSpecificReward]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefSpecificReward]
GO

CREATE PROCEDURE [dbo].[up_LoadDefSpecificReward]
AS

BEGIN
	SELECT [f_NationCodeStr], [Type], [SubType], [RewardItemNo], [RewardCount] FROM [dbo].[TB_DefSpecificReward]
END
