USE DR2_Def
GO

IF EXISTS (SELECT * FROM sys.objects WHERE OBJECT_ID = OBJECT_ID(N'[dbo].[up_LoadDefCardAbilKey]'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefCardAbilKey]
END
GO

CREATE PROCEDURE [dbo].[up_LoadDefCardAbilKey]

AS
BEGIN
	
SELECT [KeyType]
      ,[KeyValue]
      ,[StringNo]
      ,[CardKey]
  FROM [dbo].[TB_DefCardAbilKey]
  
END
GO
