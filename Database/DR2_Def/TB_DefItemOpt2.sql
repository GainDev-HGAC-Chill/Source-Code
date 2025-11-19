USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefItemOpt2]') AND type in (N'U'))
BEGIN

	CREATE TABLE [dbo].[TB_DefItemOpt2](
		[IDX] [int] IDENTITY(1,1) NOT NULL,
		[OptionType] [int] NOT NULL,
		[OptionGroup] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_OptionGroup]  DEFAULT ((0)),
		[AbleEquipPos] [int] NOT NULL,
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
		[OutRate] [int] NOT NULL,
		[NameNo] [int] NOT NULL,
		[AbilType] [int] NOT NULL,
		[ValueLv1] [int] NOT NULL,
		[ValueLv2] [int] NOT NULL,
		[ValueLv3] [int] NOT NULL,
		[ValueLv4] [int] NOT NULL,
		[ValueLv5] [int] NOT NULL,
		[ValueLv6] [int] NOT NULL,
		[ValueLv7] [int] NOT NULL,
		[ValueLv8] [int] NOT NULL,
		[ValueLv9] [int] NOT NULL,
		[ValueLv10] [int] NOT NULL,
		[ValueLv11] [int] NOT NULL,
		[ValueLv12] [int] NOT NULL,
		[ValueLv13] [int] NOT NULL,
		[ValueLv14] [int] NOT NULL,
		[ValueLv15] [int] NOT NULL,
		[ValueLv16] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv16]  DEFAULT ((0)),
		[ValueLv17] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv17]  DEFAULT ((0)),
		[ValueLv18] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv18]  DEFAULT ((0)),
		[ValueLv19] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv19]  DEFAULT ((0)),
		[ValueLv20] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv20]  DEFAULT ((0)),
		[ValueLv21] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv21]  DEFAULT ((0)),
		[ValueLv22] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv22]  DEFAULT ((0)),
		[ValueLv23] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv23]  DEFAULT ((0)),
		[ValueLv24] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv24]  DEFAULT ((0)),
		[ValueLv25] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv25]  DEFAULT ((0)),
		[ValueLv26] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv26]  DEFAULT ((0)),
		[ValueLv27] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv27]  DEFAULT ((0)),
		[ValueLv28] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv28]  DEFAULT ((0)),
		[ValueLv29] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv29]  DEFAULT ((0)),
		[ValueLv30] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv30]  DEFAULT ((0)),
		[ValueLv31] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_ValueLv31]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_DefItemOpt2] PRIMARY KEY CLUSTERED 
	(
		[OptionGroup] ASC,
		[OptionType] ASC,
		[AbleEquipPos] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Item option definition' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'TB_DefItemOpt2'
END

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[DF_TB_DefItemOpt2_OptionGroup]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemOpt2]
	ADD [OptionGroup] [int] NOT NULL CONSTRAINT [DF_TB_DefItemOpt2_OptionGroup] DEFAULT ((0))
END
GO

IF EXISTS(SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemOpt2') AND [name] = N'PK_TB_DefItemOpt2_1')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemOpt2] DROP CONSTRAINT [PK_TB_DefItemOpt2_1]
END
GO

IF NOT EXISTS(SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemOpt2') AND [name] = N'PK_TB_DefItemOpt2')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemOpt2] ADD CONSTRAINT [PK_TB_DefItemOpt2] PRIMARY KEY CLUSTERED([OptionGroup] ASC, [OptionType] ASC, [AbleEquipPos] ASC)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
END
GO

IF NOT EXISTS(SELECT * from sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemOpt2') and [name] = N'f_NationCodeStr')
BEGIN
	/* To prevent any potential data loss issues, you should review this script in detail before running it outside the context of the database designer.*/
	SET XACT_ABORT ON
	
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_OptionGroup
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv16
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv17
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv18
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv19
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv20
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv21
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv22
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv23
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv24
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv25
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv26
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv27
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv28
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv29
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv30
	ALTER TABLE dbo.TB_DefItemOpt2 DROP CONSTRAINT DF_TB_DefItemOpt2_ValueLv31
	
	CREATE TABLE dbo.Tmp_TB_DefItemOpt2
		(
		IDX int NOT NULL IDENTITY (1, 1),
		f_NationCodeStr nvarchar(50) NOT NULL,
		OptionType int NOT NULL,
		OptionGroup int NOT NULL,
		AbleEquipPos int NOT NULL,
		Memo nvarchar(50) NULL,
		OutRate int NOT NULL,
		NameNo int NOT NULL,
		AbilType int NOT NULL,
		ValueLv1 int NOT NULL,
		ValueLv2 int NOT NULL,
		ValueLv3 int NOT NULL,
		ValueLv4 int NOT NULL,
		ValueLv5 int NOT NULL,
		ValueLv6 int NOT NULL,
		ValueLv7 int NOT NULL,
		ValueLv8 int NOT NULL,
		ValueLv9 int NOT NULL,
		ValueLv10 int NOT NULL,
		ValueLv11 int NOT NULL,
		ValueLv12 int NOT NULL,
		ValueLv13 int NOT NULL,
		ValueLv14 int NOT NULL,
		ValueLv15 int NOT NULL,
		ValueLv16 int NOT NULL,
		ValueLv17 int NOT NULL,
		ValueLv18 int NOT NULL,
		ValueLv19 int NOT NULL,
		ValueLv20 int NOT NULL,
		ValueLv21 int NOT NULL,
		ValueLv22 int NOT NULL,
		ValueLv23 int NOT NULL,
		ValueLv24 int NOT NULL,
		ValueLv25 int NOT NULL,
		ValueLv26 int NOT NULL,
		ValueLv27 int NOT NULL,
		ValueLv28 int NOT NULL,
		ValueLv29 int NOT NULL,
		ValueLv30 int NOT NULL,
		ValueLv31 int NOT NULL
		)  ON [PRIMARY]
	
	DECLARE @v sql_variant 
	SET @v = N'Item option definition'
	EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_TB_DefItemOpt2', NULL, NULL
	
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_f_NationCodeStr DEFAULT N'0' FOR f_NationCodeStr
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_OptionGroup DEFAULT ((0)) FOR OptionGroup
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv16 DEFAULT ((0)) FOR ValueLv16
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv17 DEFAULT ((0)) FOR ValueLv17
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv18 DEFAULT ((0)) FOR ValueLv18
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv19 DEFAULT ((0)) FOR ValueLv19
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv20 DEFAULT ((0)) FOR ValueLv20
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv21 DEFAULT ((0)) FOR ValueLv21
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv22 DEFAULT ((0)) FOR ValueLv22
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv23 DEFAULT ((0)) FOR ValueLv23
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv24 DEFAULT ((0)) FOR ValueLv24
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv25 DEFAULT ((0)) FOR ValueLv25
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv26 DEFAULT ((0)) FOR ValueLv26
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv27 DEFAULT ((0)) FOR ValueLv27
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv28 DEFAULT ((0)) FOR ValueLv28
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv29 DEFAULT ((0)) FOR ValueLv29
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv30 DEFAULT ((0)) FOR ValueLv30
	ALTER TABLE dbo.Tmp_TB_DefItemOpt2 ADD CONSTRAINT DF_TB_DefItemOpt2_ValueLv31 DEFAULT ((0)) FOR ValueLv31
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefItemOpt2 ON
	
	IF EXISTS(SELECT * FROM dbo.TB_DefItemOpt2)
		 EXEC('INSERT INTO dbo.Tmp_TB_DefItemOpt2 (IDX, OptionType, OptionGroup, AbleEquipPos, Memo, OutRate, NameNo, AbilType, ValueLv1, ValueLv2, ValueLv3, ValueLv4, ValueLv5, ValueLv6, ValueLv7, ValueLv8, ValueLv9, ValueLv10, ValueLv11, ValueLv12, ValueLv13, ValueLv14, ValueLv15, ValueLv16, ValueLv17, ValueLv18, ValueLv19, ValueLv20, ValueLv21, ValueLv22, ValueLv23, ValueLv24, ValueLv25, ValueLv26, ValueLv27, ValueLv28, ValueLv29, ValueLv30, ValueLv31)
			SELECT IDX, OptionType, OptionGroup, AbleEquipPos, Memo, OutRate, NameNo, AbilType, ValueLv1, ValueLv2, ValueLv3, ValueLv4, ValueLv5, ValueLv6, ValueLv7, ValueLv8, ValueLv9, ValueLv10, ValueLv11, ValueLv12, ValueLv13, ValueLv14, ValueLv15, ValueLv16, ValueLv17, ValueLv18, ValueLv19, ValueLv20, ValueLv21, ValueLv22, ValueLv23, ValueLv24, ValueLv25, ValueLv26, ValueLv27, ValueLv28, ValueLv29, ValueLv30, ValueLv31 FROM dbo.TB_DefItemOpt2 WITH (HOLDLOCK TABLOCKX)')
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefItemOpt2 OFF
	
	DROP TABLE dbo.TB_DefItemOpt2
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefItemOpt2', N'TB_DefItemOpt2', 'OBJECT' 
	
	ALTER TABLE dbo.TB_DefItemOpt2 ADD CONSTRAINT
		PK_TB_DefItemOpt2 PRIMARY KEY CLUSTERED 
		(
		OptionGroup,
		OptionType,
		AbleEquipPos,
		f_NationCodeStr
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]

	SET XACT_ABORT OFF
END