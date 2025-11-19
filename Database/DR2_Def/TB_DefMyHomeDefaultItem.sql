USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefMyHomeDefaultItem]    Script Date: 08/18/2009 02:13:40 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefMyHomeDefaultItem](
	[TownNo] [smallint] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[ItemNo] [int] NULL,
 CONSTRAINT [PK_TB_DefMyHomeDefaultItem] PRIMARY KEY CLUSTERED 
(
	[TownNo] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
