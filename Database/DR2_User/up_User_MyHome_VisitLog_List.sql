USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_User_MyHome_VisitLog_List]    Script Date: 08/11/2009 11:53:38 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_VisitLog_List]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_VisitLog_List]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_User_MyHome_VisitLog_List]
@OwnerGuid UNIQUEIDENTIFIER
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    -- Insert statements for procedure here
		SELECT A.[LogGuid]
		  ,A.[VisitorGuid]
		  ,B.[Name]
		  ,A.[VisitorLog]
		  ,A.[LogTime]
		  ,A.[Private]
	  FROM [dbo].[TB_User_MyHome_VisitLog] (nolock) A
	  LEFT JOIN [dbo].[TB_CharacterBasic] (NOLOCK) B
	  ON A.[VisitorGuid] = B.[CharacterId]
	  WHERE A.OwnerGuid = @OwnerGuid

END

