USE [DR2_Def]
GO

/****** Object:  Table [dbo].[TB_DefMonster]    Script Date: 03/24/2011 16:07:13 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMonster]') AND [type] in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefMonster](
		[MonsterNo] [int] NOT NULL,
		[Name] [int] NOT NULL,
		[Memo] [nvarchar](100) NULL,
		[Abil01] [int] NOT NULL,
		[Abil02] [int] NOT NULL,
		[Abil03] [int] NOT NULL,
		[Abil04] [int] NOT NULL,
		[Abil05] [int] NOT NULL,
		[Abil06] [int] NOT NULL,
		[Abil07] [int] NOT NULL,
		[Abil08] [int] NOT NULL,
		[Abil09] [int] NOT NULL,
		[Abil10] [int] NOT NULL,
	 CONSTRAINT [PK_TB_DefMonster3] PRIMARY KEY CLUSTERED 
	(
		[MonsterNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]


	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Monster definition' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefMonster'

END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMonster]') AND [name] = N'Abil11')
BEGIN
	ALTER TABLE [dbo].[TB_DefMonster] ADD [Abil11] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_ClassReward_Abil11] DEFAULT (0)
	ALTER TABLE [dbo].[TB_DefMonster] ADD [Abil12] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_ClassReward_Abil12] DEFAULT (0)
	ALTER TABLE [dbo].[TB_DefMonster] ADD [Abil13] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_ClassReward_Abil13] DEFAULT (0)
	ALTER TABLE [dbo].[TB_DefMonster] ADD [Abil14] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_ClassReward_Abil14] DEFAULT (0)
	ALTER TABLE [dbo].[TB_DefMonster] ADD [Abil15] [int] NOT NULL CONSTRAINT [DF_TB_DefMission_ClassReward_Abil15] DEFAULT (0)
END
GO

IF EXISTS(SELECT * FROM SYS.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefMonster') and [name] = N'NationCode_Str')
BEGIN
	EXECUTE sp_rename N'dbo.TB_DefMonster.[NationCode_Str]', N'f_NationCodeStr', 'COLUMN'
END
GO

IF NOT EXISTS(SELECT * FROM SYS.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefMonster') and [name] = N'f_NationCodeStr')
BEGIN

	ALTER TABLE dbo.TB_DefMonster
		DROP CONSTRAINT DF_TB_DefMission_ClassReward_Abil11
		
	ALTER TABLE dbo.TB_DefMonster
		DROP CONSTRAINT DF_TB_DefMission_ClassReward_Abil12
		
	ALTER TABLE dbo.TB_DefMonster
		DROP CONSTRAINT DF_TB_DefMission_ClassReward_Abil13

	ALTER TABLE dbo.TB_DefMonster
		DROP CONSTRAINT DF_TB_DefMission_ClassReward_Abil14

	ALTER TABLE dbo.TB_DefMonster
		DROP CONSTRAINT DF_TB_DefMission_ClassReward_Abil15


	CREATE TABLE dbo.Tmp_TB_DefMonster
		(
		f_NationCodeStr nvarchar(50) NOT NULL,
		MonsterNo int NOT NULL,
		Name int NOT NULL,
		Memo nvarchar(100) NULL,
		Abil01 int NOT NULL,
		Abil02 int NOT NULL,
		Abil03 int NOT NULL,
		Abil04 int NOT NULL,
		Abil05 int NOT NULL,
		Abil06 int NOT NULL,
		Abil07 int NOT NULL,
		Abil08 int NOT NULL,
		Abil09 int NOT NULL,
		Abil10 int NOT NULL,
		Abil11 int NOT NULL,
		Abil12 int NOT NULL,
		Abil13 int NOT NULL,
		Abil14 int NOT NULL,
		Abil15 int NOT NULL
		)  ON [PRIMARY]

	EXECUTE sp_addextendedproperty N'MS_Description', N'Monster definition', N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefMonster', NULL, NULL

	ALTER TABLE dbo.Tmp_TB_DefMonster ADD CONSTRAINT
		DF_TB_DefMission_ClassReward_Abil11 DEFAULT ((0)) FOR Abil11

	ALTER TABLE dbo.Tmp_TB_DefMonster ADD CONSTRAINT
		DF_TB_DefMission_ClassReward_Abil12 DEFAULT ((0)) FOR Abil12

	ALTER TABLE dbo.Tmp_TB_DefMonster ADD CONSTRAINT
		DF_TB_DefMission_ClassReward_Abil13 DEFAULT ((0)) FOR Abil13

	ALTER TABLE dbo.Tmp_TB_DefMonster ADD CONSTRAINT
		DF_TB_DefMission_ClassReward_Abil14 DEFAULT ((0)) FOR Abil14

	ALTER TABLE dbo.Tmp_TB_DefMonster ADD CONSTRAINT
		DF_TB_DefMission_ClassReward_Abil15 DEFAULT ((0)) FOR Abil15

	IF EXISTS(SELECT * FROM dbo.TB_DefMonster)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefMonster (f_NationCodeStr, MonsterNo, Name, Memo, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10, Abil11, Abil12, Abil13, Abil14, Abil15)
			SELECT 0, MonsterNo, Name, Memo, Abil01, Abil02, Abil03, Abil04, Abil05, Abil06, Abil07, Abil08, Abil09, Abil10, Abil11, Abil12, Abil13, Abil14, Abil15 FROM dbo.TB_DefMonster WITH (HOLDLOCK TABLOCKX)')

	DROP TABLE dbo.TB_DefMonster

	EXECUTE sp_rename N'dbo.Tmp_TB_DefMonster', N'TB_DefMonster', 'OBJECT' 

	ALTER TABLE dbo.TB_DefMonster ADD CONSTRAINT
		PK_TB_DefMonster3 PRIMARY KEY CLUSTERED 
		(
		MonsterNo
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

END
GO

ALTER TABLE dbo.TB_DefMonster
	DROP CONSTRAINT PK_TB_DefMonster3

ALTER TABLE dbo.TB_DefMonster ADD CONSTRAINT
	PK_TB_DefMonster3 PRIMARY KEY CLUSTERED 
	(
	f_NationCodeStr,
	MonsterNo
	) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
	

