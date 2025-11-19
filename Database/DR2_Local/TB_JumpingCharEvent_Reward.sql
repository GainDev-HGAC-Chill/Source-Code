USE [DR2_Local]
GO

/****** Object:  Table [dbo].[TB_JumpingCharEvent_Reward]    Script Date: 01/10/2012 11:16:56 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_JumpingCharEvent_Reward]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_JumpingCharEvent_Reward](
		[RewardGroupNo] [int] NOT NULL,
		[Class] [int] NOT NULL,
		[Level] [int] NOT NULL,
		[MapNo] [int] NOT NULL,
		[IngQuest] [binary](350) NOT NULL DEFAULT (CONVERT([binary](350),(0),(0))),
		[EndQuest] [binary](130) NOT NULL DEFAULT (CONVERT([binary](130),(0),(0))),
		[EndQuest2] [binary](130) NOT NULL DEFAULT (CONVERT([binary](130),(0),(0))),
		[ItemGroupNo] [int] NOT NULL,
	 CONSTRAINT [PK_TB_JumpCharEvent_Reward] PRIMARY KEY CLUSTERED 
	(
		[RewardGroupNo] ASC,
		[Class] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]

END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_JumpingCharEvent_Reward]') AND [Name] = 'EndQuestExt')
BEGIN
	ALTER TABLE [dbo].[TB_JumpingCharEvent_Reward] ADD [EndQuestExt] [binary](260) NOT NULL DEFAULT (CONVERT([Binary](260),(0),(0)))
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_JumpingCharEvent_Reward]') AND [Name] = 'EndQuestExt2')
BEGIN
	ALTER TABLE [dbo].[TB_JumpingCharEvent_Reward] ADD [EndQuestExt2] [binary](480) NOT NULL DEFAULT (CONVERT([Binary](480),(0),(0)))
END

SET ANSI_PADDING OFF
GO
