USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefRevivePos_PosCX]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefRevivePos] DROP CONSTRAINT [DF_TB_DefRevivePos_PosCX]
END

GO

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefRevivePos_PosCY]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefRevivePos] DROP CONSTRAINT [DF_TB_DefRevivePos_PosCY]
END

GO

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefRevivePos_PosCZ]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefRevivePos] DROP CONSTRAINT [DF_TB_DefRevivePos_PosCZ]
END
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefRevivePos]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefRevivePos]
GO
