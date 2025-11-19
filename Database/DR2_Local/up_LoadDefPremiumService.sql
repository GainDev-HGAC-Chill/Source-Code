USE [DR2_Local]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefPremiumService]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefPremiumService]
GO

CREATE PROCEDURE [dbo].[up_LoadDefPremiumService]
AS

BEGIN
	SELECT [ServiceNo],[Title],[ServiceType],[Grade],[UseDate]
		  ,[Article01],[Article02],[Article03],[Article04],[Article05],[Article06],[Article07],[Article08],[Article09],[Article10]
		  ,[Article11],[Article12],[Article13],[Article14],[Article15],[Article16],[Article17],[Article18],[Article19],[Article20]
		  ,[Article21],[Article22],[Article23],[Article24],[Article25],[Article26],[Article27],[Article28],[Article29],[Article30]
	  FROM [dbo].[TB_DefPremiumService]
END
GO
