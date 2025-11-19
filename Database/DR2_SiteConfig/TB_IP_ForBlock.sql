USE DR2_SiteConfig
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/****** Object:  Table [dbo].[TB_IP_ForBlock]    Script Date: 06/23/2009 17:52:25 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_IP_ForBlock]') AND type in (N'U'))
	DROP TABLE [dbo].[TB_IP_ForBlock]
GO

CREATE TABLE [dbo].[TB_IP_ForBlock](
	[StartIP] [nvarchar](32) NOT NULL,
	[EndIP] [nvarchar](32) NOT NULL,
	[NationKey] [nvarchar](32) NULL,
	[NationName] [nvarchar](50) NULL
) ON [PRIMARY]
GO