USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefDefence7_Wave]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefDefence7_Wave]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefDefence7_Wave]

AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT [Mission_No],[Mission_Type],[Party_Number],[Stage_No],[Wave_No],[Wave_Delay],[Give_StrategicPoint],[Monster01],[Monster02],[Monster03],[Monster04],[Monster05],[Monster06],[Monster07],[Monster08],[Monster09],[Monster10],[TunningNo],[AddMoveSpeedPercent],[AddExpPercent],[AddHPPercent],[DamageDecRate]

	FROM [dbo].[TB_DefDefence7_Wave]
END

GO



		