USE [DR2_Def]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItem2]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefItem2]
GO

CREATE PROCEDURE [dbo].[up_LoadDefItem2]
AS

BEGIN
	SELECT [f_NationCodeStr],[ItemNo] ,[Name] ,[ResNo] ,[Type] ,[Price]
		,[SellPrice] , [Attribute] ,[Gender] ,[LevelLimit]
		,[ClassLimit] ,[f_ClassLimitDisplayFilter], [DraClassLimit] ,[f_DraClassLimitDisplayFilter] 
		,[Abil01] ,[Abil02] ,[Abil03] ,[Abil04],[Abil05] ,[Abil06] ,[Abil07] ,[Abil08] ,[Abil09]
		,[Abil10] ,[Order1],[Order2],[Order3],[CostumeGrade], [f_IsCantShareRental]
		FROM [dbo].[TB_DefItem] WITH(nolock)
	
	SELECT [f_NationCodeStr],[ItemNo] ,[Name] ,[ResNo] ,[Type] ,[Price]
		,[SellPrice] , [Attribute] ,[Gender] ,[LevelLimit]
		,[ClassLimit] ,CONVERT(BIGINT, -1), [DraClassLimit],CONVERT(bigint, -1) 
		,[Abil01] ,[Abil02] ,[Abil03] ,[Abil04],[Abil05] ,[Abil06] ,[Abil07] ,[Abil08] ,[Abil09]
		,[Abil10] ,[Order1],[Order2],[Order3],[CostumeGrade], [f_IsCantShareRental]
		FROM [dbo].[TB_DefItem_home] WITH(nolock)
		
	SELECT [f_NationCodeStr],[ItemNo] ,[Name] ,[ResNo] ,[Type] ,[Price]
		,[SellPrice] , [Attribute] ,[Gender] ,[LevelLimit]
		,[ClassLimit] ,CONVERT(BIGINT, -1) ,[DraClassLimit],CONVERT(bigint, -1)
		,[Abil01] ,[Abil02] ,[Abil03] ,[Abil04],[Abil05] ,[Abil06] ,[Abil07] ,[Abil08] ,[Abil09]
		,[Abil10] ,[Order1],[Order2],[Order3],[CostumeGrade], [f_IsCantShareRental]
		FROM [dbo].[TB_DefItem_Pet] WITH(nolock)
END
GO
