USE DR2_Member

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Take_Coupon_Event3]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_Take_Coupon_Event3]
END
go
