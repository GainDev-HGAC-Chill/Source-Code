USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefItemEnchantAbilWeight]    Script Date: 10/07/2009 10:39:27 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefItemEnchantAbilWeight](
	[EnchantLv] [tinyint] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[Weight] [int] NULL,
 CONSTRAINT [PK_TB_DefItemEnchantAbilWeight] PRIMARY KEY CLUSTERED 
(
	[EnchantLv] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
