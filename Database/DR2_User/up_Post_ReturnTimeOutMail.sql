USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Post_ReturnTimeOutMail]    Script Date: 12/21/2009 14:36:19 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_ReturnTimeOutMail]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Post_ReturnTimeOutMail]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Post_ReturnTimeOutMail]
@charguid UNIQUEIDENTIFIER
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	SET XACT_ABORT ON

	DECLARE @curdate DATETIME
	SET @curdate = DATEADD(day,3,GETDATE())

	BEGIN TRAN 

	BEGIN TRY

		INSERT INTO dbo.tb_usermail 
		([MailGuid]
   		,[FromGuid]
   		,[ToGuid]
   		,[Title]
   		,[Note]
   		,[PaymentType]
   		,[ItemGuid]
   		,[Money]
   		,[SendTime]
   		,[LimitTime]
   		,[ReadBit]
   		,[ReturnBit]
   		,[AnnexBit]
   		,[PaymentBit]
		,[FromName])

		(SELECT	NEWID() AS [mailguid]
		,[FromGuid]
		,[FromGuid]
		,[Title]
		,[Note]
		,[PaymentType]
		,[ItemGuid]
		,[Money]
		,[SendTime]
		,@curdate
		,0 AS [ReadBit]
		,1 AS [ReturnBit]
		,[AnnexBit]
		,0 AS [PaymentBit]
		,[FromName]
		FROM [dbo].[TB_UserMail]
		WHERE 
		(toguid = @charguid OR fromguid = @charguid) AND 
		LimitTime < GETDATE() AND annexbit = 0 AND 
		(itemguid <> '00000000-0000-0000-0000-000000000000' OR money <> 0) AND ReturnBit = 0)
		OPTION (KEEPFIXED PLAN)

		DELETE FROM dbo.tb_usermail WHERE (toguid = @charguid OR fromguid = @charguid) AND 
		LimitTime < GETDATE()
		OPTION (KEEPFIXED PLAN)

		COMMIT TRAN 

	END TRY
	BEGIN CATCH

		ROLLBACK TRAN

	END CATCH

END

