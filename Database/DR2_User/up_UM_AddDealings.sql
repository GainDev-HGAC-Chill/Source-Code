USE [DR2_User]
IF EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'up_UM_AddDealings'))
BEGIN
	DROP PROCEDURE [dbo].[up_UM_AddDealings]
END
GO
