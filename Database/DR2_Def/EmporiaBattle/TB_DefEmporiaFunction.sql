USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[TB_DefEmporiaFunction](
	[EmporiaID] [UNIQUEIDENTIFIER] NOT NULL,
	[Grade] [tinyint] NOT NULL,
	[Memo] [nvarchar](50) NULL,
	[FunctionNo] [smallint] NOT NULL,
	[Price_ForWeek] [smallint] NOT NULL
CONSTRAINT [IX_TB_DefEmporiaFunction] UNIQUE CLUSTERED 
(
	[EmporiaID] ASC,
	[Grade] ASC,
	[FunctionNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefEmporiaFunction_iValue01]') AND type = 'D')
BEGIN
	ALTER TABLE [dbo].[TB_DefEmporiaFunction] ADD [iValue] [int] NOT NULL CONSTRAINT [DF_TB_DefEmporiaFunction_iValue01] DEFAULT ((0))
END
GO
