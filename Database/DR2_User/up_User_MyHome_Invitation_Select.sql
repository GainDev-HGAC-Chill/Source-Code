USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_User_MyHome_Invitation_Select]    Script Date: 08/10/2009 20:54:22 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_Invitation_Select]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_Invitation_Select]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_User_MyHome_Invitation_Select]
@OwnerGuid UNIQUEIDENTIFIER
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	DECLARE @CurDate DATETIME
	SET @CurDate = GETDATE()

	SELECT 
	C.[Name],
	A.StreetNo,
	A.HouseNo,
	A.LimitTime
	FROM
	dbo.TB_User_MyHome_Invitation A
	INNER JOIN 
	dbo.TB_User_MyHome_Base B
	ON A.StreetNo = B.StreetNo AND A.HouseNo = B.HouseNo
	LEFT JOIN dbo.TB_CharacterBasic C
	ON B.OwnerGuid = C.CharacterID
	WHERE A.OwnerGuid = @OwnerGuid AND A.Used = 0 AND LimitTime > @CurDate
	
END

