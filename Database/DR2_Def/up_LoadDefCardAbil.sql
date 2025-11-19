USE DR2_Def

IF EXISTS (SELECT * FROM sys.objects WHERE object_id=OBJECT_ID('[dbo].[up_LoadDefCardAbil]'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefCardAbil]
END
GO

CREATE PROCEDURE [dbo].[up_LoadDefCardAbil]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;


	SELECT [Constellation]
		  ,[Blood]
		  ,[Hobby]
		  ,[Style]
		  ,[AbilType]
		  ,[Value]
	  FROM [dbo].[TB_DefCardAbil]

END
GO
