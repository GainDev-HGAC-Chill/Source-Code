USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_VisitLog_Delete]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_VisitLog_Delete]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_User_MyHome_VisitLog_Delete]
@LogGuid UNIQUEIDENTIFIER,
@OwnerGuid UNIQUEIDENTIFIER
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	DELETE FROM dbo.TB_User_MyHome_VisitLog WHERE LogGuid = @logguid and (OwnerGuid = @OwnerGuid or VisitorGuid = @OwnerGuid)

	IF 0 < @@ROWCOUNT
	BEGIN
		SELECT 0
	END
	ELSE
	BEGIN
		SELECT 1
	END

END

