USE [DR2_User]
GO

/****** Object:  Table [dbo].[TB_JumpingCharEvent_State]    Script Date: 01/10/2012 11:17:57 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_JumpingCharEvent_State]') AND type in (N'U'))
BEGIN

	CREATE TABLE [dbo].[TB_JumpingCharEvent_State](
		[EventNo] [int] NOT NULL,
		[MemberID] [uniqueidentifier] NOT NULL,
		[RewardCount] [int] NOT NULL,
	 CONSTRAINT [PK_TB_JumpCharEvent_State] PRIMARY KEY CLUSTERED 
	(
		[EventNo] ASC,
		[MemberID] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]

END
GO

