USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_Base_Modify]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_Base_Modify]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_User_MyHome_Base_Modify]
@StreetNo SMALLINT,
@HouseNo int,
@HomeColor INT,
@HomeStyle INT,
@HomeFence INT,
@HomeGarden INT,
@RoomWall INT,
@RoomFloor INT,
@HomePrice BIGINT,
@AuctionTime DATETIME,
@AuctionState TINYINT,
@GroundNo INT,
@OwnerGuid UNIQUEIDENTIFIER,
@EnableVisitorBit TINYINT,
@BidderGuid UNIQUEIDENTIFIER,
@FirstBiddingCost BIGINT,
@LastBiddingCost BIGINT,
@PayTexTime DATETIME,
@PayTexNotiTime DATETIME,
@TotalVisitLogCount int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

UPDATE [dbo].[TB_User_MyHome_Base]
   SET 
	   [HomeColor] = @HomeColor
	  ,[HomeStyle] = @HomeStyle
	  ,[HomeFence] = @HomeFence
	  ,[HomeGarden] = @HomeGarden
	  ,[RoomWall] = @RoomWall
	  ,[RoomFloor] = @RoomFloor
      ,[HomePrice] = @HomePrice
      ,[AuctionTime] = @AuctionTime
      ,[AuctionState] = @AuctionState
      ,[GroundNo] = @GroundNo
      ,[OwnerGuid] = @OwnerGuid
      ,[EanbleVisitorBit] = @EnableVisitorBit
      ,[BidderGuid] = @BidderGuid
      ,[FirstBiddingCost] = @FirstBiddingCost
      ,[LastBiddingCost] = @LastBiddingCost
      ,[PayTexTime] = @PayTexTime
      ,[PayTexNotiTime] = @PayTexNotiTime
	  ,[TotalVisitLogCount] = @TotalVisitLogCount
 WHERE StreetNo = @StreetNo AND HouseNo = @HouseNo

EXEC dbo.up_User_MyHome_Base_Select @StreetNo,@HouseNo

END








