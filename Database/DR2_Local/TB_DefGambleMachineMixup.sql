USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_DefGambleMachineMixup]    Script Date: 02/16/2010 10:27:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefGambleMachineMixup](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[MixPoint] [int] NOT NULL,
	[memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[GradeNo] [int] NULL,
	[Rate] [int] NULL
) ON [PRIMARY]
