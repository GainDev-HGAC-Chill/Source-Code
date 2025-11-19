USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefParty_Info]') AND [type] IN (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefParty_Info](
		[Attribute] [int] NOT NULL,
		[Continent] [int] NOT NULL,
		[Sort] [int] NOT NULL CONSTRAINT [DF_TB_DefParty_Info]  DEFAULT ((0)),	
		[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
		[Area_NameNo] [int] NOT NULL		
	 CONSTRAINT [PK_TB_DefParty_Info] PRIMARY KEY CLUSTERED 
	(
		[Attribute] ASC,
		[Continent] ASC,
		[Sort] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

GO


IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefParty_Info]') and [name] = N'Use')
BEGIN
	ALTER TABLE [dbo].[TB_DefParty_Info] ADD [Use] [int] NOT NULL CONSTRAINT [DF_TB_DefParty_Info_Use] DEFAULT (0)
END

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefParty_Info]') and [name] = N'GroundNo')
BEGIN
	ALTER TABLE [dbo].[TB_DefParty_Info] ADD [GroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefParty_Info_GroundNo] DEFAULT (0)
END

GO

