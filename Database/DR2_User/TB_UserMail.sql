USE [DR2_User]
IF NOT EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'TB_UserMail'))
BEGIN
	/****** Object:  Table [dbo].[TB_UserMail]    Script Date: 03/31/2009 18:10:13 ******/
	SET ANSI_NULLS ON
	SET QUOTED_IDENTIFIER ON
	CREATE TABLE [dbo].[TB_UserMail](
		[MailGuid] [uniqueidentifier] NOT NULL,
		[MailIndex] [bigint] IDENTITY(1,1) NOT NULL,
		[FromGuid] [uniqueidentifier] NOT NULL,
		[FromName] [nvarchar](20) NOT NULL,
		[ToGuid] [uniqueidentifier] NOT NULL,
		[Title] [nvarchar](50) NOT NULL,
		[Note] [nvarchar](200) NULL,
		[PaymentType] [tinyint] NOT NULL CONSTRAINT [DF_TB_UserMail_PaymentType]  DEFAULT ((0)),
		[ItemGuid] [uniqueidentifier] NULL,
		[Money] [bigint] NULL CONSTRAINT [DF_TB_UserMail_Money]  DEFAULT ((0)),
		[SendTime] [datetime] NOT NULL CONSTRAINT [DF_TB_UserMail_SendTime]  DEFAULT (getdate()),
		[LimitTime] [datetime] NOT NULL CONSTRAINT [DF_TB_UserMail_ReceiveTime]  DEFAULT (dateadd(day,(30),getdate())),
		[ItemNo] [int] NOT NULL CONSTRAINT [DF_TB_UserMail_ItemNo]  DEFAULT ((0)),
		[ItemNum] [smallint] NOT NULL CONSTRAINT [DF_TB_UserMail_ItemNum]  DEFAULT ((0)),
		[Enchant_01] [bigint] NOT NULL CONSTRAINT [DF_TB_UserMail_Enchante_01]  DEFAULT ((0)),
		[Enchant_02] [bigint] NOT NULL CONSTRAINT [DF_TB_UserMail_Enchante_02]  DEFAULT ((0)),
		[ItemState] [tinyint] NOT NULL CONSTRAINT [DF_TB_UserMail_ItemState]  DEFAULT ((0)),
		[ReadBit] [bit] NOT NULL CONSTRAINT [DF_TB_UserMail_ReadBit]  DEFAULT ((0)),
		[ReturnBit] [bit] NOT NULL CONSTRAINT [DF_TB_UserMail_ReturnBit]  DEFAULT ((0)),
		[AnnexBit] [bit] NOT NULL CONSTRAINT [DF_TB_UserMail_AnnexBit]  DEFAULT ((0)),
		[PaymentBit] [bit] NOT NULL CONSTRAINT [DF_TB_UserMail_PaymentBit]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_UserMail] PRIMARY KEY NONCLUSTERED 
	(
		[MailGuid] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]

END
GO

/* To prevent any potential data loss issues, you should review this script in detail before running it outside the context of the database designer.*/

SET QUOTED_IDENTIFIER ON
SET ARITHABORT ON
SET NUMERIC_ROUNDABORT OFF
SET CONCAT_NULL_YIELDS_NULL ON
SET ANSI_NULLS ON
SET ANSI_PADDING ON
SET ANSI_WARNINGS ON

ALTER TABLE dbo.TB_UserMail
	DROP COLUMN FromName
GO

alter table TB_UserMail
drop constraint DF_TB_UserMail_ItemNo
go
alter table TB_UserMail
drop constraint  DF_TB_UserMail_ItemNum
go
alter table TB_UserMail
drop constraint  DF_TB_UserMail_ItemState
go
alter table TB_UserMail
drop constraint  DF_TB_UserMail_Enchante_01
go
alter table TB_UserMail
drop constraint  DF_TB_UserMail_Enchante_02
go
alter table TB_UserMail
drop column ItemNo, ItemNum, Enchant_01,Enchant_02, ItemState
go
--CREATE NONCLUSTERED INDEX [IX_TB_UserMail_1] ON [dbo].[TB_UserMail] ([ItemGuid])
--GO

ALTER TABLE dbo.TB_UserMail ADD FromName NVARCHAR(50) NULL
GO

IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserMail]') AND name = N'IX_C_TB_UserMail_ToGuid')
	DROP INDEX [IX_C_TB_UserMail_ToGuid] ON [dbo].[TB_UserMail] WITH ( ONLINE = OFF )
GO
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserMail]') AND name = N'IX_C_TB_UserMail_MailIndex')
	DROP INDEX IX_C_TB_UserMail_MailIndex ON dbo.TB_UserMail
GO
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserMail]') AND name = N'IX_NC_TB_UserMail_ToGuid')
	DROP INDEX IX_NC_TB_UserMail_ToGuid ON dbo.TB_UserMail
GO
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserMail]') AND name = N'IX_NC_TB_UserMail_FromGuid')
	DROP INDEX IX_NC_TB_UserMail_FromGuid ON dbo.TB_UserMail
GO
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserMail]') AND name = N'IX_TB_UserMail_1')
	DROP INDEX IX_TB_UserMail_1 ON dbo.TB_UserMail
GO
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserMail]') AND name = N'IX_NC_TB_UserMail_ItemGuid')
	DROP INDEX [IX_NC_TB_UserMail_ItemGuid] ON [dbo].[TB_UserMail] WITH ( ONLINE = OFF )
GO
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_UserMail]') AND name = N'IX_NC_TB_UserMail_MailIndex')
	DROP INDEX [IX_NC_TB_UserMail_MailIndex] ON [dbo].[TB_UserMail] WITH ( ONLINE = OFF )
GO

CREATE CLUSTERED INDEX IX_C_TB_UserMail_ToGuid ON dbo.TB_UserMail(ToGuid)
CREATE INDEX IX_NC_TB_UserMail_MailIndex ON dbo.TB_UserMail(MailIndex)
CREATE INDEX IX_NC_TB_UserMail_FromGuid ON dbo.TB_UserMail(FromGuid)
CREATE INDEX IX_NC_TB_UserMail_ItemGuid ON dbo.TB_UserMail(ItemGuid)
GO


