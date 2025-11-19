USE [DR2_local]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefShopInStock]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[TB_DefShopInStock](
	[IDX] [int] NOT NULL,
	[ShopGuid] [uniqueidentifier] NOT NULL,
	[Category] [int] NOT NULL CONSTRAINT [DF_TB_DefShopInStock_Category]  DEFAULT ((0)),
	[ItemNo] [int] NOT NULL,
	[Memo] [nvarchar](300) NULL,
	[Price] [int] NOT NULL,
	[CP] [int] NOT NULL CONSTRAINT [DF_TB_DefShopInStock_CP]  DEFAULT ((0)),
	[Coin] [int] NOT NULL CONSTRAINT [DF_TB_DefShopInStock_Coin]  DEFAULT ((0)),
	[UseTime] [int] NOT NULL CONSTRAINT [DF_TB_DefShopInStock_UseTime]  DEFAULT ((0)),
	[TimeType] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefShopInStock_TimeType]  DEFAULT ((0)),
	[State] [int] NULL,
 CONSTRAINT [PK_TB_DefShopInStock] PRIMARY KEY CLUSTERED 
(
	[ShopGuid] ASC,
	[ItemNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
END
GO

ALTER TABLE [dbo].[TB_DefShopInStock] ADD [SellPrice] [int] NOT NULL DEFAULT(0)