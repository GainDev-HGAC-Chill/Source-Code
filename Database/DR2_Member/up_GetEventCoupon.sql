USE [DR2_Member]
GO
/****** Object:  StoredProcedure [dbo].[up_GetEventCoupon]    Script Date: 04/15/2009 01:27:07 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_GetEventCoupon]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_GetEventCoupon]
END
GO

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go


CREATE PROCEDURE [dbo].[up_GetEventCoupon]
@MemberGuid UNIQUEIDENTIFIER,
@EventId INT,
@SiteNo SMALLINT = NULL,
@RealmNo SMALLINT = NULL
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	IF EXISTS (SELECT * FROM dbo.TB_Event_Coupon WHERE f_EventKey = @EventId AND f_OwnerMemberGuid = @MemberGuid AND f_Site = @SiteNo AND f_Realm = @RealmNo)
	BEGIN
		SELECT 1
		RETURN
	END

	BEGIN TRAN
	
	DECLARE @COUPONID NVARCHAR(MAX)
	SELECT TOP 1 @COUPONID = f_CouponID FROM dbo.TB_Event_Coupon 
	WHERE 
	f_EventKey = @EventId AND 
	f_OwnerMemberGuid IS NULL AND
	f_TakeDate IS NULL
	
	IF @@ROWCOUNT = 0
	BEGIN
		GOTO ERROR_COUPON
	END
	ELSE
	BEGIN
		
		UPDATE dbo.TB_Event_Coupon SET f_OwnerMemberGuid = @MemberGuid, f_Site = @SiteNo, f_Realm = @RealmNo
		WHERE f_CouponID = @COUPONID

		IF @@ERROR <> 0
		BEGIN
			GOTO ERROR_COUPON
		END

	END
	
	COMMIT TRAN
	
	SELECT 0, @COUPONID
	RETURN
		
ERROR_COUPON:

	ROLLBACK TRAN
	
	SELECT 1
END

