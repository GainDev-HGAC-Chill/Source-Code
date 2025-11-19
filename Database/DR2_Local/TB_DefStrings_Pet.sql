USE [DR2_local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[TB_DefStrings_Pet](
	[StringNo] [int] NOT NULL,
	[Text] [nvarchar](500) NOT NULL,
	[TextEng] [nvarchar](500) NULL,
	[Memo] [nvarchar](100) NULL,
	[MemoLocal] [nvarchar](100) NULL,
 CONSTRAINT [PK_TB_DefStrings_Pet_StringNo] PRIMARY KEY CLUSTERED 
(
	[StringNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Define Text in Game(Pet)' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_DefStrings_Pet'
GO
