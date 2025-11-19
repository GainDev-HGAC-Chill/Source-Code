USE [DR2_Def]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefItemByLevel]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefItemByLevel]
GO

CREATE Proc [dbo].[up_LoadDefItemByLevel]
AS

BEGIN
	SELECT [ID], [Level], [ItemNo] FROM [dbo].[TB_DefItemByLevel] WITH(NOLOCK)

END
GO
