USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemPlusUpControl]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefItemPlusUpControl]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefItemPlusUpControl]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [up_LoadDefItemPlusUpControl]
// 작 성 자 : YonMy(yonmy@barunsoninter.com)
// 작 성 일 : 2009-07-08
// 최종수정자 : 
// 수 정 일 : 
// 담 당 자 : 
// N O T E : 
//	
////////////////////////////////////////////////////////////////////////
*/
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;


SELECT [TypeNo]
      ,[SuccessRateControlNo_Low]
      ,[SuccessRateControlNo_High]
FROM [dbo].[TB_DefItemPlusUpControl]
WITH (NOLOCK)

END


