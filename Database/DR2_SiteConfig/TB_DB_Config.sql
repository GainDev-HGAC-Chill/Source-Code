USE [DR2_SiteConfig]
GO

/****** Object:  Table [dbo].[TB_DB_Config]    Script Date: 04/02/2009 14:45:52 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[dbo].[TB_DB_Config]')) 
DROP TABLE [dbo].[TB_DB_Config]
GO