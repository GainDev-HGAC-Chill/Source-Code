USE [DR2_User]
IF EXISTS(SELECT * FROM sys.all_objects WHERE [object_id] = OBJECT_ID(N'[dbo].[up_Post_RecvAnnex_Payment]'))
BEGIN
	DROP PROCEDURE [dbo].[up_Post_RecvAnnex_Payment]
END
