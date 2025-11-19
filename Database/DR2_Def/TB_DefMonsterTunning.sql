USE [DR2_Def]
GO
/****** 개체:  Table [dbo].[TB_DefMonsterTunning]    스크립트 날짜: 01/15/2010 12:08:46 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefMonsterTunning]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[TB_DefMonsterTunning](
	[KeyNo] [int] NOT NULL,
	[Grade] [int] NOT NULL,
	[Level] [int] NOT NULL,
	[Memo]  [nvarchar](100) NULL,
	[Abil01] [int] NOT NULL CONSTRAINT [DF_DefMonsterTunning_Abil01] DEFAULT ((0)),
	[Abil02] [int] NOT NULL CONSTRAINT [DF_DefMonsterTunning_Abil02] DEFAULT ((0)),
	[Abil03] [int] NOT NULL CONSTRAINT [DF_DefMonsterTunning_Abil03] DEFAULT ((0)),
	[Abil04] [int] NOT NULL CONSTRAINT [DF_DefMonsterTunning_Abil04] DEFAULT ((0)),
	[Abil05] [int] NOT NULL CONSTRAINT [DF_DefMonsterTunning_Abil05] DEFAULT ((0)),
	[Abil06] [int] NOT NULL CONSTRAINT [DF_DefMonsterTunning_Abil06] DEFAULT ((0)),
	[Abil07] [int] NOT NULL CONSTRAINT [DF_DefMonsterTunning_Abil07] DEFAULT ((0)),
	[Abil08] [int] NOT NULL CONSTRAINT [DF_DefMonsterTunning_Abil08] DEFAULT ((0)),
	[Abil09] [int] NOT NULL CONSTRAINT [DF_DefMonsterTunning_Abil09] DEFAULT ((0)),
	[Abil10] [int] NOT NULL CONSTRAINT [DF_DefMonsterTunning_Abil10] DEFAULT ((0)),
 CONSTRAINT [PK_TB_MonsterTunning] PRIMARY KEY CLUSTERED 
(
	[KeyNo] ASC,
	[Grade] ASC,
	[Level] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
END
GO