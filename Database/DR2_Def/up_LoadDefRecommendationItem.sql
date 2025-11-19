IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefRecommendationItem]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[up_LoadDefRecommendationItem]
GO

/****** Object:  StoredProcedure [dbo].[up_LoadDefRecommendationItem]    Script Date: 07/09/2009 11:25:40 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefRecommendationItem]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [IDX]
		  ,[class]
		  ,[LvMin]
		  ,[LvMax]
		  ,[Item1]
		  ,[Item2]
		  ,[Item3]
		  ,[Item4]
		  ,[Item5]
		  ,[Item6]
		  ,[Item7]
		  ,[Item8]
		  ,[Item9]
		  ,[Item10]
		  ,[Item11]
		  ,[Item12]
		  ,[Item13]
		  ,[Item14]
		  ,[Item15]
		  ,[Item16]
		  ,[Item17]
		  ,[Item18]
		  ,[Item19]
		  ,[Item20]
	  FROM [dbo].[TB_DefRecommendationItem]

END

GO