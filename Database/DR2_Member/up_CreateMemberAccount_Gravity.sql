USE [DR2_Member]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_CreateMemberAccount_Gravity]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_CreateMemberAccount_Gravity]
GO

/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [dbo].[up_CreateMemberAccount_Gravity]
// 작 성 자 : 
// 작 성 일 : 
// 최종수정자 : Acepm
// 수 정 일 : 2010-09-09
// 파 일 명 : 
// N O T E :
////////////////////////////////////////////////////////////////////////
*/ 
CREATE PROC [dbo].[up_CreateMemberAccount_Gravity]
(
	@UID		int,			-- Member unique id (only for NC_Korea)
	@ID			nvarchar(20),	-- Member login id
	@PW			nvarchar(20),	-- Member login password
	@Gender		tinyint,		-- Member Gender (0:unknown, 1:Male, 2:Female)
	@GMLevel	tinyint
)
AS
SET NOCOUNT ON
DECLARE @MemberKey	uniqueidentifier
DECLARE @UserID		nvarchar(20)
DECLARE @Err		int

SET @Err = 0

SELECT @MemberKey = MemberKey FROM dbo.Member WHERE [ID] = @ID

IF(@@rowcount <> 0)
BEGIN
	SET @Err = 99
END
ELSE
BEGIN
	SET @MemberKey = NewID()
	INSERT INTO [dbo].[Member]
			   ([UID], [MemberKey], [ID], [PW],
				[Gender], [CreateDate], [GMLevel] , [Block], [Cash], 
				[TotalConnectTime], [AccDisconnectTime], [AccConnectTime], [LastLoginDate], [LastLogoutDate])
		VALUES(
		@UID, @MemberKey, @ID, 
		HashBytes('MD5', REVERSE(UPPER(@ID)) + @PW)
		, @Gender, getdate(), @GMLevel, 0, 0
		, 0, 0, 0, NULL, NULL)

	if @@ERROR <> 0
	BEGIN
		SET @Err = 1001
	ENd
END

SELECT @Err, @MemberKey, @ID, @Gender, GETDATE(), @UID
RETURN @Err
