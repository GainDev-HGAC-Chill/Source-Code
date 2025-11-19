USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[TB_DefItemEnchant_Pet](
	[TypeNo] [int] NOT NULL,
	[Level] [tinyint] NOT NULL,
	[NameNo] [int] NOT NULL,
	[Memo] [nvarchar](100) NULL,
	[Abil01] [int] NOT NULL CONSTRAINT [DF_TB_DefItemEnchant_Pet_Abil01]  DEFAULT ((0)),
	[Abil02] [int] NOT NULL CONSTRAINT [DF_TB_DefItemEnchant_Pet_Abil02]  DEFAULT ((0)),
	[Abil03] [int] NOT NULL CONSTRAINT [DF_TB_DefItemEnchant_Pet_Abil03]  DEFAULT ((0)),
	[Abil04] [int] NOT NULL CONSTRAINT [DF_TB_DefItemEnchant_Pet_Abil04]  DEFAULT ((0)),
	[Abil05] [int] NOT NULL CONSTRAINT [DF_TB_DefItemEnchant_Pet_Abil05]  DEFAULT ((0)),
	[Abil06] [int] NOT NULL CONSTRAINT [DF_TB_DefItemEnchant_Pet_Abil06]  DEFAULT ((0)),
	[Abil07] [int] NOT NULL CONSTRAINT [DF_TB_DefItemEnchant_Pet_Abil07]  DEFAULT ((0)),
	[Abil08] [int] NOT NULL CONSTRAINT [DF_TB_DefItemEnchant_Pet_Abil08]  DEFAULT ((0)),
	[Abil09] [int] NOT NULL CONSTRAINT [DF_TB_DefItemEnchant_Pet_Abil09]  DEFAULT ((0)),
	[Abil10] [int] NOT NULL CONSTRAINT [DF_TB_DefItemEnchant_Pet_Abil10]  DEFAULT ((0))
 CONSTRAINT [PK_TB_DefItemEnchant_Pet] PRIMARY KEY CLUSTERED 
(
	[TypeNo] ASC,
	[Level] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Item enchant(pet) definition' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefItemEnchant_Pet'
GO
