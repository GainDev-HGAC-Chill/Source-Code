USE [DR2_USER]
GO
/****** 개체:  StoredProcedure [dbo].[UP_LimitedItem_SyncToRecord]    스크립트 날짜: 05/21/2009 15:17:19 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_LimitedItem_SyncToRecord]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[UP_LimitedItem_SyncToRecord]
GO

/****** 개체:  StoredProcedure [dbo].[UP_LimitedItem_SyncToRecord]    스크립트 날짜: 05/21/2009 15:15:29 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE proc [dbo].[UP_LimitedItem_SyncToRecord]
	@EventNo int
	,@StartDate datetime
	,@EndDate datetime
	,@Limit_ResetPeriod int
	,@Safe_ResetPeriod int
	,@RefreshCount int
as
BEGIN

	DECLARE @rec_count int
	SELECT @rec_count = count(*) FROM TB_LimitedItemRecord where EventNo = @EventNo

	if(@rec_count > 0) --카운트가 있으면 업데이트
	begin
		update dbo.TB_LimitedItemRecord
			set StartDate = @StartDate,  
			EndDate = @EndDate,
			Limit_ResetPeriod = @Limit_ResetPeriod,
			Safe_ResetPeriod = @Safe_ResetPeriod,
			RefreshCount = @RefreshCount
			where EventNo = @EventNo
	end
	else
	begin
		insert into dbo.TB_LimitedItemRecord
			(EventNo, StartDate, EndDate, Limit_ResetPeriod, Safe_ResetPeriod,
			RefreshCount, LimitCount, SafeCount	)
			values ( @EventNo, @StartDate,  @EndDate, @Limit_ResetPeriod, @Safe_ResetPeriod,
			@RefreshCount, 0, 0 )
	end
end
