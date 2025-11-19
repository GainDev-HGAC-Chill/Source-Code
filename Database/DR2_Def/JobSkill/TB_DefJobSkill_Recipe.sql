USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_Recipe]') AND [type] IN (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefJobSkill_Recipe](
		[f_Recipe_ItemNo] [int] NOT NULL,
		[f_Order_ID] [int] NOT NULL,
		[f_Memo] NVARCHAR(50) NULL,
		[f_01Need_JobSkill_No] [int] NOT NULL,
		[f_01Need_JobSkill_Expertness] [int] NOT NULL,
		[f_02Need_JobSkill_No] [int] NOT NULL,
		[f_02Need_JobSkill_Expertness] [int] NOT NULL,
		[f_03Need_JobSkill_No] [int] NOT NULL,
		[f_03Need_JobSkill_Expertness] [int] NOT NULL,
		[f_01Resource_GroupNo] [int] NOT NULL,
		[f_01Resource_Grade] [int] NOT NULL,
		[f_01Resource_Count] [int] NOT NULL,
		[f_02Resource_GroupNo] [int] NOT NULL,
		[f_02Resource_Grade] [int] NOT NULL,
		[f_02Resource_Count] [int] NOT NULL,
		[f_03Resource_GroupNo] [int] NOT NULL,
		[f_03Resource_Grade] [int] NOT NULL,
		[f_03Resource_Count] [int] NOT NULL,
		[f_04Resource_GroupNo] [int] NOT NULL,
		[f_04Resource_Grade] [int] NOT NULL,
		[f_04Resource_Count] [int] NOT NULL,
		[f_NeedMoney] [int] NOT NULL,
		[f_ResultProbability_No] [int] NOT NULL,
		[f_ResultProbability_UpRate] [int] NOT NULL,
		[f_ResultProbability_UpRate_Item] [int] NOT NULL
	 CONSTRAINT [PK_TB_DefJobSkill_Recipe] PRIMARY KEY CLUSTERED 
	(
		[f_Recipe_ItemNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_Recipe]') AND [name] = N'f_Need_ProductPoint')
BEGIN
	ALTER TABLE [dbo].[TB_DefJobSkill_Recipe] ADD f_Need_ProductPoint int NOT NULL CONSTRAINT DF_TB_DefJobSkill_SaveIdx_f_Need_ProductPoint DEFAULT (0)
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_Recipe]') AND [name] = N'f_Expertness_Gain')
BEGIN
	ALTER TABLE [dbo].[TB_DefJobSkill_Recipe] ADD f_Expertness_Gain int NOT NULL CONSTRAINT DF_TB_DefJobSkill_SaveIdx_f_Expertness_Gain DEFAULT (0)
END
GO

IF NOT EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefJobSkill_Recipe]') AND [name] = N'NationCodeStr')
BEGIN
	CREATE TABLE dbo.Tmp_TB_DefJobSkill_Recipe
	(
		NationCodeStr nvarchar(50) NOT NULL,
		f_Recipe_ItemNo int NOT NULL,
		f_Order_ID int NOT NULL,
		f_Memo nvarchar(50) NULL,
		f_01Need_JobSkill_No int NOT NULL,
		f_01Need_JobSkill_Expertness int NOT NULL,
		f_02Need_JobSkill_No int NOT NULL,
		f_02Need_JobSkill_Expertness int NOT NULL,
		f_03Need_JobSkill_No int NOT NULL,
		f_03Need_JobSkill_Expertness int NOT NULL,
		f_01Resource_GroupNo int NOT NULL,
		f_01Resource_Grade int NOT NULL,
		f_01Resource_Count int NOT NULL,
		f_02Resource_GroupNo int NOT NULL,
		f_02Resource_Grade int NOT NULL,
		f_02Resource_Count int NOT NULL,
		f_03Resource_GroupNo int NOT NULL,
		f_03Resource_Grade int NOT NULL,
		f_03Resource_Count int NOT NULL,
		f_04Resource_GroupNo int NOT NULL,
		f_04Resource_Grade int NOT NULL,
		f_04Resource_Count int NOT NULL,
		f_NeedMoney int NOT NULL,
		f_ResultProbability_No int NOT NULL,
		f_ResultProbability_UpRate int NOT NULL,
		f_ResultProbability_UpRate_Item int NOT NULL,
		f_Need_ProductPoint int NOT NULL,
		f_Expertness_Gain int NOT NULL
	CONSTRAINT PK_TB_DefJobSkill_Recipe2 PRIMARY KEY CLUSTERED 
	(
		[NationCodeStr],
		[f_Recipe_ItemNo]
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
	
	IF EXISTS (SELECT * FROM dbo.TB_DefJobSkill_Recipe)
		EXEC('INSERT INTO dbo.Tmp_TB_DefJobSkill_Recipe (NationCodeStr, f_Recipe_ItemNo, f_Order_ID, f_Memo, f_01Need_JobSkill_No, f_01Need_JobSkill_Expertness, f_02Need_JobSkill_No, f_02Need_JobSkill_Expertness,
														f_03Need_JobSkill_No, f_03Need_JobSkill_Expertness, f_01Resource_GroupNo, f_01Resource_Grade, f_01Resource_Count, f_02Resource_GroupNo, f_02Resource_Grade, f_02Resource_Count,
														f_03Resource_GroupNo, f_03Resource_Grade, f_03Resource_Count, f_04Resource_GroupNo, f_04Resource_Grade, f_04Resource_Count, f_NeedMoney,
														f_ResultProbability_No, f_ResultProbability_UpRate, f_ResultProbability_UpRate_Item, f_Need_ProductPoint, f_Expertness_Gain)
			 SELECT 0, f_Recipe_ItemNo, f_Order_ID, f_Memo, f_01Need_JobSkill_No, f_01Need_JobSkill_Expertness, f_02Need_JobSkill_No, f_02Need_JobSkill_Expertness,
														f_03Need_JobSkill_No, f_03Need_JobSkill_Expertness, f_01Resource_GroupNo, f_01Resource_Grade, f_01Resource_Count, f_02Resource_GroupNo, f_02Resource_Grade, f_02Resource_Count,
														f_03Resource_GroupNo, f_03Resource_Grade, f_03Resource_Count, f_04Resource_GroupNo, f_04Resource_Grade, f_04Resource_Count, f_NeedMoney,
														f_ResultProbability_No, f_ResultProbability_UpRate, f_ResultProbability_UpRate_Item, f_Need_ProductPoint, f_Expertness_Gain
			 FROM dbo.TB_DefJobSkill_Recipe WITH (HOLDLOCK TABLOCKX)')
	
	DROP TABLE dbo.TB_DefJobSkill_Recipe
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefJobSkill_Recipe', 'TB_DefJobSkill_Recipe', 'OBJECT'
	
END
GO