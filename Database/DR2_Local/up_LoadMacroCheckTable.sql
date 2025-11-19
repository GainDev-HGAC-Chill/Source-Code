USE [DR2_Local]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadMacroCheckTable]    Script Date: 03/23/2009 20:58:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadMacroCheckTable]'))
BEGIN
	DROP PROCEDURE [dbo].[up_LoadMacroCheckTable]
END
GO

-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[up_LoadMacroCheckTable]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

SELECT [MacroCheckTime]
      ,[MacroReleaseTime]
      ,[MacroCheckCount]
      ,[MacroPopupMax]
      ,[MacroInputTime]
  FROM [dbo].[TB_MacroCheckTable]
	  
END



