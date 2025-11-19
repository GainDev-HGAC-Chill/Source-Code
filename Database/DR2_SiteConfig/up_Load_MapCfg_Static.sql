USE [DR2_SiteConfig]
GO

/****** Object:  StoredProcedure [dbo].[up_Load_MapCfg_Static]    Script Date: 08/25/2009 19:24:11 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Load_MapCfg_Static]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Load_MapCfg_Static]
GO

/****** Object:  StoredProcedure [dbo].[up_Load_MapCfg_Static]    Script Date: 08/25/2009 19:24:11 ******/
SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Load_MapCfg_Static]
	@tblname nvarchar(100)
AS

BEGIN
	DECLARE @SQL nvarchar(max)
	DECLARE @SQL_Params nvarchar(max)

	SET @SQL = N'(SELECT RealmNo, ChannelNo, ServerNo, GroundNo from dbo.'+@tblName+') order by RealmNo, ChannelNo, ServerNo, GroundNo'
	EXEC sp_executesql @SQL
END
GO
