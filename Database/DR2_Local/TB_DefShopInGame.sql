USE [DR2_Local]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefShopInGame') AND [name] = N'f_NationCodeStr')
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
	
	ALTER TABLE dbo.TB_DefShopInGame
		DROP CONSTRAINT DF_TB_DefShopInGame2_Category
	
	ALTER TABLE dbo.TB_DefShopInGame
		DROP CONSTRAINT DF_TB_DefShopInGame_CP
	
	ALTER TABLE dbo.TB_DefShopInGame
		DROP CONSTRAINT DF_TB_DefShopInGame_Coin
	
	ALTER TABLE dbo.TB_DefShopInGame
		DROP CONSTRAINT DF_TB_DefShopInGame_UseTime
	
	ALTER TABLE dbo.TB_DefShopInGame
		DROP CONSTRAINT DF_TB_DefShopInGame_TimeType
	
	CREATE TABLE dbo.Tmp_TB_DefShopInGame
		(
		IDX int NOT NULL IDENTITY (1, 1) NOT FOR REPLICATION,
		f_NationCodeStr nvarchar(50) NOT NULL,
		ShopGuid uniqueidentifier NOT NULL,
		Category int NOT NULL,
		ItemNo int NOT NULL,
		Memo nvarchar(300) NULL,
		Price int NOT NULL,
		CP int NOT NULL,
		Coin int NOT NULL,
		UseTime int NOT NULL,
		TimeType tinyint NOT NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'Item shop'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefShopInGame', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefShopInGame ADD CONSTRAINT
		DF_TB_DefShopInGame_f_NationCodeStr DEFAULT N'0' FOR f_NationCodeStr
	
	ALTER TABLE dbo.Tmp_TB_DefShopInGame ADD CONSTRAINT
		DF_TB_DefShopInGame2_Category DEFAULT ((0)) FOR Category
	
	ALTER TABLE dbo.Tmp_TB_DefShopInGame ADD CONSTRAINT
		DF_TB_DefShopInGame_CP DEFAULT ((0)) FOR CP
	
	ALTER TABLE dbo.Tmp_TB_DefShopInGame ADD CONSTRAINT
		DF_TB_DefShopInGame_Coin DEFAULT ((0)) FOR Coin
	
	ALTER TABLE dbo.Tmp_TB_DefShopInGame ADD CONSTRAINT
		DF_TB_DefShopInGame_UseTime DEFAULT ((0)) FOR UseTime
	
	ALTER TABLE dbo.Tmp_TB_DefShopInGame ADD CONSTRAINT
		DF_TB_DefShopInGame_TimeType DEFAULT ((0)) FOR TimeType
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefShopInGame ON
	
	IF EXISTS(SELECT * FROM dbo.TB_DefShopInGame)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefShopInGame (IDX, ShopGuid, Category, ItemNo, Memo, Price, CP, Coin, UseTime, TimeType)
			SELECT IDX, ShopGuid, Category, ItemNo, Memo, Price, CP, Coin, UseTime, TimeType FROM dbo.TB_DefShopInGame WITH (HOLDLOCK TABLOCKX)')
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefShopInGame OFF
	
	DROP TABLE dbo.TB_DefShopInGame
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefShopInGame', N'TB_DefShopInGame', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefShopInGame ADD CONSTRAINT
		PK_TB_DefShopInGame_ShopGuid_ItemNo PRIMARY KEY CLUSTERED 
		(
		ShopGuid,
		ItemNo,
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	
	COMMIT
END