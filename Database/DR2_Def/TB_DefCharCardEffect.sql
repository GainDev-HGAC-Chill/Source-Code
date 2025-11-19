USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefCharCardEffect]    Script Date: 11/27/2009 18:43:14 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefCharCardEffect](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[PopularPoint] [int] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[EffectNo] [int] NOT NULL
) ON [PRIMARY]
