USE [DR2_Def]
GO

/****** Object:  Table [dbo].[TB_DefEffectAbil_Mon]    Script Date: 02/28/2012 19:43:26 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEffectAbil_Mon]') AND [type] IN (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefEffectAbil_Mon](
		[EffectAbilNo] [int] NOT NULL,
		[Memo] [nvarchar](100) NULL,
		[Type01] [int] NOT NULL,
		[Value01] [int] NOT NULL,
		[Type02] [int] NOT NULL,
		[Value02] [int] NOT NULL,
		[Type03] [int] NOT NULL,
		[Value03] [int] NOT NULL,
		[Type04] [int] NOT NULL,
		[Value04] [int] NOT NULL,
		[Type05] [int] NOT NULL,
		[Value05] [int] NOT NULL,
		[Type06] [int] NOT NULL,
		[Value06] [int] NOT NULL,
		[Type07] [int] NOT NULL,
		[Value07] [int] NOT NULL,
		[Type08] [int] NOT NULL,
		[Value08] [int] NOT NULL,
		[Type09] [int] NOT NULL,
		[Value09] [int] NOT NULL,
		[Type10] [int] NOT NULL,
		[Value10] [int] NOT NULL,
	 CONSTRAINT [PK_TB_DefEffectAbil_Mon] PRIMARY KEY CLUSTERED 
	(
		[EffectAbilNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]

	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Ability of Buf/Debuf Definition(Monster)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefEffectAbil_Mon'
END
GO

IF EXISTS(SELECT * FROM SYS.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefEffectAbil_Mon') and [name] = N'NationCode_Str')
BEGIN
	EXECUTE sp_rename N'dbo.TB_DefEffectAbil_Mon.NationCode_Str', N'f_NationCodeStr', 'COLUMN'
END
GO

IF NOT EXISTS(SELECT * FROM SYS.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefEffectAbil_Mon') and [name] = N'f_NationCodeStr')
BEGIN
	CREATE TABLE dbo.Tmp_TB_DefEffectAbil_Mon
	(
	f_NationCodeStr nvarchar(50) NOT NULL,
	EffectAbilNo int NOT NULL,
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

	EXECUTE sp_addextendedproperty N'MS_Description', N'Ability of Buf/Debuf Definition(Monster)', N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefEffectAbil_Mon', NULL, NULL

	IF EXISTS(SELECT * FROM dbo.TB_DefEffectAbil_Mon)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefEffectAbil_Mon (f_NationCodeStr, EffectAbilNo, Memo, Type01, Value01, Type02, Value02, Type03, Value03, Type04, Value04, Type05, Value05, Type06, Value06, Type07, Value07, Type08, Value08, Type09, Value09, Type10, Value10)
			SELECT 0, EffectAbilNo, Memo, Type01, Value01, Type02, Value02, Type03, Value03, Type04, Value04, Type05, Value05, Type06, Value06, Type07, Value07, Type08, Value08, Type09, Value09, Type10, Value10 FROM dbo.TB_DefEffectAbil_Mon WITH (HOLDLOCK TABLOCKX)')

	DROP TABLE dbo.TB_DefEffectAbil_Mon

	EXECUTE sp_rename N'dbo.Tmp_TB_DefEffectAbil_Mon', N'TB_DefEffectAbil_Mon', 'OBJECT' 

	ALTER TABLE dbo.TB_DefEffectAbil_Mon ADD CONSTRAINT
		PK_TB_DefEffectAbil_Mon PRIMARY KEY CLUSTERED 
		(
		f_NationCodeStr,
		EffectAbilNo
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
GO