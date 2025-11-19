USE DR2_DEF
GO

IF NOT EXISTS(SELECT * FROM SYS.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemOptionAbil') and [name] = N'f_PieceCount')
BEGIN
	SET XACT_ABORT ON

	CREATE TABLE dbo.Tmp_TB_DefItemOptionAbil
		(
		OptionAbilNo int NOT NULL,
		f_PieceCount int NOT NULL,
		f_Order int NOT NULL,
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
	SET @v = N'Ability of Item option'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefItemOptionAbil', NULL, NULL

	ALTER TABLE dbo.Tmp_TB_DefItemOptionAbil ADD CONSTRAINT
		DF_TB_DefItemOptionAbil_f_PieceCount DEFAULT 1 FOR f_PieceCount

	ALTER TABLE dbo.Tmp_TB_DefItemOptionAbil ADD CONSTRAINT
		DF_TB_DefItemOptionAbil_f_Order DEFAULT 1 FOR f_Order

	IF EXISTS(SELECT * FROM dbo.TB_DefItemOptionAbil)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefItemOptionAbil (OptionAbilNo, Memo, Type01, Value01, Type02, Value02, Type03, Value03, Type04, Value04, Type05, Value05, Type06, Value06, Type07, Value07, Type08, Value08, Type09, Value09, Type10, Value10)
			SELECT OptionAbilNo, Memo, Type01, Value01, Type02, Value02, Type03, Value03, Type04, Value04, Type05, Value05, Type06, Value06, Type07, Value07, Type08, Value08, Type09, Value09, Type10, Value10 FROM dbo.TB_DefItemOptionAbil WITH (HOLDLOCK TABLOCKX)')

	DROP TABLE dbo.TB_DefItemOptionAbil

	EXECUTE sp_rename N'dbo.Tmp_TB_DefItemOptionAbil', N'TB_DefItemOptionAbil', 'OBJECT' 

	ALTER TABLE dbo.TB_DefItemOptionAbil ADD CONSTRAINT
		PK_TB_DefItemOptionAbil PRIMARY KEY CLUSTERED 
		(
		OptionAbilNo,
		f_PieceCount,
		f_Order
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
	SET XACT_ABORT OFF
END

IF EXISTS(SELECT * FROM SYS.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemOptionAbil') and [name] = N'NationCode_Str')
BEGIN
	EXECUTE sp_rename N'dbo.TB_DefItemOptionAbil.NationCode_Str', N'f_NationCodeStr', 'COLUMN'
END
GO

IF NOT EXISTS(SELECT * FROM SYS.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemOptionAbil') and [name] = N'f_NationCodeStr')
BEGIN
	ALTER TABLE dbo.TB_DefItemOptionAbil
		DROP CONSTRAINT DF_TB_DefItemOptionAbil_f_PieceCount

	ALTER TABLE dbo.TB_DefItemOptionAbil
		DROP CONSTRAINT DF_TB_DefItemOptionAbil_f_Order

	CREATE TABLE dbo.Tmp_TB_DefItemOptionAbil
		(
		f_NationCodeStr nvarchar(50) NOT NULL,
		OptionAbilNo int NOT NULL,
		f_PieceCount int NOT NULL,
		f_Order int NOT NULL,
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

	EXECUTE sp_addextendedproperty N'MS_Description', N'Ability of Item option', N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefItemOptionAbil', NULL, NULL

	ALTER TABLE dbo.Tmp_TB_DefItemOptionAbil ADD CONSTRAINT
		DF_TB_DefItemOptionAbil_f_PieceCount DEFAULT ((1)) FOR f_PieceCount

	ALTER TABLE dbo.Tmp_TB_DefItemOptionAbil ADD CONSTRAINT
		DF_TB_DefItemOptionAbil_f_Order DEFAULT ((1)) FOR f_Order

	IF EXISTS(SELECT * FROM dbo.TB_DefItemOptionAbil)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefItemOptionAbil (f_NationCodeStr, OptionAbilNo, f_PieceCount, f_Order, Memo, Type01, Value01, Type02, Value02, Type03, Value03, Type04, Value04, Type05, Value05, Type06, Value06, Type07, Value07, Type08, Value08, Type09, Value09, Type10, Value10)
			SELECT 0, OptionAbilNo, f_PieceCount, f_Order, Memo, Type01, Value01, Type02, Value02, Type03, Value03, Type04, Value04, Type05, Value05, Type06, Value06, Type07, Value07, Type08, Value08, Type09, Value09, Type10, Value10 FROM dbo.TB_DefItemOptionAbil WITH (HOLDLOCK TABLOCKX)')

	DROP TABLE dbo.TB_DefItemOptionAbil

	EXECUTE sp_rename N'dbo.Tmp_TB_DefItemOptionAbil', N'TB_DefItemOptionAbil', 'OBJECT' 

	ALTER TABLE dbo.TB_DefItemOptionAbil ADD CONSTRAINT
		PK_TB_DefItemOptionAbil PRIMARY KEY CLUSTERED 
		(
		f_NationCodeStr,
		OptionAbilNo,
		f_PieceCount,
		f_Order
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
GO