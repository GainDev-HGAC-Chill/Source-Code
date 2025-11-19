USE DR2_Def

IF EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID('[dbo].[up_LoadDefDeathPenalty]'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefDeathPenalty]
END
GO

CREATE PROCEDURE [dbo].[up_LoadDefDeathPenalty]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;


	SELECT [f_GroundAttr]
		  ,[f_GroundNo]
		  ,[f_LevelMin]
		  ,[f_LevelMax]
		  ,[f_SuccessionalDeath]
		  ,[f_Effect1]
		  ,[f_Effect2]
	  FROM [dbo].[TB_DefDeathPenalty]

END
GO
