USE [DR2_Local]
GO

/****** Object:  Table [dbo].[TB_Common_CashItemLimitSellMember]    Script Date: 11/08/2010 14:09:51 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[TB_Common_CashItemLimitSellMember](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[MemberGuid] [uniqueidentifier] NOT NULL,
	[CashItemIdx] [int] NOT NULL,
	[ItemBuyCount] [int] NOT NULL,
	[CreateDate] [datetime] NOT NULL
 CONSTRAINT [PK_TB_Common_CashItemLimitSellMember] PRIMARY KEY CLUSTERED 
(
	[Idx] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
