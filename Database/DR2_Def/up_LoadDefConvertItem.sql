USE [DR2_Def]
GO
/****** Object:  StoredProcedure [dbo].[up_LoadDefConvertItem]    Script Date: 05/19/2009 16:53:55 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[up_LoadDefConvertItem]') AND type in (N'P', N'PC'))
DROP PROCEDURE [dbo].[up_LoadDefConvertItem]
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
CREATE PROCEDURE [dbo].[up_LoadDefConvertItem]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	SELECT [SourceItemNo]
		  ,[SourceItemNum]
		  ,[TargetItemNo]
		  ,[TargetItemNum]
	  FROM [dbo].[TB_DefConvertItem]

END
