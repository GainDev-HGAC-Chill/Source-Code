USE [DR2_Local]
GO

/****** Object:  Table [dbo].[TB_JumpingCharEvent]    Script Date: 01/10/2012 11:16:49 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_JumpingCharEvent]') AND type in (N'U'))
BEGIN

	CREATE TABLE [dbo].[TB_JumpingCharEvent](
		[EventNo] [int] NOT NULL,
		[Memo] [nvarchar](50) NULL,
		[StartTime] [datetime] NOT NULL,
		[EndTime] [datetime] NOT NULL,
		[LevelLimit] [int] NOT NULL DEFAULT ((0)),
		[MaxRewardCount] [int] NOT NULL DEFAULT ((0)),
		[RewardGroupNo] [int] NOT NULL,
	 CONSTRAINT [PK_TB_JumpCharEvent] PRIMARY KEY CLUSTERED 
	(
		[EventNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]

END
GO

