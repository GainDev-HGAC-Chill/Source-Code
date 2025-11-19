SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

USE [DR2_Def]
GO

-- Old Version 것은 지우기
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefGuildEmporia]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefGuildEmporia]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefGuildEmporia]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefGuildEmporia]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefGuildEmporiaFunction]') AND type in (N'U'))
DROP TABLE [dbo].[TB_DefGuildEmporiaFunction]
GO
