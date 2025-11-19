USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UserAchievement_TimeLimit_Modify]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_UserAchievement_TimeLimit_Modify]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_UserAchievement_TimeLimit_Modify]
@OwnerGuid uniqueidentifier,
@AchievementIdx int,
@TimeLimit int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	if not exists(select 1 from dbo.TB_UserAchievement_TimeLimit where ownerguid = @OwnerGuid and achievementidx = @AchievementIdx)
    begin
		insert into dbo.TB_UserAchievement_TimeLimit (ownerguid,achievementidx,timelimit)
		values(@ownerguid, @achievementidx, @TimeLimit)
	end
	else
	begin
		update dbo.TB_UserAchievement_TimeLimit set timelimit = @TimeLimit
		where ownerguid = @ownerguid and achievementidx = @achievementidx
	end

END
