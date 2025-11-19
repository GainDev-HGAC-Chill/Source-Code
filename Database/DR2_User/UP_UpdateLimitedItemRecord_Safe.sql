USE [DR2_USER]
GO
/****** Object:  StoredProcedure [dbo].[UP_UpdateLimitedItemRecord_Safe]    Script Date: 05/21/2009 14:47:59 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UpdateLimitedItemRecord_Safe]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[UP_UpdateLimitedItemRecord_Safe]
GO

/****** Object:  StoredProcedure [dbo].[UP_UpdateLimitedItemRecord]    Script Date: 08/20/2009 18:15:58 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UpdateLimitedItemRecord]') AND type in (N'P', N'PC'))
	DROP PROCEDURE [dbo].[UP_UpdateLimitedItemRecord]
GO

create proc [dbo].[UP_UpdateLimitedItemRecord_Safe]
	@EventNo int,
	@UpdateDate datetime
as
begin
	update [dbo].[TB_LimitedItemRecord] set [SafeCount] = [RefreshCount], [SafeRefreshDate] = @UpdateDate
	where [EventNo] = @EventNo
end
