USE [DR2_Local]
GO
/****** Object:  Table [dbo].[TB_DefShopNpc]    Script Date: 09/17/2009 14:15:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TB_DefShopNpc](
	[IDX] [int] IDENTITY(1,1) NOT NULL,
	[ShopID] [int] NOT NULL,
	[Memo] [nvarchar](50) COLLATE Korean_Wansung_CI_AS NULL,
	[NpcGuid] [uniqueidentifier] NOT NULL,
 CONSTRAINT [PK_Table_DefShopNpc] PRIMARY KEY CLUSTERED 
(
	[ShopID] ASC,
	[NpcGuid] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
