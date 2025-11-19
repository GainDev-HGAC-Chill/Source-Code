USE [DR2_Def]
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.UP_LoadDefJobSkill_Recipe') AND [type] IN (N'P'))
BEGIN
	DROP PROCEDURE dbo.UP_LoadDefJobSkill_Recipe
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE dbo.UP_LoadDefJobSkill_Recipe
AS
BEGIN
	SET NOCOUNT ON;
	SELECT [NationCodeStr]
	  ,[f_Recipe_ItemNo]
      ,[f_Order_ID]
      ,[f_01Need_JobSkill_No]
      ,[f_01Need_JobSkill_Expertness]
      ,[f_01Resource_GroupNo]
      ,[f_01Resource_Grade]
      ,[f_01Resource_Count]
      ,[f_02Resource_GroupNo]
      ,[f_02Resource_Grade]
      ,[f_02Resource_Count]
      ,[f_03Resource_GroupNo]
      ,[f_03Resource_Grade]
      ,[f_03Resource_Count]
      ,[f_04Resource_GroupNo]
      ,[f_04Resource_Grade]
      ,[f_04Resource_Count]
      ,[f_NeedMoney]
      ,[f_ResultProbability_No]
      ,[f_ResultProbability_UpRate]
      ,[f_ResultProbability_UpRate_Item]
	  ,[f_Need_ProductPoint]
	  ,[f_Expertness_Gain]
  FROM [dbo].[TB_DefJobSkill_Recipe]
END
GO
