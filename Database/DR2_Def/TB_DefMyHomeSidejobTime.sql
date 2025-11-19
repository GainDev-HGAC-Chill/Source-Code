USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefMyHomeSidejobTime]    Script Date: 01/29/2010 16:19:37 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefMyHomeSidejobTime](
	[HomeLevel] [int] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[SidejobTime] [int] NULL,
 CONSTRAINT [PK_TB_DefMyHomeSidejobTime] PRIMARY KEY CLUSTERED 
(
	[HomeLevel] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
