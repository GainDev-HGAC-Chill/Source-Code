USE [DR2_Def]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[TB_DefExpeditionNpc]'))
	DROP PROCEDURE [dbo].[up_LoadDefExpeditionNpc]
GO

CREATE Proc [dbo].[up_LoadDefExpeditionNpc]
AS
SET Nocount On;
begin

	SELECT --[IDX],
		  [NpcGuid]
		  --,[Memo]
		  ,[MapNo]
		  ,[MinPlayerCnt]
		  ,[MaxPlayerCnt]
		  ,[NeedtemNo]
		  ,[NeedItemCnt]
		  ,[DungeonStringNo]
		  ,[ImgPath]
		  ,[DungeonInfoStringNo]
	  FROM [dbo].[TB_DefExpeditionNpc]
end