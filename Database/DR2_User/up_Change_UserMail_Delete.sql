USE DR2_USER
GO
/****** 개체:  StoredProcedure [dbo].[up_Change_UserMail_Delete]    스크립트 날짜: 07/17/2009 11:24:24 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Change_UserMail_Delete]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Change_UserMail_Delete]
GO

/****** ü:  StoredProcedure [dbo].[up_Change_UserMail_Delete]    ũƮ ¥: 07/17/2009 11:24:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Change_UserMail_Delete]') AND type in (N'P', N'PC'))
BEGIN
EXEC dbo.sp_executesql @statement = N'CREATE PROCEDURE [dbo].[up_Change_UserMail_Delete]
	@MailGuid	uniqueidentifier,
	@ReVal	INT	OUTPUT
AS
BEGIN
	SET NOCOUNT ON

	DECLARE @ItemGUID UNIQUEIDENTIFIER

	SET @ItemGUID = ( SELECT ItemGUID FROM TB_UserMail WHERE MailGuid = @MailGuid )

	BEGIN TRAN
		DELETE FROM dbo.TB_UserItem WHERE ItemGUID = @ItemGUID AND InvType = 9
		IF @@error <> 0 GOTO _errorMessage

		IF @@ROWCOUNT > 0
		BEGIN
			DELETE FROM dbo.TB_UserItem_Enchant WHERE ItemGUID = @ItemGUID
			IF @@error <> 0 GOTO _errorMessage

			DELETE FROM [dbo].[TB_ExpCard]  WHERE ItemGUID = @ItemGUID
			IF @@error <> 0 GOTO _errorMessage
		END


		DELETE FROM dbo.TB_UserMail WHERE MailGuid = @MailGuid

		IF @@error <> 0 GOTO _errorMessage

		

	COMMIT TRAN

	SET @ReVal = 0
	RETURN	
	
_errorMessage:
	ROLLBACK TRAN

	SET @ReVal = 1
	RETURN

END'
END
GO
