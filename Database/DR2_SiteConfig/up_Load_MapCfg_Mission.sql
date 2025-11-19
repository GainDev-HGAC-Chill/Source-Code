USE [DR2_SiteConfig]
GO

/****** Object:  StoredProcedure [dbo].[up_Load_MapCfg_Mission]    Script Date: 08/25/2009 19:24:52 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Load_MapCfg_Mission]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Load_MapCfg_Mission]
GO

/****** Object:  StoredProcedure [dbo].[up_Load_MapCfg_Mission]    Script Date: 08/25/2009 19:24:52 ******/
SET ANSI_NULLS ON
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Load_MapCfg_Mission]
	@tblname nvarchar(100)
AS

BEGIN
	DECLARE @SQL nvarchar(max)
	DECLARE @SQL_Params nvarchar(max)
    -- Insert statements for procedure here

	SET @SQL = N'(SELECT RealmNo, ChannelNo, ServerNo, MissionNo from dbo.'+@tblName+') order by RealmNo, ChannelNo, ServerNo, MissionNo'
	EXEC sp_executesql @SQL
END
GO
