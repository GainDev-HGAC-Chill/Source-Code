USE [DR2_local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefStrings_NationCode]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefStrings_NationCode]
GO

CREATE Proc [dbo].[up_LoadDefStrings_NationCode]
AS

