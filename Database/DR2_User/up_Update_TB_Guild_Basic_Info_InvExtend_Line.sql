USE DR2_User
GO

set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_TB_Guild_Basic_Info_InvExtend_Line]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[up_Update_TB_Guild_Basic_Info_InvExtend_Line]
END
GO

CREATE PROCEDURE [dbo].[up_Update_TB_Guild_Basic_Info_InvExtend_Line] 
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : up_Update_TB_Guild_Basic_Info_InvExtend_Line
// 작 성 자 : 김동환
// 작 성 일 : 2010-06-14
// 최종수정자 :
// 수 정 일 : 
// 파 일 명 : 
// N O T E : 길드 인벤토리 확장 - 한줄(8칸) 확장
////////////////////////////////////////////////////////////////////////
*/
	@GuildGuid uniqueidentifier,	
	@Value BINARY(40)
AS
SET NOCOUNT ON
SET LOCK_TIMEOUT 5000
SET XACT_ABORT ON	
SET NOCOUNT ON
SET XACT_ABORT ON

UPDATE dbo.TB_Guild_Basic_Info Set [GuildInvExtendIdx] = @Value Where [GuildGuid] = @GuildGuid