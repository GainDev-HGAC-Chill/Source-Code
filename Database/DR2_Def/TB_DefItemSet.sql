USE [DR2_Def]
GO
IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemSet') AND [name] = N'f_NationCodeStr')
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
	
	ALTER TABLE dbo.TB_DefItemSet
		DROP CONSTRAINT DF_TB_DefItemSet_SetNo
	
	ALTER TABLE dbo.TB_DefItemSet
		DROP CONSTRAINT DF_TB_DefItemSet_Name
	
	ALTER TABLE dbo.TB_DefItemSet
		DROP CONSTRAINT DF_TB_DefItemSet_SetAbil01
	
	ALTER TABLE dbo.TB_DefItemSet
		DROP CONSTRAINT DF_TB_DefItemSet_SetAbil02
	
	ALTER TABLE dbo.TB_DefItemSet
		DROP CONSTRAINT DF_TB_DefItemSet_NeedItem01
	
	ALTER TABLE dbo.TB_DefItemSet
		DROP CONSTRAINT DF_TB_DefItemSet_NeedItem02
	
	ALTER TABLE dbo.TB_DefItemSet
		DROP CONSTRAINT DF_TB_DefItemSet_NeedItem03
	
	ALTER TABLE dbo.TB_DefItemSet
		DROP CONSTRAINT DF_TB_DefItemSet_NeedItem04
	
	ALTER TABLE dbo.TB_DefItemSet
		DROP CONSTRAINT DF_TB_DefItemSet_NeedItem05
	
	ALTER TABLE dbo.TB_DefItemSet
		DROP CONSTRAINT DF_TB_DefItemSet_NeedItem06
	
	ALTER TABLE dbo.TB_DefItemSet
		DROP CONSTRAINT DF_TB_DefItemSet_NeedItem07
	
	ALTER TABLE dbo.TB_DefItemSet
		DROP CONSTRAINT DF_TB_DefItemSet_NeedItem08
	
	ALTER TABLE dbo.TB_DefItemSet
		DROP CONSTRAINT DF_TB_DefItemSet_NeedItem09
	
	ALTER TABLE dbo.TB_DefItemSet
		DROP CONSTRAINT DF_TB_DefItemSet_NeedItem10
	
	CREATE TABLE dbo.Tmp_TB_DefItemSet
		(
		IDX int NOT NULL IDENTITY (1, 1) NOT FOR REPLICATION,
		f_NationCodeStr nvarchar(50) NOT NULL,
		SetNo int NOT NULL,
		Name int NOT NULL,
		Memo nvarchar(100) NULL,
		SetAbil01 int NOT NULL,
		SetAbil02 int NOT NULL,
		NeedItem01 int NOT NULL,
		NeedItem02 int NOT NULL,
		NeedItem03 int NOT NULL,
		NeedItem04 int NOT NULL,
		NeedItem05 int NOT NULL,
		NeedItem06 int NOT NULL,
		NeedItem07 int NOT NULL,
		NeedItem08 int NOT NULL,
		NeedItem09 int NOT NULL,
		NeedItem10 int NOT NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'Item Combo definition'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefItemSet', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_f_NationCode DEFAULT N'0' FOR f_NationCodeStr
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_SetNo DEFAULT ((0)) FOR SetNo
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_Name DEFAULT ((0)) FOR Name
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_SetAbil01 DEFAULT ((0)) FOR SetAbil01
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_SetAbil02 DEFAULT ((0)) FOR SetAbil02
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_NeedItem01 DEFAULT ((0)) FOR NeedItem01
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_NeedItem02 DEFAULT ((0)) FOR NeedItem02
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_NeedItem03 DEFAULT ((0)) FOR NeedItem03
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_NeedItem04 DEFAULT ((0)) FOR NeedItem04
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_NeedItem05 DEFAULT ((0)) FOR NeedItem05
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_NeedItem06 DEFAULT ((0)) FOR NeedItem06
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_NeedItem07 DEFAULT ((0)) FOR NeedItem07
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_NeedItem08 DEFAULT ((0)) FOR NeedItem08
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_NeedItem09 DEFAULT ((0)) FOR NeedItem09
	
	ALTER TABLE dbo.Tmp_TB_DefItemSet ADD CONSTRAINT
		DF_TB_DefItemSet_NeedItem10 DEFAULT ((0)) FOR NeedItem10
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefItemSet ON
	
	IF EXISTS(SELECT * FROM dbo.TB_DefItemSet)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefItemSet (IDX, SetNo, Name, Memo, SetAbil01, SetAbil02, NeedItem01, NeedItem02, NeedItem03, NeedItem04, NeedItem05, NeedItem06, NeedItem07, NeedItem08, NeedItem09, NeedItem10)
			SELECT IDX, SetNo, Name, Memo, SetAbil01, SetAbil02, NeedItem01, NeedItem02, NeedItem03, NeedItem04, NeedItem05, NeedItem06, NeedItem07, NeedItem08, NeedItem09, NeedItem10 FROM dbo.TB_DefItemSet WITH (HOLDLOCK TABLOCKX)')
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefItemSet OFF
	
	DROP TABLE dbo.TB_DefItemSet
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefItemSet', N'TB_DefItemSet', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefItemSet ADD CONSTRAINT
		PK_TB_DefItemSet PRIMARY KEY CLUSTERED 
		(
		SetNo,
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	
	COMMIT
END