USE [DR2_local]
GO
/****** Object:  StoredProcedure [dbo].[up_Load_LimitedItem]    Script Date: 05/21/2009 14:54:56 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_Load_LimitedItem]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_Load_LimitedItem]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_Load_LimitedItem] 
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

SELECT [EventNo]
      ,[BagNo]
      ,[StartDate]
      ,[EndDate]
      ,[Limit_ResetPeriod]
      ,[Safe_ResetPeriod]
      ,[RefreshCount]
  FROM [dbo].[TB_LimitedItem]
  
END
