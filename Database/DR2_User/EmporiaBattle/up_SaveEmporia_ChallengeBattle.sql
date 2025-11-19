USE [DR2_User]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_SaveEmporia_ChallengeBattle]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_SaveEmporia_ChallengeBattle]
GO

CREATE PROCEDURE [dbo].[up_SaveEmporia_ChallengeBattle]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : 엠포리아 쟁탈전 신청
// 작 성 자 : YonMy
// 작 성 일 : 2009-06-10
// 최종수정자 :
// 수 정 일 : 2010-07-11
// 담 당 자 : 심헌섭
// N O T E : 도전방식 변경(경험치->길드골드)에 따라 수정
//
////////////////////////////////////////////////////////////////////////
*/
(
	@EmporiaID uniqueidentifier,
	@BattleID uniqueidentifier,
	@GuildID uniqueidentifier,
	@Cost bigint,
	@RegistDate datetime,
	@State tinyint
)
AS
SET XACT_ABORT ON
SET NOCOUNT ON
SET LOCK_TIMEOUT 3000

DECLARE @Err int
Set @Err = 0

BEGIN TRAN
		
	INSERT INTO [dbo].[TB_Emporia_ChallengeBattle]
	(
		[EmporiaID]
	,	[BattleID]
	,	[GuildID]
	,	[Exp]
	,	[RegistDate]
	,	[State]
	)
	values
	(
		@EmporiaID
	,	@BattleID
	,	@GuildID
	,	@Cost
	,	@RegistDate
	,	@State
	)

	if @@ERROR <> 0
	BEGIN
		Set @Err = 99
		GOTO ErrorHandler		
	END

COMMIT TRAN
SELECT @Err, @Cost
RETURN @Err

ErrorHandler:
ROLLBACK TRAN
SELECT @Err
RETURN @Err
GO
