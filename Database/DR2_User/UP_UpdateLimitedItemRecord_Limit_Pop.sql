USE [DR2_USER]
GO

/****** Object:  StoredProcedure [dbo].[UP_UpdateLimitedItemRecord_Limit_Pop]    Script Date: 05/21/2009 14:47:27 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_UpdateLimitedItemRecord_Limit_Pop]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[UP_UpdateLimitedItemRecord_Limit_Pop]
GO

CREATE proc [dbo].[UP_UpdateLimitedItemRecord_Limit_Pop]    
 @EventNo int    
as    
begin   
	SET NOCOUNT ON 
-- safe 의 것은 refresh 안함. refreshdate는 각자 따로 해야함.    
	BEGIN TRAN	-- 동시에 호출되는 것을 막기 위한 transaction
	DECLARE  @NowCount int
	DECLARE  @Return int
	select @NowCount = [LimitCount] from [dbo].[TB_LimitedItemRecord] where [EventNo] = @EventNo 
	IF @@ROWCOUNT <> 1
	BEGIN
		SELECT @EventNo, 0
		COMMIT TRAN
		RETURN
	END
	if @NowCount > 0
	begin    
		UPDATE [dbo].[TB_LimitedItemRecord] SET [LimitCount] = [LimitCount]-1 WHERE [EventNo] = @EventNo
	end    

	SELECT @EventNo, @NowCount
	COMMIT TRAN
end
