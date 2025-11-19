USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Admin_Clear_Achievement_UserList]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Admin_Clear_Achievement_UserList]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Admin_Clear_Achievement_UserList]
@MAIL_TITLE nvarchar(max),
@MAIL_TEXT nvarchar(max),
@SENDER_NAME nvarchar(max)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	begin tran

	delete from dbo.tb_useritem where itemno in ( select deleteitemno from dbo.tb_DeleteAchievementsTable )
	delete from dbo.TB_UserAchievementFirstComplete where FirstCompleteAchievement in ( select saveidx from dbo.tb_DeleteAchievementsTable )

	DECLARE	@charguid uniqueidentifier, @achievements varbinary(max), @charcount int

	set @charcount = 0

	DECLARE char_cursor CURSOR 
	FOR SELECT characterid, achievements FROM [dbo].[TB_UserCharacter_Extern]

	OPEN char_cursor

	FETCH NEXT FROM char_cursor INTO @charguid, @achievements

	WHILE @@FETCH_STATUS = 0
	BEGIN

		print '[' + cast(@charcount as nvarchar(max)) + '] reset achievement guid: ' + cast(@charguid as nvarchar(max))

		set @charcount = @charcount + 1

		DECLARE	@idx int, @ItemNo int, @DeleteItemNo int, @StrAchievement nvarchar(max)

		set @StrAchievement = sys.fn_varbintohexstr(@achievements)

		DECLARE a_cursor CURSOR 
		FOR SELECT SaveIdx, itemno, deleteitemno FROM dbo.tb_DeleteAchievementsTable

		OPEN a_cursor

		FETCH NEXT FROM a_cursor INTO @idx, @ItemNo, @DeleteItemNo

		WHILE @@FETCH_STATUS = 0
		BEGIN

			if dbo.udf_CheckAchievementComplete( @idx, @StrAchievement) > 0
			begin

				set @StrAchievement = dbo.udf_MakeClearAchievementHexString(@idx,@StrAchievement)

				if @ItemNo <> 0
				begin		
					DECLARE @ITEMGUID UNIQUEIDENTIFIER
					SET @ITEMGUID = NEWID()
					INSERT INTO [dbo].[TB_UserMail] SELECT NEWID(),@charguid,@charguid,@MAIL_TITLE,@MAIL_TEXT,0,@ITEMGUID,0,GETDATE(),DATEADD(DAY,30,GETDATE()),0,0,0,0,@SENDER_NAME
					INSERT INTO [dbo].[TB_USERITEM] SELECT @ITEMGUID,@charguid,9,0,@ItemNo,1,0,getdate()
				end

			end

			FETCH NEXT FROM a_cursor INTO @idx, @ItemNo, @DeleteItemNo

		END 

		CLOSE a_cursor
		DEALLOCATE a_cursor

		declare @Sqr nvarchar(max), @Param nvarchar(max), @error int
		set @Param = '@guid uniqueidentifier'
		set @Sqr = 'update dbo.TB_UserCharacter_Extern set achievements = ' + @StrAchievement + ' where characterid = @guid'

		EXEC @error = sp_executesql @Sqr, @Param, @charguid
		if @error <> 0 OR @@ERROR <> 0
		begin 
			CLOSE char_cursor
			DEALLOCATE char_cursor
			rollback tran
			return
		end

		FETCH NEXT FROM char_cursor INTO @charguid, @achievements

	END 

	CLOSE char_cursor
	DEALLOCATE char_cursor

	commit tran

END











