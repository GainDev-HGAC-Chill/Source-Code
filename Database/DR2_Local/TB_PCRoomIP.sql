USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_PCRoomIP]    Script Date: 05/18/2009 18:45:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_PCRoomIP](
	[Idx] [int] IDENTITY(1,1) NOT NULL,
	[IP] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NOT NULL,
	[PCRoomGuid] [uniqueidentifier] NOT NULL,
 CONSTRAINT [PK_TB_PCRoomIP] PRIMARY KEY CLUSTERED 
(
	[Idx] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
