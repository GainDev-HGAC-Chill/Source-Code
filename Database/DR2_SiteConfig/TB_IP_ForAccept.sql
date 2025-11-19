USE DR2_SiteConfig
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/****** Object:  Table [dbo].[TB_IP_ForAccept]    Script Date: 06/23/2009 17:52:25 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_IP_ForAccept]') AND type in (N'U'))
	DROP TABLE [dbo].[TB_IP_ForAccept]
GO

CREATE TABLE [dbo].[TB_IP_ForAccept](
	[StartIP] [nvarchar](20) NOT NULL,
	[EndIP] [nvarchar](20) NOT NULL,
	[NationKey] [nvarchar](50) NOT NULL,
	[NationName] [nvarchar](50) NOT NULL,
	[ExpireDate] [datetime] NOT NULL
) ON [PRIMARY]
GO