USE [DR2_User]
GO

/****** Object:  StoredProcedure [dbo].[up_Load_PvPLeague]    Script Date: 05/24/2010 15:29:28 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Load_PvPLeague]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_Load_PvPLeague]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Load_PvPLeague]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : PvP Laegue 불러오기(서버On시에 한번 사용)
// 작 성 자 : codenavy
// 작 성 일 : 2009-06-10
// 최종수정자 : 
// 수 정 일 : 
// 담 당 자 : codenavy
// N O T E : 
// 2010-05-24, codenavy PvP Laegue 기능 정보 로드하게 추가
////////////////////////////////////////////////////////////////////////
*/
AS
SET XACT_ABORT ON
SET NOCOUNT ON

SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

BEGIN
DECLARE @Err int

SET @Err = 0
	-- 1. TB_PvPLeague
	SELECT [LeagueGuid]
		  ,[TounamentGuid]
		  ,[LeagueState]
		  ,[Session]
		  ,[RegistDate]
	FROM [dbo].[TB_PvPLeague]
	
	--2. SELECT TOP DATA
	SELECT TOP 1 
		   [LeagueGuid]
		  ,[Session]
	FROM [dbo].[TB_PvPLeague]
	ORDER BY [RegistDate] DESC
	
	RETURN @Err
END	

