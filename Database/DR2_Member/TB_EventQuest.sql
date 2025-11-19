USE [DR2_Member]
GO
/****** Object:  Table [dbo].[TB_EventQuest]    Script Date: 08/18/2009 17:08:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_EventQuest](
	[f_StartTime] [datetime] NOT NULL,
	[f_EndTime] [bigint] NOT NULL,
	[f_Title] [nvarchar](50) NOT NULL,
	[f_Prolog] [nvarchar](500) NOT NULL,
	[f_Contents] [nvarchar](500) NOT NULL,
	[f_NpcTalk_Prolog] [nvarchar](500) NOT NULL,
	[f_NpcTalk_NotEnd] [nvarchar](500) NOT NULL,
	[f_NpcTalk_End] [nvarchar](500) NOT NULL,
	[f_RewardMailTitle] [nvarchar](50) NOT NULL,
	[f_RewardMailContents] [nvarchar](200) NOT NULL,
	[f_RewardGold] [bigint] NOT NULL
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[TB_EventQuest_CompleteStatus]    Script Date: 08/18/2009 17:08:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_EventQuest_CompleteStatus](
	[f_RealmNo] [int] NOT NULL,
	[f_CharacterGuid] [uniqueidentifier] NOT NULL,
	[f_CharacterName] [nvarchar](20) NOT NULL,
	[f_ClearTime] [datetime] NOT NULL
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[TB_EventQuest_Notice]    Script Date: 08/27/2009 13:28:40 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_EventQuest_Notice](
	[IDX] [int] IDENTITY(1,1) NOT NULL,
	[f_NoticeTime] [int] NOT NULL,
	[f_NoticeMessage] [nvarchar](100) NOT NULL,
 CONSTRAINT [PK_TB_EventQuest_Notice] PRIMARY KEY CLUSTERED 
(
	[IDX] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [IX_TB_EventQuest_Notice] UNIQUE NONCLUSTERED 
(
	[IDX] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]


GO
/****** Object:  Table [dbo].[TB_EventQuest_Reward]    Script Date: 08/18/2009 17:08:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_EventQuest_Reward](
	[f_ItemNo] [int] NOT NULL,
	[f_ItemCount] [int] NOT NULL,
--	[f_ItemTimeType] [int] NOT NULL,
--	[f_ItemTimeValue] [int] NOT NULL
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[TB_EventQuest_Status]    Script Date: 08/29/2009 03:17:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_EventQuest_Status](
	[f_RealmNo] [int] NOT NULL,
	[f_Enable] [int] NOT NULL,
	[f_Status] [int] NOT NULL,
 CONSTRAINT [IX_TB_EventQuest_Status] UNIQUE NONCLUSTERED 
(
	[f_RealmNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]


GO
/****** Object:  Table [dbo].[TB_EventQuest_Target]    Script Date: 08/18/2009 17:08:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_EventQuest_Target](
	[f_TargetItemNo] [int] NOT NULL,
	[f_TargetItemCount] [int] NOT NULL,
 CONSTRAINT [IX_TB_EventQuest_Target] UNIQUE NONCLUSTERED 
(
	[f_TargetItemNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
