USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_MonsterCard_Delete]    Script Date: 09/28/2009 18:52:11 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_MonsterCard_Delete]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_MonsterCard_Delete]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_MonsterCard_Delete]
@ItemGuid uniqueidentifier
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	delete from dbo.TB_UserItem_MonsterCard where ItemGuid = @ItemGuid
END
