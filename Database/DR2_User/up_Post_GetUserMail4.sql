USE [DR2_User]
GO

IF EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'up_Post_GetUserMail4'))
DROP PROCEDURE [dbo].[up_Post_GetUserMail4]
GO
