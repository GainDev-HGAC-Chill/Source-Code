USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Set_UserAchievement]    Script Date: 01/19/2010 14:37:54 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Set_UserAchievement]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Set_UserAchievement]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_Set_UserAchievement]
	-- Add the parameters for the stored procedure here
@charguid uniqueidentifier,
@Category int,
@Point int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	if not exists(select 1 from dbo.TB_UserAchievementRank where OwnerGuid = @charguid and [Category] = @Category)
	begin
		insert into dbo.TB_UserAchievementRank (OwnerGuid,[Category],[Point]) values(@charguid,@Category,@Point)
	end
	else
	begin
		update dbo.TB_UserAchievementRank set [Point] = @Point where OwnerGuid = @charguid and [Category] = @Category
	end
		
END
