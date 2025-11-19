USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefHiddenRewordBag]') AND type in (N'U'))
BEGIN

	CREATE TABLE [dbo].[TB_DefHiddenRewordBag](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[RewordNo] [int] NOT NULL CONSTRAINT [DF_TB_DefHiddenRewordBag_BagGrpNo] DEFAULT ((0)),
		[ContainerNo] [int] NOT NULL CONSTRAINT [DF_TB_DefHiddenRewordBag_ContainerNo] DEFAULT ((0)),
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
		[RarityCtrl] [int] NOT NULL CONSTRAINT [DF_TB_DefHiddenRewordBag_RarityCtrl] DEFAULT ((0)),
		[PlusUpCtrl] [int] NOT NULL CONSTRAINT [DF_TB_DefHiddenRewordBag_PlusUpCtrl] DEFAULT ((0))
	CONSTRAINT [PK_TB_DefHiddenRewordBag] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END

GO

