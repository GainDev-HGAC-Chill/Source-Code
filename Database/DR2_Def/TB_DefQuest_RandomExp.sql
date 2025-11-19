USE [DR2_Def]
GO

/****** Object:  Table [dbo].[TB_DefQuest_RandomExp]    Script Date: 10/20/2009 17:42:40 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefQuest_RandomExp]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_DefQuest_RandomExp](
		[f_Level] [int] NOT NULL,
		[f_Exp1] [int] NOT NULL,
		[f_Exp2] [int] NOT NULL,
		[f_Exp3] [int] NOT NULL,
		[f_Exp4] [int] NOT NULL,
		[f_Exp5] [int] NOT NULL,
		[f_Exp6] [int] NOT NULL,
		[f_Exp7] [int] NOT NULL,
		[f_Exp8] [int] NOT NULL,
		[f_Exp9] [int] NOT NULL,
		[f_Exp10] [int] NOT NULL,
	 CONSTRAINT [PK_TB_DefQuest_RandomExp] PRIMARY KEY CLUSTERED 
	(
		[f_Level] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
