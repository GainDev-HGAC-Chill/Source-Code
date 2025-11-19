USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[dbo].[TB_DefItemPlusUpgrade_Pet]'))
BEGIN
CREATE TABLE [dbo].[TB_DefItemPlusUpgrade_Pet](
	[index] [int] IDENTITY(1,1) NOT FOR REPLICATION NOT NULL,
	[EquipPos] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_Pet_EquipPos]  DEFAULT ((0)),
	[PlusLevel] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_Pet_PlusLevel]  DEFAULT ((0)),
	[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
	[SuccessRate] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_Pet_SuccessRate]  DEFAULT ((0)),
	[SuccessRateBonus] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_Pet_SuccessRateBonus]  DEFAULT ((0)),
	[NeedMoney] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_Pet_NeedMoney]  DEFAULT ((0)),
	[RareGroupNo] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_Pet_RareGroupNo]  DEFAULT ((0)),
	[RareGroupSuccessRate] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_Pet_RareGroupSuccessRate]  DEFAULT ((0)),
	[NeedItemNo01] [int] NOT NULL CONSTRAINT [DF_TB_DefItemPlusUpgrade_Pet_NeedItemNo01]  DEFAULT ((0)),
	[NeedItemCount01] [smallint] NOT NULL,
	[NeedItemNo02] [int] NOT NULL,
	[NeedItemCount02] [smallint] NOT NULL,
	[NeedItemNo03] [int] NOT NULL,
	[NeedItemCount03] [smallint] NOT NULL,
 CONSTRAINT [PK_TB_DefItemPlusUpgrade_Pet] PRIMARY KEY CLUSTERED 
(
	[EquipPos] ASC,
	[PlusLevel] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Item PlusUpgrade(pet) definition' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefItemPlusUpgrade_Pet'
END
GO


IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade_Pet') AND [name] = N'EnchantShiftCost')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade_Pet] ADD [EnchantShiftCost] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade_Pet') AND [name] = N'EnchantShiftGem')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade_Pet] ADD [EnchantShiftGem] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade_Pet') AND [name] = N'EnchantShiftItem')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade_Pet] ADD [EnchantShiftItem] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade_Pet') AND [name] = N'EnchantShiftRatePlus2')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade_Pet] ADD [EnchantShiftRatePlus2] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade_Pet') AND [name] = N'EnchantShiftRatePlus1')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade_Pet] ADD [EnchantShiftRatePlus1] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade_Pet') AND [name] = N'EnchantShiftRateSame')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade_Pet] ADD [EnchantShiftRateSame] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade_Pet') AND [name] = N'EnchantShiftRateMinus1')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade_Pet] ADD [EnchantShiftRateMinus1] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade_Pet') AND [name] = N'EnchantShiftRateMinus2')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade_Pet] ADD [EnchantShiftRateMinus2] [int] NULL
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade_Pet') AND [name] = N'EnchantShiftRateDelete')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade_Pet] ADD [EnchantShiftRateDelete] [int] NULL
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_DefItemPlusUpgrade_Pet') AND [name] = N'EnchantShiftInsurance')
BEGIN
	ALTER TABLE [dbo].[TB_DefItemPlusUpgrade_Pet] ADD [EnchantShiftInsurance] [int] NULL
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