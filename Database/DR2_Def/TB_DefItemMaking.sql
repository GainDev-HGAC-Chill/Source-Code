USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefItemMaking]    Script Date: 06/25/2009 13:51:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefItemMaking](
	[Index] [int] IDENTITY(1,1) NOT FOR REPLICATION NOT NULL,
	[No] [int] NOT NULL,
	[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[MakingTypeNo] [int] NOT NULL,
	[ContentStringNo] [int] NOT NULL,
	[NeedMoney] [int] NOT NULL,
	[NeedElementsNo] [int] NOT NULL,
	[NeedCountControlNo] [int] NOT NULL,
	[SuccessRateControlNo] [int] NOT NULL,
	[ResultControlNo] [int] NOT NULL,
	[Elements01] [int] NOT NULL,
	[CountControl01] [int] NOT NULL,
	[Elements02] [int] NOT NULL,
	[CountControl02] [int] NOT NULL,
	[Elements03] [int] NOT NULL,
	[CountControl03] [int] NOT NULL,
	[Elements04] [int] NOT NULL,
	[CountControl04] [int] NOT NULL,
	[Elements05] [int] NOT NULL,
	[CountControl05] [int] NOT NULL,
	[Elements06] [int] NOT NULL,
	[CountControl06] [int] NOT NULL,
	[Elements07] [int] NOT NULL,
	[CountControl07] [int] NOT NULL,
	[Elements08] [int] NOT NULL,
	[CountControl08] [int] NOT NULL,
	[Elements09] [int] NOT NULL,
	[CountControl09] [int] NOT NULL,
	[Elements10] [int] NOT NULL,
	[CountControl10] [int] NOT NULL
 CONSTRAINT [PK_Table_1] PRIMARY KEY CLUSTERED 
(
	[No] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]

GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Make-item definition like recipe' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'TB_DefItemMaking'

ALTER TABLE [dbo].[TB_DefItemMaking] ADD
[RarityControl] [int] NOT NULL CONSTRAINT [DF_TB_DefItemMaking_RarityControl] DEFAULT ((0))
GO
