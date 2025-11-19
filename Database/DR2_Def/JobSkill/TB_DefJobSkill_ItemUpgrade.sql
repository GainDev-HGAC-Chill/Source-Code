USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_ItemUpgrade]') AND [type] IN (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefJobSkill_ItemUpgrade](
		[f_ItemNo] [int] NOT NULL,
		[f_Memo] nvarchar(50) NULL,
		[f_Grade] [int] NOT NULL,
		[f_Resource_GroupNo] [int] NOT NULL,
		[f_Upgrade_Count] [int] NOT NULL,
		[f_Upgrade_TimeSec] [int] NOT NULL,
		[f_Basic_Expertness] [int] NOT NULL,
		[f_GatherType] [int] NOT NULL,
		[f_Machine_UseDration] [int] NOT NULL,
		[f_ResultProbability_No] [int] NOT NULL,
		[f_Resource_ProbabilityUp] [int] NOT NULL,
		[f_ErrorStateTime_AbsoluteSec] [int] NOT NULL,
		[f_ErrorStateTime_Percent] [int] NOT NULL,
		[f_ErrorState_MaxProbability] [int] NOT NULL,
		[f_ErrorState_Probability] [int] NOT NULL
	 CONSTRAINT [PK_TB_DefJobSkill_ItemUpgrade] PRIMARY KEY CLUSTERED 
	(
		[f_ItemNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefJobSkill_ItemUpgrade') and [name] = N'f_Machine_UseDration')
BEGIN
	EXECUTE sp_rename N'dbo.TB_DefJobSkill_ItemUpgrade.f_Machine_UseDration', N'Tmp_f_Machine_UseDuration', 'COLUMN' 
	EXECUTE sp_rename N'dbo.TB_DefJobSkill_ItemUpgrade.Tmp_f_Machine_UseDuration', N'f_Machine_UseDuration', 'COLUMN' 
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefJobSkill_ItemUpgrade') and [name] = N'f_Need_SaveIdx')
BEGIN
	/* To prevent any potential data loss issues, you should review this script in detail before running it outside the context of the database designer.*/
	SET XACT_ABORT ON

	ALTER TABLE dbo.TB_DefJobSkill_ItemUpgrade ADD
		f_Need_SaveIdx int NOT NULL CONSTRAINT DF_TB_DefJobSkill_Probability_f_Need_SaveIdx DEFAULT 0

	SET XACT_ABORT OFF
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefJobSkill_ItemUpgrade') and [name] = N'f_ErrorStateTime_Percent')
BEGIN
	ALTER TABLE dbo.TB_DefJobSkill_ItemUpgrade DROP COLUMN f_ErrorStateTime_Percent
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefJobSkill_ItemUpgrade') and [name] = N'f_Resource_Type')
BEGIN
	/* To prevent any potential data loss issues, you should review this script in detail before running it outside the context of the database designer.*/
	SET XACT_ABORT ON

	ALTER TABLE dbo.TB_DefJobSkill_ItemUpgrade ADD
		f_Resource_Type int NOT NULL CONSTRAINT DF_TB_DefJobSkill_Probability_f_Resource_Type DEFAULT 0

	SET XACT_ABORT OFF
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefJobskill_ItemUpgrade') and [name] = N'f_ExpertnessUpVolume')
BEGIN
	ALTER TABLE dbo.TB_DefJobskill_ItemUpgrade ADD f_ExpertnessUpVolume INT NOT NULL CONSTRAINT DF_TB_DefJobskill_ItemUpgrade_f_ExpertnessUpVolume DEFAULT 0
END