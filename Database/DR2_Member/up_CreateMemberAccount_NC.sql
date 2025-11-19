USE [DR2_Member]
GO
/****** Object:  StoredProcedure [dbo].[up_CreateMemberAccount_NC]    Script Date: 03/08/2010 21:44:36 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER Proc [dbo].[up_CreateMemberAccount_NC]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [dbo].[up_CreateMemberAccountNC]
// 작 성 자 : 
// 작 성 일 : 
// 최종수정자 : Acepm
// 수 정 일 : 2010-03-08
// 파 일 명 : 
// N O T E :
//		2009-02-12 : YonMy, 컬럼명 변경 Grade -> GMLevel
//		2010-03-08 : Acepm, 컬럼삭제 BasePW, password encoding
////////////////////////////////////////////////////////////////////////
*/ 
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
