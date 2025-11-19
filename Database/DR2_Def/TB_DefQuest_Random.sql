USE [DR2_Def]
GO
/****** Object:  Table [dbo].[TB_DefQuest_Random]    Script Date: 01/11/2010 11:18:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefQuest_Random]') AND [type] in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefQuest_Random](
		[Index] [int] NOT NULL,
		[MinLevel] [int] NOT NULL,
		[MaxLevel] [int] NOT NULL,
		[f_GroupNo] [int] NOT NULL CONSTRAINT [DF_TB_DefQuest_Random_f_GroupNo]  DEFAULT ((0)),
		[StartID] [int] NOT NULL,
		[EndID] [int] NOT NULL,
		[DisplayCount] [int] NOT NULL,
	 CONSTRAINT [PK_TB_DefQuest_Random_Index] PRIMARY KEY CLUSTERED 
	(
		[Index] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

GO
IF NOT EXISTS(SELECT * FROM sys.columns WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefQuest_Random]') AND [name] = 'Type')
BEGIN
	ALTER TABLE [dbo].[TB_DefQuest_Random] ADD [Type] [int] NOT NULL CONSTRAINT [DF_TB_DefQuest_Random_Type]  DEFAULT ((10))
END