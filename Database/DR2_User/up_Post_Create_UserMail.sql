USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Post_Create_UserMail]    Script Date: 08/07/2009 13:16:22 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Post_Create_UserMail]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Post_Create_UserMail]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[up_Post_Create_UserMail]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : 아이템 첨부 메일 발송
// 작 성 자 : 
// 작 성 일 : 2008-05-20
// 최종수정자 :
// 수 정 일 : 
// 파 일 명 : 
// N O T E : 
//	2008-10-08 : Eric Kim, CharacterDB 두개로 나누어진 것 적용
//	2009-02-04 : YonMy, 메일 수신할때 Character_Point의 RecvMailCount 증가하게 수정
////////////////////////////////////////////////////////////////////////
*/
(
	@MailGuid			UNIQUEIDENTIFIER,	--메일 guid
	@FromGuid			UNIQUEIDENTIFIER,	--메시지 발송자 메일 guid
	@ToName				NVARCHAR(20),		--메시지 수신자 캐릭터 이름
	@Title				NVARCHAR(40),		--메일 타이틀
	@Text				NVARCHAR(200),		--메일 본문

	@ItemGuid			UNIQUEIDENTIFIER,	--보내는 아이템 guid
	@Money				BIGINT,			--보내는 금액
	@PaymentType			TINYINT,		--금액 및 팩의 처리 보내는것인가?/받는것인가?
	@FromName			NVARCHAR(50)
)
AS
SET NOCOUNT ON
SET Xact_Abort ON

DECLARE @newguid UNIQUEIDENTIFIER
DECLARE @ToGuId UNIQUEIDENTIFIER
SELECT @toguid = CharacterID FROM dbo.TB_CharacterBasic WHERE [name] = @ToName AND [State] = 0

if @@rowcount = 0
begin
	select 6,NULL,NULL
end

EXEC dbo.up_Post_Create_UserMail_ByGuid @MailGuid,@FromGuid,@ToGuid,@Title,@Text,@ItemGuid,@Money,@PaymentType,@FromName


