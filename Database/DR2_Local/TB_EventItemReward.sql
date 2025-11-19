USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_EventItemReward]    Script Date: 11/04/2009 16:31:06 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_EventItemReward](
	[EventItemNo] [int] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[ResultItemNo] [int] NULL,
	[ResultItemCount] [smallint] NULL,
	[TimeType] [tinyint] NULL,
	[UseTime] [smallint] NULL,
	[Rarity] [tinyint] NULL,
	[EnchantType] [tinyint] NULL,
	[EnchantLevel] [tinyint] NULL,
	[Rate] [int] NULL
) ON [PRIMARY]

CREATE NONCLUSTERED INDEX [IX_Table_EventItemNo] ON [dbo].[TB_EventItemReward] ([EventItemNo])
GO

ALTER TABLE [dbo].[TB_EventItemReward] ADD
[Idx] [int] NOT NULL IDENTITY(1, 1)
GO

ALTER TABLE [dbo].[TB_EventItemReward] ADD CONSTRAINT [PK_TB_EventItemReward] PRIMARY KEY CLUSTERED ([Idx])
GO

ALTER TABLE [dbo].[TB_EventItemReward] ADD
[Broadcast] [tinyint] NULL
GO
