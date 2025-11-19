USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Admin_CreateMyHome]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Admin_CreateMyHome]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Admin_CreateMyHome]
@TownNo SMALLINT,-- 추가 타운 번호
@StartHouseNo int, -- 추가 홈 시작 번호 
@EndHouseNo int, -- 추가 홈 마지막 번호
@GroundNo INT,-- 9991001 로 고정
@HomePrice BIGINT,-- 최초 경매 시작 금액
@AuctionState TINYINT = NULL,-- 경매 상태 1: 경매중 0: 일반
@AuctionTime DATETIME = NULL,-- 경매 마감시간
@LvLimitMin INT = NULL, -- 경매 참가 최소 레밸
@LvLimitMax INT = NULL, -- 경매 참가 최대 레밸
@HomeStyle int = NULL -- 마이홈 내부 사이즈 결정 아이템 번호
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	WHILE @StartHouseNo <= @EndHouseNo
	BEGIN
		
		INSERT INTO dbo.TB_User_MyHome_Base (
			StreetNo,
			HouseNo,
			HomePrice,
			GroundNo,
			AuctionState,
			AuctionTime,
			FirstBiddingCost,
			LastBiddingCost,
			HomeInSideGuid,
			HomeOutSideGuid,
			HomeColor,
			HomeStyle,
			HomeFence,
			HomeGarden,
			RoomWall,
			RoomFloor,
			AuctionLvLimitMin,
			AuctionLvLimitMax
		) VALUES 
		(@TownNo
		,@StartHouseNo
		,@HomePrice
		,@GroundNo
		,@AuctionState
		,@AuctionTime
		,@HomePrice
		,@HomePrice
		,NEWID()
		,NEWID()
		,0
		,@HomeStyle
		,0
		,0
		,70000540
		,70000550
		,@LvLimitMin
		,@LvLimitMax) 

		SET @StartHouseNo = @StartHouseNo + 1
		
	END

END





