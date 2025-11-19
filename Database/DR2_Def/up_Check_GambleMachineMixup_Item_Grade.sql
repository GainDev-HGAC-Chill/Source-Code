USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Check_GambleMachineMixup_Item_Grade]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Check_GambleMachineMixup_Item_Grade]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Check_GambleMachineMixup_Item_Grade]
AS
BEGIN

	SET NOCOUNT ON;

	SELECT A.Idx,A.[Coin],B.costumegrade,B.memo
	  FROM dr2_local.[dbo].[TB_DefGambleMachine] A 
	left join dbo.tb_defitem B on A.itemno = B.Itemno
	where a.coin >= 11 and a.coin - 10 != costumegrade order by coin

END
