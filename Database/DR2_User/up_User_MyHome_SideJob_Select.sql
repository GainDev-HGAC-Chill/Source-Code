USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_User_MyHome_SideJob_Select]    Script Date: 12/10/2009 16:52:01 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_SideJob_Select]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_SideJob_Select]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_User_MyHome_SideJob_Select]
@StreetNo SMALLINT,
@HouseNo INT
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DECLARE @SQL nvarchar(MAX)
	DECLARE @SQL_Params nvarchar(MAX)

	SET @SQL = N'SELECT 
				   A.[OwnerGuid]
				  ,A.[SideJob]
				  ,A.[EndDate]
				  ,A.[SellCost]
				  ,A.[JobType]
				  ,A.[JobRate]
			  FROM [dbo].[TB_User_Myhome_SideJob] A
			  INNER JOIN dbo.TB_User_MyHome_Base B 
			  ON A.OwnerGuid = B.HomeInSideGuid'
		  
	if 0 < @StreetNo
	begin
		if 0 < @HouseNo
		begin
			SET @SQL_Params = N'@StreetNo smallint, @HouseNo int'                         
			SET @SQL = @SQL + ' WHERE B.StreetNo = @StreetNo AND B.HouseNo = @HouseNo'
			EXEC sp_executesql @SQL,@SQL_Params,@StreetNo,@HouseNo
		end
		else
		begin
			SET @SQL_Params = N'@StreetNo smallint'
			SET @SQL = @SQL + ' WHERE B.StreetNo = @StreetNo'
			EXEC sp_executesql @SQL,@SQL_Params,@StreetNo
		end
	end
	else
	begin
		EXEC sp_executesql @SQL
	end

END












