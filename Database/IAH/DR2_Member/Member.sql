USE DR2_Member
GO

ALTER TABLE [dbo].[Member] ADD
[BonusCash] [bigint] NOT NULL CONSTRAINT [DF_Member_BonusCash] DEFAULT ((0))
GO

