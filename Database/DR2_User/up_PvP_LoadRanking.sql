USE [DR2_User]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_PvP_LoadRanking]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_PvP_LoadRanking]
GO

CREATE PROCEDURE [dbo].[up_PvP_LoadRanking] 
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : up_PvP_LoadRanking
// 작 성 자 : YonMy(yonmy@barunsoninter.com)
// 작 성 일 : 2009-09-09
// 최종수정자 :
// 수 정 일 : 
// 파 일 명 : 
// N O T E : PvP Ranking Mode
//
////////////////////////////////////////////////////////////////////////
*/
AS
SET NOCOUNT ON
SET XACT_ABORT ON	

DECLARE @Err INT
SET @Err = 0

SELECT	TOP 1000
		B.[CharacterID]
	,	B.[Name]
	,	C.[Class]
	,	C.[Lv]
	,	A.[PvP_Point]
	,	A.[PvP_Win]
	,	A.[PvP_Draw]
	,	A.[PvP_Lose]
	,	A.[PvP_Kill]
	,	A.[PvP_Death]
FROM	[TB_UserCharacter_Extern] AS A
JOIN	[TB_CharacterBasic] AS B	ON A.[CharacterID] = B.[CharacterID]
JOIN	[TB_CharacterSub] AS C	ON A.[CharacterID] = C.[CharacterID]
ORDER BY A.[PvP_Point] DESC, A.[PvP_Win] DESC

RETURN @Err
GO
