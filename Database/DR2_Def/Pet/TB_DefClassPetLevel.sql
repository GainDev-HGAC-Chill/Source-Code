USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[TB_DefClassPetLevel](
	[ID] [int] NOT NULL,
	[Level] [smallint] NOT NULL,
	[Memo] [nvarchar](100) NULL,
	[Experience] [bigint] NOT NULL,
	[AddExperienceForTime] [int] NOT NULL,
	[MaxMP] [smallint] NOT NULL,
	[MP_Recovery_Speed] [smallint] NOT NULL,
	[MP_Recovery] [smallint] NOT NULL,
	[Abil01] [int] NOT NULL,
	[Abil02] [int] NOT NULL,
	[Abil03] [int] NOT NULL,
	[Abil04] [int] NOT NULL,
	[Abil05] [int] NOT NULL,
	[Abil06] [int] NOT NULL,
	[Abil07] [int] NOT NULL,
	[Abil08] [int] NOT NULL,
	[Abil09] [int] NOT NULL,
	[Abil10] [int] NOT NULL,
 CONSTRAINT [PK_TB_DefClassPetLevel] PRIMARY KEY CLUSTERED 
(
	[ID] ASC,
	[Level] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
