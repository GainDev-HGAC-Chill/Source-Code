USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_DefGambleMachineMixupPoint]    Script Date: 02/16/2010 14:46:14 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefGambleMachineMixupPoint](
	[Grade] [int] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[MixPoint] [int] NULL,
 CONSTRAINT [PK_TB_DefGambleMachineMixupPoint] PRIMARY KEY CLUSTERED 
(
	[Grade] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
