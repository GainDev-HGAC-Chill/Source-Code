USE DR2_Def
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.UP_LoadDefJobSkill_ItemUpgrade') and [type] IN (N'P'))
BEGIN
	DROP PROCEDURE dbo.UP_LoadDefJobSkill_ItemUpgrade
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
CREATE PROCEDURE dbo.UP_LoadDefJobSkill_ItemUpgrade
AS
BEGIN
	SET NOCOUNT ON;
	SELECT
	[f_ItemNo],	
	[f_Grade],
	[f_Resource_GroupNo],
	[f_Upgrade_Count],
	[f_Upgrade_TimeSec],
	[f_Basic_Expertness],
	[f_GatherType],
	[f_Machine_UseDuration],
	[f_ResultProbability_No],
	[f_Resource_ProbabilityUp],
	[f_ErrorStateTime_AbsoluteSec],
	[f_ErrorState_MaxProbability],
	[f_ErrorState_Probability],
	[f_Need_SaveIdx],
	[f_Resource_Type],
	[f_ExpertnessUpVolume]
	FROM [dbo].[TB_DefJobSkill_ItemUpgrade]
END
GO