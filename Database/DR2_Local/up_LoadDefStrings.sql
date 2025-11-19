USE [DR2_local]
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefStrings]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefStrings]
GO

CREATE Proc [dbo].[up_LoadDefStrings]
AS

BEGIN
	SELECT [StringNo], [Text], [TextEng] from dbo.TB_DefStrings WITH(NOLOCK)
	SELECT [StringNo], [Text], [TextEng] from dbo.TB_DefStrings_Item WITH(NOLOCK)
	SELECT [StringNo], [Text], [TextEng] from dbo.TB_DefStrings_Map WITH(NOLOCK)
	SELECT [StringNo], [Text], [TextEng] from dbo.TB_DefStrings_Monster WITH(NOLOCK)
	SELECT [StringNo], [Text], [TextEng] from dbo.TB_DefStrings_Pet WITH(NOLOCK)
	SELECT [StringNo], [Text], [TextEng] from dbo.TB_DefStrings_Skill WITH(NOLOCK)
END
