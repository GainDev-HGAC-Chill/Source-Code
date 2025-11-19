USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefQuest_LevelReward]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefQuest_LevelReward](
	iLevel int NOT NULL,
	iLevelPerExp int NOT NULL,
	iLevelPerMoney int NOT NULL
	)  ON [PRIMARY]
	
	RETURN
END
GO
