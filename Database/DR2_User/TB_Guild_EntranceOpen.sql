USE [DR2_User]
GO

/****** Object:  Table [dbo].[TB_Guild_EntranceOpen]    Script Date: 04/15/2010 18:59:12 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Guild_EntranceOpen]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_Guild_EntranceOpen](		
		[GuildGuid] [uniqueidentifier] NOT NULL,
		[EmporiaWinCount] [int] NOT NULL,
		[IsGuildEntrance] [tinyint] NOT NULL,
		[GuildEntranceLevel] [smallint] NOT NULL,
		[GuildEntranceClass] [bigint] NOT NULL,
		[GuildEntranceFee] [bigint] NOT NULL,
		[GuildPR] [nvarchar](40) NULL,
	 CONSTRAINT [PK_TB_Guild_EntranceOpen_GuildGuid] PRIMARY KEY CLUSTERED 
	(
		[GuildGuid] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]

	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Desc: Guild Joining Option
	' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Guild_EntranceOpen'
	
	CREATE NONCLUSTERED INDEX [IX_TB_Guild_EntranceOpen_EmporiaWinCount] ON [dbo].[TB_Guild_EntranceOpen]
	(
		[EmporiaWinCount] DESC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	
	CREATE NONCLUSTERED INDEX [IX_TB_Guild_EntranceOpen_IsGuildEntrance] ON [dbo].[TB_Guild_EntranceOpen] 
	(
		[IsGuildEntrance] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
END
GO