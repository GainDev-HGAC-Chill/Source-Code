USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_LocationItem]') AND [type] IN (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefJobSkill_LocationItem](
		[f_JobGrade] [int] NOT NULL,
		[f_Memo] nvarchar(50) NULL,
		[f_GatherType] [int] NOT NULL,
		[f_Spot_Probability] [int] NOT NULL,
		[f_Spot_TotalProbability] [int] NOT NULL,
		[f_Spot_Cycle_Min] [int] NOT NULL,
		[f_Spot_Cycle_Max] [int] NOT NULL,
		[f_Spot_Dration_Min] [int] NOT NULL,
		[f_Spot_Dration_Max] [int] NOT NULL,
		[f_ResultProbability_No] [int] NOT NULL,
		[f_01Need_SaveIdx] [int] NOT NULL,
		[f_02Need_SaveIdx] [int] NOT NULL,
		[f_03Need_SaveIdx] [int] NOT NULL,
		[f_01Need_Skill_No] [int] NOT NULL,
		[f_01Need_Expertness] [int] NOT NULL,
		[f_02Need_Skill_No] [int] NOT NULL,
		[f_02Need_Expertness] [int] NOT NULL,
		[f_03Need_Skill_No] [int] NOT NULL,
		[f_03Need_Expertness] [int] NOT NULL,
		[f_Probability_UpRate] [int] NOT NULL
	 CONSTRAINT [PK_TB_DefJobSkill_LocationItem] PRIMARY KEY CLUSTERED 
	(
		[f_JobGrade] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefJobSkill_LocationItem') and [name] = N'f_Base_Expertness')
BEGIN
	CREATE TABLE dbo.Tmp_TB_DefJobSkill_LocationItem
		(
		f_JobGrade int NOT NULL,
		f_Memo nvarchar(50) NULL,
		f_GatherType int NOT NULL,
		f_Spot_Probability int NOT NULL,
		f_Spot_TotalProbability int NOT NULL,
		f_Spot_Cycle_Min int NOT NULL,
		f_Spot_Cycle_Max int NOT NULL,
		f_Spot_Dration_Min int NOT NULL,
		f_Spot_Dration_Max int NOT NULL,
		f_ResultProbability_No int NOT NULL,
		f_Base_Expertness int NOT NULL,
		f_01Need_SaveIdx int NOT NULL,
		f_02Need_SaveIdx int NOT NULL,
		f_03Need_SaveIdx int NOT NULL,
		f_01Need_Skill_No int NOT NULL,
		f_01Need_Expertness int NOT NULL,
		f_02Need_Skill_No int NOT NULL,
		f_02Need_Expertness int NOT NULL,
		f_03Need_Skill_No int NOT NULL,
		f_03Need_Expertness int NOT NULL,
		f_Probability_UpRate int NOT NULL
		)  ON [PRIMARY]
	
	IF EXISTS(SELECT * FROM dbo.TB_DefJobSkill_LocationItem)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefJobSkill_LocationItem (f_JobGrade, f_Memo, f_GatherType, f_Spot_Probability, f_Spot_TotalProbability, f_Spot_Cycle_Min, f_Spot_Cycle_Max, f_Spot_Dration_Min, f_Spot_Dration_Max, f_ResultProbability_No, f_01Need_SaveIdx, f_02Need_SaveIdx, f_03Need_SaveIdx, f_01Need_Skill_No, f_01Need_Expertness, f_02Need_Skill_No, f_02Need_Expertness, f_03Need_Skill_No, f_03Need_Expertness, f_Probability_UpRate)
			SELECT f_JobGrade, f_Memo, f_GatherType, f_Spot_Probability, f_Spot_TotalProbability, f_Spot_Cycle_Min, f_Spot_Cycle_Max, f_Spot_Dration_Min, f_Spot_Dration_Max, f_ResultProbability_No, f_01Need_SaveIdx, f_02Need_SaveIdx, f_03Need_SaveIdx, f_01Need_Skill_No, f_01Need_Expertness, f_02Need_Skill_No, f_02Need_Expertness, f_03Need_Skill_No, f_03Need_Expertness, f_Probability_UpRate FROM dbo.TB_DefJobSkill_LocationItem WITH (HOLDLOCK TABLOCKX)')
	
	DROP TABLE dbo.TB_DefJobSkill_LocationItem
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefJobSkill_LocationItem', N'TB_DefJobSkill_LocationItem', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefJobSkill_LocationItem ADD CONSTRAINT
		PK_TB_DefJobSkill_LocationItem PRIMARY KEY CLUSTERED 
		(
		f_JobGrade
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefJobSkill_LocationItem') and [NAME] = N'f_Spot_Dration_Min')
BEGIN
	EXECUTE sp_rename N'dbo.TB_DefJobSkill_LocationItem.f_Spot_Dration_Min', N'Tmp_f_Spot_Dration_Min_1', 'COLUMN' 
	EXECUTE sp_rename N'dbo.TB_DefJobSkill_LocationItem.Tmp_f_Spot_Dration_Min_1', N'f_Spot_Duration_Min', 'COLUMN'
	EXECUTE sp_rename N'dbo.TB_DefJobSkill_LocationItem.f_Spot_Dration_Max', N'Tmp_f_Spot_Dration_Max_1', 'COLUMN' 
	EXECUTE sp_rename N'dbo.TB_DefJobSkill_LocationItem.Tmp_f_Spot_Dration_Max_1', N'f_Spot_Duration_Max', 'COLUMN' 
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefJobSkill_LocationItem') and [NAME] = N'f_01ResultProbability_No')
BEGIN

	CREATE TABLE dbo.Tmp_TB_DefJobSkill_LocationItem
		(
		f_JobGrade int NOT NULL,
		f_Memo nvarchar(50) NULL,
		f_GatherType int NOT NULL,
		f_Spot_Probability int NOT NULL,
		f_Spot_TotalProbability int NOT NULL,
		f_Spot_Cycle_Min int NOT NULL,
		f_Spot_Cycle_Max int NOT NULL,
		f_Spot_Duration_Min int NOT NULL,
		f_Spot_Duration_Max int NOT NULL,
		f_01ResultProbability_No int NOT NULL,
		f_02ResultProbability_No int NOT NULL,
		f_03ResultProbability_No int NOT NULL,
		f_04ResultProbability_No int NOT NULL,
		f_05ResultProbability_No int NOT NULL,
		f_06ResultProbability_No int NOT NULL,
		f_07ResultProbability_No int NOT NULL,
		f_08ResultProbability_No int NOT NULL,
		f_09ResultProbability_No int NOT NULL,
		f_10ResultProbability_No int NOT NULL,
		f_Base_Expertness int NOT NULL,
		f_01Need_SaveIdx int NOT NULL,
		f_02Need_SaveIdx int NOT NULL,
		f_03Need_SaveIdx int NOT NULL,
		f_01Need_Skill_No int NOT NULL,
		f_01Need_Expertness int NOT NULL,
		f_02Need_Skill_No int NOT NULL,
		f_02Need_Expertness int NOT NULL,
		f_03Need_Skill_No int NOT NULL,
		f_03Need_Expertness int NOT NULL,
		f_Probability_UpRate int NOT NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'직업스킬(채집), 채집 장소 설정 테이블'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefJobSkill_LocationItem', NULL, NULL
	
	IF EXISTS(SELECT * FROM dbo.TB_DefJobSkill_LocationItem)
	BEGIN
		 INSERT INTO dbo.Tmp_TB_DefJobSkill_LocationItem (f_JobGrade, f_Memo, f_GatherType, f_Spot_Probability, f_Spot_TotalProbability, f_Spot_Cycle_Min, f_Spot_Cycle_Max, f_Spot_Duration_Min, f_Spot_Duration_Max, f_01ResultProbability_No, f_02ResultProbability_No, f_03ResultProbability_No, f_04ResultProbability_No, f_05ResultProbability_No, f_06ResultProbability_No, f_07ResultProbability_No, f_08ResultProbability_No, f_09ResultProbability_No, f_10ResultProbability_No, f_Base_Expertness, f_01Need_SaveIdx, f_02Need_SaveIdx, f_03Need_SaveIdx, f_01Need_Skill_No, f_01Need_Expertness, f_02Need_Skill_No, f_02Need_Expertness, f_03Need_Skill_No, f_03Need_Expertness, f_Probability_UpRate)
		 SELECT f_JobGrade, f_Memo, f_GatherType, f_Spot_Probability, f_Spot_TotalProbability, f_Spot_Cycle_Min, f_Spot_Cycle_Max, f_Spot_Duration_Min, f_Spot_Duration_Max, f_ResultProbability_No, 0, 0, 0, 0, 0, 0, 0, 0, 0, f_Base_Expertness, f_01Need_SaveIdx, f_02Need_SaveIdx, f_03Need_SaveIdx, f_01Need_Skill_No, f_01Need_Expertness, f_02Need_Skill_No, f_02Need_Expertness, f_03Need_Skill_No, f_03Need_Expertness, f_Probability_UpRate FROM dbo.TB_DefJobSkill_LocationItem WITH (HOLDLOCK TABLOCKX)
	END	

	DROP TABLE dbo.TB_DefJobSkill_LocationItem
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefJobSkill_LocationItem', N'TB_DefJobSkill_LocationItem', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefJobSkill_LocationItem ADD CONSTRAINT
		PK_TB_DefJobSkill_LocationItem PRIMARY KEY CLUSTERED 
		(
		f_JobGrade
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
