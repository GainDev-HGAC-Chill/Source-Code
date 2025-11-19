USE [DR2_Member]
GO
/****** Object:  StoredProcedure [dbo].[up_Take_Coupon_Auth_Event]    Script Date: 11/04/2009 12:15:52 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Take_Coupon_Auth_Event]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Take_Coupon_Auth_Event]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE Proc [dbo].[up_Take_Coupon_Auth_Event]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명: [dbo].[up_Take_Coupon_Auth_Event]
// 작성자: 임상우
// 작성일: 10.12
// 최종수정자: 
// 수정일: 
// 파일명: 
// N O T E :  계정명으로쿠폰등록되어특정ID만지급하는시스템.
//
////////////////////////////////////////////////////////////////////////
*/ 
(
	@MemberGUID uniqueidentifier, 
	@CharacterGUID	UNIQUEIDENTIFIER,
	@SiteNo SMALLINT,
	@RealmNo SMALLINT
)
AS
SET NOCOUNT ON
BEGIN
	
	DECLARE @RewardKey int,
			@Eventkey int,
			@IDX INT,
			@f_Site SMALLINT,
			@f_Realm SMALLINT,
			@CURDATE DATETIME

	SET @CURDATE = GETDATE()

	select @RewardKey = 0,@EventKey = 0, @IDX = 0, @f_Site = 0, @f_Realm = 0
	
	select top 1 
	@IDX = A.f_IDX,
	@RewardKey = A.f_RewardKey,
	@EventKey = A.f_EventKey,
	@f_Site = A.f_Site,
	@f_Realm = A.f_Realm
	from dbo.TB_Event_Coupon A 
	INNER JOIN dbo.TB_Event_Type B
	ON A.f_EventKey = B.f_EventKey
	where 
	(A.f_OwnerMemberGuid = @MemberGUID and A.f_TakeDate is NULL) AND
	((A.f_Site IS NULL AND A.f_Realm IS NULL) OR (A.f_Site = @SiteNo AND A.f_Realm = @RealmNo)) AND
	(B.f_StartDate <= @CURDATE AND @CURDATE <= B.f_EndDate)

	if @@ROWCOUNT = 0
	BEGIN

		SELECT 6
		RETURN 6	-- 잘못된쿠폰아이디

	END

	if not exists(select 1 from dbo.TB_Event_Reward where f_RewardKey = @RewardKey)
	begin
		SELECT 2
		RETURN 2
	end

	DECLARE @STARTDATE DATETIME,
			@ENDDATE DATETIME,
			@REWARDGUID1 UNIQUEIDENTIFIER,-- 보상아이템고유아이디를미리할당한다.
			@REWARDGUID2 UNIQUEIDENTIFIER,
			@REWARDGUID3 UNIQUEIDENTIFIER,
			@REWARDGUID4 UNIQUEIDENTIFIER,
			@REWARDGUID5 UNIQUEIDENTIFIER,
			@REWARDGUID6 UNIQUEIDENTIFIER,
			@REWARDGUID7 UNIQUEIDENTIFIER,
			@REWARDGUID8 UNIQUEIDENTIFIER

	SELECT @STARTDATE = f_StartDate, @ENDDATE = f_EndDate FROM TB_EVENT_TYPE WHERE f_EventKey = @EventKey

	if @@ROWCOUNT = 0
	BEGIN

		SELECT 2
		RETURN 2	-- 잘못된이벤트타입이다.

	END

	if (@CURDATE < @STARTDATE) OR (@ENDDATE < @CURDATE)
	BEGIN 
		
		SELECT 3
		RETURN 3	-- 기간이만료된쿠폰이다.

	END

	SELECT @REWARDGUID1 = NEWID()
		   ,@REWARDGUID2 = NEWID()
		   ,@REWARDGUID3 = NEWID()
		   ,@REWARDGUID4 = NEWID()
		   ,@REWARDGUID5 = NEWID()
		   ,@REWARDGUID6 = NEWID()
		   ,@REWARDGUID7 = NEWID()
		   ,@REWARDGUID8 = NEWID()

	update dbo.TB_Event_Coupon set 
	 f_TakeDate = @CURDATE
	,f_TakerMemberGuid = @MemberGUID
	,f_TakerCharacterGuid = @CharacterGUID
	,f_RewardGuid1 = @REWARDGUID1
	,f_RewardGuid2 = @REWARDGUID2
	,f_RewardGuid3 = @REWARDGUID3 
	,f_RewardGuid4 = @REWARDGUID4 
	,f_RewardGuid5 = @REWARDGUID5 
	,f_RewardGuid6 = @REWARDGUID6 
	,f_RewardGuid7 = @REWARDGUID7 
	,f_RewardGuid8 = @REWARDGUID8 
	where f_IDX = @IDX

	IF @@ERROR <> 0
	BEGIN

		SELECT 4
		RETURN 4	-- DB ERROR

	END

	select top 1 
	0,
	 f_RewardItemNo1
	,f_RewardItemCount1
	,f_RewardTimeType1
	,f_RewardUseTime1
	,@REWARDGUID1
	,f_RewardItemNo2
	,f_RewardItemCount2
	,f_RewardTimeType2
	,f_RewardUseTime2
	,@REWARDGUID2
	,f_RewardItemNo3
	,f_RewardItemCount3
	,f_RewardTimeType3
	,f_RewardUseTime3
	,@REWARDGUID3
	,f_RewardItemNo4
	,f_RewardItemCount4
	,f_RewardTimeType4
	,f_RewardUseTime4
	,@REWARDGUID4

	,f_RewardItemNo5
	,f_RewardItemCount5
	,f_RewardTimeType5
	,f_RewardUseTime5
	,@REWARDGUID5
	,f_RewardItemNo6
	,f_RewardItemCount6
	,f_RewardTimeType6
	,f_RewardUseTime6
	,@REWARDGUID6
	,f_RewardItemNo7
	,f_RewardItemCount7
	,f_RewardTimeType7
	,f_RewardUseTime7
	,@REWARDGUID7
	,f_RewardItemNo8
	,f_RewardItemCount8
	,f_RewardTimeType8
	,f_RewardUseTime8
	,@REWARDGUID8

	,f_Money
	,f_Cash
	from dbo.TB_Event_Reward where f_RewardKey = @RewardKey

	RETURN 0	-- 성공

END