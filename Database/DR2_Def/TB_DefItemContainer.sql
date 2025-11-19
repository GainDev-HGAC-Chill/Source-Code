USE DR2_Def

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemContainer') AND [name] = N'f_NationCodeStr')
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
	
	ALTER TABLE dbo.TB_DefItemContainer
		DROP CONSTRAINT DF_TB_DefItemContainer_BagNo06
	
	ALTER TABLE dbo.TB_DefItemContainer
		DROP CONSTRAINT DF_TB_DefItemContainer_BagNo07
	
	ALTER TABLE dbo.TB_DefItemContainer
		DROP CONSTRAINT DF_TB_DefItemContainer_BagNo08
	
	ALTER TABLE dbo.TB_DefItemContainer
		DROP CONSTRAINT DF_TB_DefItemContainer_BagNo09
	
	ALTER TABLE dbo.TB_DefItemContainer
		DROP CONSTRAINT DF_TB_DefItemContainer_BagNo10
	
	ALTER TABLE dbo.TB_DefItemContainer
		DROP CONSTRAINT TB_DefItemContainer_RewardItem
	
	CREATE TABLE dbo.Tmp_TB_DefItemContainer
		(
		IDX int NOT NULL IDENTITY (1, 1) NOT FOR REPLICATION,
		f_NationCodeStr nvarchar(50) NOT NULL,
		ContainerNo int NOT NULL,
		Memo nvarchar(100) NULL,
		SuccessRateControlNo int NOT NULL,
		BagGrpNo01 int NOT NULL,
		BagGrpNo02 int NOT NULL,
		BagGrpNo03 int NOT NULL,
		BagGrpNo04 int NOT NULL,
		BagGrpNo05 int NOT NULL,
		BagGrpNo06 int NOT NULL,
		BagGrpNo07 int NOT NULL,
		BagGrpNo08 int NOT NULL,
		BagGrpNo09 int NOT NULL,
		BagGrpNo10 int NOT NULL,
		RewardItem int NOT NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'Monster''s item list that will be dropped from it'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefItemContainer', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefItemContainer ADD CONSTRAINT
		DF_TB_DefItemContainer_f_NationCodeStr DEFAULT N'0' FOR f_NationCodeStr
	
	ALTER TABLE dbo.Tmp_TB_DefItemContainer ADD CONSTRAINT
		DF_TB_DefItemContainer_BagNo06 DEFAULT ((0)) FOR BagGrpNo06
	
	ALTER TABLE dbo.Tmp_TB_DefItemContainer ADD CONSTRAINT
		DF_TB_DefItemContainer_BagNo07 DEFAULT ((0)) FOR BagGrpNo07
	
	ALTER TABLE dbo.Tmp_TB_DefItemContainer ADD CONSTRAINT
		DF_TB_DefItemContainer_BagNo08 DEFAULT ((0)) FOR BagGrpNo08
	
	ALTER TABLE dbo.Tmp_TB_DefItemContainer ADD CONSTRAINT
		DF_TB_DefItemContainer_BagNo09 DEFAULT ((0)) FOR BagGrpNo09
	
	ALTER TABLE dbo.Tmp_TB_DefItemContainer ADD CONSTRAINT
		DF_TB_DefItemContainer_BagNo10 DEFAULT ((0)) FOR BagGrpNo10
	
	ALTER TABLE dbo.Tmp_TB_DefItemContainer ADD CONSTRAINT
		TB_DefItemContainer_RewardItem DEFAULT ((0)) FOR RewardItem
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefItemContainer ON
	
	IF EXISTS(SELECT * FROM dbo.TB_DefItemContainer)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefItemContainer (IDX, ContainerNo, Memo, SuccessRateControlNo, BagGrpNo01, BagGrpNo02, BagGrpNo03, BagGrpNo04, BagGrpNo05, BagGrpNo06, BagGrpNo07, BagGrpNo08, BagGrpNo09, BagGrpNo10, RewardItem)
			SELECT IDX, ContainerNo, Memo, SuccessRateControlNo, BagGrpNo01, BagGrpNo02, BagGrpNo03, BagGrpNo04, BagGrpNo05, BagGrpNo06, BagGrpNo07, BagGrpNo08, BagGrpNo09, BagGrpNo10, RewardItem FROM dbo.TB_DefItemContainer WITH (HOLDLOCK TABLOCKX)')
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefItemContainer OFF
	
	DROP TABLE dbo.TB_DefItemContainer
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefItemContainer', N'TB_DefItemContainer', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefItemContainer ADD CONSTRAINT
		PK_TB_DefItemContainer PRIMARY KEY CLUSTERED 
		(
		ContainerNo,
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	
	COMMIT
END