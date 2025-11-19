USE [DR2_User]
GO

SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON

/****** Object:  StoredProcedure [dbo].[up_Couple_Proc_UpdateDateInfo]    Script Date: 07/10/2009 15:23:52 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Couple_Proc_UpdateDateInfo]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_Couple_Proc_UpdateDateInfo]
END
GO

/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : up_Couple_Proc_UpdateDateInfo
// 작 성 자 : 윤 상 현
// 작 성 일 : 2009-7-10
// 최종수정자 : 
// 수 정 일 : 
// 파 일 명 : 
// N O T E : 테이블의 해당 컬럼값을 변경한다.
//
////////////////////////////////////////////////////////////////////////
*/

CREATE PROC [dbo].[up_Couple_Proc_UpdateDateInfo] 
	@CharacterID uniqueidentifier,
	@DateValue DATETIME = NULL
AS
SET NOCOUNT ON
SET XACT_ABORT ON	

UPDATE [dbo].[TB_UserCouple]
	SET 
		[CouplePanaltyLimitDate]	= @DateValue
	WHERE
		[CharacterGuid]				= @CharacterID

GO
