USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_Base_Select]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_Base_Select]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_User_MyHome_Base_Select]
@StreetNo SMALLINT,
@HouseNo int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DECLARE @SQL nvarchar(MAX)
	DECLARE @SQL_Params nvarchar(MAX)

	SET @SQL = N'SELECT A.[StreetNo]
				  ,A.[HouseNo]
				  ,A.[HomeColor]
				  ,A.[HomeStyle]
				  ,A.[HomeFence]
				  ,A.[HomeGarden]
				  ,A.[RoomWall]
				  ,A.[RoomFloor]
				  ,A.[HomePrice]
				  ,A.[AuctionTime]
				  ,A.[AuctionState]
				  ,A.[GroundNo]
				  ,A.[HomeInSideGuid]
				  ,A.[HomeOutSideGuid]
				  ,A.[OwnerGuid]
				  ,B.[Name]
				  ,A.[EanbleVisitorBit]
				  ,A.[BidderGuid]
				  ,A.[FirstBiddingCost]
				  ,A.[LastBiddingCost]
				  ,A.[PayTexTime]	
				  ,A.[PayTexNotiTime]    
				  ,C.[Name]
				  ,A.[AuctionLvLimitMin]
				  ,A.[AuctionLvLimitMax]
				  ,A.[TotalVisitLogCount]
				  ,A.[ToDayHitCount]
				  ,A.[TotalHitCount]
			  FROM [dbo].[TB_User_MyHome_Base] A
			  LEFT JOIN dbo.TB_CharacterBasic B ON A.OwnerGuid = B.CharacterID
			  LEFT JOIN dbo.TB_CharacterBasic C ON A.BidderGuid = C.CharacterID'
		  
	if 0 < @StreetNo
	begin
		if 0 < @HouseNo
		begin
			SET @SQL_Params = N'@StreetNo smallint, @HouseNo int'                         
			SET @SQL = @SQL + ' WHERE StreetNo = @StreetNo AND HouseNo = @HouseNo'
			EXEC sp_executesql @SQL,@SQL_Params,@StreetNo,@HouseNo
		end
		else
		begin
			SET @SQL_Params = N'@StreetNo smallint'
			SET @SQL = @SQL + ' WHERE StreetNo = @StreetNo'
			EXEC sp_executesql @SQL,@SQL_Params,@StreetNo
		end
	end
	else
	begin
		EXEC sp_executesql @SQL
	end

END












