USE [DR2_local]
GO

/* To prevent any potential data loss issues, you should review this script in detail before running it outside the context of the database designer.*/
IF NOT EXISTS(SELECT 1 FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefFilterUnicode]'))
BEGIN
	/****** Object:  Table [dbo].[TB_DefFilterUnicode]    Script Date: 04/16/2009 18:22:16 ******/
	SET ANSI_NULLS ON
	SET QUOTED_IDENTIFIER ON
	CREATE TABLE [dbo].[TB_DefFilterUnicode](
		[IDX] [int] IDENTITY(1,1) NOT FOR REPLICATION NOT NULL,
		[StartRange] [nvarchar](1) NOT NULL,
		[EndRange] [nvarchar](1) NOT NULL,
		[FilterType] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefFilterUnicode_FilterType]  DEFAULT ((0))
	) ON [PRIMARY]
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Name-making  rule difinition such as Character name, guild name' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefFilterUnicode'
END

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
GO
ALTER TABLE dbo.TB_DefFilterUnicode
	DROP CONSTRAINT DF_TB_DefFilterUnicode_FilterType
GO
CREATE TABLE dbo.Tmp_TB_DefFilterUnicode
	(
	IDX int NOT NULL IDENTITY (1, 1) NOT FOR REPLICATION,
	f_FuncCode int NOT NULL,
	StartRange nvarchar(1) NOT NULL,
	EndRange nvarchar(1) NOT NULL,
	FilterType tinyint NOT NULL
	)  ON [PRIMARY]
GO
DECLARE @v sql_variant 
SET @v = N'Name-making  rule difinition such as Character name, guild name'
EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefFilterUnicode', NULL, NULL
GO
ALTER TABLE dbo.Tmp_TB_DefFilterUnicode ADD CONSTRAINT
	DF_TB_DefFilterUnicode_f_FuncCode DEFAULT -1 FOR f_FuncCode
GO
ALTER TABLE dbo.Tmp_TB_DefFilterUnicode ADD CONSTRAINT
	DF_TB_DefFilterUnicode_FilterType DEFAULT ((0)) FOR FilterType
GO
SET IDENTITY_INSERT dbo.Tmp_TB_DefFilterUnicode ON
GO
IF EXISTS(SELECT * FROM dbo.TB_DefFilterUnicode)
	 EXEC('INSERT INTO dbo.Tmp_TB_DefFilterUnicode (IDX, StartRange, EndRange, FilterType)
		SELECT IDX, StartRange, EndRange, FilterType FROM dbo.TB_DefFilterUnicode WITH (HOLDLOCK TABLOCKX)')
GO
SET IDENTITY_INSERT dbo.Tmp_TB_DefFilterUnicode OFF
GO
DROP TABLE dbo.TB_DefFilterUnicode
GO
EXECUTE sp_rename N'dbo.Tmp_TB_DefFilterUnicode', N'TB_DefFilterUnicode', 'OBJECT' 
GO
COMMIT
