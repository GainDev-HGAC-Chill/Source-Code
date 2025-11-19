USE [DR2_User]
GO

/****** Object:  StoredProcedure [dbo].[up_Set_PvPLeague_TeamIndex]    Script Date: 05/24/2010 15:29:28 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Set_PvPLeague_TeamIndex]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_Set_PvPLeague_TeamIndex]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Set_PvPLeague_TeamIndex]
(
	@TeamID [uniqueidentifier],
	@Index [int]
)
AS
SET XACT_ABORT ON
SET NOCOUNT ON

SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

BEGIN
	IF @TeamID IS NOT NULL	
	BEGIN
		UPDATE [dbo].[TB_PvPLeague_Team]
		SET [TournamentIndex] = @Index
		WHERE [TeamGuid] = @TeamID
	END
END	

