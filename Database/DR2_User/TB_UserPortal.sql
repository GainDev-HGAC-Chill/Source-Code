USE [DR2_User]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserPortal]'))
BEGIN

CREATE TABLE [dbo].[TB_UserPortal](
	[CharacterGuid] [uniqueidentifier] NOT NULL,
	[PortalGuid] [uniqueidentifier] NOT NULL,
	[Comment] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[GroundNo] [int] NOT NULL,
	[x] [float] NOT NULL,
	[y] [float] NOT NULL,
	[z] [float] NOT NULL,
 CONSTRAINT [PK_TB_UserPortal] PRIMARY KEY CLUSTERED 
(
	[PortalGuid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
	
END


/****** Object:  Index [PK_TB_UserPortal]    Script Date: 08/06/2012 15:30:10 ******/
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserPortal]') AND name = N'PK_TB_UserPortal')
ALTER TABLE [dbo].[TB_UserPortal] DROP CONSTRAINT [PK_TB_UserPortal]
 
/****** Object:  Index [IX_C_TB_UserPortal_CharacterGuid]    Script Date: 08/06/2012 15:31:18 ******/
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserPortal]') AND name = N'IX_C_TB_UserPortal_CharacterGuid')
DROP INDEX [IX_C_TB_UserPortal_CharacterGuid] ON [dbo].[TB_UserPortal] WITH ( ONLINE = OFF )
 
/****** Object:  Index [IX_C_TB_UserPortal_CharacterGuid]    Script Date: 08/06/2012 15:31:18 ******/
CREATE CLUSTERED INDEX [IX_C_TB_UserPortal_CharacterGuid] ON [dbo].[TB_UserPortal] 
(
	[CharacterGuid] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
 

/****** Object:  Index [PK_TB_UserPortal_PortalGuid]    Script Date: 08/06/2012 15:31:49 ******/
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserPortal]') AND name = N'PK_TB_UserPortal_PortalGuid')
ALTER TABLE [dbo].[TB_UserPortal] DROP CONSTRAINT [PK_TB_UserPortal_PortalGuid]

ALTER TABLE [dbo].[TB_UserPortal] ADD  CONSTRAINT [PK_TB_UserPortal_PortalGuid] PRIMARY KEY NONCLUSTERED 
(
	[PortalGuid] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
GO


 

