USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Update_OXQuizEventState]    Script Date: 06/22/2009 14:13:06 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_OXQuizEventState]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_OXQuizEventState]
go

/****** Object:  StoredProcedure [dbo].[up_Update_OXQuizEventState]    Script Date: 06/22/2009 14:13:09 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Update_OXQuizEventState]
@EventID INT,
@State TINYINT
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	IF NOT EXISTS(SELECT 1 FROM dbo.tb_OXQuizEventState WHERE EventID = @EventID)
	BEGIN
		INSERT INTO dbo.TB_OXQuizEventState (EventID,State) VALUES(@EventID,@State)
	END
	ELSE
	BEGIN
		UPDATE dbo.TB_OXQuizEventState SET State = @State WHERE EventID = @EventID
	END

END
