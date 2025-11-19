USE DR2_GM
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Procedure Name : UP_Failed_Order
-- Author:		박정현
-- Create date: 2009년 9월 5일
-- Description:	GM_Order 실패 처리. CmdState를 3(실패) 로 변경하고 
--              Errorcode에 에러코드를 기록한다.
-- =============================================


IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.UP_Failed_Order') AND type in (N'P', N'PC'))
DROP PROCEDURE UP_Failed_Order
GO

CREATE PROCEDURE UP_Failed_Order
(
	@OrderGUID		UNIQUEIDENTIFIER,
	@FailedCode		int
)
AS
BEGIN TRAN

DECLARE @Err int;
	SET @Err = 0;
	SET NOCOUNT ON;

	--해당 OderQuery가 존재하는가?
	SELECT CmdGUID
		FROM [dbo].[Tbl_Gm_Order]
		WHERE CmdGUID = @OrderGUID;
		
	--없다면 업데이트 안함.	
	IF @@rowcount = 0
	BEGIN
		SET @Err = 1;
		GOTO rollback_tran;
	END

	--업데이트 하자.
	UPDATE [dbo].[Tbl_Gm_Order]
	   SET CmdState = 3, ErrorCode = @FailedCode, CompleteDate = getdate()
	 WHERE CmdGUID = @OrderGUID


commit_tran:
BEGIN
	COMMIT TRAN
	SELECT @Err
	RETURN @Err
END

rollback_tran:
BEGIN
	ROLLBACK TRAN
	SELECT @Err
END