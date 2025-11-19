USE [DR2_User]
GO

IF EXISTS( SELECT * FROM sys.objects WHERE [object_id] = OBJECT_ID(N'[dbo].[up_Delete_2Week_Guild_Inventory_Log]') AND  [type] in ('P') )
BEGIN
	DROP PROCEDURE [dbo].[up_Delete_2Week_Guild_Inventory_Log]
END

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/*
////////////////////////////////////////////////////////////////////////
// Lasst Update by : 김동환
// Update date  : 2010-06-09
// Description : 2주가 지난 길드 금고 로그 데이터 삭제
// [PARAMETER] : 
// [RETURN] : 
// [REMARK]
////////////////////////////////////////////////////////////////////////
*/
CREATE PROCEDURE [dbo].[up_Delete_2Week_Guild_Inventory_Log]
AS
SET NOCOUNT ON;

DELETE dbo.TB_Guild_Inventory_Log WHERE [Date] < DATEADD(d,-14,GetDate())