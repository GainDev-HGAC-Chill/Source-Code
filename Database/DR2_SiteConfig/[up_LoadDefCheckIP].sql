USE [DR2_SiteConfig]
GO
/****** 개체:  StoredProcedure [dbo].[up_LoadDefCheckIP]    스크립트 날짜: 06/05/2009 01:57:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

ALTER PROCEDURE [dbo].[up_LoadDefCheckIP]
/*
=============================================
Last Update by :	hwoarang
Update date: 2009-06-05
Description:	
PARAMETER :
RETURN :
=============================================
*/
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	SELECT StartIP, EndIP, NationKey, NationName FROM [dbo].[TB_DefCheckIP] with(nolock)
END


/* 2009-07-20 R9459 관련 */
/*
		IP Block 방식이 변경 되면서 더 이상 사용하지 않는 테이블 삭제
		R9559 관련인데, 나중에 스크립트 수정 한 것임.
*/
USE [DR2_SiteConfig]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefCheckIP]    Script Date: 07/20/2009 17:40:59 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefCheckIP]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefCheckIP]
	GO