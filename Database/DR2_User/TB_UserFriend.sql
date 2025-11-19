USE [DR2_User]
IF NOT EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'TB_UserFriend'))
BEGIN
	/****** Object:  Table [dbo].[TB_UserFriend]    Script Date: 03/31/2009 18:00:56 ******/
	SET ANSI_NULLS ON
	SET QUOTED_IDENTIFIER ON
	CREATE TABLE [dbo].[TB_UserFriend](
		[OwnerMemberGuid] [uniqueidentifier] NOT NULL,
		[FriendGroupName] [nvarchar](20) NOT NULL CONSTRAINT [DF_TB_UserFriend_FriendGroupName]  DEFAULT (''),
		[FriendMemberGuid] [uniqueidentifier] NOT NULL CONSTRAINT [DF_TB_UserFriend_FriendMemberGuid]  DEFAULT ('00000000-0000-0000-0000-000000000000'),
		[FriendExtendName] [nvarchar](20) NULL,
		[FriendStatus] [int] NOT NULL CONSTRAINT [DF_TB_UserFriend_LinkStatus]  DEFAULT ((0))
	) ON [PRIMARY]

	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'표시상으로 MemberGuid이나, 사용은 캐릭터 Guid를 사용함' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_UserFriend', @level2type=N'COLUMN',@level2name=N'OwnerMemberGuid'
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'표시상으로 MemberGuid이나, 사용은 캐릭터 Guid를 사용함Edit...' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_UserFriend', @level2type=N'COLUMN',@level2name=N'FriendMemberGuid'
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'사용자 캐릭터 커뮤니티/친구 정보' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_UserFriend'
END
GO

/* To prevent any potential data loss issues, you should review this script in detail before running it outside the context of the database designer.*/
IF EXISTS(SELECT * FROM sys.COLUMNS WHERE object_id = OBJECT_ID(N'dbo.TB_UserFriend') AND [name] like N'FriendExtendName')
BEGIN
	BEGIN TRANSACTION
	SET QUOTED_IDENTIFIER ON
	SET ARITHABORT ON
	SET NUMERIC_ROUNDABORT OFF
	SET CONCAT_NULL_YIELDS_NULL ON
	SET ANSI_NULLS ON
	SET ANSI_PADDING ON
	SET ANSI_WARNINGS ON
	COMMIT
	BEGIN TRANSACTION
	
	ALTER TABLE dbo.TB_UserFriend
		DROP COLUMN FriendExtendName
	
	COMMIT
END

IF EXISTS(SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'dbo.TB_UserFriend') AND [name] = N'IX_C_TB_UserFriend_OwnerMemberGuid_FriendMemberGuid')
BEGIN
	DROP INDEX IX_C_TB_UserFriend_OwnerMemberGuid_FriendMemberGuid ON dbo.TB_UserFriend
END

/* To prevent any potential data loss issues, you should review this script in detail before running it outside the context of the database designer.*/
IF not EXISTS(SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'dbo.TB_UserFriend') AND [name] = N'PK_TB_UserFriend')
BEGIN
	ALTER TABLE dbo.TB_UserFriend ADD CONSTRAINT
		PK_TB_UserFriend PRIMARY KEY CLUSTERED 
		(
		OwnerMemberGuid,
		FriendMemberGuid
		) WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
END

/****** Object:  Index [IX_TB_UserFriend]    Script Date: 08/06/2012 10:59:01 ******/
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserFriend]') AND name = N'IX_TB_UserFriend')
DROP INDEX [IX_TB_UserFriend] ON [dbo].[TB_UserFriend] WITH ( ONLINE = OFF )
GO

CREATE NONCLUSTERED INDEX [IX_TB_UserFriend] ON [dbo].[TB_UserFriend] 
(
	[FriendMemberGuid] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
GO