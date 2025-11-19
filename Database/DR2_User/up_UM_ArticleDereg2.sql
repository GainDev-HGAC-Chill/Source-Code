USE [DR2_USER]
GO
/****** 개체:  StoredProcedure [dbo].[up_UM_ArticleDereg2]    ?�크립트 ?�짜: 07/17/2009 11:24:33 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UM_ArticleDereg2]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_UM_ArticleDereg2]
GO

/****** ü:  StoredProcedure [dbo].[up_UM_ArticleDereg2]    ũƮ ¥: 07/17/2009 11:24:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_UM_ArticleDereg2]') AND type in (N'P', N'PC'))
BEGIN
EXEC dbo.sp_executesql @statement = N'

/*
////////////////////////////////////////////////////////////////////////
// Lasst Update by : 
// Update date  : 
// Description : 
// [PARAMETER] : 
// [RETURN] : 
// [REMARK]
////////////////////////////////////////////////////////////////////////
*/
CREATE PROCEDURE [dbo].[up_UM_ArticleDereg2]
    (
      @ItemGuId UNIQUEIDENTIFIER
    )
AS 
    BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
        SET NOCOUNT ON ;

        DECLARE @errVal INT

        SET @errVal = 0
	
        DELETE  FROM dbo.TB_UserMarket
        WHERE   ItemGuId = @ItemGuId

        SET @errVal = @@error

        SELECT  @errVal

    END'
END
GO