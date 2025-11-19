USE [DR2_Member]
GO

/****** Object:  Table [dbo].[TB_Event_Coupon]    Script Date: 04/15/2009 01:30:03 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Event_Coupon]') AND type in (N'U'))
BEGIN

CREATE TABLE [dbo].[TB_Event_Coupon](
	[f_IDX] [int] IDENTITY(1,1) NOT NULL,
	[f_CouponID] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NOT NULL,
	[f_EventKey] [int] NOT NULL CONSTRAINT [DF_TB_Event_Coupon_f_EventKey]  DEFAULT ((1)),
	[f_RewardKey] [int] NOT NULL CONSTRAINT [DF_TB_Event_Coupon_f_RewardKey]  DEFAULT ((0)),
	[f_OwnerMemberGuid] [uniqueidentifier] NULL,
	[f_OwnerCharacterGuid] [uniqueidentifier] NULL,
	[f_TakerMemberGuid] [uniqueidentifier] NULL,
	[f_TakerCharacterGuid] [uniqueidentifier] NULL,
	[f_CreateDate] [datetime] NULL,
	[f_TakeDate] [datetime] NULL,
	[f_RewardGuid1] [uniqueidentifier] NULL,
	[f_RewardGuid2] [uniqueidentifier] NULL,
	[f_RewardGuid3] [uniqueidentifier] NULL,
	[f_RewardGuid4] [uniqueidentifier] NULL,
 CONSTRAINT [PK_TB_Event_Coupon] PRIMARY KEY CLUSTERED 
(
	[f_CouponID] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]

END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_Event_Coupon') AND [name] = N'f_Site')
BEGIN
	ALTER TABLE [dbo].[TB_Event_Coupon] ADD [f_Site] [smallint] NULL
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_Event_Coupon') AND [name] = N'f_Realm')
BEGIN
	ALTER TABLE [dbo].[TB_Event_Coupon] ADD [f_Realm] [smallint] NULL
END
GO

IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'dbo.TB_Event_Coupon') AND [name] = N'IX_TB_Event_Coupon')
BEGIN
	CREATE NONCLUSTERED INDEX [IX_TB_Event_Coupon] ON [dbo].[TB_Event_Coupon] ([f_OwnerMemberGuid], [f_EventKey], [f_Site], [f_Realm])
END
GO


IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_Event_Coupon') AND [name] = N'f_RewardGuid5')
BEGIN
	ALTER TABLE [dbo].[TB_Event_Coupon] ADD [f_RewardGuid5] [uniqueidentifier] NULL
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_Event_Coupon') AND [name] = N'f_RewardGuid6')
BEGIN
	ALTER TABLE [dbo].[TB_Event_Coupon] ADD [f_RewardGuid6] [uniqueidentifier] NULL
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_Event_Coupon') AND [name] = N'f_RewardGuid7')
BEGIN
	ALTER TABLE [dbo].[TB_Event_Coupon] ADD [f_RewardGuid7] [uniqueidentifier] NULL
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_Event_Coupon') AND [name] = N'f_RewardGuid8')
BEGIN
	ALTER TABLE [dbo].[TB_Event_Coupon] ADD [f_RewardGuid8] [uniqueidentifier] NULL
END
GO


IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_Event_Coupon]') AND name = N'IX_TB_Event_Coupon_EventId')
BEGIN
	CREATE NONCLUSTERED INDEX [IX_TB_Event_Coupon_EventId] ON [dbo].[TB_Event_Coupon] 
	(
		[f_EventKey] ASC
	)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF) ON [PRIMARY]
END
GO

IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'dbo.TB_Event_Coupon') AND [name] = N'UseLimit')
BEGIN
	ALTER TABLE [dbo].[TB_Event_Coupon] ADD [UseLimit] [tinyint] NOT NULL CONSTRAINT DF_TB_Event_Coupon_UseLimit DEFAULT (0)
END
GO

IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_Event_Coupon]') AND name = N'IX_TB_Event_Coupon_f_TakeMemberGuid')
BEGIN
	CREATE NONCLUSTERED INDEX [IX_TB_Event_Coupon_f_TakeMemberGuid] ON [dbo].[TB_Event_Coupon] 
	(
		[f_TakerMemberGuid] ASC
	)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF) ON [PRIMARY]
END
GO

IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_Event_Coupon]') AND name = N'IX_TB_Event_Coupon_f_TakerCharacterGuid')
BEGIN
	CREATE NONCLUSTERED INDEX [IX_TB_Event_Coupon_f_TakerCharacterGuid] ON [dbo].[TB_Event_Coupon] 
	(
		[f_TakerCharacterGuid] ASC
	)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF) ON [PRIMARY]
END
GO

/****** Object:  Index [IX_TB_Event_Coupon]    Script Date: 12/04/2012 09:49:46 ******/
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_Event_Coupon]') AND name = N'IX_TB_Event_Coupon')
DROP INDEX [IX_TB_Event_Coupon] ON [dbo].[TB_Event_Coupon] WITH ( ONLINE = OFF )
GO
 

/****** Object:  Index [IX_TB_Event_Coupon]    Script Date: 12/04/2012 09:49:46 ******/
CREATE NONCLUSTERED INDEX [IX_TB_Event_Coupon] ON [dbo].[TB_Event_Coupon] 
(
	[f_OwnerMemberGuid] ASC,
	[f_EventKey] ASC,
	[f_Site] ASC,
	[f_Realm] ASC,
	[f_TakeDate] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
GO

 

/****** Object:  Index [IX_TB_Event_Coupon_IDX]    Script Date: 12/04/2012 09:50:13 ******/
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_Event_Coupon]') AND name = N'IX_TB_Event_Coupon_IDX')
DROP INDEX [IX_TB_Event_Coupon_IDX] ON [dbo].[TB_Event_Coupon] WITH ( ONLINE = OFF )
GO
 
/****** Object:  Index [IX_TB_Event_Coupon_IDX]    Script Date: 12/04/2012 09:50:13 ******/
CREATE NONCLUSTERED INDEX [IX_TB_Event_Coupon_IDX] ON [dbo].[TB_Event_Coupon] 
(
	[f_IDX] ASC
)WITH (PAD_INDEX  = ON, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
GO


