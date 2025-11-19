USE [DR2_local]
GO
/****** Object:  Table [dbo].[TB_LimitedItemControl]    Script Date: 05/21/2009 14:50:03 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_LimitedItemControl](
	[IDX] [int] IDENTITY(1,1) NOT NULL,
	[ObjectType] [int] NOT NULL,
	[ObjectNo] [int] NOT NULL,
	[EventNo] [int] NOT NULL,
	[Rate] [int] NOT NULL
) ON [PRIMARY]
