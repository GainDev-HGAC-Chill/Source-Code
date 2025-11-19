USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemBag') AND [name] = N'f_NationCodeStr')
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
	
	ALTER TABLE dbo.TB_DefItemBag
		DROP CONSTRAINT DF_TB_DefItemBag_Level
	
	ALTER TABLE dbo.TB_DefItemBag
		DROP CONSTRAINT DF_TB_DefItemBag_DropMonyControlNo
	
	CREATE TABLE dbo.Tmp_TB_DefItemBag
		(
		IDX int NOT NULL IDENTITY (1, 1) NOT FOR REPLICATION,
		f_NationCodeStr nvarchar(50) NOT NULL,
		BagNo int NOT NULL,
		[Level] smallint NOT NULL,
		Memo nvarchar(100) NULL,
		ElementsNo int NOT NULL,
		SuccessRateControlNo int NOT NULL,
		CountControlNo int NOT NULL,
		DropMoneyControlNo int NOT NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'Item bag definition (bag = group)'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefItemBag', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefItemBag ADD CONSTRAINT
		DF_TB_DefItemBag_f_NationCodeStr DEFAULT N'0' FOR f_NationCodeStr
	
	ALTER TABLE dbo.Tmp_TB_DefItemBag ADD CONSTRAINT
		DF_TB_DefItemBag_Level DEFAULT ((1)) FOR [Level]
	
	ALTER TABLE dbo.Tmp_TB_DefItemBag ADD CONSTRAINT
		DF_TB_DefItemBag_DropMonyControlNo DEFAULT ((0)) FOR DropMoneyControlNo
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefItemBag ON
	
	IF EXISTS(SELECT * FROM dbo.TB_DefItemBag)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefItemBag (IDX, BagNo, [Level], Memo, ElementsNo, SuccessRateControlNo, CountControlNo, DropMoneyControlNo)
			SELECT IDX, BagNo, [Level], Memo, ElementsNo, SuccessRateControlNo, CountControlNo, DropMoneyControlNo FROM dbo.TB_DefItemBag WITH (HOLDLOCK TABLOCKX)')
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefItemBag OFF
	
	DROP TABLE dbo.TB_DefItemBag
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefItemBag', N'TB_DefItemBag', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefItemBag ADD CONSTRAINT
		PK_TB_DefItemBag_1 PRIMARY KEY CLUSTERED 
		(
		BagNo,
		[Level],
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	
	COMMIT
END