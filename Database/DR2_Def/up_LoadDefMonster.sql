USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefMonster]    Script Date: 03/24/2011 16:17:03 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

ALTER Proc [dbo].[up_LoadDefMonster]
AS

begin
	SELECT [f_NationCodeStr], [MonsterNo] ,[Name] ,[Abil01]
		,[Abil02] ,[Abil03] ,[Abil04] ,[Abil05] ,[Abil06]
		,[Abil07] ,[Abil08] ,[Abil09] ,[Abil10] ,[Abil11]
		,[Abil12] ,[Abil13] ,[Abil14] ,[Abil15]
		FROM [dbo].[TB_DefMonster] WITH(NOLOCK)
end
