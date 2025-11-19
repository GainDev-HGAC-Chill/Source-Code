USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefDefenceWave]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefDefenceWave]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefDefenceWave]

AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT [Wave_GroupNo],[Wave_No],[Wave_Delay],[Monster01],[Monster02],[Monster03],[Monster04],[Monster05],[Monster06],[Monster07],[Monster08],[Monster09],[Monster10], 
			[AddMoveSpeedPercent], [TunningNo], [AddExpPercent], [AddHPPercent], [AddDamagePercent]
	FROM [dbo].[TB_DefDefenceWave]
END

GO
