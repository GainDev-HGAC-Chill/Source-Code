USE [DR2_Def]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefSuccessRateControl') AND [name] = N'f_NationCodeStr')
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
	
	CREATE TABLE dbo.Tmp_TB_DefSuccessRateControl
		(
		[Index] int NOT NULL IDENTITY (1, 1) NOT FOR REPLICATION,
		f_NationCodeStr nvarchar(50) NOT NULL,
		No int NOT NULL,
		Memo nvarchar(50) NOT NULL,
		Rate01 smallint NOT NULL,
		Rate02 smallint NOT NULL,
		Rate03 smallint NOT NULL,
		Rate04 smallint NOT NULL,
		Rate05 smallint NOT NULL,
		Rate06 smallint NOT NULL,
		Rate07 smallint NOT NULL,
		Rate08 smallint NOT NULL,
		Rate09 smallint NOT NULL,
		Rate10 smallint NOT NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'Success rate control while making random action such as enchanting item'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefSuccessRateControl', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefSuccessRateControl ADD CONSTRAINT
		DF_TB_DefSuccessRateControl_f_NationCodeStr DEFAULT N'0' FOR f_NationCodeStr
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefSuccessRateControl ON
	
	IF EXISTS(SELECT * FROM dbo.TB_DefSuccessRateControl)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefSuccessRateControl ([Index], No, Memo, Rate01, Rate02, Rate03, Rate04, Rate05, Rate06, Rate07, Rate08, Rate09, Rate10)
			SELECT [Index], No, Memo, Rate01, Rate02, Rate03, Rate04, Rate05, Rate06, Rate07, Rate08, Rate09, Rate10 FROM dbo.TB_DefSuccessRateControl WITH (HOLDLOCK TABLOCKX)')
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefSuccessRateControl OFF
	
	DROP TABLE dbo.TB_DefSuccessRateControl
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefSuccessRateControl', N'TB_DefSuccessRateControl', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefSuccessRateControl ADD CONSTRAINT
		PK_TB_DefSuccessRateControl PRIMARY KEY CLUSTERED 
		(
		No,
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	
	COMMIT

END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefSuccessRateControl') and [name] = N'Total_Rate')
BEGIN
	ALTER TABLE dbo.TB_DefSuccessRateControl ADD
	Total_Rate int NOT NULL CONSTRAINT DF_TB_DefSuccessRateControl_Total_Rate DEFAULT 0
END