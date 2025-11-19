USE [DR2_Local]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefPremiumArticle]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefPremiumArticle]
GO

CREATE PROCEDURE [dbo].[up_LoadDefPremiumArticle]
AS

BEGIN
	SELECT [ArticleNo],[Type],[Lv]
		  ,[Abil01],[Value01]
		  ,[Abil02],[Value02]
		  ,[Abil03],[Value03]
		  ,[Abil04],[Value04]
		  ,[Abil05],[Value05]
		  ,[Abil06],[Value06]
		  ,[Abil07],[Value07]
		  ,[Abil08],[Value08]
		  ,[Abil09],[Value09]
		  ,[Abil10],[Value10]
	  FROM [dbo].[TB_DefPremiumArticle]

END
GO
