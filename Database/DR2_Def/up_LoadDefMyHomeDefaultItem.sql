USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefMyHomeDefaultItem]    Script Date: 08/18/2009 02:14:47 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefMyHomeDefaultItem]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefMyHomeDefaultItem]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefMyHomeDefaultItem]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT townno,itemno FROM dbo.tb_defmyhomedefaultitem
	
END
