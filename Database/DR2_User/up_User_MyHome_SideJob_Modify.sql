USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_User_MyHome_SideJob_Modify]    Script Date: 12/10/2009 11:32:01 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_SideJob_Modify]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_SideJob_Modify]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
create PROCEDURE [dbo].[up_User_MyHome_SideJob_Modify]
@OwnerGuid uniqueidentifier,
@Sidejob int,
@SellCost bigint
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	update dbo.tb_user_myhome_sidejob
	set SellCost = SellCost + @SellCost
	where ownerguid = @ownerguid and sidejob = @sidejob

END

