USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefGamble]') AND type in (N'U'))
BEGIN

	CREATE TABLE [dbo].[TB_DefGamble](
		[Idx] [int] IDENTITY(1,1) NOT NULL,
		[GambleNo] [int] NOT NULL,
		[ContainerNo] [int] NOT NULL,
		[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
		[TimeType] [tinyint] NULL,
		[TimeValue] [smallint] NULL,
		[RarityCtrl] [int] NULL,
		[PlusUpCtrl] [int] NOT NULL CONSTRAINT [DF_TB_DefGamble_PlusUpCtrl] DEFAULT ((0))
	CONSTRAINT [PK_TB_DefGamble] PRIMARY KEY CLUSTERED 
	(
		[Idx] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
	
END
ELSE
BEGIN

	IF  NOT EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefGamble_PlusUpCtrl]') AND type = 'D')
	BEGIN
		ALTER TABLE [dbo].[TB_DefGamble] ADD [PlusUpCtrl] [int] NOT NULL CONSTRAINT [DF_TB_DefGamble_PlusUpCtrl] DEFAULT ((0))
	END
END
GO

