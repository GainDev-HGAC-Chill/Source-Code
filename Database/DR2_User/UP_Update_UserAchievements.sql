USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[UP_Update_UserAchievements]    Script Date: 10/22/2009 18:58:08 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_Update_UserAchievements]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[UP_Update_UserAchievements]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[UP_Update_UserAchievements]

@charguid uniqueidentifier,
@type int,
@value int

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	if not exists(select 1 from dbo.TB_UserAchievements where charguid = @charguid and [type] = @type)
	begin
		insert into dbo.TB_UserAchievements (charguid,[type],[value])
		values(@charguid,@type,@value)
	end
	else
	begin
		update dbo.TB_UserAchievements set [value] = @value 
		where charguid = @charguid and [type] = @type
	end

	select @@ERROR

END



