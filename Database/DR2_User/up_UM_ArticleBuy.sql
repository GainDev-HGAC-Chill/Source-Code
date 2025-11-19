USE DR2_USER
GO
/****** 개체:  StoredProcedure [dbo].[up_UM_ArticleBuy]    스크립트 날짜: 07/17/2009 11:24:33 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UM_ArticleBuy]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_UM_ArticleBuy]
GO

/****** 개체:  StoredProcedure [dbo].[up_UM_ArticleBuy]    스크립트 날짜: 07/17/2009 11:24:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UM_ArticleBuy]') AND type in (N'P', N'PC'))
BEGIN
EXEC dbo.sp_executesql @statement = N'/*
////////////////////////////////////////////////////////////////////////
// Lasst Update by : 
// Update date  : 
// Description : 
// [PARAMETER] : 
// [RETURN] : 
// [REMARK]
//	내부에 transaction이 없으니 외부에서 걸어 줄것
////////////////////////////////////////////////////////////////////////
*/
CREATE PROCEDURE [dbo].[up_UM_ArticleBuy]
(
	@ItemGuid uniqueidentifier,
	@LeftItemNum smallint
)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	if @LeftItemNum = 0
	begin

		delete from dbo.TB_UserMarket where ItemGuId = @ItemGuid

	end
	select @@error

END'
END
GO