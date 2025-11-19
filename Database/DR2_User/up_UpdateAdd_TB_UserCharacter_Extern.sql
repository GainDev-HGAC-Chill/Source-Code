USE [DR2_User]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo][up_UpdateAdd_TB_UserCharacter_Extern]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_UpdateAdd_TB_UserCharacter_Extern] 
GO

CREATE PROC [dbo].[up_UpdateAdd_TB_UserCharacter_Extern] 
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : up_UpdateAdd_TB_UserCharacter_Extern
// 작 성 자 : YonMy(yonmy@barunsoninter.com)
// 작 성 일 : 2009-04-02
// 최종수정자 :
// 수 정 일 : 
// 파 일 명 : 
// N O T E : 캐릭 테이블의 해당 컬럼값을 증가시킨다.
//
////////////////////////////////////////////////////////////////////////
*/
	@CharacterID uniqueidentifier,
	@ValueType nvarchar(20),
	@Value bigint
AS
SET NOCOUNT ON
SET XACT_ABORT ON	

DECLARE @SQL nvarchar(1000)
DECLARE @SQL_Params nvarchar(100)

SET @SQL = N'UPDATE dbo.TB_UserCharacter_Extern Set ' + @ValueType + ' = [' + @ValueType + '] + @Value Where CharacterID = @CharacterID'
SET @SQL_Params = N'@Value bigint, @CharacterID uniqueidentifier'                         

EXEC sp_executesql @SQL, @SQL_Params, @Value, @CharacterID
GO
