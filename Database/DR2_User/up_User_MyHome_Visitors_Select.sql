USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_User_MyHome_Visitors_Select]    Script Date: 08/11/2009 20:59:51 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_Visitors_Select]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_Visitors_Select]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_User_MyHome_Visitors_Select]
@OwnerGuid UNIQUEIDENTIFIER,
@StreetNo SMALLINT,
@HouseNo INT
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	SELECT 
		A.[VisitorGuid]
		,B.[Name]
		,A.[VisitTime]
		,C.[StreetNo]
		,C.[HouseNo]
  FROM [dbo].[TB_User_MyHome_Visitors] A 
  LEFT JOIN dbo.TB_CharacterBasic B ON A.VisitorGuid = B.CharacterID
  LEFT JOIN dbo.TB_User_MyHome_Base C ON A.VisitorGuid = C.OwnerGuid
  WHERE A.StreetNo = @StreetNo AND A.HouseNo = @HouseNo
	
END



