IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UPDATE_TB_UserCharacter_Point_LogOut]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_UPDATE_TB_UserCharacter_Point_LogOut]
END 
GO

CREATE PROC [dbo].[up_UPDATE_TB_UserCharacter_Point_LogOut] 
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : up_UPDATE_TB_UserCharacter_Point_LogOut
// 작 성 자 : acepm83
// 작 성 일 : 2010-08-13
// 최종수정자 :
// 수 정 일 : 
// 파 일 명 : 
// N O T E : 캐릭터 로그 아웃시 저장되야 하는 Rank 테이블 정보 UPDATE
//
////////////////////////////////////////////////////////////////////////
*/
	@CharacterID uniqueidentifier,
	@ValueType nvarchar(25),
	@Value int
AS
SET NOCOUNT ON
SET XACT_ABORT ON

BEGIN

	DECLARE @SQL nvarchar(1000)
	DECLARE @SQL_Params nvarchar(100)

	SET @SQL = N'UPDATE dbo.TB_UserCharacter_Point Set ' + @ValueType + ' = + @Value Where CharacterID = @CharacterID'
	SET @SQL_Params = N'@Value int, @CharacterID uniqueidentifier'

	EXEC sp_executesql @SQL, @SQL_Params, @Value, @CharacterID
end

