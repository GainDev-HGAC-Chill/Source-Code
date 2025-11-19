USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefBasicOptionAmp]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefBasicOptionAmp]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefBasicOptionAmp]

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [EquipType]
		,[LevelLimit]
		,[AmplifyOptValueLV]
		,[Amplify_MaxValueLV]
		,[AmplifyRate]
		,[SuccessRate]
		,[NeedMoney]
		,[SoulItemCount]
		,[AmplifyItemNo]
		,[AmplifyItemCount]
		,[InsuranceItemNo]
	FROM [dbo].[TB_DefItemAmplify]

END
