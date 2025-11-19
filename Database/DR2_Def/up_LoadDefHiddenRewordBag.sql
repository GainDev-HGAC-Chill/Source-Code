USE [DR2_Def]
GO

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefHiddenRewordBag]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefHiddenRewordBag]
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefHiddenRewordBag]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [up_LoadDefHiddenRewordBag]
// 작 성 자 : 
// 작 성 일 : 
// 최종수정자 :
// 수 정 일 : 
// 담 당 자 : 
// N O T E : 
//	2010-01-19, 윤상현
////////////////////////////////////////////////////////////////////////
*/
AS
BEGIN
	SET NOCOUNT ON;

	SELECT [RewordNo],[ContainerNo],[RarityCtrl],[PlusUpCtrl] FROM [dbo].[TB_DefHiddenRewordBag]
END

GO
