USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Couple_Proc_Select]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Couple_Proc_Select]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


/*
////////////////////////////////////////////////////////////////////////
// Lasst Update by : 육정범
// Update date  : 2008-10-21
// Description : 커플 유틸 프로시져
// [PARAMETER] : 
// [RETURN] : 
// [REMARK] :
//	2008-06-30 육정범
//	2008-10-07 Eric Kim : character DB가 두개로 나누어 진것 적용
//				character DB에서 Couple GUID 삭제
//	2008-10-21 육정범 : SELECT, UPDATE 쿼리로 분리
//	2009-07-10 윤상현 : DeleteQuest/SweetHeartQuestTime/CouplePanaltyLimitDate  추가
////////////////////////////////////////////////////////////////////////
*/
CREATE PROCEDURE [dbo].[up_Couple_Proc_Select]
(
	@CharGuid		UNIQUEIDENTIFIER
)
AS
SET NOCOUNT ON
SET XACT_ABORT ON
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

	SELECT
		TB_Couple.[CoupleCharGuid],
		TB_User.[Name],
		TB_Couple.[StartDate],
		TB_Couple.[Status],
		DATEDIFF( DAY, TB_Couple.[StartDate], GETDATE() ) AS DDay,
		TB_Couple.[LimitDate],
		TB_Couple.[DeleteQuest],
		TB_Couple.[SweetHeartQuestTime],
		TB_Couple.[LearnSkill],
		TB_Couple.[CouplePanaltyLimitDate],
		TB_Couple.[ColorGuid],
		TB_Home.StreetNo,
		TB_Home.HouseNo
	FROM dbo.TB_UserCouple AS TB_Couple 
		LEFT JOIN dbo.TB_CharacterBasic AS TB_User ON TB_Couple.CoupleCharGuid = TB_User.CharacterID
		LEFT JOIN dbo.TB_User_MyHome_Base AS TB_Home ON TB_Couple.CoupleCharGuid = TB_Home.OwnerGuid
	WHERE [TB_Couple].[CharacterGuid] = @CharGuid and [TB_Couple].[CharacterGuid] <> '00000000-0000-0000-0000-000000000000'
	RETURN

