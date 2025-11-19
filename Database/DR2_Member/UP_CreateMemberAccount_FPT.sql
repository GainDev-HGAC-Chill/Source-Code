USE [DR2_Member]
GO

/****** Object:  StoredProcedure [dbo].[UP_CreateMemberAccount_FPT]    Script Date: 02/28/2012 19:39:54 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_CreateMemberAccount_FPT]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[UP_CreateMemberAccount_FPT]
GO

CREATE PROC [dbo].[UP_CreateMemberAccount_FPT]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [dbo].[UP_CreateMemberAccount_FPT]
// N O T E :  Create New Member (Called by Game Server)
//		2012-02-29 : 심헌섭, 베트남 전용 프로시져, 기존에 만들어져 있어야 할 FPT버전을 찾지 못해 up_CreateMemberAccount_Gravity에서 수정함
////////////////////////////////////////////////////////////////////////
*/  (
      @UID BIGINT,		-- Member unique id (only for NC_Korea)
      @ID NVARCHAR(50),	-- Member login id
      @PW NVARCHAR(64),	-- Member login password
      @Gender TINYINT,	-- Member Gender (0:unknown, 1:Male, 2:Female)
	  @GMLevel TINYINT	-- GMLevel
    )
AS

SET NOCOUNT ON
DECLARE @MemberKey UNIQUEIDENTIFIER
DECLARE @Err INT
DECLARE @Today datetime
SET @Today = GETDATE()

SET @Err = 0

SELECT @MemberKey = MemberKey FROM dbo.Member WHERE [ID] = @ID

IF(@@ROWCOUNT <> 0)
BEGIN
	UPDATE [dbo].[Member] SET [PW] = HashBytes('MD5', REVERSE(UPPER(@ID)) + @PW) WHERE [ID] = @ID
	SET @Err = 99
END
ELSE
BEGIN
	SET @MemberKey = NewID()
	INSERT INTO [dbo].[Member]
		([UID],[MemberKey],[ID],[PW],
			[Gender],[CreateDate],[GMLevel],[Block],[Cash],
			[TotalConnectTime],[AccDisconnectTime],[AccConnectTime],[LastLoginDate],[LastLogoutDate],
			[BirthDay])
			VALUES(
			@UID,@MemberKey,@ID,HashBytes('MD5', REVERSE(UPPER(@ID)) + @PW),
			@Gender,@Today,0,0,0,
			0,0,0,NULL,NULL,
			@Today)
	IF @@ERROR <> 0 
	BEGIN
		SET @Err = 1001
	END
END


SELECT  @Err, @MemberKey, @ID, @Gender, @Today, @UID
RETURN @Err

GO

