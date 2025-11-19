USE DR2_Def

IF NOT EXISTS (SELECT * FROM sys.all_objects WHERE NAME = 'DF_TB_DefMission_LevelRoot_Level_Defence')
BEGIN
	ALTER TABLE [dbo].[TB_DefMission_LevelRoot] ADD
		[Level_Defence] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_LevelRoot_Level_Defence] DEFAULT ((0))
END

IF NOT EXISTS (SELECT * FROM sys.all_objects WHERE NAME = 'DF_TB_DefMission_LevelRoot_Level_Defence7')
BEGIN
	ALTER TABLE [dbo].[TB_DefMission_LevelRoot] ADD
		[Level_Defence7] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_LevelRoot_Level_Defence7] DEFAULT ((0))
END

IF NOT EXISTS (SELECT * FROM sys.all_objects WHERE NAME = 'DF_TB_DefMission_LevelRoot_Level_Defence8')
BEGIN
	ALTER TABLE [dbo].[TB_DefMission_LevelRoot] ADD
		[Level_Defence8] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_LevelRoot_Level_Defence8] DEFAULT ((0))
END

GO
