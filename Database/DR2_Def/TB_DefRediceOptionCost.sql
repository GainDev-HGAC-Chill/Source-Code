USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefRediceOptionCost]    Script Date: 01/28/2010 15:22:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefRediceOptionCost](
	[ItemGrade] [tinyint] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[NeedItemCount] [smallint] NULL,
 CONSTRAINT [PK_TB_DefRediceOptionCost] PRIMARY KEY CLUSTERED 
(
	[ItemGrade] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
