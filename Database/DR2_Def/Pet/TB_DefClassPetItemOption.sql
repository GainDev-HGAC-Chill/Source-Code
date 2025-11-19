USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'TB_DefClassPetItemOption'))
BEGIN
	CREATE TABLE [dbo].[TB_DefClassPetItemOption](
		[ID] [int] NOT NULL,
		[Level] [smallint] NOT NULL,
		[Memo] [nvarchar](100) NULL,
		[OptionType01] [int] NOT NULL CONSTRAINT [DF_TB_DefClassPetItemOption_OptionType01]  DEFAULT ((0)),
		[OptionLv01] [int] NOT NULL CONSTRAINT [DF_TB_DefClassPetItemOption_OptionLv01]  DEFAULT ((0)),
		[OptionType02] [int] NOT NULL CONSTRAINT [DF_TB_DefClassPetItemOption_OptionType02]  DEFAULT ((0)),
		[OptionLv02] [int] NOT NULL CONSTRAINT [DF_TB_DefClassPetItemOption_OptionLv02]  DEFAULT ((0)),
		[OptionType03] [int] NOT NULL CONSTRAINT [DF_TB_DefClassPetItemOption_OptionType03]  DEFAULT ((0)),
		[OptionLv03] [int] NOT NULL CONSTRAINT [DF_TB_DefClassPetItemOption_OptionLv03]  DEFAULT ((0)),
		[OptionType04] [int] NOT NULL CONSTRAINT [DF_TB_DefClassPetItemOption_OptionType04]  DEFAULT ((0)),
		[OptionLv04] [int] NOT NULL CONSTRAINT [DF_TB_DefClassPetItemOption_OptionLv04]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_DefClassPetItemOption] PRIMARY KEY CLUSTERED
	(
		[ID] ASC,
		[Level] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
