USE [DR2_Def]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefCountControl') AND [name] = N'f_NationCodeStr')
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
	
	CREATE TABLE dbo.Tmp_TB_DefCountControl
		(
		IDX int NOT NULL IDENTITY (1, 1) NOT FOR REPLICATION,
		f_NationCodeStr nvarchar(50) NOT NULL,
		No int NOT NULL,
		Memo nvarchar(50) NOT NULL,
		Count01 smallint NOT NULL,
		Count02 smallint NOT NULL,
		Count03 smallint NOT NULL,
		Count04 smallint NOT NULL,
		Count05 smallint NOT NULL,
		Count06 smallint NOT NULL,
		Count07 smallint NOT NULL,
		Count08 smallint NOT NULL,
		Count09 smallint NOT NULL,
		Count10 smallint NOT NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'Controlling Number of Items of ItemBag'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefCountControl', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefCountControl ADD CONSTRAINT
		DF_TB_DefCountControl_f_NationCodeStr DEFAULT N'0' FOR f_NationCodeStr
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefCountControl ON
	
	IF EXISTS(SELECT * FROM dbo.TB_DefCountControl)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefCountControl (IDX, No, Memo, Count01, Count02, Count03, Count04, Count05, Count06, Count07, Count08, Count09, Count10)
			SELECT IDX, No, Memo, Count01, Count02, Count03, Count04, Count05, Count06, Count07, Count08, Count09, Count10 FROM dbo.TB_DefCountControl WITH (HOLDLOCK TABLOCKX)')
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefCountControl OFF
	
	DROP TABLE dbo.TB_DefCountControl
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefCountControl', N'TB_DefCountControl', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefCountControl ADD CONSTRAINT
		PK_TB_DefCountControl PRIMARY KEY CLUSTERED 
		(
		No,
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	
	COMMIT
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefCountControl') and [name] = N'Total_Count')
BEGIN
	ALTER TABLE dbo.TB_DefCountControl ADD
	Total_Count int NOT NULL CONSTRAINT DF_TB_DefCountControl_Total_Count DEFAULT 0
END