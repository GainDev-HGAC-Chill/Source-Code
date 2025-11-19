USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefDeathPenalty]    Script Date: 02/10/2010 20:47:59 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefDeathPenalty](
	[f_GroundAttr] [int] NOT NULL CONSTRAINT [DF_TB_DefDeathPenalty_f_GroundAttr]  DEFAULT ((0)),
	[f_GroundNo] [int] NOT NULL CONSTRAINT [DF_TB_DefDeathPenalty_f_GroundNo]  DEFAULT ((0)),
	[f_Memo] [nvarchar](200) NULL,
	[f_LevelMin] [smallint] NOT NULL CONSTRAINT [DF_TB_DefDeathPenalty_f_LevelMin]  DEFAULT ((0)),
	[f_LevelMax] [smallint] NOT NULL CONSTRAINT [DF_TB_DefDeathPenalty_f_LevelMax]  DEFAULT ((0)),
	[f_SuccessionalDeath] [tinyint] NOT NULL CONSTRAINT [DF_TB_DefDeathPenalty_f_SuccessionalDeath]  DEFAULT ((0)),
	[f_Effect1] [int] NOT NULL CONSTRAINT [DF_TB_DefDeathPenalty_Effect1]  DEFAULT ((0)),
	[f_Effect2] [int] NOT NULL CONSTRAINT [DF_TB_DefDeathPenalty_Effect2]  DEFAULT ((0))
) ON [PRIMARY]
