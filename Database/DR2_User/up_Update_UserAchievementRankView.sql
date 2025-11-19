USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Update_UserAchievementRankView]    Script Date: 12/17/2009 16:06:59 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_UserAchievementRankView]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_UserAchievementRankView]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

create PROCEDURE [dbo].[up_Update_UserAchievementRankView]
AS
BEGIN
	SET NOCOUNT ON
	truncate table dbo.TB_UserAchievementRankView
	insert into dbo.TB_UserAchievementRankView (ownerguid , totalpoint) SELECT top 100 ownerguid, totalpoint FROM [dbo].[TB_UserAchievementRankTotal] ORDER BY TotalPoint DESC
END



