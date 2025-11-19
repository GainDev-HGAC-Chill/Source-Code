USE [DR2_SiteConfig]
GO

/****** Object:  StoredProcedure [dbo].[up_LoadSiteConfig]    Script Date: 08/25/2009 19:17:47 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadSiteConfig]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadSiteConfig]
GO

/****** Object:  StoredProcedure [dbo].[up_LoadSiteConfig]    Script Date: 08/25/2009 19:17:47 ******/
SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_LoadSiteConfig]
	@tblname nvarchar(100)
AS
BEGIN
	DECLARE @SQL nvarchar(max)
	DECLARE @SQL_Params nvarchar(max)

	SET @SQL = N'(
		SELECT RealmNo, RealmName, RealmTblName, Notice_TblName
		FROM dbo.'+@tblName+')'
	EXEC sp_executesql @SQL
END
GO
