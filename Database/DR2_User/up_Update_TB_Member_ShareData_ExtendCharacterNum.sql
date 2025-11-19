USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Update_TB_Member_ShareData_ExtendCharacterNum]    Script Date: 09/23/2009 17:11:09 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_TB_Member_ShareData_ExtendCharacterNum]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_TB_Member_ShareData_ExtendCharacterNum]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROC [dbo].[up_Update_TB_Member_ShareData_ExtendCharacterNum] 
/*
////////////////////////////////////////////////////////////////////////
//
// 작 성 자 : 이훈
// 작 성 일 : 2008-10-30
// 최종수정자 :
// 수 정 일 : 
// 파 일 명 : 
// N O T E : 캐시 구매 계정 공유 창고 사용 기간 설정
//
////////////////////////////////////////////////////////////////////////
*/
@MemberKey uniqueidentifier,
@ExtendNum tinyint
AS
SET NOCOUNT ON;

if not exists(select 1 from dbo.TB_Member_ShareData where MemberKey = @MemberKey)
begin
	insert into dbo.TB_Member_ShareData (memberkey,ExtendCharacterNum) values(@MemberKey,0)
end

update dbo.TB_Member_ShareData set ExtendCharacterNum = ExtendCharacterNum + @ExtendNum
where MemberKey = @MemberKey
