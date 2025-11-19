USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_Guild_Basic_Info]    Script Date: 05/13/2010 16:46:17 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Guild_Basic_Info]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_Guild_Basic_Info](
		[GuildGuid] [uniqueidentifier] NOT NULL,
		[MasterCharacterGuid] [uniqueidentifier] NOT NULL,
		[GuildName] [nvarchar](30) COLLATE Korean_Wansung_CI_AS NULL,
		[CurrentLevel] [smallint] NOT NULL CONSTRAINT [DF_TB_GuildBasicInfo_CurrentLevel]  DEFAULT ((1)),
		[CurrentExp] [bigint] NOT NULL,
		[Emblem] [tinyint] NULL,
		[CreateDate] [datetime] NULL,
		[TaxExpRate] [smallint] NOT NULL CONSTRAINT [DF_TB_GuildBasicInfo_TaxExpRate]  DEFAULT ((0)),
		[TaxModifyDate] [datetime] NULL,
		[SkillPoint] [smallint] NOT NULL CONSTRAINT [DF_TB_Guild_Basic_Info_SkillPoint]  DEFAULT ((0)),
		[Skills] [binary](200) NOT NULL CONSTRAINT [DF_TB_Guild_Basic_Info_Skills]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_Guild_Basic_Info] PRIMARY KEY CLUSTERED 
	(
		[GuildGuid] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]

	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Guild information' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'TB_Guild_Basic_Info'	
END
GO

IF NOT EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_Guild_Basic_Info') AND [name] = N'GuildInvExtend')
BEGIN
	ALTER TABLE dbo.TB_Guild_Basic_Info ADD [GuildInvExtend] [BINARY](40) NOT NULL CONSTRAINT[DF_TB_Guild_Basic_Info_GuildInvExtend] DEFAULT((0x0124022403240424050006000C000D000E0000000000000000000000000000000000000000000000))
END

IF NOT EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_Guild_Basic_Info') AND [name] = N'GuildInvExtendIdx')
BEGIN
	ALTER TABLE dbo.TB_Guild_Basic_Info ADD [GuildInvExtendIdx] [BINARY](40) NOT NULL CONSTRAINT[DF_TB_Guild_Basic_Info_GuildInvExtendIdx] DEFAULT((0x0100020003000400050006000C000D000E0000000000000000000000000000000000000000000000))
END

IF NOT EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_Guild_Basic_Info') AND [name] = N'GuildInvAuthority')
BEGIN
	ALTER TABLE dbo.TB_Guild_Basic_Info ADD [GuildInvAuthority] [BINARY](4) NOT NULL CONSTRAINT[DF_TB_Guild_Basic_Info_GuildInvAuthority] DEFAULT((0))
END
GO

IF NOT EXISTS (SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_Guild_Basic_Info') AND [name] = N'CurrentMoney')
BEGIN
	ALTER TABLE dbo.TB_Guild_Basic_Info ADD [CurrentMoney] [bigint] NOT NULL CONSTRAINT[DF_TB_Guild_Basic_Info_CurrentMoney] DEFAULT((0))
END
GO