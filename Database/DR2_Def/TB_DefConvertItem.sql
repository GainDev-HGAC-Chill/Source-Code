USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefConvertItem]    Script Date: 05/19/2009 16:53:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefConvertItem](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[SourceItemNo] [int] NULL,
	[SourceItemNum] [smallint] NULL,
	[TargetItemNo] [int] NULL,
	[TargetItemNum] [smallint] NULL,
 CONSTRAINT [PK_TB_DefConvertItem] PRIMARY KEY CLUSTERED 
(
	[Idx] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
