USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Admin_CreateGroupMail]    Script Date: 11/30/2009 19:21:25 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Admin_CreateGroupMail]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Admin_CreateGroupMail]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Admin_CreateGroupMail]
@CmdGuid uniqueidentifier,
@Title nvarchar(50),
@Text nvarchar(200),
@Class bigint,
@LevelMin int,
@LevelMax int,
@ItemNo int,
@Count smallint,
@Money bigint,
@StartDate datetime,
@EndDate datetime,
@FromName nvarchar(50)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	insert into dbo.TB_GroupMail
	(CmdGuid, LevelMin, LevelMax, Class, Title, Text, ItemNo, Count, Money, StartDate, EndDate, FromName)
	values(@CmdGuid, @LevelMin, @LevelMax, @Class, @Title, @Text, @ItemNo, @Count, @Money, @StartDate, @EndDate, @FromName)

END
