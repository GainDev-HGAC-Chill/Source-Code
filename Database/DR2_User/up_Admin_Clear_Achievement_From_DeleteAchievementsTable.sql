USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Admin_Clear_Achievement_From_DeleteAchievementsTable]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Admin_Clear_Achievement_From_DeleteAchievementsTable]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Admin_Clear_Achievement_From_DeleteAchievementsTable]
@MAIL_TITLE nvarchar(max),
@MAIL_TEXT nvarchar(max),
@SENDER_NAME nvarchar(max)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	begin tran

	DECLARE	@idx int, @error int, @ItemNo int, @DeleteItemNo int

	DECLARE a_cursor CURSOR 
	FOR SELECT saveidx, itemno, deleteitemno FROM dbo.tb_DeleteAchievementsTable

	OPEN a_cursor

	FETCH NEXT FROM a_cursor INTO @idx, @ItemNo, @DeleteItemNo

	WHILE @@FETCH_STATUS = 0
	BEGIN

		delete from dbo.tb_useritem where itemno = @DeleteItemNo
		delete from dbo.TB_UserAchievementFirstComplete where FirstCompleteAchievement = @idx

		EXEC @error = [dbo].[up_Admin_Clear_Achievement] @idx, @ItemNo, @MAIL_TITLE, @MAIL_TEXT, @SENDER_NAME
		if @error <> 0 OR @@ERROR <> 0
		begin 
			rollback tran
			return
		end

		FETCH NEXT FROM a_cursor INTO @idx, @ItemNo, @DeleteItemNo

	END 

	CLOSE a_cursor
	DEALLOCATE a_cursor

	commit tran

END




