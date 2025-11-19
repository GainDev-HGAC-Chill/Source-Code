USE [DR2_User]
GO

/****** Object:  StoredProcedure [dbo].[up_Delete_PvPLeague_Team]    Script Date: 05/24/2010 15:29:28 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Delete_PvPLeague_Team]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_Delete_PvPLeague_Team]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Delete_PvPLeague_Team]
		@TeamID [uniqueidentifier]
AS
SET XACT_ABORT ON
SET NOCOUNT ON

SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED

DECLARE @Err INT
SET @Err = 0

BEGIN
	DELETE FROM [dbo].[TB_PvPLeague_Team]
    WHERE [TeamGuid] = @TeamID
	
	IF @@ERROR <> 0
	BEGIN
		SET @Err = 1
	END
END	

RETURN @Err
