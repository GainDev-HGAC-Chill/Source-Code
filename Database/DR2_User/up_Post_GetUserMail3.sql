USE [DR2_User]
IF EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'up_Post_GetUserMail3'))
BEGIN
	DROP PROCEDURE [dbo].[up_Post_GetUserMail3]
END
GO
