USE DR2_USER
GO

IF EXISTS(SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.[UP_UpdateWebIndunClearUserInfo]') AND [type] in (N'P'))
BEGIN
	DROP PROCEDURE dbo.[UP_UpdateWebIndunClearUserInfo]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		À°Á¤¹ü
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE dbo.[UP_UpdateWebIndunClearUserInfo]
@f_RealmNo INT,
@f_GroundNo INT,
@f_TodayCount INT
AS
BEGIN
	DECLARE @LastUpdateDate DATETIME
	DECLARE @Today DATETIME
	SET @Today = GETDATE()
	
	SELECT @LastUpdateDate = [f_LastTodayUpdate] FROM [dbo].[TB_Web_IndunClearUserCountInfo] WHERE [f_RealmNo] = @f_RealmNo AND [f_GroundNo] = @f_GroundNo
	IF @@rowcount <> 0
	BEGIN
		IF DAY(@LastUpdateDate) = DAY(@Today)
		BEGIN
			UPDATE [dbo].[TB_Web_IndunClearUserCountInfo]
			SET [f_TodayCount] = [f_TodayCount] + @f_TodayCount
				,[f_LastTodayUpdate] = @Today
			WHERE [f_RealmNo] = @f_RealmNo AND [f_GroundNo] = @f_GroundNo
		END
		ELSE
		BEGIN
			UPDATE [dbo].[TB_Web_IndunClearUserCountInfo]
			SET [f_YesterdayCount] = [f_TodayCount]
				,[f_TodayCount] = @f_TodayCount
				,[f_LastTodayUpdate] = @Today
			WHERE [f_RealmNo] = @f_RealmNo AND [f_GroundNo] = @f_GroundNo
		END
	END
	ELSE
	BEGIN
		INSERT INTO [dbo].[TB_Web_IndunClearUserCountInfo]
			([f_RealmNo]
			,[f_GroundNo]
			,[f_YesterdayCount]
			,[f_TodayCount]
			,[f_LastTodayUpdate])
		VALUES
			(@f_RealmNo
			,@f_GroundNo
			,0
			,@f_TodayCount
			,@Today)
	END
END
GO
