USE [DR2_Member]
GO
/****** Object:  StoredProcedure [dbo].[up_CS_AddMemberCash]    Script Date: 06/06/2009 22:20:39 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/****** Object:  StoredProcedure [dbo].[up_CS_CashTranCommit]    Script Date: 07/07/2009 17:27:27 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_CS_CashTranCommit]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_CS_CashTranCommit]
GO

/*	
//	TB_CashTran table 에서 CashTransaction 정보 지우기
///////////////////////////////////////////////////////////////////////////////////////
	2009-07-07 Eric Kim : 최초생성
///////////////////////////////////////////////////////////////////////////////////////
*/
CREATE PROCEDURE [dbo].[up_CS_CashTranCommit]
@TranGuid UNIQUEIDENTIFIER	-- TB_CashTran key value

AS
SET NOCOUNT ON
BEGIN

DELETE FROM [dbo].[TB_CashTran] WHERE [TranGuid] = @TranGuid

END