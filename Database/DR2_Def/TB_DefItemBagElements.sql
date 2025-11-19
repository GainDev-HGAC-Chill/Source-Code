USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemBagElements') AND [name] = N'f_NationCodeStr')
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
	
	ALTER TABLE dbo.TB_DefItemBagElements
		DROP CONSTRAINT DF_TB_DefItemBag_ItemNo01
	
	ALTER TABLE dbo.TB_DefItemBagElements
		DROP CONSTRAINT DF_TB_DefItemBag_ItemNo02
	
	ALTER TABLE dbo.TB_DefItemBagElements
		DROP CONSTRAINT DF_TB_DefItemBag_ItemNo03
	
	ALTER TABLE dbo.TB_DefItemBagElements
		DROP CONSTRAINT DF_TB_DefItemBag_ItemNo04
	
	ALTER TABLE dbo.TB_DefItemBagElements
		DROP CONSTRAINT DF_TB_DefItemBag_ItemNo05
	
	ALTER TABLE dbo.TB_DefItemBagElements
		DROP CONSTRAINT DF_TB_DefItemBag_ItemNo06
	
	ALTER TABLE dbo.TB_DefItemBagElements
		DROP CONSTRAINT DF_TB_DefItemBag_ItemNo07
	
	ALTER TABLE dbo.TB_DefItemBagElements
		DROP CONSTRAINT DF_TB_DefItemBag_ItemNo08
	
	ALTER TABLE dbo.TB_DefItemBagElements
		DROP CONSTRAINT DF_TB_DefItemBag_ItemNo09
	
	ALTER TABLE dbo.TB_DefItemBagElements
		DROP CONSTRAINT DF_TB_DefItemBag_ItemNo10
	
	CREATE TABLE dbo.Tmp_TB_DefItemBagElements
		(
		IDX int NOT NULL IDENTITY (1, 1) NOT FOR REPLICATION,
		f_NationCodeStr nvarchar(50) NOT NULL,
		BagNo int NOT NULL,
		Memo nvarchar(100) NULL,
		ItemNo01 int NOT NULL,
		ItemNo02 int NOT NULL,
		ItemNo03 int NOT NULL,
		ItemNo04 int NOT NULL,
		ItemNo05 int NOT NULL,
		ItemNo06 int NOT NULL,
		ItemNo07 int NOT NULL,
		ItemNo08 int NOT NULL,
		ItemNo09 int NOT NULL,
		ItemNo10 int NOT NULL,
		ItemNoTypeFlag smallint NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'Item list of Item bag '
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefItemBagElements', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefItemBagElements ADD CONSTRAINT
		DF_TB_DefItemBagElements_f_NationCodeStr DEFAULT N'0' FOR f_NationCodeStr
	
	ALTER TABLE dbo.Tmp_TB_DefItemBagElements ADD CONSTRAINT
		DF_TB_DefItemBag_ItemNo01 DEFAULT ((0)) FOR ItemNo01
	
	ALTER TABLE dbo.Tmp_TB_DefItemBagElements ADD CONSTRAINT
		DF_TB_DefItemBag_ItemNo02 DEFAULT ((0)) FOR ItemNo02
	
	ALTER TABLE dbo.Tmp_TB_DefItemBagElements ADD CONSTRAINT
		DF_TB_DefItemBag_ItemNo03 DEFAULT ((0)) FOR ItemNo03
	
	ALTER TABLE dbo.Tmp_TB_DefItemBagElements ADD CONSTRAINT
		DF_TB_DefItemBag_ItemNo04 DEFAULT ((0)) FOR ItemNo04
	
	ALTER TABLE dbo.Tmp_TB_DefItemBagElements ADD CONSTRAINT
		DF_TB_DefItemBag_ItemNo05 DEFAULT ((0)) FOR ItemNo05
	
	ALTER TABLE dbo.Tmp_TB_DefItemBagElements ADD CONSTRAINT
		DF_TB_DefItemBag_ItemNo06 DEFAULT ((0)) FOR ItemNo06
	
	ALTER TABLE dbo.Tmp_TB_DefItemBagElements ADD CONSTRAINT
		DF_TB_DefItemBag_ItemNo07 DEFAULT ((0)) FOR ItemNo07
	
	ALTER TABLE dbo.Tmp_TB_DefItemBagElements ADD CONSTRAINT
		DF_TB_DefItemBag_ItemNo08 DEFAULT ((0)) FOR ItemNo08
	
	ALTER TABLE dbo.Tmp_TB_DefItemBagElements ADD CONSTRAINT
		DF_TB_DefItemBag_ItemNo09 DEFAULT ((0)) FOR ItemNo09
	
	ALTER TABLE dbo.Tmp_TB_DefItemBagElements ADD CONSTRAINT
		DF_TB_DefItemBag_ItemNo10 DEFAULT ((0)) FOR ItemNo10
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefItemBagElements ON
	
	IF EXISTS(SELECT * FROM dbo.TB_DefItemBagElements)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefItemBagElements (IDX, BagNo, Memo, ItemNo01, ItemNo02, ItemNo03, ItemNo04, ItemNo05, ItemNo06, ItemNo07, ItemNo08, ItemNo09, ItemNo10, ItemNoTypeFlag)
			SELECT IDX, BagNo, Memo, ItemNo01, ItemNo02, ItemNo03, ItemNo04, ItemNo05, ItemNo06, ItemNo07, ItemNo08, ItemNo09, ItemNo10, ItemNoTypeFlag FROM dbo.TB_DefItemBagElements WITH (HOLDLOCK TABLOCKX)')
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefItemBagElements OFF
	
	DROP TABLE dbo.TB_DefItemBagElements
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefItemBagElements', N'TB_DefItemBagElements', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefItemBagElements ADD CONSTRAINT
		PK_TB_DefItemBag PRIMARY KEY CLUSTERED 
		(
		BagNo,
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	
	COMMIT
END