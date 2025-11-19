USE [DR2_Def]
GO

/****** Object:  Table [dbo].[TB_DefCardAbilKey]    Script Date: 03/26/2009 15:48:39 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[TB_DefCardAbilKey](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[KeyType] [tinyint] NOT NULL,
	[KeyValue] [tinyint] NOT NULL,
	[StringNo] [int] NULL,
 CONSTRAINT [PK_TB_DefCardAbilKey] PRIMARY KEY CLUSTERED 
(
	[Idx] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO


ALTER TABLE [dbo].[TB_DefCardAbilKey] ADD [CardKey] [tinyint] NULL
GO