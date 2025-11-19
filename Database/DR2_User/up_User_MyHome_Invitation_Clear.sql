USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_User_MyHome_Invitation_Clear]    Script Date: 08/10/2009 20:55:38 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_Invitation_Clear]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_Invitation_Clear]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
create PROCEDURE [dbo].[up_User_MyHome_Invitation_Clear]
@StreetNo SMALLINT,
@HouseNo INT
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	-- 초대장, 방문 기록, 방문 카운트 모두 초기화 시킨다.

	DELETE FROM dbo.TB_User_MyHome_Invitation WHERE StreetNo = @StreetNo AND HouseNo = @HouseNo
	DELETE FROM dbo.TB_User_MyHome_Visitors WHERE  StreetNo = @StreetNo AND HouseNo = @HouseNo
	UPDATE dbo.TB_User_MyHome_Base SET ToDayHitCount = 0, TotalHitCount = 0, TotalVisitLogCount = 0
	WHERE  StreetNo = @StreetNo AND HouseNo = @HouseNo
	
END


