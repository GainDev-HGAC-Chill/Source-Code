USE [DR2_Def]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefMissionBonusMap]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefMissionBonusMap]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefMissionBonusMap]

AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT [LevelNo],[Use],[TimeLimit],[ChanceRate],[Bonus1stMapRate],[BonusMap1],[BonusMap2]

	FROM [dbo].[TB_DefMissionBonusMap]
END

GO



		