USE DR2_User
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Load_Guild_Applicant_List]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Load_Guild_Applicant_List]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		김동환
-- Create date: 2010.04.27
-- Description:	길드가입 신청자 리스트
-- =============================================
CREATE PROCEDURE [dbo].[up_Load_Guild_Applicant_List]
AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT 
		Applicant.[GuildGuid], Applicant.[CharacterGuid],
		CharacterBasicInfo.[Name], CharacterInfo.[Lv], CharacterInfo.[Class],
		Applicant.[Message], Applicant.[RequestTime], Applicant.[IsAcceptanceState], Applicant.[GuildEntranceFee]
	FROM dbo.TB_Guild_Applicant AS Applicant
		
	JOIN dbo.TB_CharacterSub AS CharacterInfo
	ON Applicant.CharacterGuid = CharacterInfo.CharacterID
	
	JOIN dbo.TB_CharacterBasic AS CharacterBasicInfo
	ON Applicant.CharacterGuid = CharacterBasicInfo.CharacterID
	
	SET NOCOUNT OFF;
END
GO