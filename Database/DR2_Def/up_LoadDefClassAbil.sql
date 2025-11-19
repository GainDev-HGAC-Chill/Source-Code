USE [DR2_Def]
GO

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefClassAbil]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefClassAbil]
GO
