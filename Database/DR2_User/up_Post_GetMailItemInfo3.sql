USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_GetMailItemInfo3]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Post_GetMailItemInfo3]
