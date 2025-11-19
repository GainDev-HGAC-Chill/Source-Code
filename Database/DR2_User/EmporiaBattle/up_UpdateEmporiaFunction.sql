USE [DR2_User]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UpdateEmporiaFunction]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_UpdateEmporiaFunction]
GO

CREATE PROCEDURE [dbo].[up_UpdateEmporiaFunction]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : 엠포리아 기능 업데이트
// 작 성 자 : YonMy
// 작 성 일 : 2009-07-06
// 최종수정자 : 
// 수 정 일 : 
// 담 당 자 : YonMy
// N O T E : 
////////////////////////////////////////////////////////////////////////
*/
(
	@EmporiaID		uniqueidentifier,
	@Grade			tinyint,
	@FunctionNo		smallint,
	@ExtValue		bigint
)
AS
SET XACT_ABORT ON
SET NOCOUNT ON

SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

DECLARE @Ret int
SET @Ret = 0

BEGIN
	
	UPDATE	[dbo].[TB_Emporia_Function]
	SET		[ExtValue] = @ExtValue
	WHERE	[EmporiaID] = @EmporiaID AND [Grade] = @Grade AND [FunctionNo] = @FunctionNo

END
RETURN @Ret
GO