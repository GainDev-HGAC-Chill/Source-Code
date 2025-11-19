USE [DR2_User]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SelectCharacterLevel_Rank]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_SelectCharacterLevel_Rank]
END
GO

CREATE PROCEDURE [dbo].[up_SelectCharacterLevel_Rank]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : 해당 계정 케릭터의 Level Ranking
// 작 성 자 : YonMy(yonmy@barunsoninter.com)
// 작 성 일 : 2009-01-18
// 최종수정자 : 
// 수 정 일 : 
// 파 일 명 : 
// N O T E : 
//
////////////////////////////////////////////////////////////////////////
*/
(
	@MemberID	uniqueidentifier
,	@Lv			smallint
)
AS
SET NOCOUNT ON
SET XACT_ABORT ON
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

BEGIN
	
	SELECT	COUNT(A.CharacterID)
	FROM	[dbo].[TB_CharacterBasic] AS A
		INNER JOIN [dbo].[TB_CharacterSub] AS B
			ON A.[CharacterID] = B.[CharacterID]
	WHERE	A.[MemberID] = @MemberID AND A.[State] <> 1 AND B.[Lv] > @Lv

END

