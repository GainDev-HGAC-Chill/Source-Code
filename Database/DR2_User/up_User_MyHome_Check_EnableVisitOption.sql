USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_Check_EanbleVisitOption]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_Check_EanbleVisitOption]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[up_User_MyHome_Check_EanbleVisitOption]
@StreetNo SMALLINT,
@HouseNo int,
@OwnerGuid UNIQUEIDENTIFIER
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DECLARE @TargetGuid UNIQUEIDENTIFIER,
			@EnableVisitFlag TINYINT,
			@HomeInSideGuid UNIQUEIDENTIFIER,
			@GroundNo INT,
			@AuctionState TINYINT,
			@TodayDay TINYINT
			
	SELECT 
	@HomeInSideGuid = HomeInSideGuid, 
	@GroundNo = GroundNo, 
	@TargetGuid = OwnerGuid, 
	@EnableVisitFlag = ISNULL(EanbleVisitorBit,0),
	@AuctionState = ISNULL(AuctionState,0),
	@TodayDay = TodayDay
	FROM dbo.TB_User_MyHome_Base 
	WHERE StreetNo = @StreetNo AND HouseNo = @HouseNo

	DECLARE @CardGuid UNIQUEIDENTIFIER,@Used TINYINT 
	SELECT TOP 1 @CardGuid = cardguid FROM dbo.TB_User_MyHome_Invitation 
	WHERE OwnerGuid = @OwnerGuid AND StreetNO = @StreetNo AND HouseNo = @HouseNo AND Used = 0
	IF @CardGuid IS NOT NULL
	BEGIN
		UPDATE dbo.TB_User_MyHome_Invitation SET Used = 1 WHERE cardguid = @CardGuid
		GOTO ENTER_OK
	END
	
	IF @TargetGuid = @OwnerGuid OR (@EnableVisitFlag & 8) = 8 OR (1 = @AuctionState)
	BEGIN -- 주인이 없는 집이거나 자신이 주인 모두 개방 경매중
		GOTO ENTER_OK
	END
		
	IF 0 = @EnableVisitFlag 
	BEGIN
		GOTO ENTER_FAIL
	END

	IF (@EnableVisitFlag & 2) = 2
	BEGIN
		DECLARE @Guild1 UNIQUEIDENTIFIER,@Guild2 UNIQUEIDENTIFIER
		SELECT @Guild1 = GuildGuid FROM dbo.TB_Guild_Member WHERE CharacterGuid = @TargetGuid
		SELECT @Guild2 = GuildGuid FROM dbo.TB_Guild_Member WHERE CharacterGuid = @OwnerGuid
		IF @Guild1 IS NOT NULL AND @Guild2 IS NOT NULL AND @Guild1 = @Guild2
		BEGIN
			GOTO ENTER_OK
		END
		
	END

	IF (@EnableVisitFlag & 4) = 4
	BEGIN
		
		IF EXISTS(SELECT * FROM dbo.TB_UserFriend WHERE OwnerMemberGuid = @TargetGuid AND FriendMemberGuid = @OwnerGuid) AND
		   EXISTS(SELECT * FROM dbo.TB_UserFriend WHERE OwnerMemberGuid = @OwnerGuid AND FriendMemberGuid = @TargetGuid)
		BEGIN
	   		GOTO ENTER_OK
		END
		
	END	

	IF (@EnableVisitFlag & 1) = 1
	BEGIN
	
		IF (SELECT CoupleCharGuid FROM dbo.TB_UserCouple WHERE CharacterGuid = @TargetGuid) = @OwnerGuid
		BEGIN
			GOTO ENTER_OK
		END
	
	END
	
ENTER_FAIL:
	SELECT 1
	RETURN
	
ENTER_OK:

	IF @TodayDay IS NULL OR @TodayDay <> DAY(GETDATE())
	BEGIN 
		UPDATE dbo.TB_User_MyHome_Base 
		SET TodayDay = CAST(DAY(GETDATE()) AS TINYINT),
		TodayHitCount = 0
		WHERE StreetNo = @StreetNo AND HouseNo = @HouseNo
	END


	DECLARE @CurDay TINYINT
	SET @curday = CAST(DAY(GETDATE()) AS TINYINT)

	IF @TargetGuid <> @OwnerGuid 
	BEGIN

		DELETE FROM dbo.TB_User_MyHome_TodayVisitors WHERE VisitDay <> @CurDay

		IF NOT EXISTS(SELECT * FROM dbo.TB_User_MyHome_TodayVisitors WHERE VisitorGuid = @OwnerGuid AND townno = @streetno AND houseno = @HouseNo)
		BEGIN
			UPDATE dbo.TB_User_MyHome_Base 
			SET TodayHitCount = TodayHitCount + 1,
			TotalHitCount = ISNULL(TotalHitCount,0) + 1
			WHERE StreetNo = @StreetNo AND HouseNo = @HouseNo

			INSERT INTO dbo.TB_User_MyHome_TodayVisitors 
			(townno,houseno,visitorguid,visitday)
			VALUES(@streetno,@HouseNo,@OwnerGuid,@curday)
		END

		IF EXISTS(SELECT * FROM dbo.TB_User_MyHome_Visitors WHERE VisitorGuid = @OwnerGuid AND streetno = @streetno AND houseno = @HouseNo)
		BEGIN
			UPDATE dbo.TB_User_MyHome_Visitors SET VisitTime = GETDATE() WHERE VisitorGuid = @OwnerGuid
		END
		ELSE
		BEGIN
			DECLARE @VisitorCount int
			SELECT @VisitorCount = COUNT(*) FROM dbo.TB_User_MyHome_Visitors
			WHERE StreetNo = @StreetNo AND HouseNo = @HouseNo
			
			IF 10 <= @VisitorCount
			BEGIN
				BEGIN
					DELETE FROM dbo.TB_User_MyHome_Visitors 
					WHERE VisitorGuid = (SELECT TOP 1 VisitorGuid FROM dbo.TB_User_MyHome_Visitors ORDER BY VisitTime)
				END
			END
			ELSE
			BEGIN
				INSERT INTO dbo.TB_User_MyHome_Visitors (StreetNo,HouseNo,VisitorGuid,VisitTime)
				VALUES (@StreetNo,@HouseNo,@OwnerGuid,GETDATE())
			END
		END	
	END
			
	SELECT 0,@GroundNo,@HomeInSideGuid,TodayHitCount,TotalHitCount 
	FROM dbo.TB_User_MyHome_Base 
	WHERE StreetNo = @StreetNo AND HouseNo = @HouseNo
	RETURN

END














