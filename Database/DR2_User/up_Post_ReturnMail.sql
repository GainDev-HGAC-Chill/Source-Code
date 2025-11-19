USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Post_ReturnMail]    Script Date: 12/21/2009 15:09:32 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_ReturnMail]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Post_ReturnMail]


SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO



-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Post_ReturnMail]

@mailguid UNIQUEIDENTIFIER,
@mailstate TINYINT,
@charguid UNIQUEIDENTIFIER

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DECLARE @errVal INT
	SET @errVal = 0
	DECLARE @readbit BIT,@annexbit BIT,@returnbit BIT,@paymentbit BIT,@deletebit BIT
	DECLARE @paymenttype TINYINT
	DECLARE @itemguid UNIQUEIDENTIFIER
	DECLARE @money BIGINT
	DECLARE @emptyguid UNIQUEIDENTIFIER
	SET @emptyguid = '00000000-0000-0000-0000-000000000000'
	DECLARE @fromguid UNIQUEIDENTIFIER
	DECLARE @toguid UNIQUEIDENTIFIER
	DECLARE @mailtitle NVARCHAR(50)
	DECLARE @limittime DATETIME
	DECLARE @returnmailstate TINYINT
	DECLARE @mailindex BIGINT

	SET @returnmailstate = 0
	-- @mailstate code
	-- 1 : 읽기
	-- 2 : 삭제
	-- 3 : 반송
	-- 이하 두 동작시에는 쿼리에서 독립적으로 사용 할 수 없다. 다른 쿼리 내부에서 동시에 동작해야함
	-- 4 : 아이템 수령
	-- 5 : 요금 납부

	SELECT	@itemguid = ISNULL(itemguid,@emptyguid),
			@money = [money],
			@paymenttype = paymenttype,
			@fromguid = fromguid,
			@toguid = toguid,
			@mailtitle = title,
			@limittime = limittime,
			@readbit = readbit,
			@annexbit = annexbit,
			@returnbit = returnbit,
			@paymentbit = paymentbit,
			@mailindex = mailindex
	FROM dbo.tb_usermail 
	WHERE mailguid = @mailguid

	IF @@rowcount <= 0
	BEGIN 
		SET @errVal = 9
		GOTO __error_proc
	END

	IF @charguid <> @toguid
	BEGIN
		SET @errVal = 4
		GOTO __error_proc
	END

	IF @mailstate = 4 OR @mailstate = 2
		SET @deletebit = 1
	ELSE
		SET @deletebit = 0

	SET @returnmailstate = (@readbit * 1) | (@deletebit * 2) | (@returnbit * 4) | (@annexbit * 8) | (@paymentbit * 16) | @mailstate

	-- 메일 반송 기능도 아이템이 있는 메일만 가능하다.
	IF (@annexbit = 1) OR (@itemguid = @emptyguid AND @money = 0)
	BEGIN
		SET @errVal = 3
		GOTO __error_proc
	END
	ELSE IF	@returnbit = 1	-- 이미 반송된 아이템은 반송 할 수 없다.
	BEGIN
		SET @errVal = 4
		GOTO __error_proc
	END

	declare @returnmailguid uniqueidentifier
	set @returnmailguid = newid()

	exec @errVal = [dbo].[up_Post_ConvertToReturnMail] @mailguid,@returnmailguid

	if @errVal <> 0
	begin
		GOTO __error_proc
	end

	SET nocount OFF
	SELECT @errVal,@mailindex,@returnmailstate,@limittime,@mailstate,@fromguid,@returnmailguid

	RETURN

__error_proc: -- 일반 에러 

SELECT @errVal
RETURN

END





