USE DR2_Def
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.UP_LoadDefBattleSquare') AND [type] = N'P')
BEGIN
	DROP PROCEDURE dbo.UP_LoadDefBattleSquare
END
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: 2009-12-08
-- Description:	
-- =============================================
CREATE PROCEDURE dbo.[UP_LoadDefBattleSquare]
AS
BEGIN
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	SELECT [f_ItemNo],[f_EffectNo1],[f_EffectNo2],[f_EffectNo3],[f_MinimapIconNo] FROM [dbo].[TB_DefBS_Item]
	
	SELECT [f_TeamRewardIdx],[f_PointMin],[f_ItemNo1],[f_ItemCount1],[f_ItemNo2],[f_ItemCount2]		FROM [dbo].[TB_DefBS_TeamReward]
	SELECT [f_PtRewardIdx],[f_PointMin],[f_ItemNo1],[f_ItemCount1],[f_ItemNo2],[f_ItemCount2]		FROM [dbo].[TB_DefBS_PtReward]
	SELECT [f_LvRewardIdx],[f_LevelMin],[f_ItemNo1],[f_ItemCount1],[f_ItemNo2],[f_ItemCount2]		FROM [dbo].[TB_DefBS_LvReward]
	SELECT [f_BnsRewardIdx],[f_UserCountMin],[f_ItemNo1],[f_ItemCount1],[f_ItemNo2],[f_ItemCount2]	FROM [dbo].[TB_DefBS_BnsReward]

	SELECT 
		[f_NationCodeStr],
		[f_BS_GAME_IDX],
		[f_Ch_IsUse],
		[f_Ch_ChannelTitle],
		[f_Ch_LevelMin],
		[f_Ch_LevelMax],
		[f_Ch_MaxUser],
		[f_Ch_W_Sunday],
		[f_Ch_W_Monday],
		[f_Ch_W_Tuesday],
		[f_Ch_W_Wednesday],
		[f_Ch_W_Thursday],
		[f_Ch_W_Friday],
		[f_Ch_W_Saturday],
		[f_Ch_StartTime],
		[f_Ch_GameSec],
		[f_Game_GroundNo],
		[f_Game_PreOpenSec],
		[f_TeamRewardIdx],
		[f_PtRewardIdx],
		[f_LvRewardIdx],
		[f_BnsRewardIdx],
		[f_MapBagItemGroundNo],
		[f_GenGroupGroundNo],
		[f_MonsterBagControlNo]
	FROM [dbo].[TB_DefBS_Game]
END
GO
