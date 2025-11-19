USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_SpecificReward]    Script Date: 07/14/2010 14:10:37 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_SpecificReward]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_SpecificReward](
		[Type] [int] NOT NULL,
		[CharacterID] [uniqueidentifier] NOT NULL,
		[LastRewardTime] [datetime] NOT NULL,
	 CONSTRAINT [PK_TB_SpecificReward] PRIMARY KEY CLUSTERED 
	(
		[Type] ASC,
		[CharacterID] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END
GO

IF NOT EXISTS (SELECT *FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_SpecificReward') AND [name] = N'LastRewardCount')
BEGIN								     
	ALTER TABLE dbo.TB_SpecificReward ADD [LastRewardCount] smallint NOT NULL CONSTRAINT [DF_TB_SpecificReward_LastRewardCount] DEFAULT(0)
END

IF NOT EXISTS (SELECT *FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_SpecificReward') AND [name] = N'IsKeepConn')
BEGIN								     
	ALTER TABLE dbo.TB_SpecificReward ADD [IsKeepConn] smallint NOT NULL CONSTRAINT [DF_TB_SpecificReward_IsKeepConn] DEFAULT(0)
END
