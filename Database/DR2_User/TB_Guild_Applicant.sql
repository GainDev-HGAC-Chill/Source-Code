USE [DR2_User]
GO

/****** Object:  Table [dbo].[TB_Guild_Applicant]    Script Date: 04/15/2010 19:06:08 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_Guild_Applicant]') AND type in (N'U'))
BEGIN
	CREATE TABLE [dbo].[TB_Guild_Applicant](
		[GuildGuid] [uniqueidentifier] NOT NULL,
		[CharacterGuid] [uniqueidentifier] NOT NULL,
		[IsAcceptanceState] [tinyint] NOT NULL,
		[RequestTime] [datetime] NOT NULL,
		[Message] [nvarchar](100) NOT NULL,
		[GuildEntranceFee][bigint] NOT NULL,
	 CONSTRAINT [PK_TB_Guild_Applicant_Guid] PRIMARY KEY CLUSTERED 
	(
		[GuildGuid] ASC,
		[CharacterGuid] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]

	EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'Desc: Guild joining applicant list
		IsAcceptanceState
		 - 0: none
		 - 1: accept
		 - 2: reject' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'TB_Guild_Applicant'
END
GO