USE [DR2_User]
GO

/****** Object:  StoredProcedure [dbo].[up_Insert_PvPLeague_Tournament]    Script Date: 05/24/2010 15:29:28 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Insert_PvPLeague_Tournament]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_Insert_PvPLeague_Tournament]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : PvP Laegue 정보 추가
// 작 성 자 : codenavy
// 작 성 일 : 2009-06-10
// 최종수정자 : 
// 수 정 일 : 
// 담 당 자 : codenavy
// N O T E : 
// 2010-05-24, codenavy PvP Laegue 정보 추가
////////////////////////////////////////////////////////////////////////
*/
CREATE PROCEDURE [dbo].[up_Insert_PvPLeague_Tournament]
(
	@LeagueID [uniqueidentifier],
	@TournamentID [uniqueidentifier],
	@Level [int],
	@Type [int],
	@Mode [int],
	@Time [int]
)
AS
SET XACT_ABORT ON
SET NOCOUNT ON

SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

BEGIN
	DECLARE @NowDate datetime
	SET @NowDate = GetDate()
	INSERT INTO [dbo].[TB_PvPLeague_Tournament] ([LeagueGuid], [TournamentGuid], [LeagueLevel], [GameType], [GameMode], [GameTime], [BeginTime])
		 VALUES (@LeagueID, @TournamentID, @Level, @Type, @Mode, @Time, @NowDate)
	
	UPDATE [dbo].[TB_PvPLeague]
	SET [TounamentGuid] = @TournamentID
       ,[LeagueState] = 1
	WHERE [LeagueGuid] = @LeagueID
END	

