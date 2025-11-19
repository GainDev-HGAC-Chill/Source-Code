USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_User_MyHome_SideJob_Insert]    Script Date: 12/10/2009 16:51:14 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_SideJob_Insert]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_SideJob_Insert]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_User_MyHome_SideJob_Insert]
@OwnerGuid uniqueidentifier,
@Sidejob int,
@EndDate datetime,
@JobType int,
@JobRate int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	if exists(select * from dbo.tb_user_myhome_sidejob where ownerguid = @ownerguid and sidejob = @sidejob)
	begin
		select 1
		return
	end

	insert into dbo.tb_user_myhome_sidejob
	(ownerguid, sidejob, enddate, sellcost, jobtype, jobrate)
	values(@Ownerguid, @Sidejob, @enddate, 0, @jobtype, @jobrate)

	select 0
END

