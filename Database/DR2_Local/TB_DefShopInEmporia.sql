USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_DefShopInEmporia]    Script Date: 07/28/2010 15:32:31 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefShopInEmporia]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[TB_DefShopInEmporia](
	[IDX] [smallint] NOT NULL,
	[ShopGuid] [uniqueidentifier] NOT NULL,
	[Category] [int] NOT NULL CONSTRAINT [DF_TB_DefShopInEmporia_Category]  DEFAULT ((0)),
	[ItemNo] [int] NOT NULL,
	[Memo] [nvarchar](300) NULL,
	[Price] [int] NOT NULL,
	[CP] [int] NOT NULL CONSTRAINT [DF_TB_DefShopInEmporia_CP]  DEFAULT ((0)),
	[Coin] [int] NOT NULL CONSTRAINT [DF_TB_DefShopInEmporia_Coin]  DEFAULT ((0)),
	[UseTime] [int] NOT NULL CONSTRAINT [DF_TB_DefShopInEmporia_UseTime]  DEFAULT ((0)),
	[TimeType] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefShopInEmporia_TimeType]  DEFAULT ((0))
 CONSTRAINT [PK_TB_DefShopInEmporia] PRIMARY KEY CLUSTERED 
(
	[ShopGuid] ASC,
	[ItemNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
END
GO
