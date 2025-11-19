USE [DR2_Local]
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefCashShop7]'))
BEGIN
	DROP PROCEDURE [dbo].[UP_LoadDefCashShop7]
END
GO