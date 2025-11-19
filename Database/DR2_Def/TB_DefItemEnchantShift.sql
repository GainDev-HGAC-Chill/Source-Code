USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefItemPlusUpgrade]    Script Date: 10/08/2009 16:54:16 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
--테이블이 없으면 없으면
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[dbo].[TB_DefItemEnchantShift]'))
BEGIN
CREATE TABLE [dbo].[TB_DefItemEnchantShift](
	[index] [int] IDENTITY(1,1) NOT FOR REPLICATION NOT NULL,
	[EquipPos] [int] NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EquipPos] DEFAULT ((0)),
	[TargetLevel_Min] [int] NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_TargetLevel_Min] DEFAULT ((0)),
	[TargetLevel_Max] [int] NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_TargetLevel_Max] DEFAULT ((0)),
	[EnchantShiftGemNo] [int] NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftGemNo] DEFAULT ((0)),
 CONSTRAINT [PK_TB_DefItemEnchantShift] PRIMARY KEY CLUSTERED
(
	[EquipPos] ASC,
	[TargetLevel_Min] ASC,
	[TargetLevel_Max] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemEnchantShift') AND [name] = N'Memo')
BEGIN
	BEGIN TRANSACTION
	
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EquipPos	
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_TargetLevel_Min	
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_TargetLevel_Max		
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EnchantShiftGemNo
	
	CREATE TABLE dbo.Tmp_TB_DefItemEnchantShift
		(
		[index] int IDENTITY(1,1) NOT FOR REPLICATION NOT NULL,
		[EquipPos] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EquipPos] DEFAULT ((0)),
		[Memo] nvarchar(100) NULL,
		[TargetLevel_Min] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_TargetLevel_Min] DEFAULT ((0)),
		[TargetLevel_Max] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_TargetLevel_Max] DEFAULT ((0)),
		[EnchantShiftGemNo] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftGemNo] DEFAULT ((0))
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'Item EnchantShift'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefItemEnchantShift', NULL, NULL

	IF EXISTS(SELECT * FROM dbo.TB_DefItemEnchantShift)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefItemEnchantShift (EquipPos, TargetLevel_Min, TargetLevel_Max, EnchantShiftGemNo)
			SELECT EquipPos, TargetLevel_Min, TargetLevel_Max, EnchantShiftGemNo FROM dbo.TB_DefItemEnchantShift WITH (HOLDLOCK TABLOCKX)')

	DROP TABLE dbo.TB_DefItemEnchantShift

	EXECUTE sp_rename N'dbo.Tmp_TB_DefItemEnchantShift', N'TB_DefItemEnchantShift', 'OBJECT' 

	ALTER TABLE dbo.TB_DefItemEnchantShift ADD CONSTRAINT
		PK_TB_DefItemEnchantShift PRIMARY KEY CLUSTERED 
		(
		[EquipPos] ASC,
		[TargetLevel_Min] ASC,
		[TargetLevel_Max] ASC
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
	
	COMMIT
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemEnchantShift') AND [name] = N'EnchnatGrade')
BEGIN
	BEGIN TRANSACTION
	
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EquipPos
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_TargetLevel_Min
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_TargetLevel_Max
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EnchantShiftGemNo
	
	CREATE TABLE dbo.Tmp_TB_DefItemEnchantShift
		(
		[index] int IDENTITY(1,1) NOT FOR REPLICATION NOT NULL,
		[EquipPos] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EquipPos] DEFAULT ((0)),
		[Memo] nvarchar(100) NULL,
		[TargetLevel_Min] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_TargetLevel_Min] DEFAULT ((0)),
		[TargetLevel_Max] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_TargetLevel_Max] DEFAULT ((0)),
		  [EnchnatGrade] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchnatGrade] DEFAULT ((0)),
		  [EnchantItemNo] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchnatItemNo] DEFAULT ((0)),
		  [EnchantItemCount] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantItemCount] DEFAULT ((0)),
		  [NeedMoney] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_NeedMoney] DEFAULT ((0)),
		[EnchantShiftGemNo] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftGemNo] DEFAULT ((0)),
		  [EnchantShiftGemCount] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftGemCount] DEFAULT ((0)),		
		  [InsuranceItemNo] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_InsuranceItemNo] DEFAULT ((0)),
		  [EnchantShiftRatePlus2] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRatePlus2] DEFAULT ((0)),
		  [EnchantShiftRatePlus1] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRatePlus1] DEFAULT ((0)),
		  [EnchantShiftRateSame] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateSame] DEFAULT ((0)),
		  [EnchantShiftRateMinus1] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateMinus1] DEFAULT ((0)),
		  [EnchantShiftRateMinus2] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateMinus2] DEFAULT ((0)),
		  [EnchantShiftRateDelete] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateDelete] DEFAULT ((0))
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'Item EnchantShift'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefItemEnchantShift', NULL, NULL

	IF EXISTS(SELECT * FROM dbo.TB_DefItemEnchantShift)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefItemEnchantShift (EquipPos, Memo, TargetLevel_Min, TargetLevel_Max, EnchantShiftGemNo)
			SELECT EquipPos, Memo, TargetLevel_Min, TargetLevel_Max, EnchantShiftGemNo FROM dbo.TB_DefItemEnchantShift WITH (HOLDLOCK TABLOCKX)')

	DROP TABLE dbo.TB_DefItemEnchantShift

	EXECUTE sp_rename N'dbo.Tmp_TB_DefItemEnchantShift', N'TB_DefItemEnchantShift', 'OBJECT' 

	ALTER TABLE dbo.TB_DefItemEnchantShift ADD CONSTRAINT
		PK_TB_DefItemEnchantShift PRIMARY KEY CLUSTERED 
		(
		[EquipPos] ASC,
		[TargetLevel_Min] ASC,
		[TargetLevel_Max] ASC,
		[EnchnatGrade] ASC
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
	
	COMMIT
END
GO

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemEnchantShift') AND [name] = N'EquipPos')
BEGIN
	BEGIN TRANSACTION
	
	EXECUTE sp_rename N'dbo.TB_DefItemEnchantShift.EquipPos', N'EquipType', N'COLUMN' 
	
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_TargetLevel_Min
	EXECUTE sp_rename N'dbo.TB_DefItemEnchantShift.TargetLevel_Min', N'LevelLimit', N'COLUMN' 
	ALTER TABLE dbo.TB_DefItemEnchantShift ADD CONSTRAINT DF_TB_DefItemEnchantShift_LevelLimit DEFAULT ((0)) FOR [LevelLimit]
	
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_TargetLevel_Max
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT PK_TB_DefItemEnchantShift
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP column TargetLevel_Max
	
	ALTER TABLE dbo.TB_DefItemEnchantShift ADD CONSTRAINT
		PK_TB_DefItemEnchantShift PRIMARY KEY CLUSTERED 
		(
		[EquipType] ASC,
		[LevelLimit] ASC,
		[EnchnatGrade] ASC
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	COMMIT
END
GO

IF NOT EXISTS(SELECT * FROM SYS.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemEnchantShift') and [name] = N'f_NationCode')
BEGIN
	
	--ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EquipType
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_LevelLimit
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EnchnatGrade
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EnchnatItemNo
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EnchantItemCount
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_NeedMoney
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EnchantShiftGemNo
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EnchantShiftGemCount
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_InsuranceItemNo
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EnchantShiftRatePlus2
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EnchantShiftRatePlus1
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EnchantShiftRateSame
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EnchantShiftRateMinus1
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EnchantShiftRateMinus2
	ALTER TABLE dbo.TB_DefItemEnchantShift DROP CONSTRAINT DF_TB_DefItemEnchantShift_EnchantShiftRateDelete
	
	CREATE TABLE dbo.Tmp_TB_DefItemEnchantShift
		(
		[f_NationCode] nvarchar(50) NOT NULL,
		[index] int IDENTITY(1,1) NOT FOR REPLICATION NOT NULL,
		[EquipType] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EquipType] DEFAULT ((0)),
		[Memo] nvarchar(100) NULL,
		[LevelLimit] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_LevelLimit] DEFAULT ((0)),
		[EnchnatGrade] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchnatGrade] DEFAULT ((0)),
		[EnchantItemNo] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchnatItemNo] DEFAULT ((0)),
		[EnchantItemCount] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantItemCount] DEFAULT ((0)),
		[NeedMoney] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_NeedMoney] DEFAULT ((0)),
		[EnchantShiftGemNo] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftGemNo] DEFAULT ((0)),
		[EnchantShiftGemCount] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftGemCount] DEFAULT ((0)),		
		[InsuranceItemNo] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_InsuranceItemNo] DEFAULT ((0)),
		[EnchantShiftRatePlus2] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRatePlus2] DEFAULT ((0)),
		[EnchantShiftRatePlus1] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRatePlus1] DEFAULT ((0)),
		[EnchantShiftRateSame] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateSame] DEFAULT ((0)),
		[EnchantShiftRateMinus1] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateMinus1] DEFAULT ((0)),
		[EnchantShiftRateMinus2] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateMinus2] DEFAULT ((0)),
		[EnchantShiftRateDelete] int NOT NULL CONSTRAINT [DF_TB_DefItemEnchantShift_EnchantShiftRateDelete] DEFAULT ((0))
		)  ON [PRIMARY]
	
	IF EXISTS(SELECT * FROM dbo.TB_DefItemEnchantShift)
	BEGIN
		EXEC('INSERT INTO dbo.Tmp_TB_DefItemEnchantShift (f_NationCode, index, EquipType, Memo, LevelLimit,
		EnchnatGrade, EnchantItemNo, EnchantItemCount, NeedMoney, EnchantShiftGemNo, EnchantShiftGemCount,
		InsuranceItemNo, EnchantShiftRatePlus2, EnchantShiftRatePlus1, EnchantShiftRateSame, EnchantShiftRateMinus1,
		EnchantShiftRateMinus2, EnchantShiftRateDelete)
			SELECT 0, index, EquipType, Memo, LevelLimit, EnchnatGrade, EnchantItemNo, EnchantItemCount, NeedMoney,
			EnchantShiftGemNo, EnchantShiftGemCount, InsuranceItemNo, EnchantShiftRatePlus2, EnchantShiftRatePlus1,
			EnchantShiftRateSame, EnchantShiftRateMinus1, EnchantShiftRateMinus2, EnchantShiftRateDelete
		 FROM dbo.TB_DefItemEnchantShift WITH (HOLDLOCK TABLOCKX)')
	END	 
	DROP TABLE dbo.TB_DefItemEnchantShift
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefItemEnchantShift', N'TB_DefItemEnchantShift', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefItemEnchantShift ADD CONSTRAINT
		PK_TB_DefItemEnchantShift PRIMARY KEY CLUSTERED 
		(
		[f_NationCode] ASC,
		[EquipType] ASC,
		[LevelLimit] ASC,
		[EnchnatGrade] ASC
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
	
END
GO
