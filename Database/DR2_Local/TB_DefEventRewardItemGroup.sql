USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_DefEventRewardItemGroup]    Script Date: 08/05/2011 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefEventRewardItemGroup]') )
BEGIN
	CREATE TABLE [dbo].[TB_DefEventRewardItemGroup](
		[IDX] [int] IDENTITY(1,1) NOT NULL,
		[RewardItemGroup] [int] NOT NULL,
		[ItemNo] [int] NOT NULL,
		[Rate] [int] NOT NULL,
		[Count] [int] NOT NULL
	 CONSTRAINT [PK_TB_DefEventRewardItemGroup] PRIMARY KEY CLUSTERED 
	(
		[IDX] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END