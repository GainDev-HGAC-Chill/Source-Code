USE DR2_Local

GO

IF EXISTS (SELECT * FROM sys.objects WHERE OBJECT_ID = OBJECT_ID(N'[dbo].[up_LoadCardLocal]'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadCardLocal]
END
GO

CREATE PROCEDURE [dbo].[up_LoadCardLocal]

AS
BEGIN

SELECT	 [Local]
		,[Text]
  FROM [dbo].[TB_CardLocal]

END
GO  