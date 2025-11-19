USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEffectAbil_Player]') AND [name] = N'NationCodeStr')
BEGIN

CREATE TABLE [dbo].[Tmp_TB_DefEffectAbil_Player](
	[NationCodeStr] [nvarchar](50) NOT NULL,
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
 CONSTRAINT [PK_TB_DefEffectAbil_Player2] PRIMARY KEY CLUSTERED 
(
	[EffectAbilNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

	IF EXISTS (SELECT * FROM dbo.TB_DefEffectAbil_Player)
	EXEC('INSERT INTO dbo.Tmp_TB_DefEffectAbil_Player (NationCodeStr, EffectAbilNo, Memo, Type01, Value01, Type02, Value02, Type03, Value03, Type04, Value04, Type05, Value05,
													   Type06, Value06, Type07, Value07, Type08, Value08, Type09, Value09, Type10, Value10)
		  SELECT 0, EffectAbilNo, Memo, Type01, Value01, Type02, Value02, Type03, Value03, Type04, Value04, Type05, Value05,
													   Type06, Value06, Type07, Value07, Type08, Value08, Type09, Value09, Type10, Value10
		  FROM dbo.TB_DefEffectAbil_Player WITH (HOLDLOCK TABLOCKX)')
	
	DROP TABLE TB_DefEffectAbil_Player
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefEffectAbil_Player', 'TB_DefEffectAbil_Player', 'OBJECT'

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Ability of Buf/Debuf Definition(Player)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefEffectAbil_Player'

END
GO

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEffectAbil_Player]') AND [name] = N'NationCodeStr')
BEGIN
	ALTER TABLE dbo.TB_DefEffectAbil_Player
		DROP CONSTRAINT PK_TB_DefEffectAbil_Player2
	
	ALTER TABLE dbo.TB_DefEffectAbil_Player ADD CONSTRAINT
		PK_TB_DefEffectAbil_Player2 PRIMARY KEY CLUSTERED 
		(
		NationCodeStr,
		EffectAbilNo
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
GO