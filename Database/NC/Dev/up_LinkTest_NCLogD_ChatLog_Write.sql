USE [DR2_Log]
GO

IF EXISTS( SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'dbo.up_LinkTest_NCLogD_ChatLog_Write') AND [type] IN (N'P'))
BEGIN
	DROP PROCEDURE dbo.up_LinkTest_NCLogD_ChatLog_Write
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROC [dbo].[up_LinkTest_NCLogD_ChatLog_Write]
	@Act_Time DATETIME,
	@Log_ID INT,
	@iData1 INT = NULL,
	@iData2 INT = NULL,
	@iData3 INT = NULL,
	@iData4 INT = NULL,
	@iData5 INT = NULL,
	@iData6 INT = NULL,
	@iData7 INT = NULL,
	@iData8 INT = NULL,
	@iData9 INT = NULL,
	@sData1 NVARCHAR(200) = NULL,
	@sData2 NVARCHAR(200) = NULL,
	@sData3 NVARCHAR(200) = NULL,
	@sData4 NVARCHAR(200) = NULL,
	@sData5 NVARCHAR(200) = NULL,
	@bData1 BIGINT = NULL,
	@bData2 BIGINT = NULL,
	@bData3 BIGINT = NULL
AS
SET NOCOUNT ON
SET XACT_ABORT ON

DECLARE @Daily VARCHAR(20)
DECLARE @SQL	 NVARCHAR(4000)
DECLARE @SQL_Params NVARCHAR(2000)

SET @Daily = ( SELECT CONVERT(CHAR(8), GETDATE(), 112) )--오늘 날짜 테이블

SET @SQL = N' INSERT [dbo].[TB_NCLOGD_CHAT_' + @Daily + '] ('
SET @SQL = @SQL + N'[Act_Time],[Log_ID]'
SET @SQL = @SQL + N',[iData1],[iData2],[iData3],[iData4],[iData5],[iData6],[iData7],[iData8],[iData9]'
SET @SQL = @SQL + N',[sData1],[sData2],[sData3],[sData4],[sData5]'
SET @SQL = @SQL + N',[bData1],[bData2],[bData3]'
SET @SQL = @SQL + N' ) VALUES ('
SET @SQL = @SQL + N'@Act_Time,@Log_ID'
SET @SQL = @SQL + N',@iData1,@iData2,@iData3,@iData4,@iData5,@iData6,@iData7,@iData8,@iData9'
SET @SQL = @SQL + N',@sData1,@sData2,@sData3,@sData4,@sData5'
SET @SQL = @SQL + N',@bData1,@bData2,@bData3'
SET @SQL = @SQL + N') '

SET @SQL_Params = N'@Act_Time DATETIME,@Log_ID int'
SET @SQL_Params = @SQL_Params + N',@iData1 int,@iData2 int,@iData3 int,@iData4 int,@iData5 int,@iData6 int,@iData7 int,@iData8 int,@iData9 int'
SET @SQL_Params = @SQL_Params + N',@sData1 nvarchar(200),@sData2 nvarchar(200),@sData3 nvarchar(200),@sData4 nvarchar(200),@sData5 nvarchar(200)'
SET @SQL_Params = @SQL_Params + N',@bData1 bigint,@bData2 bigint,@bData3 bigint'

EXEC sp_executesql @SQL, @SQL_Params
	,@Act_Time, @Log_ID
	,@iData1 ,@iData2 ,@iData3 ,@iData4 ,@iData5 ,@iData6 ,@iData7 ,@iData8 ,@iData9
	,@sData1 ,@sData2 ,@sData3 ,@sData4 ,@sData5
	,@bData1 ,@bData2 ,@bData3

SELECT @@ERROR
