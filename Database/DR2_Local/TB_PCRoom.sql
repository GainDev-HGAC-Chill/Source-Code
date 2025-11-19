USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_PCRoom]    Script Date: 05/18/2009 18:44:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_PCRoom](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[Guid] [uniqueidentifier] NOT NULL,
	[Name] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NOT NULL,
 CONSTRAINT [PK_TB_PCRoom] PRIMARY KEY CLUSTERED 
(
	[Idx] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
