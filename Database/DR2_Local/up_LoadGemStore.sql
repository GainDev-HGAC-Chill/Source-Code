USE [DR2_Local]
GO


IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadGemStore]'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadGemStore]
END
GO

/****** Object:  StoredProcedure [dbo].[up_LoadGemStore]    Script Date: 04/08/2009 21:05:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadGemStore]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [NpcGuid]
		  ,[ItemNo]
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
		  ,[CP]
	  FROM [dbo].[TB_GemStore]
	  
END
