USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_DefRealtyDealer]    Script Date: 07/01/2009 19:06:38 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefRealtyDealer](
	[NpcGuid] [uniqueidentifier] NOT NULL,
	[GroundNo] [int] NOT NULL,
	[Cost] [int] NOT NULL
) ON [PRIMARY]
