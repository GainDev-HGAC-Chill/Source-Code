USE [DR2_GM]
GO
/****** Object:  StoredProcedure [dbo].[UP_GMProc]    Script Date: 04/14/2009 14:49:21 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[UP_GMProc]') AND type in (N'P', N'PC'))
BEGIN
	DROP PROCEDURE [dbo].[UP_GMProc]
END
GO


set ANSI_NULLS ON
set QUOTED_IDENTIFIER ON
go

CREATE PROCEDURE [dbo].[UP_GMProc]
/*
////////////////////////////////////////////////////////////////////////
//
// 프로시져명 : GM Tool 프로세스
// 작 성 자 : 김범준(tigerjune@barunsoninter.com)
// 작 성 일 : 2007-12-10
// 최종수정자 : 
// 수 정 일 : 
// 파 일 명 : 
// N O T E :  
//
////////////////////////////////////////////////////////////////////////
*/ 
(
	@f_adminID varchar(15),
	@f_adminName nvarchar(50),
	@CmdType int,
	@RealmNo	int,
	@ChannelNo int,
	@GUID1 uniqueidentifier,
	@GUID2 uniqueidentifier,
	@iValue1 int,
	@iValue2 int,
	@iValue3 int,
	@iValue4 int,
	@iValue5 int,
	@biValue1 bigint,
	@biValue2 bigint,
	@biValue3 bigint,
	@biValue4 bigint,
	@biValue5 bigint,
	@Message1 nvarchar(1000),
	@Message2 nvarchar(1000),
	@dtTime1 datetime = NULL,
	@dtTime2 datetime = NULL
)
AS
SET NOCOUNT ON
SET XACT_ABORT ON	
begin
DECLARE @Daily varchar(20)
DECLARE @SQL	 nvarchar(4000)
DECLARE @SQL_Params nvarchar(2000)
DECLARE @CmdState INT

SET @CmdState = 0

	INSERT INTO [dbo].[Tbl_Gm_Order]
			   ([CmdGUID]
			   ,[f_adminID]
			   ,[f_adminName]
			   ,[CmdState]
			   ,[CmdType]
			   ,[OrderDate]
				 ,[RealmNo]
			   ,[ChannelNo]
			   ,[GUID1]
			   ,[GUID2]
			   ,[iValue1]
			   ,[iValue2]
			   ,[iValue3]
			   ,[iValue4]
			   ,[iValue5]
			   ,[biValue1]
			   ,[biValue2]
			   ,[biValue3]
			   ,[biValue4]
			   ,[biValue5]
			   ,[message1]
			   ,[message2]
			   ,[dtTime1]
			   ,[dtTime2])
		 VALUES
			   (NEWID()
			   ,@f_adminID
			   ,@f_adminName
			   ,@CmdState
			   ,@CmdType
			   ,GETDATE()
				 ,@RealmNo
			   ,@ChannelNo
			   ,@GUID1
			   ,@GUID2
			   ,@iValue1
			   ,@iValue2
			   ,@iValue3
			   ,@iValue4
			   ,@iValue5
			   ,@biValue1
			   ,@biValue2
			   ,@biValue3
			   ,@biValue4
			   ,@biValue5
			   ,@Message1
			   ,@Message2
			   ,@dtTime1
			   ,@dtTime2)
end




