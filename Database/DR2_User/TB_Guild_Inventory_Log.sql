USE [DR2_User]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Guild_Inventory_Log]') AND [type] in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_Guild_Inventory_Log](
	[IDX] [int] IDENTITY(1,1) NOT NULL,
	[GuildGuid] [uniqueidentifier] NOT NULL,
	[ItemGuid] [uniqueidentifier] NOT NULL,
	[Date] [datetime] NOT NULL,
	[CharacterName] [nvarchar](20) COLLATE Korean_Wansung_CI_AS NOT NULL,
	[Type] [tinyint] NOT NULL,
	[ItemNo] [int] NOT NULL,
	[Count] [bigint] NOT NULL
	) ON [PRIMARY]
	
	CREATE NONCLUSTERED INDEX [IX_TB_Guild_Inventory_Log] ON [dbo].[TB_Guild_Inventory_Log] 
	(
		[GuildGuid] DESC
	)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF) ON [PRIMARY]
	
	CREATE CLUSTERED INDEX [IX_TB_Guild_Inventory_Log_Date] ON [dbo].[TB_Guild_Inventory_Log] 
	(
		[Date] DESC
	)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF) ON [PRIMARY]
END
GO