USE [DR2_Def]
GO


IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefGemStore]'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadDefGemStore]
END
GO

/****** Object:  StoredProcedure [dbo].[up_LoadDefGemStore]    Script Date: 04/14/2010 15:40:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefGemStore]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [NationCodeStr]
		  ,[NpcGuid]
		  ,[Menu]
		  ,[OrderIndex]
		  ,[ItemNo]
		  ,[ItemCount]
		  ,[Gem1]
		  ,[GemCount1]
		  ,[Gem2]
		  ,[GemCount2]
		  ,[Gem3]
		  ,[GemCount3]
		  ,[Gem4]
		  ,[GemCount4]
		  ,[Gem5]
		  ,[GemCount5]
	  FROM [dbo].[TB_DefGemStore]
	  
END

GO
