USE DR2_SiteConfig
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


/****** Object:  StoredProcedure [dbo].[UP_SetBlockIP]    Script Date: 06/23/2009 17:54:26 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_SetBlockIP]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[UP_SetBlockIP]
GO

CREATE proc [dbo].[UP_SetBlockIP] 
@FILEPATH NVARCHAR(100)
AS
Begin
	IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[GeoIPCountryWhois]') AND type in (N'U'))
	begin	
		DROP TABLE GeoIPCountryWhois
	end
	CREATE TABLE GeoIPCountryWhois
	(
		colA NVARCHAR(20) null,
		colB NVARCHAR(20) null,
		colC NVARCHAR(20) null,
		colD NVARCHAR(20) null,
		colE NVARCHAR(20) null,
		colF NVARCHAR(50) null,
		colG NVARCHAR(50) null,
	)

	DECLARE @STMT NVARCHAR(1000)
	SET  @STMT = 'BULK INSERT DBO.GeoIPCountryWhois
							 FROM ''' + @FILEPATH + '''
							 WITH (
									   FIRSTROW = 1,
									   FIELDTERMINATOR = '','',
									   ROWTERMINATOR = ''\n''
									  )'

	EXEC SP_EXECUTESQL @STMT

	SELECT TOP 10 * FROM dbo.GeoIPCountryWhois

	SELECT COUNT(*) FROM dbo.GeoIPCountryWhois
	drop TABLE TB_IP_ForBlock

	SET  @STMT ='EXEC sp_rename ''dbo.GeoIPCountryWhois.colA'',''StartIP''	'
	EXEC SP_EXECUTESQL @STMT
	
	SET  @STMT ='EXEC sp_rename ''dbo.GeoIPCountryWhois.colB'',''EndIP''	'
	EXEC SP_EXECUTESQL @STMT	
	
	SET  @STMT ='EXEC sp_rename ''dbo.GeoIPCountryWhois.colF'',''NationKey''	'
	EXEC SP_EXECUTESQL @STMT	
	
	SET  @STMT ='EXEC sp_rename ''dbo.GeoIPCountryWhois.colG'',''NationName''	'
	EXEC SP_EXECUTESQL @STMT	
	
	SET  @STMT ='EXEC sp_rename ''dbo.GeoIPCountryWhois'', ''TB_IP_ForBlock''	'
	EXEC SP_EXECUTESQL @STMT

	ALTER TABLE TB_IP_ForBlock 
	DROP COLUMN  colC, colD, colE

	delete TB_IP_ForBlock where startIP = 'beginIP'
end
GO

