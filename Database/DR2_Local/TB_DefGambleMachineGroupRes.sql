USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_DefGambleMachineGroupRes]    Script Date: 12/17/2009 12:01:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefGambleMachineGroupRes](
	[GroupNo] [int] IDENTITY(1,1) NOT NULL,
	[Description] [nvarchar](300) COLLATE Korean_Wansung_CI_AS NULL,
	[U] [tinyint] NULL,
	[V] [tinyint] NULL,
	[UVIndex] [smallint] NULL,
	[IconPath] [nvarchar](max) COLLATE Korean_Wansung_CI_AS NULL,
	[DisplayRank] [int] NULL
 CONSTRAINT [PK_TB_DefGambleMachineGroupRes] PRIMARY KEY CLUSTERED 
(
	[GroupNo] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[TB_DefGambleMachineGroupRes] ADD [Title] NVARCHAR(100) NULL
GO