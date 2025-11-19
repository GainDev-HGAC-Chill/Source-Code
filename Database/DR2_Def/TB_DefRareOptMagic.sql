USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefRareOptMagic]    Script Date: 07/10/2009 14:58:25 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefRareOptMagic](
	[MagicOptNo] [int] NOT NULL,
	[SuccessControlNo] [int] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[MagicNo01] [int] NULL,
	[MagicNo02] [int] NULL,
	[MagicNo03] [int] NULL,
	[MagicNo04] [int] NULL,
	[MagicNo05] [int] NULL,
	[MagicNo06] [int] NULL,
	[MagicNo07] [int] NULL,
	[MagicNo08] [int] NULL,
	[MagicNo09] [int] NULL,
	[MagicNo10] [int] NULL
) ON [PRIMARY]
