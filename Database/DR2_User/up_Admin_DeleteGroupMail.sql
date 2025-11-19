USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Admin_DeleteGroupMail]    Script Date: 11/30/2009 19:22:03 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Admin_DeleteGroupMail]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Admin_DeleteGroupMail]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Admin_DeleteGroupMail]
@CmdGuid uniqueidentifier
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	delete from dbo.TB_GroupMail where CmdGuid = @CmdGuid
	delete from dbo.TB_GroupMailRecvedCharacter where GroupMailGuid = @CmdGuid
END
