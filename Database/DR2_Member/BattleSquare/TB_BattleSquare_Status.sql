USE [DR2_Member]
GO
/****** Object:  Table [dbo].[TB_BattleSquare_Status]    Script Date: 09/15/2009 21:42:09 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_BattleSquare_Status](
	[f_GameIDX] [int] NOT NULL,
	[f_RealmNo] [int] NOT NULL,
	[f_ChannelNo] [int] NOT NULL,
	[f_Status] [int] NOT NULL,
	[f_LastUpdateDate] [datetime] NOT NULL,
 CONSTRAINT [PK_TB_BattleSquare_Status] PRIMARY KEY CLUSTERED 
(
	[f_GameIDX] ASC,
	[f_RealmNo] ASC,
	[f_ChannelNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
