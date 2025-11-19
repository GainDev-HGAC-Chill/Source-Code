USE [DR2_Def]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefMyHomeSidejobTime]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefMyHomeSidejobTime]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadDefMyHomeSidejobTime]
AS
BEGIN

	SET NOCOUNT ON;

	SELECT HomeLevel, SidejobTime from dbo.tb_defmyhomesidejobtime
END
