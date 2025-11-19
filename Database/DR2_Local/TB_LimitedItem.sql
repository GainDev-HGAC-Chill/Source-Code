USE [DR2_local]
GO
/****** Object:  Table [dbo].[TB_LimitedItem]    Script Date: 05/21/2009 14:49:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_LimitedItem](
	[IDX] [int] IDENTITY(1,1) NOT NULL,
	[EventNo] [int] NOT NULL,
	[Memo] [nvarchar](100) COLLATE Korean_Wansung_CI_AS NULL,
	[BagNo] [int] NOT NULL,
	[StartDate] [datetime] NOT NULL,
	[EndDate] [datetime] NULL,
	[Limit_ResetPeriod] [int] NULL,
	[Safe_ResetPeriod] [int] NOT NULL,
	[RefreshCount] [int] NOT NULL,
 CONSTRAINT [PK_TB_LimitedItemControl] PRIMARY KEY CLUSTERED 
(
	[EventNo] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
