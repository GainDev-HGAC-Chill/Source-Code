USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_Common_CashItem]    Script Date: 11/09/2009 18:53:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[TB_Common_CashItem](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[CashItemCategoryIdx] [int] NULL,
	[CashItemDisplayTypeIdx] [tinyint] NULL,
	[DisplayRank] [smallint] NULL,
	[ItemName] [nvarchar](200) COLLATE Korean_Wansung_CI_AS NOT NULL,
	[Status] [tinyint] NOT NULL,
	[Description] [nvarchar](300) COLLATE Korean_Wansung_CI_AS NOT NULL,
	[SaleType] [tinyint] NOT NULL,
	[SaleStartDate] [datetime] NULL,
	[SaleEndDate] [datetime] NULL,
	[Mileage] [int] NULL,
	[IconPath] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NOT NULL,
	[U] [tinyint] NOT NULL,
	[V] [tinyint] NOT NULL,
	[UVIndex] [tinyint] NOT NULL,
	[RegDate] [datetime] NOT NULL,
	[RegIP] [varchar](15) COLLATE Korean_Wansung_CI_AS NOT NULL,
 CONSTRAINT [PK_TB_Common_CashItem] PRIMARY KEY CLUSTERED 
(
	[Idx] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]

GO

ALTER TABLE [dbo].[TB_Common_CashItem] ALTER COLUMN [Description] [nvarchar] (300) COLLATE Korean_Wansung_CI_AS NOT NULL
GO
