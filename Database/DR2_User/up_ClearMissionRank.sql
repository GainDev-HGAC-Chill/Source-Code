USE [DR2_User]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_ClearMissionRank]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_ClearMissionRank]
GO

CREATE PROCEDURE [dbo].[up_ClearMissionRank]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [up_ClearMissionRank]
// 작 성 자 : YonMy
// 작 성 일 : 2009-03-31
// 최종수정자 : 
// 수 정 일 : 
// 담 당 자 : YonMy
// N O T E : 
//	      이훈 : Def_Mission 참조 하는것 삭제 
////////////////////////////////////////////////////////////////////////
*/
(
	@No		int
)
AS
Set Nocount on
Set Xact_Abort On

DECLARE @Err int
Set @Err = 0

BEGIN
	DECLARE @MissionKey int
	SET @MissionKey = @No
	
	IF @No < 0
	BEGIN
		TRUNCATE TABLE [dbo].[TB_Mission_Rank]
	END
	ELSE
	BEGIN
		DELETE FROM [dbo].[TB_Mission_Rank]
		WHERE [MissionKey] = @No
	END
END	
RETURN @Err
