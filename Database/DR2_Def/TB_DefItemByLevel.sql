USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefItemByLevel]') AND type in (N'U'))
BEGIN

	CREATE TABLE [dbo].[TB_DefItemByLevel](
		[ID] [int] NOT NULL,
		[Level] [int] NOT NULL,
		[Memo] [nvarchar](100) NULL,
		[ItemNo] [int] NOT NULL,
	CONSTRAINT [PK_TB_DefItemByLevel] PRIMARY KEY CLUSTERED 
	(
		[ID] ASC,
		[Level] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
	
	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'ID list of Item By Level' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefItemByLevel'

END
GO
