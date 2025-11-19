USE [DR2_Member]
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_EventQuest_Insert_CompleteStatus]') AND TYPE IN (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_EventQuest_Insert_CompleteStatus]
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
CREATE PROCEDURE dbo.[UP_EventQuest_Insert_CompleteStatus]
	@RealmNo INT,
	@CharGuid UNIQUEIDENTIFIER,
	@CharName NVARCHAR(20),
	@ClearTime DATETIME
AS
BEGIN
	SET NOCOUNT ON;

	INSERT INTO [dbo].[TB_EventQuest_CompleteStatus]
           ([f_RealmNo]
           ,[f_CharacterGuid]
           ,[f_CharacterName]
           ,[f_ClearTime])
     VALUES
           (@RealmNo
           ,@CharGuid
           ,@CharName
           ,@ClearTime)
END
GO
