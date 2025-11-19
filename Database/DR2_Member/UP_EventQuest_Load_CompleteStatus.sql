USE [DR2_Member]
GO

IF EXISTS(SELECT * FROM SYS.OBJECTS WHERE object_id = OBJECT_ID(N'dbo.[UP_EventQuest_Load_CompleteStatus]') AND TYPE in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_EventQuest_Load_CompleteStatus]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2009-08-25
-- Description:	
-- =============================================
CREATE PROCEDURE dbo.[UP_EventQuest_Load_CompleteStatus]
	@RealmNo INT,
	@ExternInt INT
AS
BEGIN
	SET NOCOUNT ON;

	SELECT @ExternInt
	SELECT [f_CharacterGuid] FROM [dbo].[TB_EventQuest_CompleteStatus] WHERE [f_RealmNo] = @RealmNo
END
GO
