USE [DR2_User]
GO
/****** Object:  Table [dbo].[TB_Web_UserItemInfo_Status]    Script Date: 06/11/2010 15:59:04 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Web_UserItemInfo_Status]') and [type] in (N'U'))
BEGIN

	CREATE TABLE [dbo].[TB_Web_UserItemInfo_Status](
		[f_RealmNo] [int] NOT NULL,
		[f_ItemGuid] [uniqueidentifier] NOT NULL,
		[f_PhysAttackMin] [int] NOT NULL,
		[f_PhysAttackMax] [int] NOT NULL,
		[f_MagicAttackMin] [int] NOT NULL,
		[f_MagicAttackMax] [int] NOT NULL,
		[f_PhysDefence] [int] NOT NULL,
		[f_MagicDefence] [int] NOT NULL,
		[f_EnchantLevel] [int] NOT NULL,
		[f_RarityLevel] [int] NOT NULL,
		[f_RarityValue] [int] NOT NULL,
		[f_RapairMoney] [bigint] NOT NULL,
	 CONSTRAINT [PK_TB_Web_UserItemInfo_Status_1] PRIMARY KEY NONCLUSTERED 
	(
		[f_RealmNo] ASC,
		[f_ItemGuid] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]

	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'아이템 고유 ID(장비만)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_UserItemInfo_Status', @level2type=N'COLUMN',@level2name=N'f_ItemGuid'
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'TB_BaseItemInfo 테이블의 필드에서 f_BaseXXXXXXX 필드와 동의(현재값)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_UserItemInfo_Status', @level2type=N'COLUMN',@level2name=N'f_PhysAttackMin'
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'TB_BaseItemInfo 테이블의 필드에서 f_BaseXXXXXXX 필드와 동의(현재값)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_UserItemInfo_Status', @level2type=N'COLUMN',@level2name=N'f_PhysAttackMax'
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'TB_BaseItemInfo 테이블의 필드에서 f_BaseXXXXXXX 필드와 동의(현재값)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_UserItemInfo_Status', @level2type=N'COLUMN',@level2name=N'f_MagicAttackMin'
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'TB_BaseItemInfo 테이블의 필드에서 f_BaseXXXXXXX 필드와 동의(현재값)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_UserItemInfo_Status', @level2type=N'COLUMN',@level2name=N'f_MagicAttackMax'
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'TB_BaseItemInfo 테이블의 필드에서 f_BaseXXXXXXX 필드와 동의(현재값)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_UserItemInfo_Status', @level2type=N'COLUMN',@level2name=N'f_PhysDefence'
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'TB_BaseItemInfo 테이블의 필드에서 f_BaseXXXXXXX 필드와 동의(현재값)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_UserItemInfo_Status', @level2type=N'COLUMN',@level2name=N'f_MagicDefence'
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'장비일 경우 인챈트 레벨' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_UserItemInfo_Status', @level2type=N'COLUMN',@level2name=N'f_EnchantLevel'
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'아이템 영력 등급' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_UserItemInfo_Status', @level2type=N'COLUMN',@level2name=N'f_RarityLevel'
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'아이템 영력' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_UserItemInfo_Status', @level2type=N'COLUMN',@level2name=N'f_RarityValue'
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'수리비용' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_UserItemInfo_Status', @level2type=N'COLUMN',@level2name=N'f_RapairMoney'
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'사용자 캐릭터 아이템 능력치 최종 정보' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Web_UserItemInfo_Status'
END


IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_Web_UserItemInfo_Status]') AND name = N'IX_TB_Web_UserItemInfo_Status')
DROP INDEX [IX_TB_Web_UserItemInfo_Status] ON [dbo].[TB_Web_UserItemInfo_Status] WITH ( ONLINE = OFF )
GO


IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_Web_UserItemInfo_Status]') AND name = N'PK_TB_Web_UserItemInfo_Status_1')
ALTER TABLE [dbo].[TB_Web_UserItemInfo_Status] DROP CONSTRAINT [PK_TB_Web_UserItemInfo_Status_1]
GO

IF  NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_Web_UserItemInfo_Status]') AND name = N'CPK_TB_Web_UserItemInfo_Status_1')
ALTER TABLE [dbo].[TB_Web_UserItemInfo_Status] ADD  CONSTRAINT [CPK_TB_Web_UserItemInfo_Status_1] PRIMARY KEY CLUSTERED 
(
	[f_RealmNo] ASC,
	[f_ItemGuid] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
GO
