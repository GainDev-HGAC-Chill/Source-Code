USE [DR2_Member]
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_EventQuest_Update_Status]') AND type in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_EventQuest_Update_Status]
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
CREATE PROCEDURE dbo.[UP_EventQuest_Update_Status]
	@RealmNo INT,
	@Status INT,
	@Enable INT
AS
BEGIN
	SET NOCOUNT ON;

	IF EXISTS(SELECT 1 FROM [dbo].[TB_EventQuest_Status] WHERE [f_RealmNo] = @RealmNo)
	BEGIN
		UPDATE [dbo].[TB_EventQuest_Status]
		SET [f_Status] = @Status
		WHERE [f_RealmNo] = @RealmNo
	END
	ELSE
	BEGIN
		INSERT INTO [dbo].[TB_EventQuest_Status]
		([f_RealmNo],[f_Enable],[f_Status])
		VALUES (@RealmNo,@Enable,@Status)
	END
END
GO
