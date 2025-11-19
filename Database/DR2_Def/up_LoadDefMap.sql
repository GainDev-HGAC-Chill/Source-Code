USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefMap]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefMap]
End	
GO

/****** Object:  StoredProcedure [dbo].[up_LoadDefMap]    Script Date: 01/17/2013 18:37:49 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE Proc [dbo].[up_LoadDefMap]
AS

BEGIN

	SET NOCOUNT ON
	SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

	SELECT [f_NationCodeStr],
		[MapNo], [MapKey], [Attribute], [NameNo],
		[XmlPath], [ZoneCX], [ZoneCY], [ZoneCZ],
		[Continent], [HometownNo], [Hidden_Index],
		[Abil01], [Abil02], [Abil03], [Abil04], [Abil05],
		[Recommend_Level], [Recommend_Party],
		[Group_TXT], [LevelLimit_Min], [LevelLimit_Max], [DESCRIPTION_TEXT],
		[PartyBreakIn], [PartyBreakIn_Item], [PartyBreakIn_CashItem]
		FROM [dbo].[TB_DefMap]with(nolock)

	SELECT [f_NationCodeStr], [AbilNo]
		,[Type01] ,[Value01] ,[Type02] ,[Value02]
		,[Type03] ,[Value03] ,[Type04] ,[Value04]
		,[Type05] ,[Value05] ,[Type06] ,[Value06]
		,[Type07] ,[Value07] ,[Type08] ,[Value08]
		,[Type09] ,[Value09] ,[Type10] ,[Value10]
		FROM [dbo].[TB_DefMapAbil]with(nolock)
		
	SELECT [MapNo], [MissionNo],
		[ConnetedMapNo01],[ConnetedMapNo02],[ConnetedMapNo03],
		[ConnetedMapNo04],[ConnetedMapNo05]
	 FROM [dbo].[TB_DefMapToMission]with(nolock)
		
END