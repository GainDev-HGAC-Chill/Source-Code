USE [DR2_USER]
GO
/****** Object:  Table [dbo].[TB_LimitedItemRecord]    Script Date: 05/21/2009 14:50:31 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_LimitedItemRecord](
	[IDX] [int] IDENTITY(1,1) NOT NULL,
	[EventNo] [int] NOT NULL,
	[Memo] [nvarchar](100) NULL,
	[LimitRefreshDate] [datetime] NULL,
	[SafeRefreshDate] [datetime] NULL,
	[StartDate] [datetime] NOT NULL,
	[EndDate] [datetime] NOT NULL,
	[Limit_ResetPeriod] [int] NOT NULL,
	[Safe_ResetPeriod] [int] NOT NULL,
	[RefreshCount] [int] NOT NULL,
	[LimitCount] [int] NOT NULL,
	[SafeCount] [int] NOT NULL,
 CONSTRAINT [PK_TB_LimitedItemRecord] PRIMARY KEY CLUSTERED 
(
	[EventNo] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
