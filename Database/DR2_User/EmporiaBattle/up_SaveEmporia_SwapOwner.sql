USE [DR2_User]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveEmporia_SwapOwner]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveEmporia_SwapOwner]
GO
