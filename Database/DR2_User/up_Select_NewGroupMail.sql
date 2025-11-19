USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Select_NewGroupMail]    Script Date: 12/01/2009 12:11:15 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Select_NewGroupMail]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Select_NewGroupMail]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Select_NewGroupMail]
@CharGuid uniqueidentifier,
@Level int,
@Class bigint
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	declare @Table table(CmdGuid uniqueidentifier, title nvarchar(50), text nvarchar(200), itemno int, itemcount smallint, money bigint, fromname nvarchar(50) )

	declare @CurDate datetime
	set @CurDate = getdate()

	if @Level = 0 and @Class = 0
	begin
		insert into @Table
		select CmdGuid, title, text, itemno, count, money, fromname from dbo.TB_GroupMail
		where (LevelMin = @Level and LevelMax = @Level and
		Class = @Class and
		StartDate <= @CurDate and @CurDate <= EndDate) and
		CmdGuid not in (select GroupMailGuid from dbo.TB_GroupMailRecvedCharacter where CharGuid = @CharGuid)
	end
	else
	begin
		insert into @Table
		select CmdGuid, title, text, itemno, count, money, fromname from dbo.TB_GroupMail
		where not (Class=0 and LevelMin=0 and LevelMax=0) and
		((LevelMin=0 and LevelMax=0) or (LevelMin<=@Level and @Level<=LevelMax)) and
		((Class=0) or ((Class&@Class) > 0)) and
		(StartDate <= @CurDate and @CurDate <= EndDate) and
		CmdGuid not in (select GroupMailGuid from dbo.TB_GroupMailRecvedCharacter where CharGuid = @CharGuid)
	end

	insert into dbo.TB_GroupMailRecvedCharacter
	select @CharGuid,CmdGuid from @Table

	select title, text, itemno, itemcount, money, fromname from @Table
END




