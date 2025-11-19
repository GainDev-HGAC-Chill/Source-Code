USE [DR2_Def]
GO

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefClassAbil_NationCode]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefClassAbil_NationCode]
GO

CREATE Proc [dbo].[up_LoadDefClassAbil_NationCode]
AS

begin
	SELECT [NationCodeStr], [AbilNo]
		,[Type01] ,[Value01] ,[Type02] ,[Value02]
		,[Type03] ,[Value03] ,[Type04] ,[Value04]
		,[Type05] ,[Value05] ,[Type06] ,[Value06]
		,[Type07] ,[Value07] ,[Type08] ,[Value08]
		,[Type09] ,[Value09] ,[Type10] ,[Value10]
		FROM [dbo].[TB_DefClassAbil] with(nolock)

	SELECT [NationCodeStr], [AbilNo]
		,[Type01] ,[Value01] ,[Type02] ,[Value02]
		,[Type03] ,[Value03] ,[Type04] ,[Value04]
		,[Type05] ,[Value05] ,[Type06] ,[Value06]
		,[Type07] ,[Value07] ,[Type08] ,[Value08]
		,[Type09] ,[Value09] ,[Type10] ,[Value10]
		FROM [dbo].[TB_DefClassAbil_Monster] with(nolock)

	SELECT [NationCodeStr], [AbilNo]
		,[Type01] ,[Value01] ,[Type02] ,[Value02]
		,[Type03] ,[Value03] ,[Type04] ,[Value04]
		,[Type05] ,[Value05] ,[Type06] ,[Value06]
		,[Type07] ,[Value07] ,[Type08] ,[Value08]
		,[Type09] ,[Value09] ,[Type10] ,[Value10]
		FROM [dbo].[TB_DefClassAbil_Skill] with(nolock)
end







