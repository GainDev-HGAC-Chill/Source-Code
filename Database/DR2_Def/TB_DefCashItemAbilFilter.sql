USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefCashItemAbilFilter]    Script Date: 05/08/2009 15:24:28 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefCashItemAbilFilter](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[AbilType] [smallint] NOT NULL,
 CONSTRAINT [PK_TB_DefCashItemAbilFilter] PRIMARY KEY CLUSTERED 
(
	[Idx] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
