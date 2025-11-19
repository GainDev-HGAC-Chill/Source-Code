USE [DR2_User]
GO

IF EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'up_Post_CheckAndClearMailLimitTime2'))
BEGIN
	DROP PROCEDURE [dbo].[up_Post_CheckAndClearMailLimitTime2]
END
GO
