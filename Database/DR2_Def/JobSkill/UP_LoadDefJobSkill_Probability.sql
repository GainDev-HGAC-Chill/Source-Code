
USE DR2_Def
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.UP_LoadDefJobSkill_Probability') and [type] IN (N'P'))
BEGIN
	DROP PROCEDURE dbo.UP_LoadDefJobSkill_Probability
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
CREATE PROCEDURE dbo.UP_LoadDefJobSkill_Probability
AS
BEGIN
	SET NOCOUNT ON;
	SELECT
		[NationCodeStr]
		,[f_No]
		,[f_Type]
		,[f_TotalProbability]
		,[f_01ResultNo]
		,[f_01Count]
		,[f_01Probability]
		,[f_02ResultNo]
		,[f_02Count]
		,[f_02Probability]
		,[f_03ResultNo]
		,[f_03Count]
		,[f_03Probability]
		,[f_04ResultNo]
		,[f_04Count]
		,[f_04Probability]
		,[f_05ResultNo]
		,[f_05Count]
		,[f_05Probability]
		,[f_06ResultNo]
		,[f_06Count]
		,[f_06Probability]
		,[f_07ResultNo]
		,[f_07Count]
		,[f_07Probability]
		,[f_08ResultNo]
		,[f_08Count]
		,[f_08Probability]
		,[f_09ResultNo]
		,[f_09Count]
		,[f_09Probability]
		,[f_10ResultNo]
		,[f_10Count]
		,[f_10Probability]
		,[f_01Need_SaveIdx]
	FROM [dbo].[TB_DefJobSkill_Probability]
END
GO
