USE [DR2_Local]
GO

/****** Object:  Table [dbo].[TB_Common_CashItemLimitSell]    Script Date: 11/08/2010 14:09:51 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[TB_Common_CashItemLimitSell](
	[CashItemIdx] [int] NOT NULL,
	[ItemTotalCount] [int] NOT NULL,
	[ItemLimitCount] [int] NOT NULL,
	[ItemBuyLimitCount] [int] NOT NULL
 CONSTRAINT [PK_TB_Common_CashItemLimitSell] PRIMARY KEY CLUSTERED 
(
	[CashItemIdx] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO


