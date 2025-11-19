USE [DR2_User]
IF EXISTS(SELECT * FROM sys.all_objects WHERE object_id = OBJECT_ID(N'up_Post_ConvertToReturnMail'))
BEGIN
	DROP PROCEDURE [dbo].[up_Post_ConvertToReturnMail]
END
GO

/****** Object:  StoredProcedure [dbo].[up_Post_ConvertToReturnMail]    Script Date: 03/31/2009 14:04:37 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[up_Post_ConvertToReturnMail]
@mailguid UNIQUEIDENTIFIER,
@returnmailguid UNIQUEIDENTIFIER
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DECLARE @errVal INT
	SET @errVal = 0

	BEGIN TRAN

	BEGIN TRY

		INSERT INTO dbo.tb_usermail 
		SELECT	@returnmailguid AS [mailguid]
		,[FromGuid]
		,[FromGuid]
		,[Title]
		,[Note]
		,[PaymentType]
		,[ItemGuid]
		,[Money]
		,[SendTime]
		,[LimitTime]
		,0 AS [ReadBit]
		,1 AS [ReturnBit]
		,[AnnexBit]
		,0 AS [PaymentBit]
		,[FromName]
		FROM [dbo].[TB_UserMail] WHERE mailguid = @mailguid

		IF @@error <> 0
		BEGIN 
			SET @errVal = 6
			GOTO __rollback_proc
		END

		DELETE FROM dbo.tb_usermail WHERE mailguid = @mailguid
		IF @@error <> 0 OR @@rowcount = 0
		BEGIN 
			SET @errVal = 6
			GOTO __rollback_proc
		END
		
		COMMIT TRAN

		RETURN @errVal

	END TRY
	BEGIN CATCH

		SET @errVal = 7
		GOTO __rollback_proc
		
	END CATCH

__rollback_proc: -- 트랜잭션 에러

ROLLBACK TRAN

RETURN @errVal

END
GO
