USE [DR2_User]
GO

/****** Object:  Table [dbo].[TB_UserCharacter_Card]    Script Date: 03/13/2009 22:18:26 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserCharacter_Card]'))
BEGIN

CREATE TABLE [dbo].[TB_UserCharacter_Card](
	[CharacterGuid] [uniqueidentifier] NOT NULL,
	[Year] [tinyint] NOT NULL,
	[Sex] [tinyint] NOT NULL,
	[Local] [int] NOT NULL,
	[PopularPoint] [bigint] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Card_PopularPoint]  DEFAULT ((0)),
	[Enable] [tinyint] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Card_Enable]  DEFAULT ((1)),
	[Comment] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[Constellation] [tinyint] NOT NULL,
	[Sports] [tinyint] NOT NULL,
	[Hobby] [tinyint] NOT NULL,
	[Style] [tinyint] NOT NULL,
	[Abil1] [smallint] NULL,
	[Value] [int] NULL,
	[Abil2] [smallint] NULL,
	[Value2] [int] NULL,
	[Abil3] [smallint] NULL,
	[Value3] [int] NULL,
	[Abil4] [smallint] NULL,
	[Value4] [int] NULL,
 CONSTRAINT [PK_TB_UserCharacter_Card] PRIMARY KEY CLUSTERED 
(
	[CharacterGuid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]

END

GO

ALTER TABLE [dbo].[TB_UserCharacter_Card] DROP COLUMN [Sports]
GO

ALTER TABLE [dbo].[TB_UserCharacter_Card] ADD [Blood] [tinyint] NOT NULL
GO

ALTER TABLE [dbo].[TB_UserCharacter_Card] ADD
[BGndNo] [int] NULL
GO

ALTER TABLE [dbo].[TB_UserCharacter_Card] DROP
COLUMN [Abil1],
COLUMN [Value],
COLUMN [Abil2],
COLUMN [Value2],
COLUMN [Abil3],
COLUMN [Value3],
COLUMN [Abil4],
COLUMN [Value4]
GO

ALTER TABLE [dbo].[TB_UserCharacter_Card] ADD
[TodayPopularPoint] [bigint] NOT NULL CONSTRAINT [DF_TB_UserCharacter_Card_TodayPopularPoint]  DEFAULT ((0))
GO
