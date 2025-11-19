USE [DR2_local]
GO

/****** Object:  Table [dbo].[TB_PCCafe]    Script Date: 11/10/2010 20:43:34 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS( SELECT * FROM sys.all_objects WHERE object_id = object_id( N'dbo.TB_PCCafe' ) )
BEGIN
	CREATE TABLE [dbo].[TB_PCCafe](
		[f_Idx] [int] IDENTITY(1,1) NOT NULL,
		[f_Name] [nvarchar](50) NOT NULL,
		[f_IP] [nvarchar](50) NOT NULL,
		[f_Grade] [tinyint] NOT NULL,
	 CONSTRAINT [PK_TB_PCCafe] PRIMARY KEY CLUSTERED 
	(
		[f_Idx] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
GO


