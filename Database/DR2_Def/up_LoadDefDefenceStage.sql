USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefDefenceStage]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefDefenceStage]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefDefenceStage]

AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT [MissionNo],[Party_Number],[Stage_No],[Stage_Time],[Wave_GroupNo],[AddMonster_GroupNo],[TimeToExp_Rate],[ResultNo],[ResultCount],[Direction_Item]
	FROM [dbo].[TB_DefDefenceStage]
END

GO
