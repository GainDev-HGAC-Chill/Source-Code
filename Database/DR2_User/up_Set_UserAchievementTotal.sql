USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Set_UserAchievementTotal]    Script Date: 01/19/2010 14:38:44 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Set_UserAchievementTotal]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Set_UserAchievementTotal]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Set_UserAchievementTotal]
@charguid uniqueidentifier,
@Point int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	if not exists(select 1 from dbo.TB_UserAchievementRankTotal where OwnerGuid = @charguid)
	begin
		insert into dbo.TB_UserAchievementRankTotal (ownerguid,totalpoint) values(@charguid,@point)
	end
	else
	begin
		update dbo.TB_UserAchievementRankTotal set totalpoint = @point where ownerguid = @charguid
	end
		
END
