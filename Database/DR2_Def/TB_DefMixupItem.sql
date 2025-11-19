USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefMixupItem]    Script Date: 07/15/2009 04:20:10 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefMixupItem](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[ItemGrade] [int] NULL,
	[EquipPos] [int] NULL,
	[GenderLimit] [int] NULL,
	[SuccessControlNo] [int] NULL,
	[RarityControlNo] [int] NULL,
	[ItemBagNo01] [int] NULL,
	[ItemBagNo02] [int] NULL,
	[ItemBagNo03] [int] NULL,
	[ItemBagNo04] [int] NULL,
	[ItemBagNo05] [int] NULL,
	[ItemBagNo06] [int] NULL,
	[ItemBagNo07] [int] NULL,
	[ItemBagNo08] [int] NULL,
	[ItemBagNo09] [int] NULL,
	[ItemBagNo10] [int] NULL
) ON [PRIMARY]
