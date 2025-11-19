USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefItemBagGroup]    Script Date: 10/22/2009 18:51:44 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemBagGroup') AND [name] = N'f_NationCodeStr')
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
	
	CREATE TABLE dbo.Tmp_TB_DefItemBagGroup
		(
		IDX int NOT NULL,
		f_NationCodeStr nvarchar(50) NOT NULL,
		BagGroupNo int NOT NULL,
		Memo nvarchar(50) NOT NULL,
		SuccessRateNo int NOT NULL,
		BagNo01 int NOT NULL,
		BagNo02 int NOT NULL,
		BagNo03 int NOT NULL,
		BagNo04 int NOT NULL,
		BagNo05 int NOT NULL,
		BagNo06 int NOT NULL,
		BagNo07 int NOT NULL,
		BagNo08 int NOT NULL,
		BagNo09 int NOT NULL,
		BagNo10 int NOT NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'Item bag group definition
	  bag group = bag of bags'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefItemBagGroup', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefItemBagGroup ADD CONSTRAINT
		DF_TB_DefItemBagGroup_f_NationCodeStr DEFAULT N'0' FOR f_NationCodeStr
	
	IF EXISTS(SELECT * FROM dbo.TB_DefItemBagGroup)
	BEGIN
		SELECT DISTINCT BagGroupNo, Memo, SuccessRateNo, BagNo01, BagNo02, BagNo03, BagNo04, BagNo05, BagNo06, BagNo07, BagNo08, BagNo09, BagNo10 INTO #Tmp FROM dbo.TB_DefItemBagGroup WITH (HOLDLOCK TABLOCKX)
		INSERT INTO dbo.Tmp_TB_DefItemBagGroup (IDX, BagGroupNo, Memo, SuccessRateNo, BagNo01, BagNo02, BagNo03, BagNo04, BagNo05, BagNo06, BagNo07, BagNo08, BagNo09, BagNo10)
			SELECT ROW_NUMBER() OVER (ORDER BY BagGroupNo), BagGroupNo, Memo, SuccessRateNo, BagNo01, BagNo02, BagNo03, BagNo04, BagNo05, BagNo06, BagNo07, BagNo08, BagNo09, BagNo10 FROM dbo.#Tmp WITH (HOLDLOCK TABLOCKX)
		DROP TABLE dbo.#Tmp
	END
	
	DROP TABLE dbo.TB_DefItemBagGroup
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefItemBagGroup', N'TB_DefItemBagGroup', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefItemBagGroup ADD CONSTRAINT
		PK_TB_DefItemBagGroup PRIMARY KEY CLUSTERED 
		(
		BagGroupNo,
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	COMMIT
END