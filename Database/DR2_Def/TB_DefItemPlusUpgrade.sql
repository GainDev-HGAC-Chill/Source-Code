USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefItemPlusUpgrade]    Script Date: 10/08/2009 16:54:16 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[dbo].[TB_DefItemPlusUpgrade]'))
BEGIN
CREATE TABLE [dbo].[TB_DefItemPlusUpgrade](
	[index] [int] IDENTITY(1,1) NOT FOR REPLICATION NOT NULL,
	[EquipPos] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_EquipPos]  DEFAULT ((0)),
	[PlusLevel] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_PlusLevel]  DEFAULT ((0)),
	[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
	[SuccessRate] [smallint] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_SuccessRate]  DEFAULT ((0)),
	[SuccessRateBonus] [smallint] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_SuccessRateBonus]  DEFAULT ((0)),
	[NeedMoney] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_NeedMoney]  DEFAULT ((0)),
	[RareGroupNo] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_RareGroupNo]  DEFAULT ((0)),
	[RareGroupSuccessRate] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_RareGroupSuccessRate]  DEFAULT ((0)),
	[NeedItemNo01] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_NeedItemNo01]  DEFAULT ((0)),
	[NeedItemCount01] [smallint] NOT NULL,
	[NeedItemNo02] [int] NOT NULL,
	[NeedItemCount02] [smallint] NOT NULL,
	[NeedItemNo03] [int] NOT NULL,
	[NeedItemCount03] [smallint] NOT NULL,
 CONSTRAINT [PK_TB_DefItemPlusUpgrade] PRIMARY KEY CLUSTERED 
(
	[EquipPos] ASC,
	[PlusLevel] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO

ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] DROP CONSTRAINT [DF_TB_DefItemPlusUpgrade_SuccessRate]
GO

ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] DROP CONSTRAINT [DF_TB_DefItemPlusUpgrade_SuccessRateBonus]
GO

ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] ALTER COLUMN [SuccessRate] [int] NOT NULL
ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] ALTER COLUMN [SuccessRateBonus] [int] NOT NULL
GO

ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] ADD CONSTRAINT [DF_TB_DefItemPlusUpgrade_SuccessRate] DEFAULT ((0)) FOR [SuccessRate]
GO

ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] ADD CONSTRAINT [DF_TB_DefItemPlusUpgrade_SuccessRateBonus] DEFAULT ((0)) FOR [SuccessRateBonus]
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftCost')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] ADD [EnchantShiftCost] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftGem')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] ADD [EnchantShiftGem] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftItem')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] ADD [EnchantShiftItem] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftRatePlus2')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] ADD [EnchantShiftRatePlus2] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftRatePlus1')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] ADD [EnchantShiftRatePlus1] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftRateSame')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] ADD [EnchantShiftRateSame] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftRateMinus1')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] ADD [EnchantShiftRateMinus1] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftRateMinus2')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] ADD [EnchantShiftRateMinus2] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftRateDelete')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] ADD [EnchantShiftRateDelete] [int] NULL
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftInsurance')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] ADD [EnchantShiftInsurance] [int] NULL
END
GO

-- 인챈트전이 관련 필드 제거
IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftCost')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] DROP column [EnchantShiftCost]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftGem')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] DROP column [EnchantShiftGem]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftItem')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] DROP column [EnchantShiftItem]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftRatePlus2')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] DROP column [EnchantShiftRatePlus2]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftRatePlus1')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] DROP column [EnchantShiftRatePlus1]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftRateSame')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] DROP column [EnchantShiftRateSame]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftRateMinus1')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] DROP column [EnchantShiftRateMinus1]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftRateMinus2')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] DROP column [EnchantShiftRateMinus2]
END

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftRateDelete')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] DROP column [EnchantShiftRateDelete]
END
GO

IF EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade') AND [name] = N'EnchantShiftInsurance')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade] DROP column [EnchantShiftInsurance]
END
GO

IF NOT EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.[TB_DefItemPlusUpgrade]') and name = N'NationCodeStr')
BEGIN

	ALTER TABLE dbo.TB_DefItemPlusUpgrade
			DROP CONSTRAINT DF_TB_DefItemPlusUpgrade_EquipPos
			
	ALTER TABLE dbo.TB_DefItemPlusUpgrade
			DROP CONSTRAINT DF_TB_DefItemPlusUpgrade_PlusLevel
			
	ALTER TABLE dbo.TB_DefItemPlusUpgrade
			DROP CONSTRAINT DF_TB_DefItemPlusUpgrade_SuccessRate
			
	ALTER TABLE dbo.TB_DefItemPlusUpgrade
			DROP CONSTRAINT DF_TB_DefItemPlusUpgrade_SuccessRateBonus
			
	ALTER TABLE dbo.TB_DefItemPlusUpgrade
			DROP CONSTRAINT DF_TB_DefItemPlusUpgrade_NeedMoney
			
	ALTER TABLE dbo.TB_DefItemPlusUpgrade
			DROP CONSTRAINT DF_TB_DefItemPlusUpgrade_RareGroupNo
			
	ALTER TABLE dbo.TB_DefItemPlusUpgrade
			DROP CONSTRAINT DF_TB_DefItemPlusUpgrade_RareGroupSuccessRate
			
	ALTER TABLE dbo.TB_DefItemPlusUpgrade
			DROP CONSTRAINT DF_TB_DefItemPlusUpgrade_NeedItemNo01

	CREATE TABLE [dbo].[Tmp_TB_DefItemPlusUpgrade](
	[NationCodeStr] [nvarchar](50) NOT NULL,
	[index] [int] IDENTITY(1,1) NOT FOR REPLICATION NOT NULL,
	[EquipPos] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_EquipPos]  DEFAULT ((0)),
	[PlusLevel] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_PlusLevel]  DEFAULT ((0)),
	[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
	[SuccessRate] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_SuccessRate]  DEFAULT ((0)),
	[SuccessRateBonus] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_SuccessRateBonus]  DEFAULT ((0)),
	[NeedMoney] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_NeedMoney]  DEFAULT ((0)),
	[RareGroupNo] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_RareGroupNo]  DEFAULT ((0)),
	[RareGroupSuccessRate] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_RareGroupSuccessRate]  DEFAULT ((0)),
	[NeedItemNo01] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_NeedItemNo01]  DEFAULT ((0)),
	[NeedItemCount01] [smallint] NOT NULL,
	[NeedItemNo02] [int] NOT NULL,
	[NeedItemCount02] [smallint] NOT NULL,
	[NeedItemNo03] [int] NOT NULL,
	[NeedItemCount03] [smallint] NOT NULL,
	 CONSTRAINT [PK_TB_DefItemPlusUpgrade2] PRIMARY KEY CLUSTERED 
	(
		[NationCodeStr] ASC,
		[EquipPos] ASC,
		[PlusLevel] ASC
	)WITH (STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
	) ON [PRIMARY]
	
	SET IDENTITY_INSERT dbo.Tmp_TB_DefItemPlusUpgrade ON
	
	IF EXISTS (SELECT * FROM dbo.TB_DefItemPlusUpgrade)
	EXEC ('INSERT INTO dbo.Tmp_TB_DefItemPlusUpgrade ([NationCodeStr], [index], [EquipPos], [PlusLevel], [Memo], [SuccessRate], [SuccessRateBonus], [NeedMoney],
													  [RareGroupNo], [RareGroupSuccessRate], [NeedItemNo01], [NeedItemCount01], [NeedItemNo02], [NeedItemCount02], [NeedItemNo03], [NeedItemCount03])
		   SELECT 0, [index], [EquipPos], [PlusLevel], [Memo], [SuccessRate], [SuccessRateBonus], [NeedMoney],
													  [RareGroupNo], [RareGroupSuccessRate], [NeedItemNo01], [NeedItemCount01], [NeedItemNo02], [NeedItemCount02], [NeedItemNo03], [NeedItemCount03]
		   FROM dbo.TB_DefItemPlusUpgrade WITH (HOLDLOCK TABLOCKX)')
		   
	SET IDENTITY_INSERT dbo.Tmp_TB_DefItemPlusUpgrade OFF
	
	ALTER TABLE dbo.TB_DefItemPlusUpgrade
		DROP CONSTRAINT PK_TB_DefItemPlusUpgrade
	
	DROP TABLE TB_DefItemPlusUpgrade
	
	EXECUTE sp_rename N'dbo.Tmp_TB_DefItemPlusUpgrade', 'TB_DefItemPlusUpgrade', 'OBJECT'
	
	CREATE NONCLUSTERED INDEX IX_NC_TB_DefItemPlusUpgrade2 ON dbo.TB_DefItemPlusUpgrade
		(
		NationCodeStr,
		EquipPos,
		PlusLevel
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END
GO