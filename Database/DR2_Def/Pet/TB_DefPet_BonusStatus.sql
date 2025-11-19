USE [DR2_Def]
GO

USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[TB_DefPet_BonusStatus](
	[ID] [int] NOT NULL,
	[Memo] [nvarchar](100) NULL,
	[Select_Rate] [tinyint] NOT NULL,
	[ItemOpt2_OptionType_01] [INT] NOT NULL,
	[ItemOpt2_Rate_01] [INT] NOT NULL,
	[ItemOpt2_OptionType_02] [INT] NOT NULL,
	[ItemOpt2_Rate_02] [INT] NOT NULL,
	[ItemOpt2_OptionType_03] [INT] NOT NULL,
	[ItemOpt2_Rate_03] [INT] NOT NULL,
	[ItemOpt2_OptionType_04] [INT] NOT NULL,
	[ItemOpt2_Rate_04] [INT] NOT NULL,
	[ItemOpt2_OptionType_05] [INT] NOT NULL,
	[ItemOpt2_Rate_05] [INT] NOT NULL,
	[ItemOpt2_ValueLv1_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv2_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv3_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv4_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv5_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv6_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv7_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv8_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv9_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv10_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv11_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv12_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv13_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv14_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv15_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv16_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv17_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv18_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv19_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv20_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv21_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv22_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv23_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv24_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv25_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv26_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv27_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv28_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv29_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv30_Rate] [INT] NOT NULL,
	[ItemOpt2_ValueLv31_Rate] [INT] NOT NULL,
 CONSTRAINT [PK_TB_DefPet_BonusStatus] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO


