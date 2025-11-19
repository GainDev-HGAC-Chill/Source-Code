USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_User_MyHome_SideJob_Remove]    Script Date: 12/10/2009 11:32:37 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_SideJob_Remove]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_SideJob_Remove]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_User_MyHome_SideJob_Remove]
@OwnerGuid uniqueidentifier,
@Sidejob int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	delete from dbo.tb_user_myhome_sidejob where ownerguid = @ownerguid and sidejob = @sidejob
END
