USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[UP_LoadDefAchievements]    Script Date: 10/22/2009 18:54:41 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LoadDefAchievements]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[UP_LoadDefAchievements]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[UP_LoadDefAchievements]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [Idx]
		  ,[f_NationCodeStr]
		  ,[Category]
		  ,[TitleNo]
		  ,[DiscriptionNo]
		  ,[Type]
		  ,[Value]
		  ,[ItemNo]
		  ,[SaveIdx]
		  ,[RankPoint]
		  ,[Level]
		  ,[SYear]
		  ,[SMonth]
		  ,[SDay]
		  ,[SHour]
		  ,[SMinute]
		  ,[EYear]
		  ,[EMonth]
		  ,[EDay]
		  ,[EHour]
		  ,[EMinute]
		  ,[UseTime]
		  ,[IsUse]
		  ,[GroupNo]
		  ,[CustomValue]
	  FROM [dbo].[TB_DefAchievements]

END



