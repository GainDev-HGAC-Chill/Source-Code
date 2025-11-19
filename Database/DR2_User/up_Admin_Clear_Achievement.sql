USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Admin_Clear_Achievement]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Admin_Clear_Achievement]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Admin_Clear_Achievement]
@DeleteIdx int,
@ItemNo int,
@MAIL_TITLE nvarchar(max),
@MAIL_TEXT nvarchar(max),
@SENDER_NAME nvarchar(max)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	declare @Delete table(guid uniqueidentifier,idx int,achievements varbinary(max))
	insert into @Delete select characterid, @DeleteIdx,achievements from dbo.TB_UserCharacter_Extern where dbo.udf_CheckAchievementComplete( @DeleteIdx,Achievements) > 0

	begin tran

	DECLARE	@charguid uniqueidentifier, @idx int, @error int, @achievements varbinary(max)

	DECLARE char_cursor CURSOR 
	FOR SELECT guid, idx, achievements FROM @Delete

	OPEN char_cursor

	FETCH NEXT FROM char_cursor INTO @charguid, @idx, @achievements

	WHILE @@FETCH_STATUS = 0
	BEGIN

		declare @Sqr nvarchar(max), @Param nvarchar(max)
		set @Param = '@guid uniqueidentifier'
		set @Sqr = 'update dbo.TB_UserCharacter_Extern set achievements = ' + dbo.udf_MakeClearAchievementHexString(@idx,@achievements)
		+ ' where characterid = @guid'

		EXEC @error = sp_executesql @Sqr, @Param, @charguid
		if @error <> 0 OR @@ERROR <> 0
		begin 
			rollback tran
			return
		end

		if @ItemNo <> 0
		begin		
			DECLARE @ITEMGUID UNIQUEIDENTIFIER
			SET @ITEMGUID = NEWID()
			INSERT INTO [dbo].[TB_UserMail] SELECT NEWID(),@charguid,@charguid,@MAIL_TITLE,@MAIL_TEXT,0,@ITEMGUID,0,GETDATE(),DATEADD(DAY,30,GETDATE()),0,0,0,0,@SENDER_NAME
			INSERT INTO [dbo].[TB_USERITEM] SELECT @ITEMGUID,@charguid,9,0,@ItemNo,1,0,getdate()
		end

		FETCH NEXT FROM char_cursor INTO @charguid, @idx, @achievements

	END 

	CLOSE char_cursor
	DEALLOCATE char_cursor

	commit tran

END


