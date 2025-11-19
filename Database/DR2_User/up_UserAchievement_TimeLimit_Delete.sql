USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UserAchievement_TimeLimit_Delete]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_UserAchievement_TimeLimit_Delete]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_UserAchievement_TimeLimit_Delete]
@OwnerGuid uniqueidentifier,
@AchievementIdx int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	delete from dbo.TB_UserAchievement_TimeLimit where ownerguid = @OwnerGuid and achievementidx = @AchievementIdx

END
