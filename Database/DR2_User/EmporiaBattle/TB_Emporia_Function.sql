USE [DR2_User]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Guild_EmporiaFunction]') AND type in (N'U'))
DROP TABLE [dbo].[TB_Guild_EmporiaFunction]
GO

CREATE TABLE [dbo].[TB_Emporia_Function](
	[EmporiaID] [uniqueidentifier] NOT NULL,
	[Grade] [tinyint] NOT NULL,
	[FunctionNo] [smallint] NOT NULL,
	[HaveDate] [datetime] NULL,
	[ExpirationDate] [datetime] NULL,
	[ExtValue] [bigint] NULL
CONSTRAINT [IX_NC_TB_Emporia_Function] UNIQUE NONCLUSTERED 
(
	[EmporiaID] ASC,
	[Grade] ASC,
	[FunctionNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]



