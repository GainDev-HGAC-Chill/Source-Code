USE [DR2_Local]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[dbo].[TB_DefPremiumArticle]')) 
BEGIN
	CREATE TABLE [dbo].[TB_DefPremiumArticle](
		[ArticleNo] [int] NOT NULL,
		[Type] [smallint] NOT NULL,
		[Lv] [smallint] NOT NULL,
		[Memo] [nvarchar](100) NULL,
		[Abil01] [int] NOT NULL,
		[Value01] [int] NOT NULL,
		[Abil02] [int] NOT NULL,
		[Value02] [int] NOT NULL,
		[Abil03] [int] NOT NULL,
		[Value03] [int] NOT NULL,
		[Abil04] [int] NOT NULL,
		[Value04] [int] NOT NULL,
		[Abil05] [int] NOT NULL,
		[Value05] [int] NOT NULL,
		[Abil06] [int] NOT NULL,
		[Value06] [int] NOT NULL,
		[Abil07] [int] NOT NULL,
		[Value07] [int] NOT NULL,
		[Abil08] [int] NOT NULL,
		[Value08] [int] NOT NULL,
		[Abil09] [int] NOT NULL,
		[Value09] [int] NOT NULL,
		[Abil10] [int] NOT NULL,
		[Value10] [int] NOT NULL,
	 CONSTRAINT [PK_TB_PremiumServiceType] PRIMARY KEY CLUSTERED 
	(
		[ArticleNo] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
GO
