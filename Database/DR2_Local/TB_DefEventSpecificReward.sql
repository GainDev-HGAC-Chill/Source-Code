USE [DR2_Local]
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEventSpecificReward]') AND type in (N'U'))
BEGIN
	DROP TABLE [dbo].[TB_DefEventSpecificReward]
END

USE [DR2_Local]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEventSpecificReward]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefEventSpecificReward](
		[EventNo] [int] NOT NULL DEFAULT (0),
		[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
		[EventStartTime] [datetime] NOT NULL DEFAULT (0),
		[EventEndTime] [datetime] NOT NULL DEFAULT (0),
		[LevelLimit] [smallint] NOT NULL DEFAULT (0),
		[DraLevelLimit] [smallint] NOT NULL DEFAULT (0),
		[RewardCount] [smallint] NOT NULL DEFAULT (0),
		[RewardPeriod] [smallint] NOT NULL DEFAULT (0),
		[RewardItemGroupNo] [int] NOT NULL DEFAULT (0),
	CONSTRAINT [PK_TB_DefSpecificRewardEvent2] PRIMARY KEY CLUSTERED
	(
		[EventNo] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	)ON [PRIMARY]
END
GO