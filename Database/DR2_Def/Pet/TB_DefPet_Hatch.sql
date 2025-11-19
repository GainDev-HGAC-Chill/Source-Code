USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'TB_DefPet_Hatch') AND [type] in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefPet_Hatch](
		[ID] [int] NOT NULL,
		[Memo] [nvarchar](100) NULL,
		[Class_01] [int] NOT NULL,
		[Level_01] [smallint] NOT NULL,
		[Rate_01] [int] NOT NULL,
		[BonusStatusID_01_1] [int] NOT NULL,
		[BonusStatusID_01_2] [int] NOT NULL DEFAULT(0),
		[BonusStatusID_01_3] [int] NOT NULL DEFAULT(0),
		[Class_02] [int] NOT NULL DEFAULT(0),
		[Level_02] [smallint] NOT NULL DEFAULT(0),
		[Rate_02] [int] NOT NULL DEFAULT(0),
		[BonusStatusID_02_1] [int] NOT NULL DEFAULT(0),
		[BonusStatusID_02_2] [int] NOT NULL DEFAULT(0),
		[BonusStatusID_02_3] [int] NOT NULL DEFAULT(0),
		[Class_03] [int] NOT NULL DEFAULT(0),
		[Level_03] [smallint] NOT NULL DEFAULT(0),
		[Rate_03] [int] NOT NULL DEFAULT(0),
		[BonusStatusID_03_1] [int] NOT NULL DEFAULT(0),
		[BonusStatusID_03_2] [int] NOT NULL DEFAULT(0),
		[BonusStatusID_03_3] [int] NOT NULL DEFAULT(0),
		[Class_04] [int] NOT NULL DEFAULT(0),
		[Level_04] [smallint] NOT NULL DEFAULT(0),
		[Rate_04] [int] NOT NULL DEFAULT(0),
		[BonusStatusID_04_1] [int] NOT NULL DEFAULT(0),
		[BonusStatusID_04_2] [int] NOT NULL DEFAULT(0),
		[BonusStatusID_04_3] [int] NOT NULL DEFAULT(0),
		[Class_05] [int] NOT NULL DEFAULT(0),
		[Level_05] [smallint] NOT NULL DEFAULT(0),
		[Rate_05] [int] NOT NULL DEFAULT(0),
		[BonusStatusID_05_1] [int] NOT NULL DEFAULT(0),
		[BonusStatusID_05_2] [int] NOT NULL DEFAULT(0),
		[BonusStatusID_05_3] [int] NOT NULL DEFAULT(0),
		[Period_01] [smallint] NOT NULL,
		[PeriodRate_01] [int] NOT NULL,
		[Period_02] [smallint] NOT NULL DEFAULT(0),
		[PeriodRate_02] [int] NOT NULL DEFAULT(0),
		[Period_03] [smallint] NOT NULL DEFAULT(0),
		[PeriodRate_03] [int] NOT NULL DEFAULT(0),
		[Period_04] [smallint] NOT NULL DEFAULT(0),
		[PeriodRate_04] [int] NOT NULL DEFAULT(0),
		[Period_05] [smallint] NOT NULL DEFAULT(0),
		[PeriodRate_05] [int] NOT NULL DEFAULT(0),
		[Period_06] [smallint] NOT NULL DEFAULT(0),
		[PeriodRate_06] [int] NOT NULL DEFAULT(0),
		[Period_07] [smallint] NOT NULL DEFAULT(0),
		[PeriodRate_07] [int] NOT NULL DEFAULT(0),
		[Period_08] [smallint] NOT NULL DEFAULT(0),
		[PeriodRate_08] [int] NOT NULL DEFAULT(0),
		[Period_09] [smallint] NOT NULL DEFAULT(0),
		[PeriodRate_09] [int] NOT NULL DEFAULT(0),
		[Period_10] [smallint] NOT NULL DEFAULT(0),
		[PeriodRate_10] [int] NOT NULL DEFAULT(0),
	 CONSTRAINT [PK_TB_DefPet_Hatch] PRIMARY KEY CLUSTERED 
	(
		[ID] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
GO




IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefPet_Hatch') AND [name] = N'f_NationCodeStr')
BEGIN
	/* To prevent any potential data loss issues, you should review this script in detail before running it outside the context of the database designer.*/
	BEGIN TRANSACTION
	SET QUOTED_IDENTIFIER ON
	SET ARITHABORT ON
	SET NUMERIC_ROUNDABORT OFF
	SET CONCAT_NULL_YIELDS_NULL ON
	SET ANSI_NULLS ON
	SET ANSI_PADDING ON
	SET ANSI_WARNINGS ON
	COMMIT
	BEGIN TRANSACTION
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Bonus__4AE30379
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Bonus__4BD727B2
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Class__4CCB4BEB
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Level__4DBF7024
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Rate___4EB3945D
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Bonus__4FA7B896
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Bonus__509BDCCF
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Bonus__51900108
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Class__52842541
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Level__5378497A
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Rate___546C6DB3
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Bonus__556091EC
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Bonus__5654B625
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Bonus__5748DA5E
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Class__583CFE97
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Level__593122D0
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Rate___5A254709
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Bonus__5B196B42
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Bonus__5C0D8F7B
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Bonus__5D01B3B4
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Class__5DF5D7ED
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Level__5EE9FC26
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Rate___5FDE205F
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Bonus__60D24498
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Bonus__61C668D1
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Bonus__62BA8D0A
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__63AEB143
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__64A2D57C
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__6596F9B5
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__668B1DEE
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__677F4227
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__68736660
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__69678A99
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__6A5BAED2
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__6B4FD30B
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__6C43F744
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__6D381B7D
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__6E2C3FB6
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__6F2063EF
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__70148828
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__7108AC61
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__71FCD09A
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__72F0F4D3
	
	ALTER TABLE dbo.TB_DefPet_Hatch
		DROP CONSTRAINT DF__TB_DefPet__Perio__73E5190C
	
	CREATE TABLE dbo.Tmp_TB_DefPet_Hatch
		(
		f_NationCodeStr nvarchar(50) NOT NULL,
		ID int NOT NULL,
		Memo nvarchar(100) NULL,
		Class_01 int NOT NULL,
		Level_01 smallint NOT NULL,
		Rate_01 int NOT NULL,
		BonusStatusID_01_1 int NOT NULL,
		BonusStatusID_01_2 int NOT NULL,
		BonusStatusID_01_3 int NOT NULL,
		Class_02 int NOT NULL,
		Level_02 smallint NOT NULL,
		Rate_02 int NOT NULL,
		BonusStatusID_02_1 int NOT NULL,
		BonusStatusID_02_2 int NOT NULL,
		BonusStatusID_02_3 int NOT NULL,
		Class_03 int NOT NULL,
		Level_03 smallint NOT NULL,
		Rate_03 int NOT NULL,
		BonusStatusID_03_1 int NOT NULL,
		BonusStatusID_03_2 int NOT NULL,
		BonusStatusID_03_3 int NOT NULL,
		Class_04 int NOT NULL,
		Level_04 smallint NOT NULL,
		Rate_04 int NOT NULL,
		BonusStatusID_04_1 int NOT NULL,
		BonusStatusID_04_2 int NOT NULL,
		BonusStatusID_04_3 int NOT NULL,
		Class_05 int NOT NULL,
		Level_05 smallint NOT NULL,
		Rate_05 int NOT NULL,
		BonusStatusID_05_1 int NOT NULL,
		BonusStatusID_05_2 int NOT NULL,
		BonusStatusID_05_3 int NOT NULL,
		Period_01 smallint NOT NULL,
		PeriodRate_01 int NOT NULL,
		Period_02 smallint NOT NULL,
		PeriodRate_02 int NOT NULL,
		Period_03 smallint NOT NULL,
		PeriodRate_03 int NOT NULL,
		Period_04 smallint NOT NULL,
		PeriodRate_04 int NOT NULL,
		Period_05 smallint NOT NULL,
		PeriodRate_05 int NOT NULL,
		Period_06 smallint NOT NULL,
		PeriodRate_06 int NOT NULL,
		Period_07 smallint NOT NULL,
		PeriodRate_07 int NOT NULL,
		Period_08 smallint NOT NULL,
		PeriodRate_08 int NOT NULL,
		Period_09 smallint NOT NULL,
		PeriodRate_09 int NOT NULL,
		Period_10 smallint NOT NULL,
		PeriodRate_10 int NOT NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'1차 Pet알의 부활정보( 펫의 종류별 부활할 확률 / 사용될 TB_DefPet_BonusStatus )'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefPet_Hatch', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF_TB_DefPet_Hatch_f_NationCodeStr DEFAULT N'0' FOR f_NationCodeStr
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Bonus__4AE30379 DEFAULT ((0)) FOR BonusStatusID_01_2
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Bonus__4BD727B2 DEFAULT ((0)) FOR BonusStatusID_01_3
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Class__4CCB4BEB DEFAULT ((0)) FOR Class_02
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Level__4DBF7024 DEFAULT ((0)) FOR Level_02
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Rate___4EB3945D DEFAULT ((0)) FOR Rate_02
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Bonus__4FA7B896 DEFAULT ((0)) FOR BonusStatusID_02_1
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Bonus__509BDCCF DEFAULT ((0)) FOR BonusStatusID_02_2
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Bonus__51900108 DEFAULT ((0)) FOR BonusStatusID_02_3
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Class__52842541 DEFAULT ((0)) FOR Class_03
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Level__5378497A DEFAULT ((0)) FOR Level_03
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Rate___546C6DB3 DEFAULT ((0)) FOR Rate_03
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Bonus__556091EC DEFAULT ((0)) FOR BonusStatusID_03_1
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Bonus__5654B625 DEFAULT ((0)) FOR BonusStatusID_03_2
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Bonus__5748DA5E DEFAULT ((0)) FOR BonusStatusID_03_3
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Class__583CFE97 DEFAULT ((0)) FOR Class_04
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Level__593122D0 DEFAULT ((0)) FOR Level_04
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Rate___5A254709 DEFAULT ((0)) FOR Rate_04
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Bonus__5B196B42 DEFAULT ((0)) FOR BonusStatusID_04_1
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Bonus__5C0D8F7B DEFAULT ((0)) FOR BonusStatusID_04_2
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Bonus__5D01B3B4 DEFAULT ((0)) FOR BonusStatusID_04_3
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Class__5DF5D7ED DEFAULT ((0)) FOR Class_05
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Level__5EE9FC26 DEFAULT ((0)) FOR Level_05
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Rate___5FDE205F DEFAULT ((0)) FOR Rate_05
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Bonus__60D24498 DEFAULT ((0)) FOR BonusStatusID_05_1
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Bonus__61C668D1 DEFAULT ((0)) FOR BonusStatusID_05_2
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Bonus__62BA8D0A DEFAULT ((0)) FOR BonusStatusID_05_3
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__63AEB143 DEFAULT ((0)) FOR Period_02
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__64A2D57C DEFAULT ((0)) FOR PeriodRate_02
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__6596F9B5 DEFAULT ((0)) FOR Period_03
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__668B1DEE DEFAULT ((0)) FOR PeriodRate_03
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__677F4227 DEFAULT ((0)) FOR Period_04
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__68736660 DEFAULT ((0)) FOR PeriodRate_04
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__69678A99 DEFAULT ((0)) FOR Period_05
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__6A5BAED2 DEFAULT ((0)) FOR PeriodRate_05
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__6B4FD30B DEFAULT ((0)) FOR Period_06
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__6C43F744 DEFAULT ((0)) FOR PeriodRate_06
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__6D381B7D DEFAULT ((0)) FOR Period_07
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__6E2C3FB6 DEFAULT ((0)) FOR PeriodRate_07
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__6F2063EF DEFAULT ((0)) FOR Period_08
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__70148828 DEFAULT ((0)) FOR PeriodRate_08
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__7108AC61 DEFAULT ((0)) FOR Period_09
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__71FCD09A DEFAULT ((0)) FOR PeriodRate_09
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__72F0F4D3 DEFAULT ((0)) FOR Period_10
	
	ALTER TABLE dbo.Tmp_TB_DefPet_Hatch ADD CONSTRAINT
		DF__TB_DefPet__Perio__73E5190C DEFAULT ((0)) FOR PeriodRate_10
	
	IF EXISTS(SELECT * FROM dbo.TB_DefPet_Hatch)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefPet_Hatch (ID, Memo, Class_01, Level_01, Rate_01, BonusStatusID_01_1, BonusStatusID_01_2, BonusStatusID_01_3, Class_02, Level_02, Rate_02, BonusStatusID_02_1, BonusStatusID_02_2, BonusStatusID_02_3, Class_03, Level_03, Rate_03, BonusStatusID_03_1, BonusStatusID_03_2, BonusStatusID_03_3, Class_04, Level_04, Rate_04, BonusStatusID_04_1, BonusStatusID_04_2, BonusStatusID_04_3, Class_05, Level_05, Rate_05, BonusStatusID_05_1, BonusStatusID_05_2, BonusStatusID_05_3, Period_01, PeriodRate_01, Period_02, PeriodRate_02, Period_03, PeriodRate_03, Period_04, PeriodRate_04, Period_05, PeriodRate_05, Period_06, PeriodRate_06, Period_07, PeriodRate_07, Period_08, PeriodRate_08, Period_09, PeriodRate_09, Period_10, PeriodRate_10)
			SELECT ID, Memo, Class_01, Level_01, Rate_01, BonusStatusID_01_1, BonusStatusID_01_2, BonusStatusID_01_3, Class_02, Level_02, Rate_02, BonusStatusID_02_1, BonusStatusID_02_2, BonusStatusID_02_3, Class_03, Level_03, Rate_03, BonusStatusID_03_1, BonusStatusID_03_2, BonusStatusID_03_3, Class_04, Level_04, Rate_04, BonusStatusID_04_1, BonusStatusID_04_2, BonusStatusID_04_3, Class_05, Level_05, Rate_05, BonusStatusID_05_1, BonusStatusID_05_2, BonusStatusID_05_3, Period_01, PeriodRate_01, Period_02, PeriodRate_02, Period_03, PeriodRate_03, Period_04, PeriodRate_04, Period_05, PeriodRate_05, Period_06, PeriodRate_06, Period_07, PeriodRate_07, Period_08, PeriodRate_08, Period_09, PeriodRate_09, Period_10, PeriodRate_10 FROM dbo.TB_DefPet_Hatch WITH (HOLDLOCK TABLOCKX)')
	
	DROP TABLE dbo.TB_DefPet_Hatch
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefPet_Hatch', N'TB_DefPet_Hatch', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefPet_Hatch ADD CONSTRAINT
		PK_TB_DefPet_Hatch PRIMARY KEY CLUSTERED 
		(
		ID,
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	
	COMMIT
END