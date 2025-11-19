USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'[DF_TB_DefGmCmd_Level]') AND type = 'D')
BEGIN
ALTER TABLE [dbo].[TB_DefGmCmd] DROP CONSTRAINT [DF_TB_DefGmCmd_Level]
END
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefGmCmd]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefGmCmd]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefGmCmd]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefGmCmd]
GO


