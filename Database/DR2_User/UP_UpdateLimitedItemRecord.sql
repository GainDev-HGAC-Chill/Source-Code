USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[UP_UpdateLimitedItemRecord]    Script Date: 05/21/2009 14:45:45 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UpdateLimitedItemRecord]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[UP_UpdateLimitedItemRecord]
GO

/****** Object:  StoredProcedure [dbo].[UP_UpdateLimitedItemRecord]    Script Date: 05/21/2009 14:45:52 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE proc [dbo].[UP_UpdateLimitedItemRecord]
	@EventNo int,
	@UpdateDate datetime
as
begin
begin tran
	update [dbo].[TB_LimitedItemRecord] set SafeCount = SafeCount + RefreshCount, SafeRefreshDate = @UpdateDate
	where EventNo = @EventNo
commit tran
end
