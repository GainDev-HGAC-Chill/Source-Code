USE [DR2_Def]
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemAbil_Pet') AND [name] = N'f_NationCodeStr')
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
	
	CREATE TABLE dbo.Tmp_TB_DefItemAbil_Pet
		(
		f_NationCodeStr nvarchar(50) NOT NULL,
		ItemAbilNo int NOT NULL,
		Memo nvarchar(100) NULL,
		Type01 int NOT NULL,
		Value01 int NOT NULL,
		Type02 int NOT NULL,
		Value02 int NOT NULL,
		Type03 int NOT NULL,
		Value03 int NOT NULL,
		Type04 int NOT NULL,
		Value04 int NOT NULL,
		Type05 int NOT NULL,
		Value05 int NOT NULL,
		Type06 int NOT NULL,
		Value06 int NOT NULL,
		Type07 int NOT NULL,
		Value07 int NOT NULL,
		Type08 int NOT NULL,
		Value08 int NOT NULL,
		Type09 int NOT NULL,
		Value09 int NOT NULL,
		Type10 int NOT NULL,
		Value10 int NOT NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'Ability of Items(Pet)'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefItemAbil_Pet', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefItemAbil_Pet ADD CONSTRAINT
		DF_TB_DefItemAbil_Pet_f_NationCodeStr DEFAULT N'0' FOR f_NationCodeStr
	
	IF EXISTS(SELECT * FROM dbo.TB_DefItemAbil_Pet)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefItemAbil_Pet (ItemAbilNo, Memo, Type01, Value01, Type02, Value02, Type03, Value03, Type04, Value04, Type05, Value05, Type06, Value06, Type07, Value07, Type08, Value08, Type09, Value09, Type10, Value10)
			SELECT ItemAbilNo, Memo, Type01, Value01, Type02, Value02, Type03, Value03, Type04, Value04, Type05, Value05, Type06, Value06, Type07, Value07, Type08, Value08, Type09, Value09, Type10, Value10 FROM dbo.TB_DefItemAbil_Pet WITH (HOLDLOCK TABLOCKX)')
	
	DROP TABLE dbo.TB_DefItemAbil_Pet
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefItemAbil_Pet', N'TB_DefItemAbil_Pet', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefItemAbil_Pet ADD CONSTRAINT
		PK_TB_DefItemAbil_Pet PRIMARY KEY CLUSTERED 
		(
		ItemAbilNo,
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	
	COMMIT
END
