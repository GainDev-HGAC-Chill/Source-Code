USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefTransTower]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefTransTower]
GO

CREATE PROCEDURE [dbo].[up_LoadDefTransTower]
AS

BEGIN
	SELECT 
			[ID]
		,	[Sort]
		,	[GroundNo]
		,	[Spawn]
		,	[Price]
		,	[NameNo]
	FROM [dbo].[TB_DefTransTower]
	WITH(NOLOCK)
END
