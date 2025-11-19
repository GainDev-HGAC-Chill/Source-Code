USE [DR2_User]
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_User_MyHome_VisitLog_Add]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_User_MyHome_VisitLog_Add]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[up_User_MyHome_VisitLog_Add]
@OwnerGuid UNIQUEIDENTIFIER,
@VisitorGuid UNIQUEIDENTIFIER,
@VisitorMemberGuid UNIQUEIDENTIFIER,
@VisitLog NVARCHAR(80),
@Private tinyint
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	DECLARE @logguid UNIQUEIDENTIFIER,
			@MAX_VISITLOG_COUNT INT,
			@CurLogCount INT

	if not exists(select 1 from dbo.TB_User_MyHome_Base where ownerguid = @ownerguid)
	begin
		select 1
		return
	end		

	SET @MAX_VISITLOG_COUNT = 300

	SELECT @CurLogCount = COUNT(*) FROM dbo.TB_User_MyHome_VisitLog WHERE OwnerGuid = @OwnerGuid

	IF @MAX_VISITLOG_COUNT <= @CurLogCount
	BEGIN
		
		SELECT TOP 1 @logguid = logguid FROM dbo.TB_User_MyHome_VisitLog 
		WHERE OwnerGuid = @OwnerGuid ORDER BY LOGTIME
		DELETE FROM dbo.TB_User_MyHome_VisitLog WHERE LogGuid = @logguid
		
	END
	
	INSERT INTO dbo.TB_User_MyHome_VisitLog (logguid,ownerguid,visitorguid,visitorlog,logtime,Private)
	VALUES(NEWID(),@OwnerGuid,@VisitorGuid,@VisitLog,GETDATE(),@Private)

	declare @OldLogTime datetime, @AddValue int
	set @OldLogTime = dateadd(day,-1,getdate())
	set @AddValue = 0

	-- 하루 이상 지난 방문자 목록은 모두 지운다.
	delete from dbo.TB_User_MyHome_WriteLog_Visitors where VisitTime <= @OldLogTime

	if not exists(select 1 from dbo.TB_User_MyHome_WriteLog_Visitors where HomeOwnerGuid = @OwnerGuid and VisitorGuid = @VisitorMemberGuid)
		and @OwnerGuid <> @VisitorGuid
	begin
		set @AddValue = 1
		insert into dbo.TB_User_MyHome_WriteLog_Visitors (HomeOwnerGuid,VisitorGuid,VisitTime)
		values (@OwnerGuid, @VisitorMemberGuid, getdate())
	end

	select StreetNo, HouseNo, HomeInSideGuid, @AddValue from dbo.TB_User_MyHome_Base where OwnerGuid = @OwnerGuid

END




