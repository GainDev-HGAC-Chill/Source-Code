USE DR2_USER
GO
/****** 개체:  StoredProcedure [dbo].[up_Post_DeleteMail]    스크립트 날짜: 07/17/2009 11:24:31 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_DeleteMail]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Post_DeleteMail]
GO
/****** 개체:  StoredProcedure [dbo].[up_Post_DeleteMail]    스크립트 날짜: 07/17/2009 11:24:31 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_DeleteMail]') AND type in (N'P', N'PC'))
BEGIN
EXEC dbo.sp_executesql @statement = N'-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Post_DeleteMail]

@mailguid uniqueidentifier,
@mailstate tinyint,
@charguid uniqueidentifier

AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	declare @errVal int
	set @errVal = 0
	declare @readbit bit,@annexbit bit,@returnbit bit,@paymentbit bit,@deletebit bit
	declare @paymenttype tinyint
	declare @itemguid uniqueidentifier
	declare @money bigint
	declare @emptyguid uniqueidentifier
	set @emptyguid = ''00000000-0000-0000-0000-000000000000''
	declare @fromguid uniqueidentifier
	declare @toguid uniqueidentifier
	declare @mailtitle nvarchar(50)
	declare @limittime datetime
	declare @returnmailstate tinyint
	declare @mailindex bigint

	set @returnmailstate = 0
	-- @mailstate code
	-- 1 : 읽기
	-- 2 : 삭제
	-- 3 : 반송
	-- 이하 두 동작시에는 쿼리에서 독립적으로 사용 할 수 없다. 다른 쿼리 내부에서 동시에 동작해야함
	-- 4 : 아이템 수령
	-- 5 : 요금 납부

	select	@itemguid = isnull(itemguid,@emptyguid),
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
	from dbo.tb_usermail 
	where mailguid = @mailguid

	if @@rowcount <= 0
	begin 
		set @errVal = 9
		goto __error_proc
	end

	if @charguid <> @toguid
	begin
		set @errVal = 4
		goto __error_proc
	end

	if @mailstate = 4 or @mailstate = 2
		set @deletebit = 1
	else
		set @deletebit = 0

	set @returnmailstate = (@readbit * 1) | (@deletebit * 2) | (@returnbit * 4) | (@annexbit * 8) | (@paymentbit * 16) | @mailstate

	-- 만약 아이템 정보가 있는 메일을 삭제 하려 하면 지금은 에러
	-- 차후 아이템도 지워도 되면 그때 삭제 하는 기능을 추가 하자
	-- 아직 수령 하지 않은 상태고 아이템/돈 정보가 있으면 지울 수 없음
	if (@AnnexBit = 0) and (@itemguid <> @emptyguid or @money <> 0)
	begin										

		set @errVal = 2
		goto __error_proc

	end
	
	-- 텍스트만 있는 메일이면 그냥 삭제 가능
	delete from dbo.tb_usermail where mailguid = @mailguid
	
	if @@error <> 0 
	begin
		set @errVal = 6
		goto __error_proc
	end

	set nocount off
	select @errVal,@mailindex,@returnmailstate,@limittime,@mailstate,@fromguid,@mailguid

	return

__error_proc: -- 일반 에러 

	select @errVal
	return

END'
END
GO