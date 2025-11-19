USE [DR2_local]
GO

/****** Object:  Table [dbo].[TB_PCCafeAbil]    Script Date: 11/10/2010 20:47:41 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS( SELECT * FROM sys.all_objects WHERE object_id = object_id( N'dbo.TB_PCCafeAbil' ) )
BEGIN
	CREATE TABLE [dbo].[TB_PCCafeAbil](
		[f_Grade] [tinyint] NOT NULL,
		[f_AbilNo] [int] NOT NULL,
	 CONSTRAINT [PK_TB_PCCafeAbil_f_Grade] PRIMARY KEY CLUSTERED 
	(
		[f_Grade] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
GO

IF EXISTS ( SELECT 1 FROM sys.columns WHERE object_Id = OBJECT_ID( N'dbo.TB_PCCafeAbil') AND name = N'f_AbilNo' )
BEGIN
	ALTER TABLE dbo.TB_PCCafeAbil DROP COLUMN f_AbilNo
END

IF NOT EXISTS ( SELECT 1 FROM sys.columns WHERE object_Id = OBJECT_ID( N'dbo.TB_PCCafeAbil') AND name = N'f_AbilNo01' )
BEGIN 
	ALTER TABLE dbo.TB_PCCafeAbil ADD [f_AbilNo01][int] NOT NULL CONSTRAINT [DF_TB_PCCafeAbil_f_AbilNo01] DEFAULT(0)
END

IF NOT EXISTS ( SELECT 1 FROM sys.columns WHERE object_Id = OBJECT_ID( N'dbo.TB_PCCafeAbil') AND name = N'f_AbilNo02' )
BEGIN 
	ALTER TABLE dbo.TB_PCCafeAbil ADD [f_AbilNo02][int] NOT NULL CONSTRAINT [DF_TB_PCCafeAbil_f_AbilNo02] DEFAULT(0)
END

IF NOT EXISTS ( SELECT 1 FROM sys.columns WHERE object_Id = OBJECT_ID( N'dbo.TB_PCCafeAbil') AND name = N'f_AbilNo03' )
BEGIN 
	ALTER TABLE dbo.TB_PCCafeAbil ADD [f_AbilNo03][int] NOT NULL CONSTRAINT [DF_TB_PCCafeAbil_f_AbilNo03] DEFAULT(0)
END

IF NOT EXISTS ( SELECT 1 FROM sys.columns WHERE object_Id = OBJECT_ID( N'dbo.TB_PCCafeAbil') AND name = N'f_AbilNo04' )
BEGIN 
	ALTER TABLE dbo.TB_PCCafeAbil ADD [f_AbilNo04][int] NOT NULL CONSTRAINT [DF_TB_PCCafeAbil_f_AbilNo04] DEFAULT(0)
END