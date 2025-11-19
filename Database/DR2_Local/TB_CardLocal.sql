USE [DR2_Local]
GO

/****** Object:  Table [dbo].[TB_CardLocal]    Script Date: 03/26/2009 15:47:44 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_CardLocal](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[Text] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[Local] [int] NOT NULL,
 CONSTRAINT [PK_TB_CardLocal] PRIMARY KEY CLUSTERED 
(
	[Idx] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
