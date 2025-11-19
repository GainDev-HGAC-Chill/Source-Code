USE [DR2_Def]
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItem') AND [name] = N'f_NationCodeStr')
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
	
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_Type
	
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_SellPrice
	
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_Attribute
	
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_Gender
	
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_LevelLimit
	
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_ClassLimit
	
	CREATE TABLE dbo.Tmp_TB_DefItem
		(
		f_NationCodeStr nvarchar(50) NOT NULL,
		ItemNo int NOT NULL,
		Name int NOT NULL,
		ResNo int NULL,
		Memo nvarchar(100) NULL,
		Type smallint NOT NULL,
		Price int NOT NULL,
		SellPrice int NOT NULL,
		Attribute int NOT NULL,
		Gender tinyint NOT NULL,
		LevelLimit smallint NOT NULL,
		ClassLimit bigint NOT NULL,
		Abil01 int NOT NULL,
		Abil02 int NOT NULL,
		Abil03 int NOT NULL,
		Abil04 int NOT NULL,
		Abil05 int NOT NULL,
		Abil06 int NOT NULL,
		Abil07 int NOT NULL,
		Abil08 int NOT NULL,
		Abil09 int NOT NULL,
		Abil10 int NOT NULL,
		Order1 int NULL,
		Order2 int NULL,
		Order3 int NULL,
		CostumeGrade int NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'Item list'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefItem', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem_ DEFAULT N'0' FOR f_NationCodeStr
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_Type DEFAULT ((0)) FOR Type
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_SellPrice DEFAULT ((0)) FOR SellPrice
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_Attribute DEFAULT ((0)) FOR Attribute
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_Gender DEFAULT ((0)) FOR Gender
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_LevelLimit DEFAULT ((0)) FOR LevelLimit
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_ClassLimit DEFAULT ((0)) FOR ClassLimit
	
	IF EXISTS(SELECT * FROM dbo.TB_DefItem)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefItem (ItemNo, Name, ResNo, Memo, Type, Price, SellPrice, Attribute, Gender, LevelLimit, ClassLimit, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10, Order1, Order2, Order3, CostumeGrade)
			SELECT ItemNo, Name, ResNo, Memo, Type, Price, SellPrice, Attribute, Gender, LevelLimit, ClassLimit, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10, Order1, Order2, Order3, CostumeGrade FROM dbo.TB_DefItem WITH (HOLDLOCK TABLOCKX)')
	
	DROP TABLE dbo.TB_DefItem
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefItem', N'TB_DefItem', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefItem ADD CONSTRAINT
		PK_TB_DefItem3 PRIMARY KEY CLUSTERED 
		(
		ItemNo,
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	
	COMMIT
END


IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItem') and [name] = N'f_IsCantShareRental')
BEGIN
	ALTER TABLE dbo.TB_DefItem ADD [f_IsCantShareRental] TINYINT CONSTRAINT DF_TB_DefItem_f_IsCantShareRental DEFAULT(0)
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItem') and [name] = N'f_ClassLimitDisplayFilter')
BEGIN
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem_
	
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_Type
	
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_SellPrice
	
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_Attribute
	
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_Gender
	
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_LevelLimit
	
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_ClassLimit
	
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem_f_IsCantShareRental
	
	CREATE TABLE dbo.Tmp_TB_DefItem
		(
		f_NationCodeStr nvarchar(50) NOT NULL,
		ItemNo int NOT NULL,
		Name int NOT NULL,
		ResNo int NULL,
		Memo nvarchar(100) NULL,
		Type smallint NOT NULL,
		Price int NOT NULL,
		SellPrice int NOT NULL,
		Attribute int NOT NULL,
		Gender tinyint NOT NULL,
		LevelLimit smallint NOT NULL,
		ClassLimit bigint NOT NULL,
		f_ClassLimitDisplayFilter bigint NOT NULL,
		Abil01 int NOT NULL,
		Abil02 int NOT NULL,
		Abil03 int NOT NULL,
		Abil04 int NOT NULL,
		Abil05 int NOT NULL,
		Abil06 int NOT NULL,
		Abil07 int NOT NULL,
		Abil08 int NOT NULL,
		Abil09 int NOT NULL,
		Abil10 int NOT NULL,
		Order1 int NULL,
		Order2 int NULL,
		Order3 int NULL,
		CostumeGrade int NULL,
		f_IsCantShareRental tinyint NULL
		)  ON [PRIMARY]
	
	DECLARE @v1 sql_variant 
	SET @v1 = N'Item list'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefItem', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem_ DEFAULT (N'0') FOR f_NationCodeStr
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_Type DEFAULT ((0)) FOR Type
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_SellPrice DEFAULT ((0)) FOR SellPrice
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_Attribute DEFAULT ((0)) FOR Attribute
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_Gender DEFAULT ((0)) FOR Gender
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_LevelLimit DEFAULT ((0)) FOR LevelLimit
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_ClassLimit DEFAULT ((0)) FOR ClassLimit
	
	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem_f_ClassLimitDisplayFilter DEFAULT -1 FOR f_ClassLimitDisplayFilter

	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem_f_IsCantShareRental DEFAULT ((0)) FOR f_IsCantShareRental
	
	IF EXISTS(SELECT * FROM dbo.TB_DefItem)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefItem (f_NationCodeStr, ItemNo, Name, ResNo, Memo, Type, Price, SellPrice, Attribute, Gender, LevelLimit, ClassLimit, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10, Order1, Order2, Order3, CostumeGrade, f_IsCantShareRental)
			SELECT f_NationCodeStr, ItemNo, Name, ResNo, Memo, Type, Price, SellPrice, Attribute, Gender, LevelLimit, ClassLimit, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10, Order1, Order2, Order3, CostumeGrade, f_IsCantShareRental FROM dbo.TB_DefItem WITH (HOLDLOCK TABLOCKX)')
	
	DROP TABLE dbo.TB_DefItem
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefItem', N'TB_DefItem', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefItem ADD CONSTRAINT
		PK_TB_DefItem3 PRIMARY KEY CLUSTERED 
		(
		ItemNo,
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END

/*DraClassLimit가 없으면 f_ClassLimitDisplayFilter두개 컬럼을 추가함 */
IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItem') and [name] = N'DraClassLimit')
BEGIN
	BEGIN TRANSACTION
	
	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem_

	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_Type

	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_SellPrice

	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_Attribute

	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_Gender

	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_LevelLimit

	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem3_ClassLimit

	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem_f_ClassLimitDisplayFilter

	ALTER TABLE dbo.TB_DefItem
		DROP CONSTRAINT DF_TB_DefItem_f_IsCantShareRental

	CREATE TABLE dbo.Tmp_TB_DefItem
		(
		f_NationCodeStr nvarchar(50) NOT NULL,
		ItemNo int NOT NULL,
		Name int NOT NULL,
		ResNo int NULL,
		Memo nvarchar(100) NULL,
		Type smallint NOT NULL,
		Price int NOT NULL,
		SellPrice int NOT NULL,
		Attribute int NOT NULL,
		Gender tinyint NOT NULL,
		LevelLimit smallint NOT NULL,
		ClassLimit bigint NOT NULL,
		f_ClassLimitDisplayFilter bigint NOT NULL,
		DraClassLimit bigint NOT NULL DEFAULT (0),
		f_DraClassLimitDisplayFilter bigint NOT NULL DEFAULT (-1),
		Abil01 int NOT NULL,
		Abil02 int NOT NULL,
		Abil03 int NOT NULL,
		Abil04 int NOT NULL,
		Abil05 int NOT NULL,
		Abil06 int NOT NULL,
		Abil07 int NOT NULL,
		Abil08 int NOT NULL,
		Abil09 int NOT NULL,
		Abil10 int NOT NULL,
		Order1 int NULL,
		Order2 int NULL,
		Order3 int NULL,
		CostumeGrade int NULL,
		f_IsCantShareRental tinyint NULL
		)  ON [PRIMARY]

	/*DECLARE @v sql_variant */
	SET @v = NULL
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefItem', NULL, NULL

	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem_ DEFAULT (N'0') FOR f_NationCodeStr

	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_Type DEFAULT ((0)) FOR Type

	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_SellPrice DEFAULT ((0)) FOR SellPrice

	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_Attribute DEFAULT ((0)) FOR Attribute

	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_Gender DEFAULT ((0)) FOR Gender

	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_LevelLimit DEFAULT ((0)) FOR LevelLimit

	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem3_ClassLimit DEFAULT ((0)) FOR ClassLimit

	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem_f_ClassLimitDisplayFilter DEFAULT ((-1)) FOR f_ClassLimitDisplayFilter

	ALTER TABLE dbo.Tmp_TB_DefItem ADD CONSTRAINT
		DF_TB_DefItem_f_IsCantShareRental DEFAULT ((0)) FOR f_IsCantShareRental

	IF EXISTS(SELECT * FROM dbo.TB_DefItem)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefItem (f_NationCodeStr, ItemNo, Name, ResNo, Memo, Type, Price, SellPrice, Attribute, Gender, LevelLimit, ClassLimit, f_ClassLimitDisplayFilter, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10, Order1, Order2, Order3, CostumeGrade, f_IsCantShareRental)
			SELECT f_NationCodeStr, ItemNo, Name, ResNo, Memo, Type, Price, SellPrice, Attribute, Gender, LevelLimit, ClassLimit, f_ClassLimitDisplayFilter, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10, Order1, Order2, Order3, CostumeGrade, f_IsCantShareRental FROM dbo.TB_DefItem WITH (HOLDLOCK TABLOCKX)')

	DROP TABLE dbo.TB_DefItem

	EXECUTE sp_rename N'dbo.Tmp_TB_DefItem', N'TB_DefItem', 'OBJECT' 

	ALTER TABLE dbo.TB_DefItem ADD CONSTRAINT
		PK_TB_DefItem3 PRIMARY KEY CLUSTERED 
		(
		ItemNo,
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
	COMMIT
END