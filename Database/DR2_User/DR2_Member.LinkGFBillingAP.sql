/*
제작자 : YonMy
작업 내용 : 대만 GF Billing 연동을 위한 프로시져


작업 내용: 
1. TB_MemberSub Table에 (퍼블리셔용)확장 변수 추가 : 대만 GF 모바일 락 사용유무로 사용
2. up_SelectMemberID 생성 : MemberID 확인
3. up_CreateMemberAccount_GF 생성 : 대만 GF용 계정생성 프로시져
4. up_SelectMemberAuthData_ExtVar 생성 : 대만 GF용 로그인
5. up_CS_SelectMemberCash_ByID : ID로 캐쉬값 가지고오기
6. up_CS_AddMemberCash_ByID : ID로 캐쉬 증가
7. CashLog Type에 'APServer' 추가
8. up_ChangeMemberSub_ExtVar 생성 : 확장 변수 수정
9. up_ChangeMemberSub_ExtVar_ByID 생성 : 확장 변수 (ID로) 수정
10. up_CreateCoupon_GF 생성 : 대만 GF용 쿠폰 생성
*/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET NOCOUNT ON
GO
USE DR2_Member
GO

-- 퍼블리셔용 확장변수 추가
ALTER TABLE [dbo].[TB_MemberSub] ADD [ExtVar] [smallint] NULL
GO

CREATE Proc [dbo].[up_SelectMemberID]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [dbo].[up_SelectMemberID]
// 작 성 자 : YonMy
// 작 성 일 : 2009-03-06
// 최종수정자 : YonMy
// 수 정 일 : 
// 담 당 자 : 
// N O T E : 계정사용 여부 확인
////////////////////////////////////////////////////////////////////////
*/
(
	@ID	nvarchar(20)
)
AS
SET NOCOUNT ON
BEGIN
	DECLARE @Err int
	SET @Err = 0
	
	SELECT	@Err
	,	[ID]
	,	[PW]
	,	[BasePW]
	FROM	[dbo].[Member]
	WHERE	[ID] = @ID

	IF @@ROWCOUNT = 0
	BEGIN
		SET @Err = 1
		SELECT @Err
	END
	RETURN @Err
END

GO

CREATE PROC [dbo].[up_CreateMemberAccount_GF]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [dbo].[up_CreateMemberAccount_GF]
// 작 성 자 : 
// 작 성 일 : 
// 최종수정자 : YonMy
// 수 정 일 : 2009-03-06
// 파 일 명 : 
// N O T E :  GF(대만 SoftWorld용 계정 생성)
////////////////////////////////////////////////////////////////////////
*/  (
      @ID NVARCHAR(20),	-- Member login id
      @PW NVARCHAR(20),	-- Member login password
      @Gender TINYINT,		-- Member Gender (0:unknown, 1:Male, 2:Female)
      @Birthday NVARCHAR(40),
      @ExtVar SMALLINT	-- Use Mobile Lock
    )
AS

SET nocount ON
DECLARE @MemberKey UNIQUEIDENTIFIER
DECLARE @Err INT
DECLARE @UID INT

SET @MemberKey = NEWID()
SET @Err = 0
SET @UID = 0

BEGIN TRAN

IF EXISTS (SELECT 1 FROM dbo.Member WHERE [ID] = @ID) 
BEGIN 
	SET @MemberKey = '00000000-0000-0000-0000-000000000000'
	SET @Err = 99
END
ELSE 
BEGIN
	INSERT  INTO [dbo].[Member]
		(
			[UID]
		,	[MemberKey]
		,	[ID]
		,	[PW]
		,	[BasePW]
		,	[Gender]
		,	[CreateDate]
		,	[GMLevel]
		,	[Block]
		,	[Cash]
		,	[TotalConnectTime]
		,	[AccDisconnectTime]
		,	[AccConnectTime]
		,	[LastLoginDate]
		,	[LastLogoutDate]
		,	[BirthDay]
		)
        VALUES
        (
			@UID
		,	@MemberKey
		,	@ID
		,	NULL
		,	@PW
		,	@Gender
		,	GETDATE()
		,	0
		,	0
		,	0
		,	0
		,	0
		,	0
		,	NULL
		,	NULL
		,	@Birthday
		)
		
	IF @@ERROR <> 0 
	BEGIN
		SET @Err = 1001
	END
	ELSE
	BEGIN
		INSERT  INTO [dbo].[MemberSub]
			(
				[MemberKey]
			,	[ExtVar]
			)
			VALUES
			(
				@MemberKey
			,	@ExtVar
			)
		
		IF @@ERROR <> 0
		BEGIN
			SET @Err = 1001
		END	
	END
END

IF @Err = 0
BEGIN
	COMMIT TRAN
END
ELSE
BEGIN
	ROLLBACK TRAN
END

SELECT  @Err, @MemberKey, @ID, @Gender, @Birthday, @UID
RETURN @Err
GO


CREATE Proc [dbo].[up_SelectMemberAuthData_ExtVar]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [dbo].[up_SelectMemberAuthData_ExtVar]
// 작 성 자 : YonMy
// 작 성 일 : 2009-03-06
// 최종수정자 :
// 수 정 일 : 
// 담 당 자 : 
// N O T E : GF용 Auth

////////////////////////////////////////////////////////////////////////
*/
(
	@ID	nvarchar(20)
)
AS
SET NOCOUNT ON
BEGIN
	DECLARE @Err int
	SET @Err = 0
	
	SELECT		A.[MemberKey]
			,	A.[ID]
			,	A.[PW]
			,	A.[BasePW]
			,	A.[Gender]
			,	A.[BirthDay]
			,	A.[TotalConnectTime]
			,	A.[AccDisconnectTime]
			,	A.[AccConnectTime]
			,	A.[LastLoginDate]
			,	A.[LastLogoutDate]
			,	getdate()
			,	A.[GMLevel]
			,	A.[Block]
			,	A.[BlockStartTime]
			,	A.[BlockEndTime]
			,	A.[ConnectionChannel]
			,	B.[ExtVar]
	FROM	[dbo].[Member] A
		LEFT JOIN [dbo].[TB_MemberSub] B 
			ON A.MemberKey = B.MemberKey
	WHERE	A.ID = @ID
	
	EXEC [dbo].[up_Select_DefGMAccountIP] @ID
	return @Err
END
GO

CREATE PROCEDURE [dbo].[up_CS_SelectMemberCash_ByID]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [dbo].[p_CS_SelectMemberCash_ByID]
// 작 성 자 : YonMy
// 작 성 일 : 2009-03-06
// 최종수정자 : YonMy
// 수 정 일 : 
// 담 당 자 : 
// N O T E : ID로 Cash가지고 오기
////////////////////////////////////////////////////////////////////////
*/

@ID	nvarchar(20)

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	SELECT @ID, isnull(Cash,0) from dbo.Member where ID = @ID

END
GO

CREATE PROCEDURE  [dbo].[up_CS_AddMemberCash_ByID]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [dbo].[up_CS_SelectMemberCash_ByID]
// 작 성 자 : YonMy
// 작 성 일 : 2009-03-06
// 최종수정자 : YonMy
// 수 정 일 : 
// 담 당 자 : 
// N O T E : ID로 Cash Add
////////////////////////////////////////////////////////////////////////
*/
	@ID	NVARCHAR(20),
	@CharGuid UNIQUEIDENTIFIER,
	@Cash BIGINT,				-- Cash to add
	@Type TINYINT,
	@Status CHAR(1)
AS
SET NOCOUNT ON
BEGIN

DECLARE @ERROR INT
SET @ERROR = 0

BEGIN TRAN

	DECLARE @MemberGuId UNIQUEIDENTIFIER
	DECLARE @OLDCASH BIGINT
	
	SELECT @MemberGuId = [MemberKey], @OLDCASH = ISNULL([CASH],0) FROM DBO.MEMBER WHERE [ID] = @ID

	IF @OLDCASH + @Cash < 0
	BEGIN
		SET @ERROR = 1000		
		GOTO __ERROR
	END

	UPDATE dbo.Member SET [Cash] = [Cash] + @Cash WHERE MemberKey = @MemberGuId
	IF @@ERROR <> 0
	BEGIN 
		SET @ERROR = 1001
		GOTO __ERROR
	END


	INSERT INTO [dbo].[tbl_CashLog] (MemberKey,CharacterID,f_Type,f_Status,f_amount,f_current,f_date)
	VALUES(@MEMBERGUID,@CharGuid,@Type,@Status,@Cash,@OLDCASH + @Cash,GETDATE())
	IF @@ERROR <> 0
	BEGIN 
		SET @ERROR = 1001
		GOTO __ERROR
	END

COMMIT TRAN

SELECT @ERROR,@ID,@OLDCASH,isnull([CASH],0),@CASH FROM dbo.Member WHERE MemberKey = @MemberGuId
RETURN @ERROR

__ERROR:

ROLLBACK TRAN

SELECT @ERROR,@ID,@OLDCASH,isnull([CASH],0),@CASH FROM dbo.Member WHERE MemberKey = @MemberGuId

RETURN @ERROR

END
GO

-- CashLog Type에 APServer
INSERT INTO [dbo].[tbl_CashType]([f_name]) VALUES('AP Server')
GO

CREATE PROCEDURE [dbo].[up_ChangeMemberSub_ExtVar]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [dbo].[up_CreateMemberAccount_GF]
// 작 성 자 : 
// 작 성 일 : 
// 최종수정자 : YonMy
// 수 정 일 : 2009-03-06
// 파 일 명 : 
// N O T E :  GF(대만 SoftWorld용 핸드폰락 사용유무수정)
////////////////////////////////////////////////////////////////////////
*/  
(
      @MemberKey	UNIQUEIDENTIFIER,	-- MemberKey
      @ExtVar		SMALLINT
)
AS

SET nocount ON
DECLARE @Err INT
SET @Err = 0

BEGIN
	UPDATE	[dbo].[TB_MemberSub]
	SET		[ExtVar] = @ExtVar
	WHERE	[MemberKey] = @MemberKey
	
	IF @@ERROR <> 0
	BEGIN
		SET @Err = 99
	END
	
	SELECT @Err
	RETURN @Err
END
GO

CREATE PROCEDURE [dbo].[up_ChangeMemberSub_ExtVar_ByID]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [dbo].[up_ChangeMemberSub_ExtVar_ByID]
// 작 성 자 : 
// 작 성 일 : 
// 최종수정자 : YonMy
// 수 정 일 : 2009-03-06
// 파 일 명 : 
// N O T E :  GF(대만 SoftWorld용 핸드폰락 사용유무수정)
////////////////////////////////////////////////////////////////////////
*/  
(
      @ID		NVARCHAR(20),-- MemberID
      @ExtVar	SMALLINT
)
AS

SET nocount ON
DECLARE @Err INT

SET @Err = 0

BEGIN TRAN

	DECLARE @MemberKey UNIQUEIDENTIFIER
	SELECT @MemberKey = [MemberKey] FROM [dbo].[Member] WHERE [ID] = @ID
	
	IF @@ROWCOUNT = 0
	BEGIN 
		SET @Err = 99
		GOTO __ERROR
	END
	
	UPDATE	[dbo].[TB_MemberSub]
	SET		[ExtVar] = @ExtVar
	WHERE	[MemberKey] = @MemberKey
	
	IF @@ERROR <> 0
	BEGIN
		SET @Err = 99
		GOTO __ERROR
	END
	
COMMIT TRAN
SELECT @Err
RETURN @Err

__ERROR:

ROLLBACK TRAN
SELECT @Err
RETURN @Err
GO

CREATE PROC [dbo].[up_CreateCoupon_GF]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : [dbo].[up_CreateCoupon_GF]
// 작 성 자 : 
// 작 성 일 : 
// 최종수정자 : YonMy
// 수 정 일 : 2009-03-06
// 파 일 명 : 
// N O T E :  GF(대만 SoftWorld용 쿠폰 발금)
////////////////////////////////////////////////////////////////////////
*/  
(
	@ID			NVARCHAR(20),-- Member login id
	@CouponID	NVARCHAR(50),-- CouponID
	@EventKey	INT,
	@RewardKey	INT
)
AS

SET nocount ON

DECLARE @Err INT
SET @Err = 0

BEGIN TRAN

DECLARE @MemberKey UNIQUEIDENTIFIER
SELECT @MemberKey=[MemberKey] FROM [dbo].[Member] WHERE [ID] = @ID

IF @@ROWCOUNT <> 0
BEGIN
	-- EventKey가 있는지 확인
	IF EXISTS (SELECT 1 FROM [dbo].[TB_Event_Type] WHERE [f_EventKey] = @EventKey)
	BEGIN
		
		-- RewardKey가 있는지 확인
		IF EXISTS (SELECT 1 FROM [dbo].[TB_Event_Reward] WHERE [f_RewardKey] = @RewardKey)
		BEGIN
			
			-- 존재하는 Coupon인지 확인
			IF EXISTS (SELECT 1 FROM [dbo].[TB_Event_Coupon] WHERE [f_CouponID] = @CouponID)
			BEGIN
				SET @Err = 4 -- Error CouponID Already
			END
			ELSE
			BEGIN
				INSERT INTO [dbo].[TB_Event_Coupon]
				(
					[f_CouponID]
				,	[f_EventKey]
				,	[f_RewardKey]
				,	[f_OwnerMemberGuid]
				)
				VALUES
				(
					@CouponID
				,	@EventKey
				,	@RewardKey
				,	@MemberKey
				)
				
				COMMIT TRAN
				SELECT @Err, @CouponID
				RETURN @Err
			END
			
		END
		ELSE
		BEGIN
			SET @Err = 1028	-- RewardKey Error
		END
	END
	ELSE
	BEGIN
		SET @Err = 516 -- EventKey Error
	END	
END
ELSE
BEGIN
	SET @Err = 1 -- User ID Error
END

ROLLBACK TRAN
SELECT @Err, @CouponID
RETURN @Err
GO






