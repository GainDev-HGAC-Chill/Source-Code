USE [DR2_User]
GO

/****** Object:  StoredProcedure [dbo].[up_Set_PvPLeague_State]    Script Date: 05/24/2010 15:29:28 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Set_PvPLeague_State]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_Set_PvPLeague_State]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Set_PvPLeague_State]
(
	@LeagueID [uniqueidentifier],
	@State [int]
)
AS
SET XACT_ABORT ON
SET NOCOUNT ON

SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

BEGIN
	IF @LeagueID IS NOT NULL	
	BEGIN
		UPDATE [dbo].[TB_PvPLeague]
		SET [LeagueState] = @State
		WHERE [LeagueGuid] = @LeagueID
	END
	
	SELECT [LeagueState]
    FROM [dbo].[TB_PvPLeague]
	WHERE [LeagueGuid] = @LeagueID
END	

