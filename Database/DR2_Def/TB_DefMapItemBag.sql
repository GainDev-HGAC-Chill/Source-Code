USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefAchievements]    Script Date: 10/22/2009 18:51:44 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefMapItemBag') AND [name] = N'f_NationCodeStr')
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
	
	CREATE TABLE dbo.Tmp_TB_DefMapItemBag
		(
		IDX int NOT NULL IDENTITY (1, 1),
		f_NationCodeStr nvarchar(50) NOT NULL,
		MapNo int NOT NULL,
		Memo nvarchar(50) NOT NULL,
		SuccessRateNo int NOT NULL,
		BagGrp01 int NOT NULL,
		BagGrp02 int NOT NULL,
		BagGrp03 int NOT NULL,
		BagGrp04 int NOT NULL,
		BagGrp05 int NOT NULL,
		BagGrp06 int NOT NULL,
		BagGrp07 int NOT NULL,
		BagGrp08 int NOT NULL,
		BagGrp09 int NOT NULL,
		BagGrp10 int NOT NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'맵에서 드랍되는 아이템을 결정합니다. TB_DefItemBagGroup 을 참조 합니다.'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefMapItemBag', NULL, NULL

	ALTER TABLE dbo.Tmp_TB_DefMapItemBag ADD CONSTRAINT
		DF_TB_DefMapItemBag_f_NationCode DEFAULT N'0' FOR f_NationCodeStr
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefMapItemBag ON
	
	IF EXISTS(SELECT * FROM dbo.TB_DefMapItemBag)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefMapItemBag (IDX, MapNo, Memo, SuccessRateNo, BagGrp01, BagGrp02, BagGrp03, BagGrp04, BagGrp05, BagGrp06, BagGrp07, BagGrp08, BagGrp09, BagGrp10)
			SELECT IDX, MapNo, Memo, SuccessRateNo, BagGrp01, BagGrp02, BagGrp03, BagGrp04, BagGrp05, BagGrp06, BagGrp07, BagGrp08, BagGrp09, BagGrp10 FROM dbo.TB_DefMapItemBag WITH (HOLDLOCK TABLOCKX)')
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefMapItemBag OFF
	
	DROP TABLE dbo.TB_DefMapItemBag
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefMapItemBag', N'TB_DefMapItemBag', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefMapItemBag ADD CONSTRAINT
		PK_TB_DefMapItemBag PRIMARY KEY CLUSTERED 
		(
		MapNo,
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	
	COMMIT
END