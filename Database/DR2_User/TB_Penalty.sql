USE [DR2_User]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Penalty]') AND type in (N'U'))
DROP TABLE [dbo].[TB_Penalty]
GO

CREATE TABLE [dbo].[TB_Penalty](
	[CharacterID] [uniqueidentifier] NOT NULL,
	[Type] [int] NOT NULL,
	[Value] [int] NOT NULL,
	[BeginDate] [datetime] NOT NULL,
	[EndDate] [datetime] NOT NULL
 CONSTRAINT [PK_TB_Penalty] PRIMARY KEY NONCLUSTERED 
(
	[CharacterID] ASC,
	[Type] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO



