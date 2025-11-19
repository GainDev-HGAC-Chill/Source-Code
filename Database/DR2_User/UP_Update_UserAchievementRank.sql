USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[UP_Update_UserAchievementRank]    Script Date: 10/28/2009 19:32:06 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_Update_UserAchievementRank]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[UP_Update_UserAchievementRank]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[UP_Update_UserAchievementRank]

@charguid uniqueidentifier,
@Category int,
@Point int

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	if not exists(select 1 from dbo.TB_UserAchievementRankTotal where OwnerGuid = @charguid)
	begin
		insert into dbo.TB_UserAchievementRankTotal (ownerguid,totalpoint)
		values(@charguid,@point)
	end
	else
	begin
		update dbo.TB_UserAchievementRankTotal set totalpoint = totalpoint + @point
		where ownerguid = @charguid
	end

	if not exists(select 1 from dbo.TB_UserAchievementRank where OwnerGuid = @charguid and [Category] = @Category)
	begin
		insert into dbo.TB_UserAchievementRank (OwnerGuid,[Category],[Point])
		values(@charguid,@Category,@Point)
	end
	else
	begin
		update dbo.TB_UserAchievementRank set [Point] = [Point] + @Point
		where OwnerGuid = @charguid and [Category] = @Category
	end

	select @@ERROR

END






