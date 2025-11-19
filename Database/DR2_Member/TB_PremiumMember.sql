USE [DR2_Member]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID(N'[dbo].[TB_PremiumMember]')) 
BEGIN
	CREATE TABLE [dbo].[TB_PremiumMember](
		[MemberKey] [uniqueidentifier] NOT NULL,
		[PremiumServiceNo] [int] NOT NULL,
		[StartDate] [datetime] NOT NULL,
		[EndDate] [datetime] NOT NULL,
	 CONSTRAINT [PK_TB_PremiumMember] PRIMARY KEY CLUSTERED 
	(
		[MemberKey] ASC
	)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
	) ON [PRIMARY]
END
GO

