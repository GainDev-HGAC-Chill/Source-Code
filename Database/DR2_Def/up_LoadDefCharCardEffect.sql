USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefCharCardEffect]    Script Date: 11/27/2009 18:43:59 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefCharCardEffect]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefCharCardEffect]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefCharCardEffect]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [PopularPoint]
		  ,[EffectNo]
	  FROM [dbo].[TB_DefCharCardEffect]
END
