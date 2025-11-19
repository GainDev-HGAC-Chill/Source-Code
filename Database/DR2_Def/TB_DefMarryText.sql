USE [DR2_Def]
GO
IF  NOT EXISTS (SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'TB_DefMarryText'))
BEGIN
	/****** 개체:  Table [dbo].[TB_DefMarryText]    스크립트 날짜: 08/15/2009 17:09:07 ******/
	SET ANSI_NULLS ON
	SET QUOTED_IDENTIFIER ON
	CREATE TABLE [dbo].[TB_DefMarryText](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[Group] [int] NOT NULL CONSTRAINT [DF_TB_MarryText_Group]  DEFAULT ((0)),
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
		[TextNo] [bigint] NOT NULL CONSTRAINT [DF_TB_MarryText_TextNo]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_DefMarryText] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

GO
