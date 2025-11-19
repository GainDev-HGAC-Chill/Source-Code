USE [DR2_Member]
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_EventQuest_Delete_CompleteStatus]') AND type in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_EventQuest_Delete_CompleteStatus]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE dbo.[UP_EventQuest_Delete_CompleteStatus]
	@RealmNo INT,
	@StartTime DATETIME
AS
BEGIN
	SET NOCOUNT ON;

	DELETE FROM [dbo].[TB_EventQuest_CompleteStatus] WHERE [f_RealmNo] = @RealmNo AND [f_ClearTime] < @StartTime
END
GO
