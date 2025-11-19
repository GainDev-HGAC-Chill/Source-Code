USE [DR2_USER]
GO

/****** Object:  StoredProcedure [dbo].[UP_UpdateLimitedItemRecord_Limit]    Script Date: 05/21/2009 14:46:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UpdateLimitedItemRecord_Limit]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[UP_UpdateLimitedItemRecord_Limit]
GO

CREATE proc [dbo].[UP_UpdateLimitedItemRecord_Limit]
	@EventNo int,
	@RefreshCount int,
	@UpdateDate datetime
as
BEGIN
	SET NOCOUNT ON
	-- safe 의 것은 refresh 안함. refreshdate는 각자 따로 해야함.
	DECLARE @SafeCount int
	DECLARE @LimitCount int
	SELECT @LimitCount = [LimitCount], @SafeCount = [SafeCount] FROM [dbo].[TB_LimitedItemRecord] WHERE [EventNo] = @EventNo
	IF @@ROWCOUNT <> 1
	BEGIN
		SELECT @EventNo, 0
		RETURN
	END

	IF @SafeCount < @RefreshCount
	BEGIN
		SET @RefreshCount = @SafeCount
	END
	

	UPDATE [dbo].[TB_LimitedItemRecord] 
		SET [LimitCount] = @RefreshCount,
		[SafeCount] = [SafeCount] - @RefreshCount,
		[LimitRefreshDate] = @UpdateDate
		WHERE [EventNo] = @EventNo

	SELECT @EventNo, @RefreshCount
END

