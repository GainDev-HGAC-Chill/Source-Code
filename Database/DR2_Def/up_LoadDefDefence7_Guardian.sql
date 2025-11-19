USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefDefence7_Guardian]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefDefence7_Guardian]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefDefence7_Guardian]

AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT [Guardian_No],[Monster_No],[Guardian_Abil01],[Guardian_Abil02],[Guardian_TunningNo],[Need_StrategicPoint],[Upgrade_Type],[Upgrade_Step],[Upgrade_01],[Upgrade_02],
		[Skill01_No], [Skill01_StrategicPoint], [Skill02_No], [Skill02_StrategicPoint], [Sell_StrategicPoint], [GuardianType], [AutoSell_StrategicPoint]
	FROM [dbo].[TB_DefDefence7_Guardian]
END

GO



		