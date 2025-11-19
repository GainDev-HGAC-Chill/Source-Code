USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefHometownToMapCost]    Script Date: 08/31/2009 20:53:54 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefHometownToMapCost]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefHometownToMapCost]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadDefHometownToMapCost]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	SELECT LevelLimit,Cost FROM dbo.TB_DefHometownToMapCost
END
