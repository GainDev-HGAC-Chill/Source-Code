USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_MonsterCard_Create]    Script Date: 09/28/2009 18:51:21 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_MonsterCard_Create]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_MonsterCard_Create]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_MonsterCard_Create]
@ItemGuid uniqueidentifier,
@LimitTime datetime
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	insert into dbo.TB_UserItem_MonsterCard 
	(ItemGuid,LimitTime)
	values(@ItemGuid,@LimitTime)

END
