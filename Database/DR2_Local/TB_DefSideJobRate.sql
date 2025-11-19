USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_DefSideJobRate]    Script Date: 12/10/2009 16:53:39 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefSideJobRate](
	[SideJob] [int] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[CostRate] [int] NULL,
	[SoulRate] [int] NULL,
	[SuccessRate] [int] NULL,
	[PayRate] [int] NULL,
 CONSTRAINT [PK_TB_DefSideJobRate] PRIMARY KEY CLUSTERED 
(
	[SideJob] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
