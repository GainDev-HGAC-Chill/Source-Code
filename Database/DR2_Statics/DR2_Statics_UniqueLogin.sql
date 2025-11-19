USE DR2_Statics
go


CREATE TABLE dbo.tbl_UniqueLogin
(
	f_idx INT IDENTITY(1,1) NOT NULL,
	f_LoginID nvarchar(20) NULL,
	f_regdate SMALLDATETIME NOT NULL,	
	f_realmNo INT NOT NULL,
 CONSTRAINT [PK_tbl_UniqueLogin_f_idx] PRIMARY KEY NONCLUSTERED ([f_idx] ASC)	
)	
GO

CREATE CLUSTERED INDEX IX_C_tbl_UniqueLogin_f_regdate ON dbo.tbl_UniqueLogin(f_regdate)
go


ALTER PROC [dbo].[up_WEB_Statics_Basic_Create]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : dbo.up_WEB_Statics_Basic_Create
// 작 성 자 : Richard Kim(tigerjune@barunsoninter.com)
// 작 성 일 : 2008-07-02
// 최종수정자 :
// 수 정 일 : 
// 파 일 명 : 
// N O T E : 기본통계 산출, JOB으로 새벽에 돌린다.
//
////////////////////////////////////////////////////////////////////////
*/
(
		@realmNo int --Realm number를 Parameter
)
as
SET NOCOUNT ON
SET XACT_ABORT ON

DECLARE @MemDB nvarchar(50)
DECLARE @USERDB nvarchar(50)
DECLARE @LogDB nvarchar(50)
DECLARE @today nvarchar(10)
DECLARE @yesterday nvarchar(10)
DECLARE @f_type int
DECLARE @SQL nvarchar(2000)
DECLARE @Params nvarchar(2000)

SET @today = CONVERT(nvarchar(10), getdate(), 20)				--2008-06-19
SET @yesterday = CONVERT(nvarchar(10), getdate()-1, 20)				--2008-06-19
SET @MemDB = 'DR2_Member_'
SET @USERDB = 'DR2_User_'
SET @LogDB = 'DR2_Log_'

SET @USERDB = @USERDB+CAST(@realmNo AS varchar(7))+'_'
SET @LogDB = @LogDB+CAST(@realmNo AS varchar(7))

SET @MemDB = @MemDB+REPLACE(@today,'-','')		--DR2_Member_2_20080619
SET @USERDB = @USERDB+REPLACE(@today,'-','')		--DR2_User_2_20080619

BEGIN TRAN

		--1.로그인수 통계
		SET @f_type = 1001
		SET @SQL = N'INSERT dbo.tbl_StaticsBasic(f_type, f_date, f_realm, f_val1, f_val2) 
				SELECT @f_type, @yesterday, @realmNo, COUNT(*) AS f_val1, COUNT(distinct(A.MemberKey)) as f_val2 
				FROM  '+@LogDB+'.dbo.TB_'+REPLACE(@yesterday,'-','')+' A
				INNER JOIN '+@MemDB+'.dbo.Member B ON A.ID = B.ID WHERE B.GMLevel = 0 AND LogType = 1104'
		SET @Params = '@yesterday nvarchar(10), @f_type int, @realmNo int'
		EXEC sp_executesql @SQL, @Params, @yesterday, @f_type, @realmNo
		IF @@error <> 0 GOTO errorHandler

		--2.동접자 통계
		SET @f_type = 1002
		SET @SQL = N'INSERT dbo.tbl_StaticsBasic(f_type, f_date, f_hour, f_realm, f_val1) 
						SELECT @f_type, @yesterday, f_hour, @realmNo, iValue1
						FROM (
							SELECT f_hour, SUM(iValue1) AS iValue1 FROM 
							(
								SELECT DATEPART(hh, A.LogDate) as f_hour, MAX(B.iValue3) AS iValue1
								FROM '+@LogDB+'.dbo.TB_'+REPLACE(@yesterday,'-','')+' A
								INNER JOIN '+@LogDB+'.dbo.TB_'+REPLACE(@yesterday,'-','')+'_Sub B
								ON A.LogGUID=B.LogGuid
								WHERE A.LogType = 1003 
								GROUP BY A.ChannelNo, DATEPART(hh, A.LogDate) 
							) AS tmp
							GROUP BY f_hour
						) AS tmp2 '
		SET @Params = '@yesterday nvarchar(10), @f_type int, @realmNo int'
		EXEC sp_executesql @SQL, @Params, @yesterday, @f_type, @realmNo
		IF @@error <> 0 GOTO errorHandler

		--3.액티브유저 통계
		SET @f_type = 1003
		SET @SQL = N'INSERT dbo.tbl_StaticsBasic(f_type, f_date, f_realm, f_val1, f_val2) 
				SELECT @f_type, @yesterday, @realmNo, 
				(SELECT COUNT(*) FROM '+@MemDB+'.dbo.Member WHERE GMLevel = 0) as f_val1
				,count(distinct(A.MemberKey)) AS f_val2 
				from '+@MemDB+'.dbo.Member A 
				Inner Join '+@USERDB+'.dbo.TB_CharacterBasic B On A.MemberKey = B.MemberID
				WHERE A.GMLevel = 0 '
		SET @Params = '@yesterday nvarchar(10), @f_type int, @realmNo int'

		EXEC sp_executesql @SQL, @Params, @yesterday, @f_type, @realmNo
		IF @@error <> 0 GOTO errorHandler


	--4.Unique Login User
		SET @f_type = 1003
		SET @SQL = N'INSERT dbo.tbl_UniqueLogin(f_LoginID, f_regdate, f_realmNo) 
				SELECT distinct(id), @yesterday, @realmNo
				from '+@LogDB+'.dbo.TB_'+REPLACE(@yesterday,'-','')+' where logtype=1104'				
		SET @Params = '@yesterday nvarchar(10), @realmNo int'

		EXEC sp_executesql @SQL, @Params, @yesterday, @realmNo
		IF @@error <> 0 GOTO errorHandler


COMMIT TRAN
RETURN

errorHandler:
		ROLLBACK TRAN
		RETURN
GO

