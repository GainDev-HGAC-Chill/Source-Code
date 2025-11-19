USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefItemMaking]    Script Date: 06/25/2009 13:53:49 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemMaking]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefItemMaking]
GO

USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefItemMaking]    Script Date: 06/25/2009 13:53:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE Proc [dbo].[up_LoadDefItemMaking]
AS

begin
	SELECT [No] ,[MakingTypeNo] ,[ContentStringNo] ,[NeedMoney] ,[NeedElementsNo]
		,[NeedCountControlNo] ,[SuccessRateControlNo] ,[ResultControlNo]
		,[Elements01] ,[CountControl01]
		,[Elements02] ,[CountControl02] ,[Elements03] ,[CountControl03] ,[Elements04]
		,[CountControl04] ,[Elements05] ,[CountControl05] ,[Elements06] ,[CountControl06]
		,[Elements07] ,[CountControl07] ,[Elements08] ,[CountControl08] ,[Elements09]
		,[CountControl09] ,[Elements10] ,[CountControl10],[RarityControl]
		FROM [dbo].[TB_DefItemMaking] WITH(NOLOCK)
end







