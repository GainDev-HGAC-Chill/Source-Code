USE [DR2_Local]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[dbo].[TB_DefPremiumService]')) 
BEGIN
	CREATE TABLE [dbo].[TB_DefPremiumService](
		[ServiceNo] [int] NOT NULL,
		[Title] [nvarchar](50) NOT NULL,
		[ServiceType] [tinyint] NOT NULL,
		[Grade] [tinyint] NOT NULL,
		[Memo] [nvarchar](100) NULL,
		[UseDate] [smallint] NOT NULL,
		[Article01] [int] NOT NULL,
		[Article02] [int] NOT NULL,
		[Article03] [int] NOT NULL,
		[Article04] [int] NOT NULL,
		[Article05] [int] NOT NULL,
		[Article06] [int] NOT NULL,
		[Article07] [int] NOT NULL,
		[Article08] [int] NOT NULL,
		[Article09] [int] NOT NULL,
		[Article10] [int] NOT NULL,
		[Article11] [int] NOT NULL,
		[Article12] [int] NOT NULL,
		[Article13] [int] NOT NULL,
		[Article14] [int] NOT NULL,
		[Article15] [int] NOT NULL,
		[Article16] [int] NOT NULL,
		[Article17] [int] NOT NULL,
		[Article18] [int] NOT NULL,
		[Article19] [int] NOT NULL,
		[Article20] [int] NOT NULL,
		[Article21] [int] NOT NULL,
		[Article22] [int] NOT NULL,
		[Article23] [int] NOT NULL,
		[Article24] [int] NOT NULL,
		[Article25] [int] NOT NULL,
		[Article26] [int] NOT NULL,
		[Article27] [int] NOT NULL,
		[Article28] [int] NOT NULL,
		[Article29] [int] NOT NULL,
		[Article30] [int] NOT NULL,
	 CONSTRAINT [PK_TB_PremiumService] PRIMARY KEY CLUSTERED 
	(
		[ServiceNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
GO
