USE DR2_User
GO
/****** Object:  Table [dbo].[TB_User_ChatBlock]    Script Date: 07/14/2010 14:10:37 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_User_ChatBlock]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_User_ChatBlock](
		[CharacterID] [uniqueidentifier] NOT NULL,
		[BlockName] [nvarchar](20) NOT NULL,
		[BlockType] [tinyint] NOT NULL,
	 CONSTRAINT [PK_TB_User_ChatBlock] PRIMARY KEY CLUSTERED 
	(
		[CharacterID] ASC,
		[BlockName] ASC
	)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
	) ON [PRIMARY]
END
GO