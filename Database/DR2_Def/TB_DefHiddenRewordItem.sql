USE [DR2_Def]
GO
IF  NOT EXISTS (SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'TB_DefHiddenRewordItem'))
BEGIN
	/****** 개체:  Table [dbo].[TB_DefHiddenRewordItem]    스크립트 날짜: 01/05/2010 11:03:07 ******/
	SET ANSI_NULLS ON
	SET QUOTED_IDENTIFIER ON
	CREATE TABLE [dbo].[TB_DefHiddenRewordItem](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[ItemCount] [int] NOT NULL CONSTRAINT [DF_TB_HiddenRewordItem_ItemCount]  DEFAULT ((0)),
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
		[MinLevel] [int] NOT NULL CONSTRAINT [DF_TB_HiddenRewordItem_MinLevel]  DEFAULT ((0)),
		[MaxLevel] [int] NOT NULL CONSTRAINT [DF_TB_HiddenRewordItem_MaxLevel]  DEFAULT ((0)),
		[ItemNo] [int] NOT NULL CONSTRAINT [DF_TB_HiddenRewordItem_ItemNo]  DEFAULT ((0)),
	 CONSTRAINT [PK_TB_DefHiddenRewordItem] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

GO
