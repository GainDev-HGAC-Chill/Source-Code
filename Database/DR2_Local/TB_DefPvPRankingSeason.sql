USE [DR2_Local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[TB_DefPvPRankingSeason](
	[IDX] [int] NOT NULL IDENTITY(1,1),
	[Schedule] [datetime] NOT NULL,
	[memo] [nvarchar] (50) NULL,
	[Season_InitPoint] [int] NOT NULL,
	[Cycle_Pass] [tinyint] NOT NULL,
	[Cycle_Day] [int] NOT NULL,
	[Cycle_PointRate] [real] NOT NULL,
	[Cycle_GivePoint] [int] NOT NULL,
CONSTRAINT [IX_NC_TB_DefPvPRankingSeason] UNIQUE NONCLUSTERED 
(
	[Schedule] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[TB_DefPvPRankingSeason] ALTER COLUMN [Cycle_PointRate] [float] NOT NULL
GO
