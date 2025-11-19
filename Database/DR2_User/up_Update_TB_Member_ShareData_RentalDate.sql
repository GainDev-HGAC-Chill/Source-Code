USE [DR2_User]
GO
/****** Object:  StoredProcedure [dbo].[up_Update_TB_Member_ShareData_RentalDate]    Script Date: 09/23/2009 17:12:17 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Update_TB_Member_ShareData_RentalDate]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Update_TB_Member_ShareData_RentalDate]

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROC [dbo].[up_Update_TB_Member_ShareData_RentalDate] 
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
	@RentalInv nvarchar(50),
	@RentalTime datetime
AS
SET NOCOUNT ON
SET LOCK_TIMEOUT 5000
SET XACT_ABORT ON	

if not exists(select 1 from dbo.TB_Member_ShareData where MemberKey = @MemberKey)
begin
	insert into dbo.TB_Member_ShareData (memberkey,ExtendCharacterNum) values(@MemberKey,0)
end

DECLARE @SQL nvarchar(1000)
DECLARE @SQL_Params nvarchar(100)

SET @SQL = N'UPDATE dbo.TB_Member_ShareData Set ' + @RentalInv + ' = @RentalTime Where MemberKey = @MemberKey'
SET @SQL_Params = N'@RentalTime datetime, @MemberKey uniqueidentifier'                         

EXEC sp_executesql @SQL, @SQL_Params, @RentalTime, @MemberKey




