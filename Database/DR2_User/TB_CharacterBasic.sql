USE [DR2_User]
GO

/****** Object:  Index [IX_TB_CharacterBasic_DeleteDate]    Script Date: 01/25/2011 17:26:11 ******/
IF  EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[TB_CharacterBasic]') AND name = N'IX_TB_CharacterBasic_DeleteDate')
DROP INDEX [IX_TB_CharacterBasic_DeleteDate] ON [dbo].[TB_CharacterBasic] WITH ( ONLINE = OFF )
GO

/****** Object:  Index [IX_TB_CharacterBasic_DeleteDate]    Script Date: 01/25/2011 17:26:11 ******/
CREATE NONCLUSTERED INDEX [IX_TB_CharacterBasic_DeleteDate] ON [dbo].[TB_CharacterBasic] 
(
	[DeleteDate] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
GO


