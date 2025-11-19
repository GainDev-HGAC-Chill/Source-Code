USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadMyHomeInfo]    Script Date: 02/06/2010 19:11:58 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadMyHomeInfo]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadMyHomeInfo]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[up_LoadMyHomeInfo]
@StreetNo smallint,
@HouseNo int = 0
AS
BEGIN

	EXEC dbo.up_LoadMyHometown @StreetNo, @HouseNo
	
	DECLARE @SQL nvarchar(MAX)
	DECLARE @SQL_Params nvarchar(MAX)

	SET @SQL = N'SELECT
			B.[ItemGuid],
			B.[OwnerGuid],
			B.[InvType],
			B.[InvPos],
			B.[ItemNo],
			B.[Count],

			D.Enchant_01,
			D.Enchant_02,
			D.Enchant_03,
			D.Enchant_04,

			B.[State],
			B.[CreateDate],
			
			E.[x],
			E.[y],
			E.[z],
			E.[dir],
			E.[ParentGuid],
			E.[LinkIdx]

	  FROM 
	  [dbo].[TB_User_MyHome_Base] A
	  INNER JOIN [dbo].[TB_UserItem] B ON A.HomeInSideGuid = B.OwnerGuid OR A.HomeOutSideGuid = B.OwnerGuid
	  LEFT JOIN [dbo].[TB_UserItem_Enchant] D ON B.ItemGuid = D.ItemGuid
	  LEFT JOIN [dbo].[TB_User_MyHome_EquipItem] E ON B.ItemGuid = E.ItemGuid'

	if 0 < @StreetNo
	begin
		if 0 < @HouseNo
		begin
			SET @SQL_Params = N'@StreetNo smallint, @HouseNo int'                         
			SET @SQL = @SQL + ' WHERE A.StreetNo = @StreetNo AND A.HouseNo = @HouseNo'
			EXEC sp_executesql @SQL,@SQL_Params,@StreetNo,@HouseNo
		end
		else
		begin
			SET @SQL_Params = N'@StreetNo smallint'
			SET @SQL = @SQL + ' WHERE A.StreetNo = @StreetNo'
			EXEC sp_executesql @SQL,@SQL_Params,@StreetNo
		end
	end
	else
	begin
		EXEC sp_executesql @SQL
	end

END















