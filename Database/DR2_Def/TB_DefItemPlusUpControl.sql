USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefItemPlusUpControl]') AND type in (N'U'))
BEGIN

	CREATE TABLE [dbo].[TB_DefItemPlusUpControl](
		[IDX] [int] NOT NULL,
		[TypeNo] [int] NOT NULL,
		[SuccessRateControlNo_Low] [int] NOT NULL,
		[SuccessRateControlNo_High] [int] NOT NULL,
	CONSTRAINT [PK_TB_DefItemPlusUpControl] PRIMARY KEY CLUSTERED 
	(
		[TypeNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]	
END
GO

