USE [DR2_User]
GO

/****** Object:  StoredProcedure [dbo].[up_Insert_PvPLeague_Team]    Script Date: 05/24/2010 15:29:28 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Insert_PvPLeague_Team]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_Insert_PvPLeague_Team]
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
// 2010-05-24, codenavy PvPLeague_Team 정보 추가
////////////////////////////////////////////////////////////////////////
*/
CREATE PROCEDURE [dbo].[up_Insert_PvPLeague_Team]
		@LeagueID [uniqueidentifier],
		@TeamID [uniqueidentifier],
		@strTeamName [nvarchar](100),
		@Index [int],
		@UserID1 [uniqueidentifier],
		@UserID2 [uniqueidentifier],
		@UserID3 [uniqueidentifier],
		@UserID4 [uniqueidentifier]
AS
SET XACT_ABORT ON
SET NOCOUNT ON

SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

BEGIN
	DECLARE @NowDate datetime
	SET @NowDate = GetDate()
	
	INSERT INTO [dbo].[TB_PvPLeague_Team] ([LeagueGuid], [TeamGuid], [TeamName], [UserGuid1], [UserGuid2], [UserGuid3], [UserGuid4], [RegistDate], [TournamentIndex], [LeagueLevel], [Point])
		 VALUES (@LeagueID, @TeamID, @strTeamName, @UserID1, @UserID2, @UserID3, @UserID4, @NowDate, @Index, 1, 0)
	
	SELECT @TeamID
END	

