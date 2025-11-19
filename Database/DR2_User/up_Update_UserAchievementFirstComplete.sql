USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Update_UserAchievementFirstComplete]    Script Date: 10/22/2009 18:57:18 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_UserAchievementFirstComplete]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_UserAchievementFirstComplete]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Update_UserAchievementFirstComplete]
@SaveIdx int,
@OwnerGuid uniqueidentifier
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	if exists(select 1 from dbo.TB_UserAchievementFirstComplete where FirstCompleteAchievement = @SaveIdx)
	begin
		select 1
		return
	end
	else
	begin
		insert into dbo.TB_UserAchievementFirstComplete (FirstCompleteAchievement,OwnerGuid,CompleteDate)
		values(@SaveIdx,@OwnerGuid,getdate())
	end

	select 0, @SaveIdx, name from dbo.TB_CharacterBasic where CharacterID = @OwnerGuid
END
